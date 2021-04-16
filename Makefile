#
# Chose one of these mallocs:
MALLOC=smalloc
#
# Gnu malloc, fastest but uses most memory.
#MALLOC=gmalloc
#
# Lars special malloc for LPmud. Uses least memory, but has an inefficient
# recombination scheme that may slow down the game after long uptimes.
#MALLOC=malloc
#
# Define what random number generator to use.
# If no one is specified, a guaranteed bad one will be used.
#
RAND=RANDOM
YFLAGS=-d
#
# If you don't have 'strchr', then add next flag to CFLAGS.
# -Dstrchr=index
#
# If you don't have flex, replace '-DFLEX' with '-DLEX' below and
# redefine 'LEX=lex'.
LEX=lex
#LEX=flex
CFLAGS=-DTRACE -D$(RAND) -O -DLEX -DMALLOC_$(MALLOC) 
CC=/usr/ucb/cc
#
# Add extra libraries here.
#
LIBS= -lm
#
# Add str.c here if you don't have memcpy() or strtol()
#
SRC=lang.y lexical.l main.c lnode.c interpret.c simulate.c object.c backend.c\
    comm1.c ed.c regexp.c wiz_list.c swap.c $(MALLOC).c string_space.c \
    call_out.c parse.c otable.c dumpstat.c stralloc.c
#
# Add str.o here if you don't have memcpy() or strtol()
#
OBJ=lang.o lexical.o main.o lnode.o interpret.o simulate.o object.o backend.o\
    comm1.o ed.o regexp.o wiz_list.o swap.o string_space.o $(MALLOC).o \
    call_out.o parse.o otable.o dumpstat.o stralloc.o

debug: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o debug $(LIBS)

parse: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o parse $(LIBS)

lint: *.c
	lint *.c

call_out.o: object.h interpret.h

swap.o: swap.c lnode.h object.h config.h interpret.h

lang.o: lang.c lnode.h config.h object.h interpret.h

lang.c y.tab.h: lang.y

lexical.o: lexical.c lnode.h config.h

lexical.c: lexical.l

lnode.o: lnode.h config.h

interpret.o: lnode.h interpret.h config.h object.h

simulate.o: interpret.h object.h config.h sent.h lnode.h wiz_list.h

wiz_list.o: wiz_list.h interpret.h

main.o: lnode.h config.h object.h interpret.h

clean:
	rm -f *.o y.tab.h lang.c lexical.c comm1.c comm2.c comm.h *.ln mon.out
	rm -f parse core frontend mudlib/core mudlib/debug.log TAGS frontend.c
	rm -f config.status lpmud.log
#	find . -name '*.i' -print -exec rm -f \{} \;
#	find . -name '*~' -print -exec rm -f \{} \;
#	find . -name '*#' -print -exec rm -f \{} \;
#	find . -name '*.orig' -print -exec rm -f \{} \;
#	find . -name '*.rej' -print -exec rm -f \{} \;

object.o: interpret.h object.h sent.h lnode.h config.h wiz_list.h

backend.o: object.h lnode.h config.h interpret.h wiz_list.h

comm1.o: comm.h sent.h interpret.h object.h config.h

comm2.o: config.h comm.h

frontend: comm2.o frontend.o
	$(CC) $(CFLAGS) comm2.o frontend.o -o frontend $(LIBS)

frontend.o: frontend.c config.h comm.h

ed.o: regexp.h object.h config.h interpret.h

regexp.o: regexp.h

otable.o: config.h object.h interpret.h

dumpstat.o: object.h interpret.h lnode.h

parse.o: lnode.h interpret.h config.h object.h wiz_list.h

stralloc.o: config.h

TAGS: $(SRC)
	etags $(SRC)

diff:
	make_diffs

count_active: count_active.o
	$(CC) count_active.o -o count_active

all: parse count_active
