#include <cstddef>
#include <span>
#include <string_view>

#include "beto/calls.h"
#include "fmt/print.hpp"
#include "mem/buff.hpp"

void print(char c) {
    low::print_char(c);
}

void print(std::string_view str) {
    low::write(1, str.data(), str.length());
}

void printfmt(std::string_view str, std::string_view fmt_str) {
    const auto fmt_break = str.find("{}");

    // Not formatted
    if (fmt_break == str.npos) {
        print(str);
        return;
    }

    // Lil buffer for output
    MemBuffer<256> membuff{};

    const auto first_len = fmt_break;
    const auto secnd_len = str.size() - first_len - 2;  // Take the "{}" in account

    membuff.append({ str.data(), first_len });
    membuff.append(fmt_str);
    membuff.append({ str.data() + fmt_break + 2, secnd_len });

    low::write(1, membuff.data(), membuff.written());
}
