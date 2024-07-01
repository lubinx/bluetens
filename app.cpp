#include <ultracore/timeo.h>
#include <cstdlib>

#include <timer.h>
#include <adc.h>

#include "fstab.h"
#include "app.hpp"
#include "sh/shell.hpp"

#ifdef NDEBUG
    #if defined(DEBUG_LOKI_PARSER) || defined(NO_SHUTDOWN) || defined(NO_DET_HV_OUTPUT) || \
        defined(NO_DET_CHARGING) || defined(NO_DET_BATTERY)
        #pragma GCC error "remove debug definitions in common_config.h"
    #endif
#endif

/**************************************************************************
 *  @const
 *************************************************************************/
#ifndef PRELOAD_BLOCK_COUNT
    #define PRELOAD_BLOCK_COUNT         (8)
#endif

    #define INTENSITY_STEP_TIMEOUT      (150)
    #define BATTERY_DET_TIMEOUT         (15 * 1000)
    #define BATTERY_NOTI_TIMEOUT        (5 * 60 * 1000)

    /// @DUTY section
    #define DUTY_SECTION_ID             (0x10)
    #define DUTY_EMS_ID                 (0x11)
    #define DUTY_EMS_ASY_ID             (0x12)
    #define DUTY_TENS_ID                (0x13)
    #define DUTY_END_ID                 (0x1F)

    /// @INTERVAL section
    #define INTV_SECTION_ID             (0x20)
    #define INTV_END_ID                 (0x2F)

#ifndef  STACK_SIZE_APP
    #define STACK_SIZE_APP              (640)
#endif

#ifndef BATTERY_ADC_CALIB
    #pragma GCC warning "no BATTERY_ADC_CALIB defined, default to 0"
    #define BATTERY_ADC_CALIB           (0)
#endif

/***************************************************************************/
/** @extern
****************************************************************************/
enum Loki::mode_t MODE;
Bluetooth::BD_addr_t const *BDAddr;

TApplication *App;
TTensPeripheral *BLE;

static uint32_t __stack[STACK_SIZE_APP / sizeof(uint32_t)];

/**************************************************************************
 *  @internal
 *************************************************************************/
static char const *ManufactoryingFile = "test_50hz.lok";

struct TENS_context
{
    timeout_t PRELOAD_timeo;
    uint32_t IDLE_shutdown_timeout;

    clock_t TUV_POWER_ticking;
    uint32_t TUV_POWER_discharge_count;

    clock_t LOAD_ticking;
    uint32_t LOAD_det_timeout;
    uint16_t LOAD_discharge_count;
    uint16_t LOAD_feedback_count;
};
static struct TENS_context TENS_context;

#ifndef NO_DET_BATTERY
    struct BATT_context
    {
        timeout_t intv;
        ADC_attr_t attr;
    };
    static struct BATT_context BATT_context;
#endif

/**************************************************************************
 *  @export
 *************************************************************************/
MD5_t file_md5(int fd)
{
    struct file_md5_context
    {
        MD5_context_t md5;
        uint8_t buf[64];
    };
    struct file_md5_context *ctx = (struct file_md5_context *)std::malloc(sizeof(struct file_md5_context));

    off_t pos = lseek(fd, 0, SEEK_CUR);
    lseek(fd, 0, SEEK_SET);

    MD5_init(&ctx->md5);
    while (true)
    {
        int len = read(fd, ctx->buf, sizeof(ctx->buf));

        if (len > 0)
            MD5_update(&ctx->md5, ctx->buf, len);
        else
            break;
    }

    MD5_t retval = MD5_final(&ctx->md5);
    std::free(ctx);
    lseek(fd, pos, SEEK_SET);

    return retval;
}

/**************************************************************************
 *  @weak link
 *************************************************************************/
__attribute__((weak))
void USB_plugin(void)
{
    // nothing to do
}

__attribute__((weak))
void PLATFORM_idle(void)
{
    // nothing to do
}

__attribute__((weak))
void PLATFORM_msg_activity(uint32_t MsgId)
{
    ARG_UNUSED(MsgId);
    // nothing to do
}

