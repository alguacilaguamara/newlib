
//https://github.com/seL4/seL4_libs/blob/master/libsel4vka/include/vka/vka.h#L17
int getpid()
{
    // pid_t ret;
    //return (int)sel4utils_process_t.pd;
    return __syscall(SYS_getpid);
} 
