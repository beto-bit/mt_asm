OUTPUT := symbols.o

CC := gcc
CFLAGS := -O2 -g

OBJS := memcmp.o memcpy.o memmove.o memset.o strlen.o

${OUTPUT}: ${OBJS}
	ld -r $^ -o $@

.PHONY: clean
clean:
	rm ${OUTPUT} ${OBJS}
