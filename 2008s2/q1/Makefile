# COMP1927 08s2 Exam

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-g

exe: main.o Tree.o
	$(CC) $(LDFLAGS) -o exe Tree.o main.o

main.o: main.c Tree.h
	$(CC) -c $(CFLAGS) main.c

Tree.o: Tree.c Tree.h q1.c
	$(CC) -c $(CFLAGS) Tree.c

clean:
	rm -f exe Tree.o main.o tmp core
