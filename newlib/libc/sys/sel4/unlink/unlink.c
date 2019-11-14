#include <unistd.h>
#include <fcntl.h>
#include "syscall.h"

int unlink(char *name)
{
    #ifdef SYS_unlink
        return syscall(SYS_unlink, path);
    #else
        return syscall(SYS_unlinkat, AT_FDCWD, path, 0);
    #endif
} 
