export LC_ALL = cs_CZ.utf8
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
LDLIBS = -lm

all: no-comment clean
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: test.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
	./test

no-comment: no-comment.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

run: all
	./no-comment no-comment.c

clean:
	rm -f *.o test

.PHONY: all run clean