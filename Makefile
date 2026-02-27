export LC_ALL = cs_CZ.utf8
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
LDLIBS = -lm

all: no-comment primes clean

test: test.o error.o eratosthenes.o
	$(CC) $(CFLAGS) -DUSE_INLINE -DNO_CHECK -o  $@ $^ $(LDLIBS)
	./test

primes: primes.o eratosthenes.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

no-comment: no-comment.o error.o
	$(CC) $(CFLAGS) -o $@ $^

run: all
	./no-comment no-comment.c

clean:
	rm -f *.o test out.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all run clean test