
//https://github.com/seL4/seL4_libs/blob/master/libsel4vka/include/vka/vka.h#L17
#include <unistd.h>
#include "syscall.h"

pid_t getpid(void)
{
	return __syscall(SYS_getpid);
}