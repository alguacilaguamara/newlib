//https://es.stackoverflow.com/questions/113221/para-que-se-usa-stat-en-el-c%C3%B3digo
/*informacion sobre un archivo o directorio*/
//https://github.com/seL4/musllibc/blob/b41b6f8ff99a4328a681023b64234938459854fc/src/stat/stat.c
int stat(const char *file, struct stat *st)
{
    #ifdef SYS_stat
        return syscall(SYS_stat, path, buf);
    #else
        return syscall(SYS_fstatat, AT_FDCWD, path, buf, 0);
    #endif
} 
