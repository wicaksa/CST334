CC = gcc

all : fifo

CFLAGS = -D DEBUG

fifo : fifo.c
	gcc $(CFLAGS) -o fifo fifo.c queue.c node.c

clean: 
	rm fifo