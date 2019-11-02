//http://manpages.ubuntu.com/manpages/bionic/es/man2/brk.2.html
/*Hay que aumentar el espacio de datos del programa en incr*/
//https://github.com/seL4/musllibc/blob/b41b6f8ff99a4328a681023b64234938459854fc/src/linux/sbrk.c
// caddr_t sbrk(int incr)
// {
//    /* void *
//     vspace_new_sized_stack(vspace_t * vspace, size_t n_pages)*/
    
//     if (inc) return (void *)__syscall_ret(-ENOMEM);
// 	return (void *)__syscall(SYS_brk, 0);
// } 

#include <stdint.h>
#include <errno.h>
#include "syscall.h"

void *sbrk(intptr_t inc)
{
	if (inc) return (void *)__syscall_ret(-ENOMEM);
	return (void *)__syscall(SYS_brk, 0);
}