__attribute__((weak))
void PLATFORM_start_defile(void)
{
    // nothing to do
}

__attribute__((weak))
uint32_t INTENSITY_adjust(uint32_t value, int adjust)
{
    /// for all @single channel
    value += adjust;

    if (value <= 0)
        value = 1;

    return value;
}

/**************************************************************************
 *  @TApplication
 *************************************************************************/
TApplication::TApplication() :
    FManufactoringMode(false),
    FState(stateStopped), FShuttingdown(false),
    FLastActivity(0),
    FRunningTickStart(0), FIntensity(0),
    FCurrFile(NULL),
    FDefFiles(), FLastFileMd5(MD5_NULL),
    FBatt(0)
{
    /// @hardware initialize
    PLATFORM_init();

    /// gpio @debounce
    #ifdef PIN_ADD_BUTTON
        GPIO_debounce(PIN_POWER_BUTTON | PIN_ADD_BUTTON | PIN_SUB_BUTTON, GPIO_DEBOUNCE_INTV);
        GPIO_hold_repeating(PIN_ADD_BUTTON | PIN_SUB_BUTTON, GPIO_HOLD_REPEAT_INTV);
    #else
        GPIO_debounce(PIN_POWER_BUTTON, GPIO_DEBOUNCE_INTV);
    #endif

    timeout_init(&TENS_context.PRELOAD_timeo, 0, PRELOAD_timeo_callback, 0);
    TENS_context.IDLE_shutdown_timeout = SHUTDOWN_IDLE_SECONDS * 1000;
    TENS_context.LOAD_det_timeout = LOAD_DET_TIMEOUT;

    /// @BLE
    BLE = new TTensPeripheral();
    BLE->PowerAcquire();

    /// @application defered startup
    FMsgQueue.PostMessage(MSG_STARTUP, 0);
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstack(&attr, __stack, sizeof(__stack));

        pthread_create(&FThreadId, &attr, MessageLoopThreadEntry, this);
        pthread_attr_destroy(&attr);
    }
}

void TApplication::MessageLoop(void)
{
    while (true)
    {
        uint32_t MsgId;
        uint32_t Msg;

        if (FMsgQueue.GetMessage(MsgId, Msg))
        {
            UpdateLastActivity(MsgId);

            switch (MsgId)
            {
            case MSG_STARTUP:
                MSG_Startup(Msg);
                break;
            case MSG_SHUTDOWN:
                MSG_Shutdown(Msg);
                break;

            case MSG_STARTING:
                MSG_Starting(Msg);
                break;
            case MSG_STOPPING:
                MSG_Stopping(Msg);
                break;
            case MSG_PRELOAD_BLOCK:
                MSG_PreloadBlock(Msg);
                break;
            case MSG_START_DEFAULT_FILE:
                MSG_StartDefaultFile(Msg);
                break;

            case MSG_SET_INTENSITY:
                MSG_SetIntensity(Msg);
                break;

            case MSG_NOTIFY_INTENSITY:
                MSG_NotifyIntensity(Msg);
                break;
            case MSG_NOTIFY_BATTERY:
                MSG_NotifyBattery(Msg);
                break;
            };
        }
        else
        {
            PLATFORM_idle();
            Idle();
        }
    }
}

void TApplication::Run(void)
{
    // msleep(SLEEP_FOREVER);
    BLE->Run();
}

void TApplication::Shutdown(void)
{
    FMsgQueue.PostMessage(MSG_SHUTDOWN, 0);
}

