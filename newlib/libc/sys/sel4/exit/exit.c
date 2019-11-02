#include <stdlib.h>
#include "syscall.h"

//por ejemplo, buscar musllibc para sel4 hay ejemplos
//https://github.com/seL4/musllibc/blob/b41b6f8ff99a4328a681023b64234938459854fc/src/exit/_Exit.c
_Noreturn void _Exit(int ec)
{
    //seL4_DebugHalt;
    __syscall(SYS_exit_group, ec);
        for (;;) __syscall(SYS_exit, ec);
} 
