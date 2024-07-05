#include <unistd.h>
#include <stropts.h>

#include <uart.h>
#include <adc.h>
#include <flash.h>

#include "app.hpp"
#include "ble.hpp"

#include "shell.hpp"
#include "fstab.h"

#ifndef STACK_SIZE_UART_SHELL
    #define STACK_SIZE_UART_SHELL       (512)
#endif

#ifndef STACK_SIZE_BLE_SHELL
    #define STACK_SIZE_BLE_SHELL        (640)
#endif

/***************************************************************************/
/** @internal
****************************************************************************/
static int SHELL_bdname(struct UCSH_env *env) __attribute__((used));
static int SHELL_battery(struct UCSH_env *env);

static int BATT_compat_transform(int val);

/// @var
static int blevfd = 0;
// shell env
static struct UCSH_env BLE_sh_env;
static struct UCSH_env UART_sh_env;
// shell stacks
static uint32_t BLE_sh_stack[STACK_SIZE_BLE_SHELL / sizeof(uint32_t)];
static uint32_t UART_sh_stack[STACK_SIZE_UART_SHELL / sizeof(uint32_t)];

/***************************************************************************/
/** @initialization
****************************************************************************/
void SHELL_init(void)
{
    UCSH_init();

#if LOKI_SUPPORT_VERSION > 1
    UCSH_register("mode", SHELL_mode);
#endif
    UCSH_register("ssta",   SHELL_start_script);
    UCSH_register("osto",   SHELL_stop_output);
    UCSH_register("shdn",   SHELL_shutdown);
    UCSH_register("str",    SHELL_set_intensity);

    UCSH_register("md5",    SHELL_md5);
    UCSH_register("stat",   SHELL_status);
    UCSH_register("clrfs",  SHELL_clearfs);

    UCSH_register("sdef",   SHELL_default_file);
#if DEF_FILE_COUNT > 1
    UCSH_register("ndef",   SHELL_default_file2);
#endif

    UCSH_register("bat",    SHELL_battery);
    UCSH_register("ota",    SHELL_ota);

#ifndef NO_ADNAME_CHANGE
    UCSH_register("btnm",   SHELL_bdname);
#endif
#ifndef NO_SHELL_DUMP
    UCSH_register("dump",   SHELL_dump);
#endif

    if (true)
    {
        uint32_t timeout = 3000;
        ioctl(__stdout_fd, OPT_RD_TIMEO, &timeout);
        UCSH_init_instance(&UART_sh_env, __stdout_fd, sizeof(UART_sh_stack), UART_sh_stack);
    }

    if (true)
    {
        blevfd = BLE->Shell.CreateVFd();
        UCSH_init_instance(&BLE_sh_env, blevfd, sizeof(BLE_sh_stack), BLE_sh_stack);
    }
}

void __trace(char const *fmt, ...)
{
    static char buffer[256];

    va_list vl;
    va_start(vl, fmt);
    int len = TRACE_vsprintf(buffer, fmt, vl);
    va_end(vl);

    write(__stdout_fd, buffer, len);
}

/***************************************************************************/
/** @notifications
****************************************************************************/
void Notification(notification_t noti, ...)
{
    static char const *messages[] =
    {
        "NOTIFY strength 0x%06x\r\n",
        "NOTIFY strength %u\r\n",
        "NOTIFY battery %u\r\n",
        "NOTIFY low battery\r\n",
        "NOTIFY charging\r\n",
        "NOTIFY noload\r\n",
        "NOTIFY shutdown\r\n",
        "NOTIFY error stop\r\n",
    };

    char const *msg = messages[noti];
    int len;
    char buf[32];

    if (noti <= NOTIFY_BATTERY)
    {
        uint32_t v;
        va_list vl;
        va_start(vl, noti);

        v = va_arg(vl, uint32_t);

        if (NOTIFY_BATTERY == noti)
            v = BATT_compat_transform(v);

        len = sprintf(buf, msg, v);
        va_end(vl);

        msg = buf;
    }
    else
        len = strlen(msg);

    puts(msg);

    if (blevfd)
        write(blevfd, msg, len);
}

/***************************************************************************/
/** SHELL @misc
****************************************************************************/
int SHELL_status(struct UCSH_env *env)
{
    uint32_t len = sprintf(env->buf, "tick=%u,lmd5=", (unsigned)App->RunningSeconds());
    len += MD5_printf(&env->buf[len], App->LastFileMd5());

    int str = App->Intensity();
    if (60 < str)
        len += sprintf(&env->buf[len], ",str=0x%08x\r\n",str);
    else
        len += sprintf(&env->buf[len], ",str=%d\r\n",str);

    write(env->fd, env->buf, len);
    return ECHO_OFF;
}

