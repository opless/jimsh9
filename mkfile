</$objtype/mkfile


BIN=jimsh

DEFAULTOBJ=\
	_load-static-exts.$O \
	jim-subcmd.$O jim-interactive.$O jim-format.$O jim.$O utf8.$O jimregexp.$O jimiocompat.$O \
	plan9.$O \
	_initjimsh.$O _stdlib.$O linenoise.$O

EXTENSIONS=\
	jim-tty.$O \
	jim-aio.$O \
	jim-array.$O \
	jim-clock.$O \
	jim-eventloop.$O \
	jim-exec.$O \
	jim-file.$O \
	jim-history.$O \
	jim-interp.$O \
	jim-load.$O \
	jim-namespace.$O \
	jim-pack.$O \
	jim-package.$O \
	jim-posix.$O \
	jim-readdir.$O \
	jim-regexp.$O \
	jim-signal.$O \
	jim-syslog.$O \
	glob.$O \
	nshelper.$O \
	oo.$O \
	stdlib.$O \
	tclcompat.$O \
	tree.$O

CFLAGS=-c -p -DPLAN9 -DHAVE_NO_AUTOCONF -DUSE_LINENOISE -I.


$BIN: $DEFAULTOBJ jimsh.$O
	$LD -o $target $prereq


%.$O: %.c
	$CC $CFLAGS $stem.c

clean:V:
	rm $BINOBJ $BIN
