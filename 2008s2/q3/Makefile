# COMP1927 08s2 Exam

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-g

exe: main.o Graph.o
	$(CC) $(LDFLAGS) -o exe Graph.o main.o

main.o: main.c Graph.h
	$(CC) -c $(CFLAGS) main.c

Graph.o: Graph.c Graph.h q3.c
	$(CC) -c $(CFLAGS) Graph.c

clean:
	rm -f exe Graph.o main.o tmp core
