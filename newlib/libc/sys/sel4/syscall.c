#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "includes/syscall.h"
#include "close/close.c"
#include "environ/environ.c"
#include "execve/execve.c"
#include "exit/exit.c"
#include "fork/fork.c"
#include "fstat/fstat.c"
#include "getpid/getpid.c"
#include "gettimeofday/gettimeofday.c"
#include "includes/errno.h"
#include "includes/features.h"
#include "includes/libc.h"
#include "includes/limits.h"
#include "isatty/isatty.c"
#include "kill/kill.c"
#include "link/link.c"
#include "lseek/lseek.c"
#include "open/open.c"
#include "read/read.c"
#include "sbrk/sbrk.c"
#include "stat/stat.c"
#include "times/times.c"
#include "unlink/unlink.c"
#include "wait/wait.c"
#include "write/write.c"
#include "libc.h"


































