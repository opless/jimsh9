#define PLAN9C

#include "plan9.h"

int __isalpha(int c) { return isalpha(c); }
int __isalnum(int c) { return isalnum(c); }
int __isdigit(int c) { return isdigit(c); }
int __islower(int c) { return islower(c); }
int __isupper(int c) { return isupper(c); }
int __isspace(int c) { return isspace(c); }
int __isxdigit(int c) { return isxdigit(c); }
int __isprint(int c) { return isprint(c); }
int __isgraph(int c) { return isgraph(c); }
int __ispunct(int c) { return ispunct(c); }
int __iscntrl(int c) { return iscntrl(c); }


int __stat(const char *name, nein_stat *st){
Dir *dir = dirstat(name);
int rc = (dir != NULL);
if(st) {
  st->st_size = dir->length;
  st->st_mode = dir->mode;
  free(dir);
}
return rc;
}

int errno =0;
extern char **environ=NULL;


char *strerror(int dummy) {
static char __errstr[]="";
return __errstr;
}

int isatty(int fd) {
  char p[16]; /* normal will be /dev/cons */
  int rc = fd2path(fd,p,16);
  if(rc != 0) return -1;
  rc = strncmp("/dev/cons",p,16) == 0;
  return rc;
}

