#include <span>
#include <string_view>

#include "fmt/string.hpp"
#include "fmt/print.hpp"

int main(std::span<std::string_view> args) {

    constexpr auto maybe_num1 = str_to_int("0x69");
    constexpr auto maybe_num2 = str_to_int("-13");
    constexpr auto maybe_num3 = str_to_int("42");

    printfmt<HEX>("{}\n", maybe_num1.value_or(0));
    printfmt<DEC>("{}\n", maybe_num2.value_or(0));
    printfmt<DEC>("{}\n", maybe_num3.value_or(0));

    return 0;
}
