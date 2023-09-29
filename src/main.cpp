#include <cmath>
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
    constexpr auto res2 = math::integer_log(0x1ffu, 16u);
    constexpr auto res1 = math::integer_log(999u, 10u);
    constexpr auto res = no_digits<DEC>(-100);
    // constexpr auto res6 = no_digits<HEX>(0xabcd);

    constexpr auto dec_fmt = format_num<DEC>(99);
    constexpr auto hex_fmt = format_num<HEX>(0xaaaabbbbccccdddd);

    print_members(dec_fmt);
    print_members(hex_fmt);

    return 0;
}

