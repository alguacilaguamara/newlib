#include <stdlib.h>
#include "syscall.h"

_Noreturn void _Exit(int ec)
{
    //seL4_DebugHalt;
    __syscall(SYS_exit_group, ec);
        for (;;) __syscall(SYS_exit, ec);
} 
