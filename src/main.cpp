#include "beto/calls.h"

#include <array>
#include <cstddef>
#include <span>
#include <string_view>
#include <numeric>


void print(char c) {
    low::print_char(c);
}

void print(std::string_view str) {
    low::write(1, str.data(), str.size());
}


int main(int argc, char* argv[]) {
    print(argv[0]);
    print('\n');

    return 0;
}