void TApplication::GPIO_callback(uint32_t pins)
{
    if (FShuttingdown)
        while (1) NVIC_SystemReset();

#ifdef PIN_POWER_BUTTON
    if (PIN_POWER_BUTTON == (PIN_POWER_BUTTON & pins))
    {
        FShuttingdown = true;
        FMsgQueue.PostMessage(MSG_SHUTDOWN, 0);
    }
#endif

#ifdef PIN_CHARGING_DET
    if (PIN_CHARGING_DET == (PIN_CHARGING_DET & pins) && DET_is_charging())
    {
        if (! FManufactoringMode)
        {
            USB_plugin();

            FShuttingdown = true;
            FMsgQueue.PostMessage(MSG_STOPPING, stopCharging);
        }
    }
#endif

#if defined(PIN_ADD_BUTTON) || defined(PIN_SUB_BUTTON)
    {
        int adjust;

        if (PIN_ADD_BUTTON == (PIN_ADD_BUTTON & pins))
            adjust = 1;
        else if (PIN_SUB_BUTTON == (PIN_SUB_BUTTON & pins))
            adjust = -1;
        else
            adjust = 0;

        if (0 != adjust)
            SetIntensity(INTENSITY_adjust(FIntensity, adjust), true);
    }
#endif

#ifdef PIN_DIAL_EN
    if (PIN_DIAL_CW == (PIN_DIAL_CW & pins))
    {
        static clock_t ADJUEST_tick = 0;
        clock_t now = clock();

        if (50 < now - ADJUEST_tick)
        {
            ADJUEST_tick = now;
            int adjust;

            if (GPIO_peek(PIN_DIAL_CCW))
                adjust = -1;
            else
                adjust = 1;

            SetIntensity(INTENSITY_adjust(FIntensity, adjust), true);
        }
    }
#endif
}

int TApplication::StartDebug(void)
{
    if (PrepareStart())
    {
        FCurrBlock.InfRepeat();
        FCurrBlock.FrequencyT(540);
        FCurrBlock.Cluster(1);
        FCurrBlock.ImpulseUS(100);
        FCurrBlock.IntervalMS(0);

        FMsgQueue.PostMessage(MSG_STARTING, INTENSITY_adjust(0, 1));
    }
    return 0;
}

int TApplication::StartFile(char const *filename, uint32_t cutoff_seconds)
{
    if (PrepareStart())
    {
        FCurrFile = new TLokiParser();
        if (! FCurrFile)
        {
            Stop();
            return ENOMEM;
        }

        int fd = FCurrFile->Open(filename);
        if (-1 == fd)
        {
            delete FCurrFile;
            FCurrFile = NULL;

            Stop();
            return ENOENT_BLUETENS;
        }
        else
            FLastFileMd5 = file_md5(fd);

    #if LOKI_SUPPORT_VERSION > 1
        MODE =  FCurrFile->Mode();
    #endif
    #ifdef FORCE_MODE
        MODE = FORCE_MODE;
    #endif

        FCutoffSeconds = cutoff_seconds;
        FCurrBlock.Repeat(0);
        FMsgQueue.PostMessage(MSG_STARTING, INTENSITY_adjust(0, 1));

    #ifdef DEFILE_USING_LAST_RUNNING
        UpdateDefaultFile(0, filename);
    #endif
    }

    // failure on PrepareStart() also consider no error
    //  later a NOTIFY will be sent
    return 0;
}

void TApplication::StartDefaultFile(uint8_t idx)
{
    FMsgQueue.PostMessage(MSG_START_DEFAULT_FILE, idx);
}

void TApplication::SetIntensity(uint32_t value, bool Notification)
{
    if (FIntensity != value && 0 < value)
    {
        if (stateRunning == FState)
        {
            FMsgQueue.PostMessage(MSG_SET_INTENSITY, value);

            if (Notification)
                FMsgQueue.PostMessage(MSG_NOTIFY_INTENSITY, value);
        }
        else
        {
            if (FManufactoringMode || stateStopped == FState)
                FMsgQueue.PostMessage(MSG_START_DEFAULT_FILE, 0);
        }
    }
}

void TApplication::Stop()
{
    if (FState != stateStopped)
        FMsgQueue.PostMessage(MSG_STOPPING, stopAbort);

    if (pthread_self() != FThreadId)
    {
        clock_t TickStart = clock();
        while (FState != stateStopped)
        {
            if (clock() - TickStart >= 3000)
                NVIC_SystemReset();
            else
                msleep(10);
        }
    }
}

