#include <cstddef>
#include <span>
#include <string_view>

#include "fmt/print.hpp"
#include "sync/thread.hpp"

int foo(int num);

int main(std::span<std::string_view> args) {
    syn::SimThread thrd{ foo, 9 };

    return 0;
}
