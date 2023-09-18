BUILD_DIR := build
TARGET := main

C_SRCS := src/main.c
AS_SRCS := src/utils.asm

C_OBJS := $(C_SRCS:%.c=${BUILD_DIR}/%.o)
AS_OBJS := $(AS_SRCS:%.asm=${BUILD_DIR}/%.asm.o)
DEPS := $(C_SRCS:%.c=${BUILD_DIR}/%.d)

AS := nasm
ASFLAGS := -f elf64 -g

CC := gcc
CFLAGS := -O2 -g -std=c11 -nostdlib \
		  -Wall -Wextra -pedantic -Warray-bounds \
		  -Wdeprecated -Wcast-qual \
		  -Wundef -Wunused -Wshadow \
		  -Wdouble-promotion -Wfloat-equal \
		  -MP -MD

${TARGET}: ${C_OBJS} ${AS_OBJS}
	@ echo "Linking..."
	@ ld $^ -o $@

${BUILD_DIR}/%.o: %.c
	@ mkdir -p $(dir $@)
	@ echo "Compiling $<"
	@ ${CC} ${CFLAGS} $< -c -o $@

${BUILD_DIR}/%.asm.o: %.asm
	@ mkdir -p $(dir $@)
	@ echo "Compiling $<"
	@ ${AS} ${ASFLAGS} $< -o $@

compile_flags.txt: Makefile
	@ echo ${CFLAGS} | tr ' ' '\n' > $@

.PHONY: run
run: main
	@ ./main

.PHONY: clean
clean:
	rm -rf ${TARGET} ${BUILD_DIR}

.PHONY: test
test:
	@echo ${C_SRCS}
	@echo ${AS_SRCS}
	@echo ${C_OBJS}
	@echo ${AS_OBJS}
	@echo ${DEPS}

-include ${DEPS}
