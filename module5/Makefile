CC = gcc

all : step1 step1fixed matrix

CFLAGS = -D DEBUG

step1 : threadHello_step1.c
	gcc $(CFLAGS) -o step1 threadHello_step1.c -pthread 

step1fixed : threadHelloFixed_step1_Fixed.c
	gcc $(CFLAGS) -o step1fixed threadHelloFixed_step1_Fixed.c -pthread 

matrix : matrix_multiplication.c
	gcc $(CFLAGS) -o matrix matrix_multiplication.c -pthread 

clean: 
	rm step1 step1fixed matrix