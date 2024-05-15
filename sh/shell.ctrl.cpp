#include <cctype>

#include "app.hpp"
#include "shell.hpp"
#include "loki.hpp"

int SHELL_mode(struct UCSH_env *env)
{
    if (env->argc > 1)
    {
        uint32_t val = (uint32_t)atoi(env->argv[1]);
        if (val > Loki::MODE_MAX_VALUE)
            return EINVAL;

        MODE = (Loki::mode_t)val;
    }

    UCSH_printf(env, "mode %d\r\n", MODE);
    return ECHO_OFF;
}

int SHELL_start_script(struct UCSH_env *env)
{
    if (env->argc < 2)
        return EINVAL;

    uint32_t cutoff;
    char *param = CMD_paramvalue_byname("cut", env->argc, env->argv);

    if (param)
    {
        char *p;

        cutoff = strtoul(param, &p, 10);
        // hex
        if (0 == cutoff && 'x' == std::tolower(*p))
            cutoff = strtoul(param, &p, 16);
    }
    else
        cutoff = 0;

    return App->StartFile(env->argv[1], cutoff);
}

int SHELL_stop_output(struct UCSH_env *env)
{
    ARG_UNUSED(env);
    App->Stop();
    return 0;
}

int SHELL_shutdown(struct UCSH_env *env)
{
    ARG_UNUSED(env);
    App->Shutdown();
    return 0;
}

int SHELL_set_intensity(struct UCSH_env *env)
{
    uint32_t str;

    if (2 == env->argc)
    {
        char *p;

        str = strtoul(env->argv[1], &p, 10);
        // hex prop
        if (0 == str && 'x' == std::tolower(*p))
            str = strtoul(env->argv[1], &p, 16);

        App->SetIntensity(str, false);
        msleep(10);
    }
    str = App->Intensity();

    if (str > 60)
        UCSH_printf(env, "str=0x%06x\r\n", (unsigned)str);
    else
        UCSH_printf(env, "str=%u\r\n", (unsigned)str);

    return ECHO_OFF;
}