int TApplication::UpdateDefaultFile(uint8_t idx, char const *filename)
{
    /*
    if (0 == strncmp("test", filename, 4))
        return 0;
    */

    if (idx < DEF_FILE_COUNT)
    {
        if (0 != strncmp(FDefFiles[idx], filename, NVM_DEF_FILE_SIZE))
        {
            strncpy(FDefFiles[idx], filename, NVM_DEF_FILE_SIZE);
            NVM_set(NVM_DEF_FILE_ID_BASE + idx, FDefFiles, NVM_DEF_FILE_SIZE);
        }
        return 0;
    }
    else
        return EINVAL;
}

void TApplication::UpdateLastActivity(uint32_t MsgId)
{
    PLATFORM_msg_activity(MsgId);
    FLastActivity = clock();
}

//--------------------------------------------------------------------------
/// TApplication @private
//--------------------------------------------------------------------------
bool TApplication::PrepareStart(void)
{
    bool retval;

    switch (FState)
    {
    /*
        GPIO callback without debounce may cause dupicate calling start,
        return false to avoid
    */
    case stateStarting:
        retval = false;
        break;

    case stateRunning:
        Stop();
        goto falling_through_dummy;
falling_through_dummy:
    case stateStopped:
        retval = true;
        break;

    case stateCharging:
        retval = FManufactoringMode;
        if (! retval)
            FMsgQueue.PostMessage(MSG_STOPPING, stopCharging);
        break;

    case stateLowBattery:
        retval = FManufactoringMode;
        if (! retval)
            FMsgQueue.PostMessage(MSG_STOPPING, stopLowBattery);
        break;

    default:
        FMsgQueue.PostMessage(MSG_STOPPING, stopError);
        retval = false;
        break;
    }

    if (retval)
        FState = stateStarting;
    return retval;
}

void TApplication::Idle(void)
{
#if ! defined(NO_SHUTDOWN) && (SHUTDOWN_IDLE_SECONDS > 0)
    if (! DET_is_charging() && TENS_context.IDLE_shutdown_timeout < clock() - FLastActivity)
        FMsgQueue.PostMessage(MSG_SHUTDOWN, 0);
#endif
}

//--------------------------------------------------------------------------
/// TApplication @message handler
//--------------------------------------------------------------------------
void TApplication::MSG_Startup(uint32_t const)
{
    /// @battery detect
    #ifndef NO_DET_BATTERY
        ADC_attr_init(&BATT_context.attr, 1000, BATT_adc_callback);
        ADC_attr_positive_input(&BATT_context.attr, PIN_BATT);

        #ifdef BATT_NUMERATOR
            ADC_attr_scale(&BATT_context.attr, BATT_NUMERATOR, BATT_DENOMINATOR);
        #endif
        ADC_start_convert(&BATT_context.attr, this);

        timeout_init(&BATT_context.intv, BATTERY_DET_TIMEOUT, BATT_intv_callback, TIMEOUT_FLAG_REPEAT);
        timeout_start(&BATT_context.intv, this);
    #endif

    if (PLATFORM_startup())
    {
        int fd = open(ManufactoryingFile, 0);
        if (-1 != fd)
        {
            close(fd);

            FManufactoringMode = true;
            memset(FDefFiles, 0, sizeof(FDefFiles));

            for (uint8_t i = 0; i < DEF_FILE_COUNT; i ++)
                NVM_set(NVM_DEF_FILE_ID_BASE + i, FDefFiles[i], NVM_DEF_FILE_SIZE);
        }
        else
        {
            FManufactoringMode = false;

            for (uint8_t i = 0; i < DEF_FILE_COUNT; i ++)
            {
                if (0 != NVM_get(NVM_DEF_FILE_ID_BASE + i, FDefFiles[i], NVM_DEF_FILE_SIZE))
                    FDefFiles[i][0] = '\0';
            }
        }

        if (DET_is_charging())
            FState = stateCharging;

        /// @battery detect
#ifndef NO_DET_BATTERY
        for (int i = 0; i < 100; i ++)
        {
            if (0 != FBatt)
                break;
            else
                msleep(10);
        }
#endif

        /// @device id
        while (! BLE->GAP_IsReady())
            msleep(10);
        BDAddr = BLE->BDAddr();

        // dutch device start with BDAddr 0x087CEE
        #ifdef DUTCH_SHUTDOWN_IDLE_SECONDS
            if (IS_DUTCH_DEVICE())
            {
                TENS_context.IDLE_shutdown_timeout = DUTCH_SHUTDOWN_IDLE_SECONDS * 1000;
                TENS_context.LOAD_det_timeout = DUTCH_LOAD_DET_TIMEOUT;
            }
        #endif

        BLE->ADV_Start();

        /// @SHELL init & startup
        SHELL_init();
    }
    else
        MSG_Shutdown(0);
}

