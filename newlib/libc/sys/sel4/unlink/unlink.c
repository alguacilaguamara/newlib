#include <unistd.h>
#include <fcntl.h>
#include "syscall.h"

int unlink(char *name)
{
    #ifdef SYS_unlink
        return syscall(SYS_unlink, name);
    #else
        return syscall(SYS_unlinkat, AT_FDCWD, name, 0);
    #endif
} 
