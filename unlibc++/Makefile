TARGET := libunlibc++.a
BUILD_DIR := build

INTRINSIC_SYMBOLS := intrinsics/symbols.o

CXX_ENTRY := x86_64/entry.cpp
SRCS := x86_64/start.asm \
		x86_64/low/calls.asm \
		x86_64/low/utils.asm

OBJS := ${BUILD_DIR}/entry.o \
		${SRCS:%.asm=${BUILD_DIR}/%.asm.o}

AS := nasm
ASFLAGS := -f elf64 -g

CXX := clang++
CXXFLAGS := -std=c++20 -O2 -g \
			-ffreestanding -nostdlib -static\
			-Wall -Wextra -pedantic

${TARGET}: ${OBJS} ${INTRINSIC_SYMBOLS}
	@ echo "Archiving into $@..."
	@ ar rcs $@ $^

${BUILD_DIR}/entry.o: ${CXX_ENTRY}
	@ mkdir -p $(dir $@)
	@ echo "Compiling $<"
	@ ${CXX} ${CXXFLAGS} -c $< -o $@

${BUILD_DIR}/%.asm.o: %.asm
	@ mkdir -p $(dir $@)
	@ echo "Assembling $<"
	@ ${AS} ${ASFLAGS} $< -o $@


${INTRINSIC_SYMBOLS}:
	make -C $(dir ${INTRINSIC_SYMBOLS})


compile_flags.txt: Makefile
	@ echo ${CFLAGS} | tr ' ' '\n' > $@

.PHONY: clean
clean:
	rm -rf ${TARGET} ${BUILD_DIR}
	make -C $(dir ${INTRINSIC_SYMBOLS}) clean
