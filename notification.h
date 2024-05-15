#ifndef __NOTIFICATION_H
#define __NOTIFICATION_H

#include <features.h>

__BEGIN_DECLS

    enum notification_t
    {
        NOTIFY_INTENSITY_BASE16,
        NOTIFY_INTENSITY_BASE10,
        NOTIFY_BATTERY,
        NOTIFY_STOP_BATTERY,
        NOTIFY_STOP_CHARGING,
        NOTIFY_STOP_NOLOAD,
        NOTIFY_STOP_SHUTDOWN,
        NOTIFY_STOP_ERROR,
    };

    /// @implements at shell.cpp bcuz uartfd was created there
extern
    void Notification(notification_t noti, ...);

__END_DECLS
#endif
