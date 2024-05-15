#ifndef __FS_TAB_H
#define __FS_TAB_H

#include <features.h>

__BEGIN_DECLS

extern __attribute__((nothrow))
    void FLASH_mountfs(void);
extern __attribute__((nothrow))
    void FLASH_unmountfs(void);

__END_DECLS
#endif
