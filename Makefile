TARGET := main
BUILD_DIR := build
INCLUDE_DIR := include

LIB_DIR := unlibc++/include

SRCS := src/main.cpp \
		src/fmt/print.cpp \
		src/mem/alloc.cpp \
		src/sync/time.cpp

OBJS := $(SRCS:%.cpp=${BUILD_DIR}/%.o)
DEPS := $(SRCS:%.cpp=${BUILD_DIR}/%.d)

CXX := clang++
CXXFLAGS := -O0 -g3 -std=c++20 \
			-ffreestanding -nostdlib \
			-flto -static \
			-fno-exceptions -fno-rtti \
			-I ${INCLUDE_DIR} \
			-I ${LIB_DIR} \
		    -Wall -Wextra -pedantic -Warray-bounds \
		    -Wdeprecated -Wcast-qual \
		    -Wundef -Wunused -Wshadow \
		    -Wdouble-promotion -Wfloat-equal \
		    -MP -MD


${TARGET}: ${OBJS} unlibc++/libunlibc++.a
	@ echo "Linking..."
	@ ${CXX} ${CXXFLAGS} -L unlibc++ -l unlibc++ $^ -o $@

${BUILD_DIR}/%.o: %.cpp
	@ mkdir -p $(dir $@)
	@ echo "Compiling $<"
	@ ${CXX} ${CXXFLAGS} $< -c -o $@

unlibc++/libunlibc++.a:
	make -C unlibc++


compile_flags.txt: Makefile
	@ echo ${CXXFLAGS} | tr ' ' '\n' > $@

.PHONY: run
run: main
	@ ./main

.PHONY: clean
clean:
	rm -rf ${TARGET} ${BUILD_DIR}

-include ${DEPS}
