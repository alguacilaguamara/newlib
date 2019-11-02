#include <stat.h>
#include <errno.h>
#include <fcntl.h>
#include "syscall.h"
#include "libc.h"

//https://github.com/seL4/seL4_libs/blob/master/libsel4vka/include/vka/vka.h#L17
//https://github.com/seL4/musllibc/blob/b41b6f8ff99a4328a681023b64234938459854fc/src/stat/fstat.c
int fstat(int file, struct stat *st)
{
    int ret = __syscall(SYS_fstat, fd, st);
	if (ret != -EBADF || __syscall(SYS_fcntl, fd, F_GETFD) < 0)
		return __syscall_ret(ret);

	char buf[15+3*sizeof(int)];
	__procfdname(buf, fd);
#ifdef SYS_stat
	return syscall(SYS_stat, buf, st);
#else
	return syscall(SYS_fstatat, AT_FDCWD, buf, st, 0);
#endif
} 
