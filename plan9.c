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

/* strftime adapted from kvik's lua port */
int _strfmttime_initialised=0;
size_t
strftime(char *destination, size_t destination_max, char *format, struct tm *fake_tm)
{
  char *s, mod;
  Fmt f;

  if(! _strfmttime_initialised) {
    _strfmttime_initialised = 1;
    tmfmtinstall();
  }

  Tm *tm = (Tm*)fake_tm;

  fmtstrinit(&f);
  for(s = format; *s; s++){
    if(s[0] != '%'){
      fmtprint(&f, "%c", s[0]);
      continue;
    }
    s++;
    if(s[0] == '%'){
      fmtprint(&f, "%");
      continue;
    }
    if(s[0] == 'E' || s[0] == '0'){
      mod = s[0];
      s++;
    }
    switch(s[0]){
    case 'n': fmtprint(&f, "\n"); break;
    case 't': fmtprint(&f, "\t"); break;

    case 'y': fmtprint(&f, "%τ", tmfmt(tm, "YY")); break;
    case 'Y': fmtprint(&f, "%τ", tmfmt(tm, "YYYY")); break;

    case 'm': fmtprint(&f, "%τ", tmfmt(tm, "MM")); break;
    case 'b': fmtprint(&f, "%τ", tmfmt(tm, "MMM")); break;
    case 'B': fmtprint(&f, "%τ", tmfmt(tm, "MMMM")); break;

    /* TODO: week of the year calculation */
    case 'U': fmtprint(&f, "00"); break;
    case 'W': fmtprint(&f, "01"); break;

    case 'j': fmtprint(&f, "%.3d", tm->yday + 1); break;
    case 'd': fmtprint(&f, "%.2d", tm->mday); break;

    case 'w': fmtprint(&f, "%τ", tmfmt(tm, "W")); break;
    case 'a': fmtprint(&f, "%τ", tmfmt(tm, "WW")); break;
    case 'A': fmtprint(&f, "%τ", tmfmt(tm, "WWW")); break;

    case 'H': fmtprint(&f, "%τ", tmfmt(tm, "hh")); break;
    case 'I': fmtprint(&f, "%d", tm->hour % 12); break;

    case 'M': fmtprint(&f, "%τ", tmfmt(tm, "mm")); break;

    case 'S': fmtprint(&f, "%τ", tmfmt(tm, "ss")); break;

    case 'c': case 'x': fmtprint(&f, "%τ", tmfmt(tm, nil)); break;
    case 'X': fmtprint(&f, "%τ", tmfmt(tm, "hh[:]mm[:]ss")); break;

    case 'p': fmtprint(&f, "%τ", tmfmt(tm, "a")); break;

    case 'Z': fmtprint(&f, "%τ", tmfmt(tm, "Z")); break;

    default:
      fmtprint(&f, "%%");
      if(mod)
        fmtprint(&f, "%c", mod);
      fmtprint(&f, "%c", s[0]);
      break;
    }
    mod = 0;
  }
  s = fmtstrflush(&f);
  strncpy(destination,s,destination_max);
  free(s);
  return strlen(destination);
}

int __stat(const char *name, nein_stat *st){
  Dir *dir = dirstat(name);
  int rc = (dir != NULL);
  if(st) {
    st->st_size = dir->length;
    st->st_mode = dir->mode;
    st->st_atime= dir->atime;
    st->st_ctime= dir->mtime;
    st->st_mtime= dir->mtime;
    st->st_nlink= 1;

    free(dir);
  }
  return rc;
}

char *dirname(char *n) {
  static char empty[] = "";
  static char root[] = "/";
  char *s=nil;
  long slen;
  if(! n) return nil;
  slen = strlen(n);
  if(slen == 0)
    return empty;
  // strip trailing '/'s
  while (slen > 0 && n[slen-1] == '/')
    slen--;
  if(slen == 0) return root;
  s = malloc(slen+1);
  if(s == nil) return nil;  // urgh, bail
  strncpy(s,n,slen);
  return s;
}

int mkdir(char *n, int mode) {
  char *p = nil;
  int f=0, rc=-1;

  if(access(n,AEXIST)) { // entry exists
    errno = EEXIST;
    goto mkdir_error;
  }
  p = dirname(n);
  if(access(p,AEXIST)) { // Can't write in a folder that doesn't exist
    errno = ENOENT;
    goto mkdir_error;
  }
  if(access(p,AWRITE)) { // Can't write to the folder, so can't create
    errno = EACCES;
  }
  f = create(n, OREAD, DMDIR | mode);
  if(f < 0){
    errno = EPERM; // permission to create a folder is denied anyway.
    goto mkdir_error;
  } else {
    rc = 0;
    close(f);
  }
mkdir_error:
  free(p);
  return rc;
}

int rename(const char *oldpath, const char *newpath) {
if(oldpath == NULL || newpath == NULL) {
  errno = EINVAL;
  return -1;
}

//TODO Implement rename.

errno = EINVAL;
return -1;

}

