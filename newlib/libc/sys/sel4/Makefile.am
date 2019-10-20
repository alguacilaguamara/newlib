AUTOMAKE_OPTIONS = cygnus
INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)
AM_CCASFLAGS = $(INCLUDES)
 
noinst_LIBRARIES = lib.a
 
if MAY_SUPPLY_SYSCALLS
extra_objs = syscalls.o close/close.o environ/environ.o execve/execve.o exit/exit.o fork/fork.o fstat/fstat.o getpid/getpid.o gettimeofday/gettimeofday.o isatty/isatty.o kill/kill.o link/link.o lseek/lseek.o open/open.o read/read.o sbrk/sbrk.o stat/stat.o times/times.o unlink/unlink.o wait/wait.o
else                    # syscalls.c into multiple files in the previous step
extra_objs =
endif
 
lib_a_SOURCES =
lib_a_LIBADD = $(extra_objs)
EXTRA_lib_a_SOURCES = syscalls.c crt0.c close/close.c environ/environ.c execve/execve.c exit/exit.c fork/fork.c fstat/fstat.c getpid/getpid.c gettimeofday/gettimeofday.c isatty/isatty.c kill/kill.c link/link.c lseek/lseek.c open/open.c read/read.c sbrk/sbrk.c stat/stat.c times/times.c unlink/unlink.c wait/wait.c
lib_a_DEPENDENCIES = $(extra_objs)      # syscalls.c into multiple files
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)
 
if MAY_SUPPLY_SYSCALLS
all: crt0.o
endif
 
ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host