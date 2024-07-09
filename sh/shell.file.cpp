#include <ultracore.h>

#include <fcntl.h>
#include <dirent.h>
#include <time.h>

#include <cstdint>
#include <cstring>
#include <cctype>
#include <climits>

#include <flash.h>
#include <sh/ucsh.h>

#include "app.hpp"
#include "shell.hpp"

/** @override */
int UCSH_ls(struct UCSH_env *env)
{
    DIR *dir = opendir(".");

    if (dir)
    {
        struct dirent *ent;

        while ((ent = readdir(dir)) != NULL)
        {
            if ('.' == ent->d_name[0])
                continue;

            UCSH_printf(env, "%-10s %5u\r\n", ent->d_name, ent->d_size);
            /*
            struct tm *tv = localtime(&ent->d_modificaion_ts);

            UCSH_printf(env, "%-8s %-5u %d/%02d/%02d %02d:%02d\r\n",
                ent->d_name,
                ent->d_size,
                1900 + tv->tm_year, tv->tm_mon + 1, tv->tm_mday, tv->tm_hour, tv->tm_min);
            */
        }

        closedir(dir);
        return END_OF_LS;
    }
    else
        return errno;
}

/** @override */
int UCSH_cat(struct UCSH_env *env)
{
    if (env->argc < 2)
        return EINVAL;

    char const *filename = env->argv[1];
    if (! *filename)
        return EINVAL;

    size_t size = 0;
    char *param = CMD_paramvalue_byname("s", env->argc, env->argv);

    if (! param)
        param =  CMD_paramvalue_byname("l", env->argc, env->argv);

    if (param)
    {
        char *p;
        size = strtoul(param, &p, 10);
        if (0 == size && 'x' == std::tolower(*p))
            size = strtoul(param, NULL, 16);
    }
    if (0 == size)
        size = std::numeric_limits<size_t>::max();

    int file_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC);
    if (-1 == file_fd)
        return errno;

    int retval = 0;
    char break_cond = '\0';

    while (size > 0)
    {
        if (-1 == (retval = read(env->fd, env->buf, size > 64  ? 64 : size)))
        {
            retval = 0; // REVIEW: timedout is not a error
            break;
        }

        App->UpdateLastActivity();
        FILE_downloading();

        /// break condition: @shell input (ctrl + d and ctrl + d)
        if (1 == retval && 0x4 == env->buf[0])
        {
            if (break_cond == env->buf[0])
            {
                retval = 0;
                break;
            }
            else
            {
                break_cond = env->buf[0];
                continue;
            }
        }
        else if (break_cond && sizeof(break_cond) != write(file_fd, env->buf, sizeof(break_cond)))
        {
            retval = -1;
            break;
        }
        break_cond = '\0';

        if (retval > 0)
        {
            if (retval != writebuf(file_fd, env->buf, retval))
            {
                retval = -1;
                break;
            }

            size -= retval;
        }
        else
            break;
    }

    close(file_fd);
    FILE_download_complete();
    writeln(env->fd, NULL, 0);

    if (retval < 0)
        return errno;
    else
        return END_OF_CAT;
}

int SHELL_clearfs(struct UCSH_env *env)
{
    char *param = CMD_paramvalue_byname("s", env->argc, env->argv);
    if (! param)
        return EINVAL;

    char *p;
    size_t size = strtoul(param, &p, 10);
    if (0 == size && 'x' == std::tolower(*p))
        size = strtoul(param, NULL, 16);

    if (0 == size)
        return EINVAL;

    DIR *dir = opendir(".");
    if (dir)
    {
        struct dirent *ent;

        while ((ent = readdir(dir)) != NULL)
        {
            if ('.' == ent->d_name[0])
                continue;

            // something error with filesystem
            if (ent->d_size > FLASH_AVAIL_SIZE)
            {
                FILESYSTEM_format(".", "ultrafs");
                break;
            }

            if (ent->d_size <= size)
            {
                bool remove_file = true;

                for (uint8_t i = 0; i < DEF_FILE_COUNT; i ++)
                {
                    char *p = App->DefaultFile(i);
                    if (0 == std::strcmp(p, ent->d_name))
                    {
                        remove_file = false;
                        break;
                    }
                }

                if (remove_file)
                    unlinkat(dir->fd, ent->d_name, 0);
            }
        }
        return closedir(dir);
    }
    else
        return errno;
}

int SHELL_dump(struct UCSH_env *env)
{
    if (env->argc < 2)
        return EINVAL;

    int file_fd = open(env->argv[1], O_RDONLY);
    if (-1 == file_fd)
        return errno;

    while (true)
    {
        int retval = read(file_fd, env->buf, 64);
        msleep(0);

        if (retval > 0)
        {
            if (retval != writebuf(env->fd, env->buf, retval))
                return errno;
            else
                App->UpdateLastActivity();
        }
        else
            break;
    }

    close(file_fd);
    writeln(env->fd, NULL, 0);

    return END_OF_DUMP;
}

int SHELL_default_file(struct UCSH_env *env)
{
    if (2 == env->argc)
    {
        int fd = open(env->argv[1], O_RDONLY);
        if (-1 != fd)
        {
            App->UpdateDefaultFile(0, env->argv[1]);
            close(fd);
        }
    }

    UCSH_printf(env, "sdef=%s\r\n", App->DefaultFile(0));
    return ECHO_OFF;
}

int SHELL_default_file2(struct UCSH_env *env)
{
    if (env->argc > 1)
    {
        char *param = env->argv[1];
        char *filename;

        int idx = strtoul(param, &filename, 10);
        if (idx < 0 || idx > DEF_FILE_COUNT - 1 || '=' != *filename)
            return EINVAL;

        filename ++;

        if ('\0' != filename[0])
        {
            int fd = open(filename, O_RDONLY);
            if (-1 == fd)
                return errno;
            close(fd);
        }

        App->UpdateDefaultFile((uint8_t)idx, filename);
        return 0;
    }
    else
    {
        for (uint8_t i = 0; i < DEF_FILE_COUNT; i ++)
            UCSH_printf(env, "idx=%d;filename=%s\r\n", i, App->DefaultFile(i));

        return ECHO_OFF;
    }
}

int SHELL_md5(struct UCSH_env *env)
{
    if (2 != env->argc)
        return EINVAL;

    int fd = open(env->argv[1], O_RDONLY);
    if (-1 == fd)
        return errno;

    MD5_t md5 = file_md5(fd);
    int len = MD5_printf(env->buf, &md5);
    len += sprintf(&env->buf[len], "\r\n");

    write(env->fd, env->buf, len);

    close(fd);
    return ECHO_OFF;
}
