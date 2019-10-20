//https://linux.die.net/man/2/unlink
//https://github.com/seL4/musllibc/blob/b41b6f8ff99a4328a681023b64234938459854fc/src/unistd/unlink.c
int unlink(char *name)
{
    #ifdef SYS_unlink
        return syscall(SYS_unlink, path);
    #else
        return syscall(SYS_unlinkat, AT_FDCWD, path, 0);
    #endif
} 
