MAKEFLAGS := -j $(shell nproc)

TARGET := main
BUILD_DIR := build
INCLUDE_DIR := include

C_SRCS := src/main.c \
		  src/utils/utils.c src/utils/string.c \
		  src/fmt/print.c \
		  src/sync/thread.c \
		  src/mem/buffering.c \
		  src/time/time.c

AS_SRCS := src/start.s src/low/calls.s src/low/utils.s

C_OBJS := $(C_SRCS:%.c=${BUILD_DIR}/%.o)
AS_OBJS := $(AS_SRCS:%.s=${BUILD_DIR}/%.s.o)
DEPS := $(C_SRCS:%.c=${BUILD_DIR}/%.d)

AS := aarch64-linux-gnu-as
ASFLAGS := -g

CC := aarch64-linux-gnu-gcc
CFLAGS := -O2 -g -std=c23 -ffreestanding -nostdlib -fno-stack-protector \
		  -I ${INCLUDE_DIR} \
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

${BUILD_DIR}/%.s.o: %.s
	@ mkdir -p $(dir $@)
	@ echo "Compiling $<"
	@ ${AS} ${ASFLAGS} $< -o $@

compile_flags.txt: Makefile
	@ echo ${CFLAGS} | tr ' ' '\n' > $@

.PHONY: run
run: main
	@ qemu-aarch64-static ./main

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
