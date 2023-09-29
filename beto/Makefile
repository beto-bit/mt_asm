TARGET := libbeto.a
BUILD_DIR := build

AS_SRCS := src/start.asm src/low/calls.asm src/low/utils.asm
OBJS := $(AS_SRCS:%.asm=${BUILD_DIR}/%.asm.o) ${BUILD_DIR}/entry.o

AS := nasm
ASFLAGS := -f elf64 -g

CXX := g++
CXXFLAGS := -O2 -g -std=c++20 -ffreestanding -nostdlib \
			-Wall -Wextra -pedantic

CXX_ENTRY := src/entry.cpp

${TARGET}: ${OBJS}
	@ echo "Archiving into $@..."
	@ ar rcs $@ $^

${BUILD_DIR}/entry.o: ${CXX_ENTRY}
	@ echo "Compiling $<"
	@ ${CXX} ${CXXFLAGS} -c $< -o $@

${BUILD_DIR}/%.asm.o: %.asm
	@ mkdir -p $(dir $@)
	@ echo "Assembling $<"
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
	@echo ${OBJS}
	@echo ${DEPS}
