#include <cstddef>
#include <span>
#include <string_view>

#include "fmt/print.hpp"
#include "sync/thread.hpp"


int foo(int num) {
    return num * num;
}

int juan(void) {
    return 69;
}

int main(std::span<std::string_view> args) {

    return 0;
}
