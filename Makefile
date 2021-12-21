CC=gcc
PREFIX=/usr

build: 
	${CC} tuk.c -lgit2 -o tuk

install: 
	cp tuk ${PREFIX}
