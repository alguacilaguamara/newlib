#include <unistd.h>
#include <errno.h>
#include "syscall.h"
#include "libc.h"

static int dummy(int fd)
{
	return fd;
}

weak_alias(dummy, __aio_close);

int close(int fd)
{
	fd = __aio_close(fd);
	int r = __syscall_cp(SYS_close, fd);
	if (r == -EINTR) r = 0;
	return __syscall_ret(r);
}


//https://github.com/seL4/seL4_libs/blob/c7e4a85edc3048979fbc962ace2dbe657e8d0b3c/libsel4muslcsys/src/syscalls.h
  //     int close(int file)
    //    {
      //      return 0;
        //}
    
