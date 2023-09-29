#pragma once

#include <concepts>
#include <cstdint>
#include <type_traits>

namespace math
{

template <std::integral T>
constexpr std::make_unsigned_t<T> abs(T num) {
    return (num >= 0) ? num : -num;
}

constexpr std::uint8_t integer_log(
    std::unsigned_integral auto num,
    std::unsigned_integral auto base
) {
    std::uint8_t result = 1;

    while (num >= base) {
        num /= base;
        ++result;
    }

    return result;
}

constexpr std::signed_integral auto
integer_pow(
    std::signed_integral auto base,
    std::uint8_t exponent
) {
    auto result = base;

    for (; exponent > 1; --exponent)
        result *= base;

    return result;
}

} // namespace math