void TApplication::MSG_Shutdown(uint32_t const)
{
    FShuttingdown = true;

#ifndef NO_DET_BATTERY
    ADC_stop_convert(&BATT_context.attr);
#endif

    if (stateRunning == FState || stateStarting == FState)
        MSG_Stopping(stopShutdown);

    PLATFORM_shutdown();
    BLE->Shutdown();
}

void TApplication::MSG_StartDefaultFile(uint32_t const idx)
{
    if (FManufactoringMode)
    {
        StartFile(ManufactoryingFile);
        FMsgQueue.PostMessage(MSG_SET_INTENSITY, INTENSITY_adjust(0, 1));
    }
    else
    {
        PLATFORM_start_defile();
        StartFile(FDefFiles[idx]);
    }
}

void TApplication::MSG_Starting(uint32_t const str)
{
#ifdef DEFILE_RUNNING_NO_AD
    if (! BLE->IsConnected())
        BLE->ADV_Stop();
#endif

    TIMER_match_configure(HW_TIMER0, FREQ_HW_TIMER0, TIMER_output_callback);
    OUTPUT_off();
    INTENSITY_ctrl_init();

    FRunningTickStart = clock();
    TENS_context.TUV_POWER_ticking = FRunningTickStart;
    TENS_context.TUV_POWER_discharge_count = 0;

    TENS_context.LOAD_ticking = TENS_context.LOAD_discharge_count = TENS_context.LOAD_feedback_count = 0;

    MSG_PreloadBlock(0);

    if (TIMER_match_cached_sections(HW_TIMER0) > 0)
    {
        TIMER_start(HW_TIMER0);
        FState = stateRunning;

        MSG_SetIntensity(str);
        FMsgQueue.PostMessage(MSG_NOTIFY_INTENSITY, str);
    }
    else
        FMsgQueue.PostMessage(MSG_STOPPING, stopAbort);
}

void TApplication::MSG_Stopping(uint32_t const reason)
{
    INTENSITY_ctrl_release(FIntensity);
    TIMER_deconfigure(HW_TIMER0);
    OUTPUT_release();

    if (FCurrFile)
        delete FCurrFile;

    FCurrFile = NULL;
    FIntensity = 0;
    FCutoffSeconds = 0;

    switch (reason)
    {
    case stopShutdown:
        Notification(NOTIFY_STOP_SHUTDOWN);
        FState = stateStopped;
        break;

    case stopAbort:
        if (stateStarting == FState || stateRunning == FState)
            FState = stateStopped;
        break;

    case stopNoLoad:
        Notification(NOTIFY_STOP_NOLOAD);
        FState = stateStopped;
        break;

    case stopCharging:
#ifdef NO_CHARGING_DET
        FState = stateStopped;
#else
        Notification(NOTIFY_STOP_CHARGING);
        FState = stateCharging;
        FMsgQueue.PostMessage(MSG_SHUTDOWN, 0);
#endif
        break;

    case stopLowBattery:
#ifdef NO_DET_BATTERY
        FState = stateStopped;
#else
        Notification(NOTIFY_STOP_BATTERY);
        PLATFORM_lowbattery();
        FMsgQueue.PostMessage(MSG_SHUTDOWN, 0);
#endif
        break;

    default:
    // case stopError:
        Notification(NOTIFY_STOP_ERROR);
        break;
    };

#ifdef DEFILE_RUNNING_NO_AD
    if (! FShuttingdown && ! BLE->IsConnected())
            BLE->ADV_Start();
#endif
}

