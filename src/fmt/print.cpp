#include <span>
#include <string_view>

#include "beto/calls.h"
#include "fmt/print.hpp"

void print(char c) {
    low::print_char(c);
}

void print(std::string_view str) {
    low::write(1, str.data(), str.length());
}

void printfmt(std::string_view str, std::string_view fmt_str) {
    print(fmt_str); print('\n');
}
