/*ESTE SOBRA CREO!!
*/
clock_t times(struct tms *tms)
{
    return __syscall(SYS_times, tms);
} 
