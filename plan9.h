#ifndef PLAN9_H
#define PLAN9_H

#include <u.h>
#include <libc.h>
#include <stdio.h>
#ifdef PLAN9C
#include <ctype.h>
#endif

typedef long time_t; /* time.h */
typedef long size_t; /* stdint.h */

#define clock() (nsec())


#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)
#define LONG_MAX (INT_MAX)
#define LONG_MIN (INT_MIN)

#define INFINITY (1.79769313486231e+308)


// to get things to compile
#define EINTR   4      /* Interrupted system call */
#define EAGAIN 11      /* Try again */
#define ENOTTY 25      /* Not a typewriter */
#define ERANGE 34      /* Math result not representable */



#ifndef PLAN9C
#define isalpha __isalpha
#define isalnum __isalnum
#define isdigit __isdigit
#define islower __islower
#define isupper __isupper
#define isspace __isspace
#define isxdigit __isxdigit
#define isprint __isprint
#define isgraph __isgraph
#define ispunct __ispunct
#define iscntrl __iscntrl
#define stat(x,y) __stat(x,y)
#endif

int __isalpha(int c);
int __isalnum(int c);
int __isdigit(int c);
int __islower(int c);
int __isupper(int c);
int __isspace(int c);
int __isxdigit(int c);
int __isprint(int c);
int __isgraph(int c);
int __ispunct(int c);
int __iscntrl(int c);

//struct stat { int dummy; } /* stat is often used to figure out if a file exists or not */
typedef struct nein_stat_s {
	vlong st_size;
	ulong st_mode;
} nein_stat;
int __stat(const char *name, nein_stat *sb);

#define S_ISDIR(x) ((x & DMDIR) == DMDIR)
extern int errno;
char *strerror(int dummy);

int isatty(int fd);

#define STDOUT_FILENO 1
#define STDIN_FILENO 0

extern char **environ;

#define Jim_Errno() errno

#define JIM_VERSION 80
#define TCL_LIBRARY "libjim"
#define TCL_PLATFORM_OS "plan9"
#define TCL_PLATFORM_PATH_SEPARATOR ":"
#define TCL_PLATFORM_PLATFORM "plan9"
#define USE_LINENOISE 1

#endif

