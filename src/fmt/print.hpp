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
struct DEC {
    static constexpr size_t size = 20;
};

struct HEX {
    static constexpr size_t size = 16;
};

/// Returns an array of characters depending on the specified
/// format type.
/// The array is of size 20 if DEC, 16 if HEX
template<typename T>
requires std::is_same_v<T, DEC> || std::is_same_v<T, HEX>
std::array<int, T::size>
killme() {
    if constexpr (std::is_same_v<T, DEC>) {
        return {0, 1};
    }
    else {
        return {5};
    }
}
