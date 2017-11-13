PROGRAM_NAME = string_test
VERSION = "0.0.1"
DEFINES = -D VERSION='$(VERSION)' \
          -D PROGRAM_NAME='"$(PROGRAM_NAME)"'
CC = gcc
CFLAGS += -O0 -g -Wall $(DEFINES)
LINK = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

prefix ?= /usr/local
eprefix = $(prefix)
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = $(INSTALL)

default: depend $(OBJS)
	$(LINK) $(LDFLAGS) -o $(PROGRAM_NAME) $(OBJS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $(SRCS) >> ./.depend

-include .depend

clean:
	rm -f *.o ./.depend $(PROGRAM_NAME)

distclean:
	rm -f debian/$(PROGRAM_NAME).*.debhelper debian/$(PROGRAM_NAME).*.log
	rm -f debian/$(PROGRAM_NAME).substvars debian/files
	rm -Rf debian/$(PROGRAM_NAME)
	rm -f build-stamp install-stamp

install-bin: default
	mkdir -p $(eprefix)/bin
	$(INSTALL) -s $(PROGRAM_NAME) $(eprefix)/bin

install: install-bin
