TARGET := main
BUILD_DIR := build
INCLUDE_DIR := include

SRCS := src/main.cpp \
		src/fmt/print.cpp

OBJS := $(SRCS:%.cpp=${BUILD_DIR}/%.o)
DEPS := $(SRCS:%.cpp=${BUILD_DIR}/%.d)

CXX := g++
CXXFLAGS := -O2 -g -std=c++20 -ffreestanding -nostdlib -fno-exceptions -fno-rtti \
			-I ${INCLUDE_DIR} \
			-I. -Lbeto -lbeto \
			-Lsym -lsym \
		    -Wall -Wextra -pedantic -Warray-bounds \
		    -Wdeprecated -Wcast-qual \
		    -Wundef -Wunused -Wshadow \
		    -Wdouble-promotion -Wfloat-equal \
		    -MP -MD

${TARGET}: ${OBJS} beto/libbeto.a sym/libsym.a
	@ echo "Linking..."
	@ ld $^ -o $@

${BUILD_DIR}/%.o: %.cpp
	@ mkdir -p $(dir $@)
	@ echo "Compiling $<"
	@ ${CXX} ${CXXFLAGS} $< -c -o $@

beto/libbeto.a:
	${MAKE} -C beto

sym/libsym.a:
	${MAKE} -C sym

compile_flags.txt: Makefile
	@ echo ${CXXFLAGS} | tr ' ' '\n' > $@

.PHONY: run
run: main
	@ ./main

.PHONY: clean
clean:
	rm -rf ${TARGET} ${BUILD_DIR}

.PHONY: test
test:
	@echo ${SRCS}
	@echo ${AS_SRCS}
	@echo ${OBJS}
	@echo ${AS_OBJS}
	@echo ${DEPS}

-include ${DEPS}
