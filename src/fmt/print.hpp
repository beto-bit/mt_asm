#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <string_view>
#include <type_traits>

// Basic printing
void print(char c);
void print(std::string_view str);

// Formatting
constexpr char num_to_hex(std::integral auto num) {
    if (num > 15) return '?';

    if (num < 10) {
        return num + '0';
    } else {
        return num + 'A' - 10;
    }
}


// Why do I do this
struct DEC;
struct HEX;

template<typename T>
requires std::is_same_v<T, DEC> || std::is_same_v<T, HEX>
// If DEC size is 20
// If HEX size is 16
std::array<int, std::is_same_v<T, DEC> ? 2 : 1>
killme() {
    if constexpr (std::is_same_v<T, DEC>) {
        return {0, 1};
    }
    else {
        return {5};
    }
}
