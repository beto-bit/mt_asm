#include "beto/calls.h"
#include "print.hpp"

void print(char c) {
    low::print_char(c);
}

void print(std::string_view str) {
    low::write(1, str.data(), str.length());
}

