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


/* The tm struct isn't in Plan9, but a similar struct^Wtypedef is Tm
 * The below is a renamed Tm struct, so we can manipulate it in the same way as in ANSI C
 *
 * caveat: All the date/time functions that are used in ANSI C are also slightly different
 *         as they don't use pointers for the time_t value.
 *         strftime doesn't exist either, but we can code for that, elsewhere.
 *
 */

struct tm {
  int tm_sec;    /* Seconds (0-60) */
  int tm_min;    /* Minutes (0-59) */
  int tm_hour;   /* Hours (0-23) */
  int tm_mday;   /* Day of the month (1-31) */
  int tm_mon;    /* Month (0-11) */
  int tm_year;   /* Year - 1900 */
  int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
  int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
  //int tm_isdst;  /* NEIN Daylight saving time */
  char zone[4];  /* 9 time zone name */
  int  tzoff;    /* 9 time zone delta from GMT */
};
/* strftime adapted from kvik's lua implementation  */
size_t strftime(char *destination, size_t destination_max, char *format, struct tm *fake_tm);


#define Jim_Errno() errno

#define JIM_VERSION 80
#define TCL_LIBRARY "libjim"
#define TCL_PLATFORM_OS "plan9"
#define TCL_PLATFORM_PATH_SEPARATOR ":"
#define TCL_PLATFORM_PLATFORM "plan9"
#define USE_LINENOISE 1

#endif

