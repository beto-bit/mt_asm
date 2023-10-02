#pragma once

#include <concepts>
#include <string_view>

#include "fmt/fmt.hpp"

// Basic printing
void print(char c);
void print(std::string_view str);
void println(std::string_view str);

/// Formatted printing (with strings)
void printfmt(std::string_view str, std::string_view fmt_str);

/// Formatted printing
template<typename T>
requires is_format_kind<T>
void printfmt(std::string_view str, std::integral auto num)
{
    const auto fmt_arr = format_num<T>(num);
    const auto fmt_str = string_from_span(fmt_arr);

    printfmt(str, fmt_str);
}

