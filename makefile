CC=gcc
CFLAGS=-I.
DEPS = linkedList.h parser.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Lab3.out: lab3.o linkedList.o parser.o
	$(CC) -o lab3 lab3.o linkedList.o parser.o

