export LC_ALL = cs_CZ.utf8
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
LDLIBS = -lm

all: primes primes-i no-comment
	make clean

run: all
	./primes
	./primes-i

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

primes-i: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -DUSE_INLINE -o $@ $^ $(LDLIBS)

no-comment: no-comment.o error.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all run clean