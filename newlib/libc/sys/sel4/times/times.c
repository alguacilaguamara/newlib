//https://github.com/seL4/seL4_libs/blob/c7e4a85edc3048979fbc962ace2dbe657e8d0b3c/libsel4vmm/include/vmm/platform/ioports.h
//https://github.com/seL4/musllibc/blob/b41b6f8ff99a4328a681023b64234938459854fc/src/time/times.c
clock_t times(struct tms *tms)
{
    return __syscall(SYS_times, tms);
} 
