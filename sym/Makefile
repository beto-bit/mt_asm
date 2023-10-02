CC := gcc
CFLAGS := -std=c11 -O2 -g -Wall -Wextra -pedantic

OBJS := strlen.o memchr.o memcmp.o

libsym.a: ${OBJS}
	ar rcs $@ $^

.PHONY: clean
clean:
	rm -f libsym.a ${OBJS}
