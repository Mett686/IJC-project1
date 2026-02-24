export LC_ALL = cs_CZ.utf8
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
LDLIBS = -lm

all: test clean
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: test.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

no-comment: no-comment.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

run: all
	./test

clean:
	rm -f *.o

.PHONY: all run clean