void TApplication::MSG_PreloadBlock(uint32_t const)
{
    /// @stop somewhere else
    if (stateStarting != FState && stateRunning != FState)
        return;

    if (FCurrFile || FCurrBlock.IsInfRepeat())
    {
        int preload = PRELOAD_BLOCK_COUNT - 1 - TIMER_match_cached_sections(HW_TIMER0);
        TLokiBlock *block;

        while (preload > 0)
        {
            if (! FCurrBlock.LoopNext())
            {
                block = FCurrFile->NextBlock();
                if (! block ||
                    (FCutoffSeconds > 0 && (clock() - FRunningTickStart) / 1000 > FCutoffSeconds))
                {
                    // TRACE("read done, %d msec", FCurrFile->TimeEstimateMS());
                    // TRACE("waiting cached blocks to finish...");

                    delete FCurrFile;
                    FCurrFile = NULL;
                    break;
                }
                else
                    FCurrBlock = block;
            }

            block = &FCurrBlock;

#ifndef DEBUG_LOKI_PARSER
            if (block->Cluster() > 0)
            {
#if LOKI_SUPPORT_VERSION > 1
                uint16_t duty_id;
                uint32_t repeat;
                uint32_t end;
                uint32_t duty = block->ImpulseUS() - TUV_ERRATA_US;

                if (Loki::MODE_EMS == MODE)
                {
                    duty_id = DUTY_EMS_ID;

                    repeat = 2 * block->Cluster();
                    end = 1000000 * 10 / block->FrequencyT() / 2;
                }
                else
                {
                    if (Loki::MODE_TENS == MODE)
                        duty_id = DUTY_TENS_ID;
                    else
                        duty_id = DUTY_EMS_ASY_ID;

                    repeat = block->Cluster();
                    end = 1000000 * 10 / block->FrequencyT();
                }

                TIMER_match_section(HW_TIMER0, DUTY_SECTION_ID, repeat);
                preload --;

                TIMER_match(HW_TIMER0, DUTY_END_ID, end, NULL);
                TIMER_match(HW_TIMER0, duty_id, end - duty - CAPACITOR_DISCHARGE_US, (void *)duty);
#else
                TIMER_match_section(HW_TIMER0, DUTY_SECTION_ID, 2 * block->Cluster());
                preload --;

                uint32_t end = 1000000 * 10 / block->FrequencyT() / 2 - 2;
                uint32_t duty = block->ImpulseUS() - TUV_ERRATA_US;

                TIMER_match(HW_TIMER0, DUTY_END_ID, end, NULL);
                TIMER_match(HW_TIMER0, DUTY_EMS_ID, end - duty - CAPACITOR_DISCHARGE_US, (void *)duty);
#endif
            }

            if (block->IntervalMS() > 0)
            {
                TIMER_match_section(HW_TIMER0, INTV_SECTION_ID, 1);
                preload --;
                TIMER_match(HW_TIMER0, INTV_END_ID, block->IntervalMS() * 1000, NULL);
            }
#endif
        }
    }

    clock_t now = clock();

    /**
     *  TUV testing square root to 10v
     */
    if (now - TENS_context.TUV_POWER_ticking > 200)
    {
        INTENSITY_TUV_power_control(TENS_context.TUV_POWER_discharge_count > (400 / (1000 / 200)), FIntensity);

        TENS_context.TUV_POWER_ticking = now;
        TENS_context.TUV_POWER_discharge_count = 0;
    }

#ifndef NO_DET_HV_OUTPUT
    if (2 < TENS_context.LOAD_discharge_count)
    {
        if (0 == TENS_context.LOAD_ticking)
            TENS_context.LOAD_ticking = now;

        if (TENS_context.LOAD_det_timeout < now - TENS_context.LOAD_ticking)
        {
            if (0 == TENS_context.LOAD_feedback_count)
                FMsgQueue.PostMessage(MSG_STOPPING, stopNoLoad);

            TENS_context.LOAD_ticking = now;
            TENS_context.LOAD_discharge_count = TENS_context.LOAD_feedback_count = 0;
        }
    }
#endif

    if (! FCurrFile && ! FCurrBlock.IsInfRepeat() && ! TIMER_is_running(HW_TIMER0))
    {
        // TRACE("all done");
        FMsgQueue.PostMessage(MSG_STOPPING, stopAbort);
    }
    else
    {
        // scheduing MSG_PreloadBlock() yield to main thread idle
        timeout_start(&TENS_context.PRELOAD_timeo, this);
    }
}

