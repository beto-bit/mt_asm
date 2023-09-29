#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <type_traits>

#include "math/util.hpp"


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

template<typename T>
concept is_format_kind = std::is_same_v<T, DEC> || std::is_same_v<T, HEX>;


/// Returns the number of digits of a number
/// In the case of DEC, includes the '-' sign.
template<typename T>
requires is_format_kind<T>
constexpr std::uint8_t no_digits(std::integral auto num) {
    if constexpr (std::is_same_v<T, DEC>)
    {
        const bool is_negative = (num < 0) ? true : false;
        const std::uint8_t digits = math::integer_log(math::abs(num), 10u);

        return digits + is_negative;
    }
    else {
        return math::integer_log(math::abs(num), 16u);
    }
}

/// Returns an array of characters depending on the specified
/// format type.
/// The array is of size 20 if DEC, 16 if HEX
template<typename T>
requires is_format_kind<T>
constexpr std::array<char, T::size>
format_num(std::integral auto num)
{
    if constexpr (std::is_same_v<T, DEC>)
    {
        std::array<char, 20> buff{};
        const bool is_negative = (num < 0) ? true : false;

        // Reverse enter characters in the buffer
        size_t index = no_digits<DEC>(num) - 1;
        num = math::abs(num);

        while (true) {
            auto div = num / 10;
            auto mod = num % 10;

            buff[index] = num_to_hex(mod);

            if (!div) break;

            --index;
            num = div;
        }

        if (is_negative)
            buff[--index] = '-';

        return buff;
    }
    else
    {
        std::array<char, 16> buff{};

        size_t index = no_digits<HEX>(num) - 1;

        while (true) {
            auto div = num / 16;
            auto mod = num % 16;

            buff[index] = num_to_hex(mod);

            if (!div) break;

            --index;
            num = div;
        }

        return buff;
    }
}

