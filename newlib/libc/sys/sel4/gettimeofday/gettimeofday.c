#include <time.h>
#include <sys/time.h>
#include "syscall.h"

int gettimeofday(struct timeval *p, struct timezone *z)
{
    //sel4platsupport_get_default_timer
    struct timespec ts;
	if (!tv) return 0;
	clock_gettime(CLOCK_REALTIME, &ts);
	tv->tv_sec = ts.tv_sec;
	tv->tv_usec = (int)ts.tv_nsec / 1000;
	return 0;
} 
