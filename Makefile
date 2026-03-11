export LC_ALL = cs_CZ.utf8
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -MMD -MP
LDLIBS = -lm

SRCS = primes.c eratosthenes.c bitarray.c error.c
OBJS = $(SRCS:.c=.o)
TARGETS = primes primes-i no-comment

xlogin = xknotem00

all: $(TARGETS)

-include $(OBJS:.o=.d)

primes: primes.c eratosthenes.c error.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

primes-i: primes.c eratosthenes.c error.c bitarray.c
	$(CC) $(CFLAGS) -DUSE_INLINE $^ -o $@ $(LDLIBS)

no-comment: no-comment.o error.o
	$(CC) $(CFLAGS) -D_POSIX_C_SOURCE $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


run:
	ulimit -s unlimited && ./primes
	ulimit -s unlimited && ./primes-i

clean:
	rm -f *.o *.d $(TARGETS) $(xlogin).zip

zip:
	zip $(xlogin).zip *.c *.h Makefile

.PHONY: all run clean zip primes*