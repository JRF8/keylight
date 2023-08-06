# this is my makefile for keylight

CC=gcc #compiler

all:	keylight.o
	$(CC) keylight.c -o keylight

clean:  keylight.o keylight
	rm keylight.o keylight

install:	keylight
	cp keylight /usr/local/bin/
	chown root:root /usr/local/bin/keylight
	chmod ug+s /usr/local/bin/keylight

uninstall:	/usr/local/bin/keylight
	rm /usr/local/bin/keylight
