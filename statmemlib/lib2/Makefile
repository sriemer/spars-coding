LIB_NAME = lib2.a
VERSION = "0:0:0"
DEFINES = -D VERSION='$(VERSION)' \
          -D LIB_NAME='"$(LIB_NAME)"'
CC = gcc
CFLAGS += -O0 -g -Wall $(DEFINES)
LDFLAGS += -fPIC -shared
LINK = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

prefix ?= /usr/local
eprefix = $(prefix)
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = $(INSTALL)

default: depend $(OBJS)
	$(LINK) $(LDFLAGS) -o $(LIB_NAME) $(OBJS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $(SRCS) >> ./.depend

-include .depend

clean:
	rm -f *.o ./.depend $(LIB_NAME)

distclean:
	rm -f debian/$(LIB_NAME).*.debhelper debian/$(LIB_NAME).*.log
	rm -f debian/$(LIB_NAME).substvars debian/files
	rm -Rf debian/$(LIB_NAME)
	rm -f build-stamp install-stamp

install-bin: default
	mkdir -p $(eprefix)/lib
	$(INSTALL) -s $(LIB_NAME) $(eprefix)/lib

install: install-bin