static int SHELL_battery(struct UCSH_env *env)
{
    int v = App->Battery();

    if (1 == env->argc)
        v = BATT_compat_transform(v);

    UCSH_printf(env, "%d mv\r\n", v);
    return ECHO_OFF;
}

static int SHELL_bdname(struct UCSH_env *env)
{
    char *AdName;
    if (2 == env->argc)
    {
        AdName = env->argv[1];

        NVM_set(NVM_AD_NAME_ID, AdName, NVM_AD_NAME_SIZE);
    }
    else
    {
        AdName = &env->buf[64];

        if (0 != NVM_get(NVM_AD_NAME_ID, AdName, NVM_AD_NAME_SIZE))
            strncpy(AdName, PROJECT_NAME, NVM_AD_NAME_SIZE);
    }

    UCSH_printf(env,  "btnm=%s\r\n", AdName);
    return ECHO_OFF;
}

/***************************************************************************/
/** UCSH @override
****************************************************************************/
void UCSH_startup_handle(struct UCSH_env *env)
{
    if (env->fd == __stdout_fd)
    {
        UCSH_printf(env,  "%s Shell v.%d.%d.%d\r\n", PROJECT_NAME,
            __MAJOR(PROJECT_VERSION), __MINOR(PROJECT_VERSION), __RELEASE(PROJECT_VERSION));

        if (BDAddr)
            printf("id=%04X%02X%06X\r\n", BDAddr->NAP, BDAddr->UAP, BDAddr->LAP);

        // show bat=val
        printf("bat=%d\r\n", App->Battery());
    }
}

int UCSH_help(struct UCSH_env *env)
{
    ARG_UNUSED(env);
    return ECHO_OFF;
}

uint8_t UCSH_leading_count(void)
{
    return 1;
}

bool UCSH_leading_filter(char *buf, size_t count)
{
    ARG_UNUSED(count);
    return buf[0] == '>';
}

void UCSH_prompt_handle(struct UCSH_env *env)
{
    ARG_UNUSED(env);
    App->UpdateLastActivity();
}

void UCSH_error_handle(struct UCSH_env *env, int err)
{
    char const *msg;

    switch(err)
    {
    case 0:
        msg = "ok";
        break;

    case END_OF_LS:
        msg = "end of ls";
        break;

    case END_OF_DUMP:
        msg = "end of dump";
        break;

    case END_OF_CAT:
        msg = "end of cat";
        break;

    case EOTA_CRC:
        msg = "invalid crc";
        break;
    case EOTA_PAYLOAD:
        msg = "invalid packet";
        break;

    case ECHO_OFF:
        msg = NULL;
        break;

    case ECMD:
        msg = "command not understood";
        break;
    default:
        msg = "failure";
        break;
    }
    if (msg)
        UCSH_printf(env, "%d: %s\r\n", err, msg);
}

int UCSH_version(struct UCSH_env *env)
{
    UCSH_printf(env, "v.%d.%d.%d\r\n",
        __MAJOR(PROJECT_VERSION), __MINOR(PROJECT_VERSION), __RELEASE(PROJECT_VERSION));
    return ECHO_OFF;
}

int UCSH_datetime(struct UCSH_env *env)
{
    ARG_UNUSED(env);
    return ENOSYS;
}

int UCSH_nvm(struct UCSH_env *env)
{
    ARG_UNUSED(env);
    return ENOSYS;
}

int UCSH_pwd(struct UCSH_env *env)
{
    ARG_UNUSED(env);
    return ENOSYS;
}

int UCSH_chdir(struct UCSH_env *env)
{
    ARG_UNUSED(env);
    return ENOSYS;
}

int UCSH_mkdir(struct UCSH_env *env)
{
    ARG_UNUSED(env);
    return ENOSYS;
}

int UCSH_rmdir(struct UCSH_env *env)
{
    ARG_UNUSED(env);
    return ENOSYS;
}

/***************************************************************************/
/** @internal
****************************************************************************/
static int BATT_compat_transform(int val)
{
#ifdef BATTERY_COMPAT_BLUETENS_V1
    #define BATTERY_FULL_VOLTAGE        (4150)
    #define BATTERY_LOW_VOLTAGE         (3500)
    return ((int)val - BATTERY_LOW_VOLTAGE) * 1200 / (BATTERY_FULL_VOLTAGE - BATTERY_LOW_VOLTAGE) + 3800;
#else
    return val;
#endif
}
