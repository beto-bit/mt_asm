#include <cstddef>

#include "unlibc++/calls.hpp"
#include "unlibc++/memflags.h"


void* operator new(size_t size) {
    void* memory = low::mmap(
        nullptr,
        size + 8,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANON,
        -1,
        0
    );

    *(size_t*) memory = size + 8;

    return (size_t*) memory + 1;
}

void operator delete(void* ptr) {
    size_t* memory = (size_t*) ptr - 1;
    low::munmap(memory, *memory);
}


void operator delete(void* ptr, size_t size) {
    low::munmap((size_t*) ptr - 1, size + 8);
}


void* operator new[](size_t size) {
    void* memory = low::mmap(
        nullptr,
        size + 8,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANON,
        -1,
        0
    );

    *(size_t*) memory = size + 8;

    return (size_t*) memory + 1;
}

void operator delete[](void* ptr) {
    size_t* memory = (size_t*) ptr - 1;
    low::munmap(memory, *memory);
}

 void operator delete[](void* ptr, size_t size) {
     low::munmap((size_t*) ptr - 1, size + 8);
 }
