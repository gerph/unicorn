/* Hastily hacked together logging options */

#include "qemu/osdep.h"
#include "qemu/log.h"

#define DEFAULT_LOG_FILENAME "qemu.log"

/* FIXME: Should be one of these per context, not global? */
char *qemu_logfilename = NULL;
int64_t qemu_loglevel = 0;
FILE *qemu_logfh = NULL;

int qemu_log(const char *fmt, ...)
{
    /* FIXME: Locking needed */
    if (!qemu_logfh)
    {
        char *filename = qemu_logfilename ? qemu_logfilename : DEFAULT_LOG_FILENAME;
        qemu_logfh = fopen(filename, "w");
        if (qemu_logfh)
        {
            /* FIXME: Set buffering to none? */
        }
    }
    if (qemu_logfh)
    {
        /* Only if we opened the log do we try writing anything. */
        int ret;
        va_list ap;
        va_start(ap, fmt);
        ret = vfprintf(qemu_logfh, fmt, ap);
        va_end(ap);
        return ret;
    }
    else
    {
        return 0;
    }
}

void qemu_set_loglevel(int64_t log_flags)
{
    /* FIXME: Locking needed? */
    qemu_loglevel = log_flags;
    /* FIXME: Close file if set to 0? */
}

int64_t qemu_get_loglevel(void)
{
    /* FIXME: Locking needed? */
    return qemu_loglevel;
}

/* FIXME: Provide a function that allows the filename to be set? */
