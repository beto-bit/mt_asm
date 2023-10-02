#include "fmt/print.hpp"
#include <span>

struct Shitty {};

void print_members(std::span<const int> spn) {
    for (int num : spn) {
        print(num_to_hex(num));
        print(' ');
    }
    print('\n');
}

int main() {
    auto dec_fmt = killme<DEC>();
    auto hex_fmt = killme<HEX>();
    // auto juan = killme<Shitty>();

    print_members(dec_fmt);
    print_members(hex_fmt);

    // print_members(juan);
        
    return 0;
}

