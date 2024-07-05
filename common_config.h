#ifndef __COMMON_CONFIG_H
#define __COMMON_CONFIG_H               1

#include <features.h>
#include <stdint.h>
#include <stdbool.h>
#include <ultracore/nvm.h>

// NOTE: debug running
    // #define DEBUG_LOKI_PARSER
    #define NO_SHUTDOWN
    #define NO_DET_HV_OUTPUT
    // #define NO_DET_CHARGING
    // #define NO_DET_BATTERY

#ifdef NDEBUG
    #undef DEBUG_LOKI_PARSER
    #undef NO_SHUTDOWN
    #undef NO_DET_HV_OUTPUT
    #undef NO_DET_CHARGING
    #undef NO_DET_BATTERY
#endif

/* v1 change bluetooth name */
    #define NO_ADNAME_CHANGE
/* v1 no enough FLASH spaces */
    // #define NO_SHELL_DUMP

/** @override in config.h @GPIO debounce & hold to repeat */
    #define GPIO_DEBOUNCE_INTV          (150)
    #define GPIO_HOLD_REPEAT_INTV       (300)

/** @define > 0 in config.h to enable auto shutdown */
    // #define SHUTDOWN_IDLE_SECONDS    (0)

/** @TIMER0 use as output frequency(1us), changing this will boost file execute time */
    #define FREQ_HW_TIMER0              (1000000)
    // #define FREQ_HW_TIMER0              (4000000)

/// @override in config.h
    #define DEF_FILE_COUNT              (1)
    #define DEFILE_RUNNING_NO_AD
    // #define DEFILE_USING_LAST_RUNNING

/** @battery ADC */
    #define BATTERY_EMPTY_VOLTAGE       (3150)
    /// @bluetens product has history issue: 5000mv is full battery
    // #define BATTERY_COMPAT_BLUETENS_V1

/** @file io */
    #define FILE_downloading()
    #define FILE_download_complete()

/** @misc */
    #define LOAD_DET_TIMEOUT            (3000)
    #define CAPACITOR_DISCHARGE_US      (50)

/** NVM */
    #define NVM_AD_NAME_ID              NVM_DEFINE_KEY('a', 'd', 'v', 'n')
        #define NVM_AD_NAME_SIZE        (24)
    #define NVM_DEF_FILE_ID_BASE        NVM_DEFINE_KEY('d', 'e', 'f', '1')
        #define NVM_DEF_FILE_SIZE       (32)

    // fitsuit
    #define NVM_STORED_INTENSITY_ID     (NVM_USER_ID_BASE + 0x100)

__BEGIN_DECLS
extern __attribute__((nothrow))
    void USB_plugin(void);

extern __attribute__((nothrow))
    void PLATFORM_init(void);
extern __attribute__((nothrow))
    bool PLATFORM_startup(void);
extern __attribute__((nothrow))
    void PLATFORM_shutdown(void);
extern __attribute__((nothrow))
    void PLATFORM_msg_activity(uint32_t MsgId);
extern __attribute__((nothrow))
    void PLATFORM_idle(void);
extern __attribute__((nothrow))
    void PLATFORM_lowbattery(void);
extern __attribute__((nothrow))
    void PLATFORM_start_defile(void);

extern __attribute__((nothrow))
    void INTENSITY_ctrl_init(void);
extern __attribute__((nothrow))
    void INTENSITY_ctrl_release(uint32_t value);
extern __attribute__((nothrow))
    int INTENSITY_ctrl(uint32_t value);
extern __attribute__((nothrow))
    uint32_t INTENSITY_adjust(uint32_t value, int adjust);
extern __attribute__((nothrow))
    void INTENSITY_TUV_power_control(bool en, uint32_t intensity);

__END_DECLS
#endif
