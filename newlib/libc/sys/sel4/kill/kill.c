int kill(int pid, int sig)
{
    //es va_list
  //  sys_tgkill(pid);

    /*o es algo más test_kill_from_parent(struct env *env)?*/
    
	return syscall(SYS_kill, pid, sig);
} 
