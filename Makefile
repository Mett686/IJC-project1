export LC_ALL = cs_CZ.utf8
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
LDLIBS = -lm
xlogin = xknotem00

all: primes primes-i no-comment

run:
	ulimit -s unlimited && ./primes
	ulimit -s unlimited && ./primes-i

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

primes-i: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -DUSE_INLINE -o $@ $^ $(LDLIBS)

no-comment: no-comment.o error.o
	$(CC) $(CFLAGS) -D_POSIX_C_SOURCE -o $@ $^

clean:
	rm -f *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

zip:
	zip $(xlogin).zip *.c *.h Makefile

.PHONY: all run clean