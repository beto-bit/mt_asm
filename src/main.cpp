#include <span>
#include <string_view>

#include "fmt/print.hpp"

int main(std::span<const std::string_view> args) {

    for (auto str : args) {
        println(str);
    }

    return 0;
}
