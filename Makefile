# this is my makefile for keylight

CC=gcc #compiler
PREFIX=/usr/local


all:	keylight.o
	$(CC) keylight.c -o keylight

clean:  keylight.o keylight
	rm keylight.o keylight

install:	keylight
	cp keylight $(DESTDIR)$(PREFIX)/bin/
	chown root:root $(DESTDIR)$(PREFIX)/bin/keylight
	chmod ug+s $(DESTDIR)$(PREFIX)/bin/keylight

uninstall:	$(DESTDIR)$(PREFIX)/bin/keylight
	rm $(DESTDIR)$(PREFIX)/bin/keylight
