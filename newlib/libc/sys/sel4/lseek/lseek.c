//http://sopa.dis.ulpgc.es/prog_c/FICHER.HTM
//https://github.com/seL4/musllibc/blob/b41b6f8ff99a4328a681023b64234938459854fc/src/stdio/fseek.c
int lseek(int file, int ptr, int dir)
{
    long sys_lseek(va_list ap);
} 
