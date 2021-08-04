CC = gcc

all : ts pc

CFLAGS = -D DEBUG

ts : threadSync.c
	gcc $(CFLAGS) -o ts threadSync.c -pthread 

pc : pc.c
	gcc $(CFLAGS) -o pc pc.c -pthread 

clean: 
	rm ts pc