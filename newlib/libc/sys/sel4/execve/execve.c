//http://manpages.ubuntu.com/manpages/bionic/es/man2/execve.2.html
//https://github.com/seL4/musllibc/blob/b41b6f8ff99a4328a681023b64234938459854fc/src/process/execve.c
int execve(const char *path, char *const argv[], char *const envp[])
{
	/* do we need to use environ if envp is null? */
	return syscall(SYS_execve, path, argv, envp);
}
