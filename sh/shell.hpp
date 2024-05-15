#ifndef __SHELL_H
#define __SHELL_H

#include <sh/ucsh.h>

/***************************************************************************
 *  @errno
 ***************************************************************************/
    /**
        @override the standard error for compatiable
    */
    #define END_OF_LS                   (1  /* + USER_ERRNO_BASE */)
    #define END_OF_DUMP                 (2  /* + USER_ERRNO_BASE */)
    #define END_OF_CAT                  (3  /* + USER_ERRNO_BASE */)

    #define EOTA_CRC                    (10 /* + USER_ERRNO_BASE */)
    #define EOTA_PAYLOAD                (11 /* + USER_ERRNO_BASE */)

    #define ECHO_OFF                    0xFFFF

/***************************************************************************
 *  @export
 ***************************************************************************/
extern
    void SHELL_init(void);

/***************************************************************************
 *  @shell commands
 ***************************************************************************/
extern
    int SHELL_default_file(struct UCSH_env *env);
extern
    int SHELL_default_file2(struct UCSH_env *env);

extern
    int SHELL_start_script(struct UCSH_env *env);
extern
    int SHELL_stop_output(struct UCSH_env *env);
extern
    int SHELL_shutdown(struct UCSH_env *env);

extern
    int SHELL_set_intensity(struct UCSH_env *env);

extern
    int SHELL_mode(struct UCSH_env *env);
extern
    int SHELL_status(struct UCSH_env *env);

/** by @override UCSH_ls
extern
    int SHELL_ls(struct UCSH_env *env);
*/
/** by @override UCSH_cat
extern
    int SHELL_cat(struct UCSH_env *env);
*/
extern
    int SHELL_clearfs(struct UCSH_env *env);
extern
    int SHELL_dump(struct UCSH_env *env);
extern
    int SHELL_md5(struct UCSH_env *env);

extern
    int SHELL_ota(struct UCSH_env *env);

#endif