void TApplication::MSG_SetIntensity(uint32_t const value)
{
    int retval = INTENSITY_ctrl(value);

    if (retval > 0)
        FIntensity = retval;
}

void TApplication::MSG_NotifyIntensity(uint32_t const)
{
    if (FIntensity > 0)
    {
        if (FIntensity > 60)
            Notification(NOTIFY_INTENSITY_BASE16, FIntensity);
        else
            Notification(NOTIFY_INTENSITY_BASE10, FIntensity);
    }
}

void TApplication::MSG_NotifyBattery(uint32_t const val)
{
    Notification(NOTIFY_BATTERY, val);
}

/**************************************************************************
 *  @internal
 *************************************************************************/
void *TApplication::MessageLoopThreadEntry(void *arg)
{
    static_cast<TApplication *>(arg)->MessageLoop();
}

void TApplication::PRELOAD_timeo_callback(void *arg)
{
    static_cast<TApplication *>(arg)->FMsgQueue.PostMessage(MSG_PRELOAD_BLOCK, 0);
}

void TApplication::TIMER_output_callback(uint16_t id, void *arg, uint32_t loop)
{
    switch (id)
    {
    case DUTY_EMS_ID:
        TENS_context.TUV_POWER_discharge_count ++;

        if (0 == (0x01 & loop))
        {
            TENS_context.LOAD_discharge_count ++;
            OUTPUT_a();
        }
        else
            OUTPUT_b();

        goto TIMER_SPIN;

#if LOKI_SUPPORT_VERSION > 1
    case DUTY_EMS_ASY_ID:
    case DUTY_TENS_ID:
        TENS_context.TUV_POWER_discharge_count ++;
        TENS_context.LOAD_discharge_count ++;
        OUTPUT_a();

        goto TIMER_SPIN;
#endif

    case INTV_SECTION_ID:
        OUTPUT_openleak();
        break;

    case DUTY_END_ID:
        goto duty_fallthrough;
duty_fallthrough:
    case INTV_END_ID:
        OUTPUT_off();
        break;
    }

    if (false)
    {
TIMER_SPIN:
        TIMER_spin(HW_TIMER0, (uint32_t)arg);

        if (DET_HV_output())
            TENS_context.LOAD_feedback_count ++;

#if LOKI_SUPPORT_VERSION > 1
        if (DUTY_TENS_ID == id)
            OUTPUT_asy();
        else
#endif
            OUTPUT_off();
    }
}

void TApplication::BATT_intv_callback(void *arg)
{
#ifndef NO_DET_BATTERY
    ADC_start_convert(&BATT_context.attr, arg);
#else
    ARG_UNUSED(arg);
#endif
}

void TApplication::BATT_adc_callback(int volt, int raw, void *arg)
{
    ARG_UNUSED(raw);

#ifndef NO_DET_BATTERY
    static clock_t noti_tick = 0;
    ADC_stop_convert(&BATT_context.attr);

    TApplication *self = static_cast<TApplication *>(arg);
    volt += BATTERY_ADC_CALIB;

    if (! DET_is_charging())
    {
        if (stateLowBattery != self->FState && volt < BATTERY_EMPTY_VOLTAGE)
        {
            self->FShuttingdown = true;
            self->FState = stateLowBattery;

            self->FMsgQueue.PostMessage(MSG_STOPPING, stopLowBattery);
        }

        if (self->FBatt > 0)
        {
            clock_t now = clock();

            if (now - noti_tick > BATTERY_NOTI_TIMEOUT)
            {
                self->FMsgQueue.PostMessage(MSG_NOTIFY_BATTERY, volt);
                noti_tick = now;
            }
        }
    }

    self->FBatt = volt;
#else
    ARG_UNUSED(volt, arg);
#endif
}

