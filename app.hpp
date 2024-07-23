#ifndef __MESSAGE_LOOP_HPP
#define __MESSAGE_LOOP_HPP              1

#include <bluetooth/uuid.h>
#include <pthread.h>
#include <hash/md5.h>
#include <uc++/message.queue.hpp>

#include "config.h"

#include "notification.h"
#include "ble.hpp"
#include "loki.hpp"

extern Bluetooth::BD_addr_t const *BDAddr;
extern MD5_t file_md5(int fd);
extern Loki::mode_t MODE;

#define IS_DUTCH_DEVICE()               (0x087C == BDAddr->NAP && 0xEE == BDAddr->UAP)

enum TMessageId
{
    MSG_STARTUP,
    MSG_SHUTDOWN,
    MSG_GPIO,

    MSG_STARTING,
    MSG_STOPPING,
    MSG_PRELOAD_BLOCK,
    MSG_START_DEFAULT_FILE,

    MSG_SET_INTENSITY,
    MSG_NOTIFY_INTENSITY,
    MSG_NOTIFY_BATTERY,
};

class TApplication
{
public:     // type
    typedef MessageQueue<uint32_t, 10, 100> TMessageQueue;

    enum state_t
    {
        stateStopped,
        stateStarting,
        stateRunning,

        // exception state
        stateCharging,
        stateLowBattery
    };

    enum stop_reason_t
    {
        stopAbort,      // when receive "osto"
        stopShutdown,   // when hit hardware button / script done
        stopCharging,
        stopLowBattery,
        stopNoLoad,
        stopError,      // somekind impossiable
    };

public:
    TApplication();

    void Run(void);
    void UpdateLastActivity(uint32_t MsgId = 0);

    void Shutdown(void);
    void GPIO_callback(uint32_t pins);

    int StartDebug(void);
    int StartFile(char const *filename, uint32_t cutoff_seconds = 0);
    void StartDefaultFile(uint8_t idx);

    void SetIntensity(uint32_t value, bool Notification);
    void Stop();

    char *DefaultFile(uint8_t const idx);
    int UpdateDefaultFile(uint8_t idx, char const *filename);

public:     // properties
    bool Shuttingdown() const
        { return FShuttingdown; }
    enum state_t State() const
        { return FState; }

    uint32_t RunningSeconds() const
        { return stateRunning == FState ? (clock() - FRunningTickStart) / 1000 : 0; }

    uint32_t Intensity(void) const
        { return FIntensity; }

    int Battery(void) const
        { return FBatt; }

    MD5_t const *LastFileMd5(void) const
        {  return &FLastFileMd5; };

private:
    bool PrepareStart(void);
    void Idle(void);

private:
    pthread_t FThreadId;
    bool FManufactoringMode;
    enum state_t FState;
    bool FShuttingdown;

    TMessageQueue FMsgQueue;
    clock_t FLastActivity;

    clock_t FRunningTickStart;
    uint32_t FIntensity;
    TLokiParser *FCurrFile;
    TLokiBlockParams FCurrBlock;
    uint32_t FCutoffSeconds;

    char FDefFiles[DEF_FILE_COUNT][NVM_DEF_FILE_SIZE];
    MD5_t FLastFileMd5;

    volatile int FBatt;

private:    // messages
    void MessageLoop(void) __attribute__((noreturn));

    void MSG_Startup(uint32_t const);
    void MSG_Shutdown(uint32_t const);

    void MSG_Starting(uint32_t const str);
    void MSG_Stopping(uint32_t const reason);
    void MSG_PreloadBlock(uint32_t const);
    void MSG_StartDefaultFile(uint32_t const);

    void MSG_SetIntensity(uint32_t const value);

    void MSG_NotifyIntensity(uint32_t const value);
    void MSG_NotifyBattery(uint32_t const);

private:    // static
    static void *MessageLoopThreadEntry(void *arg);

    static void PRELOAD_timeo_callback(void *arg);
    static void TIMER_output_callback(uint16_t id, void *arg, uint32_t loop);

    static void BATT_intv_callback(void *arg);
    static void BATT_adc_callback(int volt, int raw, void *arg);
};
extern TApplication *App;

#endif
