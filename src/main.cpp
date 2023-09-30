#include "fmt/print.hpp"
#include <cstddef>

int main() {
    int* ptr = new int[100];

    for (size_t i = 0; i < 100; ++i) {
        ptr[i] = i + 1;
    }

    int sum = 0;
    for (size_t i = 0; i < 100; ++i) {
        sum += ptr[i];
    }

    printfmt<DEC>("Num is: {}\n", sum);

    delete[] ptr;

    return 0;
}

