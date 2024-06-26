#include <fs/ultrafs.h>
#include <flash.h>

#include "fstab.h"

static struct ULTRAFS_attr_t *attr = NULL;

/****************************************************************************
 *  @filesystem
 ****************************************************************************/
void FILESYSTEM_startup(void) /** @override */
{
    FLASH_mountfs();
}

/****************************************************************************
 *  @export
 ****************************************************************************/
void FLASH_mountfs(void)
{
#if FLASH_PAGE_SIZE > 2048
    #define FS_CLUSTER_SIZE             (FLASH_PAGE_SIZE / 2)
#else
    #define FS_CLUSTER_SIZE             (FLASH_PAGE_SIZE)
#endif
    int flash_fd = FLASH_createfd();
    attr = ULTRAFS_mount_root(flash_fd, FS_CLUSTER_SIZE, FLASH_AVAIL_SIZE, FLASH_ERASE_FILL);
}

void FLASH_unmountfs(void)
{
    if (NULL != attr)
        ULTRAFS_unmount(attr);
}
