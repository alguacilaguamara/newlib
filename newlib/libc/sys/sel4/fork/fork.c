#include "libc.h"

pid_t fork(void)
{
        pid_t ret;
        __fork_handler(-1);
    #ifdef SYS_fork
        ret = syscall(SYS_fork);
    #else
        ret = syscall(SYS_clone, SIGCHLD, 0);
    #endif
        __fork_handler(!ret);
        return ret;
} 
