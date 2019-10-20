//https://docs.sel4.systems/Tutorials/dynamic-4.html
//https://github.com/seL4/musllibc/blob/b41b6f8ff99a4328a681023b64234938459854fc/src/time/gettimeofday.c
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
