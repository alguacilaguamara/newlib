/* Create a new TCB */
/* hint: vka_alloc_tcb()
    * int vka_alloc_tcb(vka_t *vka, vka_object_t *result);
    * @param vka Pointer to vka interface.
    * @param result Structure for the TCB object.  This gets initialised.
    * @return 0 on success
    */
//https://github.com/seL4/musllibc/blob/b41b6f8ff99a4328a681023b64234938459854fc/src/process/fork.c
/*int fork()*/
//{
    //seL4_TCB_SetSpace()
    //seL4_TCB_WriteRegisters()
   /* pid_t ret;
    __fork_handler(-1);
    ret = syscall(SYS_fork);
    if (libc.main_thread && !ret)
    {
        pthread_t self = __pthread_self();
        self->tid = self->pid = syscall(SYS_getpid);
        memset(&self->robust_list, 0, sizeof self->robust_list);
        libc.threads_minus_1 = 0;
        libc.main_thread = self;
    }
    __fork_handler(!ret);
    return (int)ret;*/

    // vka_object_t tcb_object = {0};
    
    
//}
//https://github.com/seL4/musllibc/blob/b41b6f8ff99a4328a681023b64234938459854fc/src/process/fork.c
pid_t fork(void)
{
        pid_t ret;
        sigset_t set;
        __fork_handler(-1);
        __block_all_sigs(&set);
    #ifdef SYS_fork
        ret = syscall(SYS_fork);
    #else
        ret = syscall(SYS_clone, SIGCHLD, 0);
    #endif
        if (!ret) {
            pthread_t self = __pthread_self();
            self->tid = __syscall(SYS_gettid);
            self->robust_list.off = 0;
            self->robust_list.pending = 0;
            libc.threads_minus_1 = 0;
        }
        __restore_sigs(&set);
        __fork_handler(!ret);
        return ret;
} 
