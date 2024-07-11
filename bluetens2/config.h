#ifndef __CONFIG_H
#define __CONFIG_H

#include <features.h>
#include <unistd.h>

#include <vinfo.h>
#include <gpio.h>

#include "../common_config.h"

    // #define NO_PINKTENS

#if defined(QN908X)
    #include "qn908x/QN908X_porting.h"
#elif defined(EFR32BG22C224F512GM40)
    #define BG22
    #include "bg22/BG22_porting.h"
#endif

__BEGIN_DECLS

#if   defined(BLUETENS2)
    #define PROJECT_NAME                "Bluetens2"
    #define PROJECT_ID                  "blt"
#elif defined(DUOSPORT2)
    #define PROJECT_NAME                "DuoSport2"
    #define PROJECT_ID                  "bst"
#elif defined(PINKTENS)
    #define PROJECT_NAME                "Pinktens"
    #define PROJECT_ID                  "pkt"
    #ifdef NO_PINKTENS
        #pragma GCC error "this is Pinktens project, can't have NO_PINKTENS"
    #endif
#elif defined(MEDTENS)
    #define PROJECT_NAME                "Medtens"
    #define PROJECT_ID                  "mdt"
    // TODO: force TENS on Medtens?
    #define FORCE_MODE                  Loki::MODE_TENS
#endif

#if defined(QN908X)
    #include "QN908X_porting.h"
    #define PROJECT_VERSION             VERSION_INFO(3, 3, 6)
#elif defined(EFR32BG22C224F512GM40)
    #define BG22
    #include "BG22_porting.h"
    #define PROJECT_VERSION             VERSION_INFO(3, 2, 5)
#endif

/// @shutdown after 30 seconds idle
    #define SHUTDOWN_IDLE_SECONDS       (30)

/// @dutch
    #define DUTCH_SHUTDOWN_IDLE_SECONDS (60)
    #define DUTCH_LOAD_DET_TIMEOUT      (10000)

/// @loki parser
    #define LOKI_SUPPORT_VERSION        (2)

/// @override
    // #undef DEFILE_RUNNING_NO_AD
    #undef NO_SHELL_DUMP

/// @battery override
    #undef BATTERY_LOW_VOLTAGE
    #define BATTERY_LOW_VOLTAGE         (3100)

/// change @default file count to 4
    #undef DEF_FILE_COUNT
    #define DEF_FILE_COUNT              (4)

/** @TUV errata */
    #define TUV_ERRATA_US               (3)

static inline
    bool DET_is_pinktens(void)
    {
    #if ! defined(NO_PINKTENS)
        GPIO_setdir_input_pp(PULL_UP, PINKTENS_DET, true);

        bool retval = 0 != GPIO_peek(PINKTENS_DET);
        GPIO_disable(PINKTENS_DET);
        return retval;
    #else
        return false;
    #endif
    }

static inline
    void OUTPUT_a(void)
    {
        GPIO_clear(PIN_OUT2 | PIN_OUT3 | PIN_ASY_CTL);
        GPIO_set(PIN_OUT1 | PIN_OUT4 | PIN_HV_CTRL);
    }

static inline
    void OUTPUT_asy(void)
    {
        GPIO_clear(PIN_HV_CTRL | PIN_OUT1 | PIN_OUT4);
        GPIO_set(PIN_ASY_CTL | PIN_OUT2 | PIN_OUT3);
    }

static inline
    void OUTPUT_b(void)
    {
        GPIO_clear(PIN_OUT1 | PIN_OUT4);
        GPIO_set(PIN_OUT2 | PIN_OUT3);
    }

static inline
    void OUTPUT_openleak(void)
    {
        GPIO_clear(PIN_LDO_POWER);

        GPIO_clear(PIN_ASY_CTL);
        GPIO_set(PIN_HV_CTRL | PIN_OUT1 | PIN_OUT2 | PIN_OUT3 | PIN_OUT4);
    }

static inline
    void OUTPUT_off(void)
    {
        GPIO_set(PIN_LDO_POWER);

        GPIO_set(PIN_HV_CTRL);
        GPIO_clear(PIN_ASY_CTL | PIN_OUT1 | PIN_OUT2 | PIN_OUT3 | PIN_OUT4);
    }

static inline
    void OUTPUT_release(void)
    {
        GPIO_clear(PIN_LDO_POWER);

        GPIO_set(PIN_OUT1 | PIN_OUT2 | PIN_OUT3 | PIN_OUT4);
        usleep(CAPACITOR_DISCHARGE_US);

        GPIO_clear(PIN_HV_CTRL);
        GPIO_clear(PIN_OUT1 | PIN_OUT2 | PIN_OUT3 | PIN_OUT4);
    }

static inline
    bool DET_is_charging(void)
    {
    #ifndef NO_DET_CHARGING
        #ifdef QN908X
            return 0 == GPIO_peek(PIN_CHARGING_DET);
        #else
            return 0 != GPIO_peek(PIN_CHARGING_DET);
        #endif
    #else
        return false;
    #endif
    }

static inline
    bool DET_HV_output(void)
    {
        return 0 == GPIO_peek(PIN_HV_PULSE_DET);
    }

__END_DECLS
#endif
