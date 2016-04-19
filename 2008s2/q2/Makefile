# COMP1927 08s2 Exam

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-g

exe: main.o List.o
	$(CC) $(LDFLAGS) -o exe List.o main.o

main.o: main.c List.h
	$(CC) -c $(CFLAGS) main.c

List.o: List.c List.h q2.c
	$(CC) -c $(CFLAGS) List.c

clean:
	rm -f exe List.o main.o tmp core
