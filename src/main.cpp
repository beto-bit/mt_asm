#include <span>

#include "math/util.hpp"
#include "fmt/print.hpp"

struct Shitty {};

void print_members(std::span<const char> spn) {
    for (char c : spn) {
        print(c);
        print(',');
    }
    print('\n');
}

int main() {
    constexpr auto dec_fmt = format_num<DEC>(-69420);
    constexpr auto hex_fmt = format_num<HEX>(0xaaaabbbbccccdddd);

    print_members(dec_fmt);
    print_members(hex_fmt);

    // print(dec_fmt);

    return 0;
}

