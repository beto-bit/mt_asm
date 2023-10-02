#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string_view>


constexpr bool is_dec_digit(char c) {
    return (c >= '0') && (c <= '9');
}

constexpr bool is_hex_digit(char c) {
    return (c >= 'A') && (c <= 'F');
}

constexpr std::uint8_t char_to_digit(char c) {
    if (is_dec_digit(c))
        return c - '0';
    else if (is_hex_digit(c))
        return c - 'A' + 10;

    return -1;
}


constexpr std::optional<int> str_to_int(std::string_view str) {
    [[unlikely]]
    if (str.starts_with("0x"))
    {
        int count = 0;

        // Ignore first two digits
        for (size_t idx = 2; idx < str.size(); ++idx) {
            char ch = str[idx];

            // If char is not hex
            if (!(is_dec_digit(ch) || is_hex_digit(ch)))
                return std::nullopt;

            count = count * 16 + char_to_digit(ch);
        }

        return count;
    }


    // Not hex path
    bool is_negative = str.starts_with('-');

    int count = 0;

    // Ignore the first digit if negative
    for (size_t idx = is_negative; idx < str.size(); ++idx) {
        char ch = str[idx];

        if (!is_dec_digit(ch))
            return std::nullopt;

        count = count * 10 + char_to_digit(ch);
    }

    return is_negative ? -count : count;
}
