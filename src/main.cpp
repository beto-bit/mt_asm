#include <cstddef>
#include <span>
#include <string_view>

#include "fmt/print.hpp"
#include "sync/thread.hpp"
#include "sync/time.hpp"

int foo(int num) {
    printfmt<DEC>("From another thread: {}\n", num);
    syn::sleep(0.5);

    return 0;
}

int main(std::span<std::string_view> args) {
    syn::SimThread thrd{ foo,42 };
    
    printfmt<DEC>("TID: {}\n", thrd.get_tid());

    thrd.join();

    return 0;
}
