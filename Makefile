TARGET := main
BUILD_DIR := build
INCLUDE_DIR := include

LIB := beto
LIB_DIR := beto

SRCS := src/main.cpp

OBJS := $(SRCS:%.cpp=${BUILD_DIR}/%.o)
DEPS := $(SRCS:%.cpp=${BUILD_DIR}/%.d)

CXX := g++
CXXFLAGS := -O2 -g -std=c++20 -ffreestanding -nostdlib \
			-I ${INCLUDE_DIR} \
			-I. -L ${LIB_DIR} -l ${LIB} \
		    -Wall -Wextra -pedantic -Warray-bounds \
		    -Wdeprecated -Wcast-qual \
		    -Wundef -Wunused -Wshadow \
		    -Wdouble-promotion -Wfloat-equal \
		    -MP -MD

${TARGET}: ${OBJS} ${LIB_DIR}/lib${LIB}.a
	@ echo "Linking..."
	@ ld $^ -o $@

${BUILD_DIR}/%.o: %.cpp
	@ mkdir -p $(dir $@)
	@ echo "Compiling $<"
	@ ${CXX} ${CXXFLAGS} $< -c -o $@


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
