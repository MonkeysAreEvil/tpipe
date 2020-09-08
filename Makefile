# Change values of variables to adapt.
CC = gcc
PRG1 = tpipe
OBJS1 = $(PRG1).o
PRG2 = tap
OBJS2 =$(PRG2).o
OPTFLAGS= -ansi -pedantic -O4
CFLAGS = -Wall $(OPTFLAGS)
LDFLAGS = -L.
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/man/man1

all:	$(PRG1) $(PRG2)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

$(PRG1):	$(OBJS1)
	$(CC) $(CFLAGS) -o $(PRG1) $(OBJS1) $(LDFLAGS) $(LIBS)

$(PRG2):	$(OBJS2)
	$(CC) $(CFLAGS) -o $(PRG2) $(OBJS2) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(PRG1) $(PRG2)

again:	clean all

install:	all
	cp $(PRG1) $(BINDIR)
#	cp $(PRG2) $(BINDIR)
	cp $(PRG1).1 $(MANDIR)
	if [ `uname | grep Linux` ]; then cd $(MANDIR) && gzip $(PRG1).1; fi
#	cp $(PRG2).1 $(MANDIR)
#	if [ `uname | grep Linux` ]; then cd $(MANDIR) && gzip $(PRG2).1; fi

uninstall:
	rm $(BINDIR)/$(PRG1)
#	rm $(BINDIR)/$(PRG2)
	rm $(MANDIR)/$(PRG1).*
#	rm $(MANDIR)/$(PRG2).*

