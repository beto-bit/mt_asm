#include <atomic>
#include <cstddef>
#include <memory>
#include <span>
#include <string_view>
#include <utility>

#include "fmt/string.hpp"
#include "fmt/print.hpp"
#include "sync/thread.hpp"


std::atomic<int> atm_count = 0;
int count = 0;

int foo(const int* inc) {
    for (int i = 0; i < 10'000; ++i) {
        atm_count += *inc;
        count += *inc;
    }

    return 0;
}


using FooThread = syn::SimThread<const int*>;
using FooThreadUPtr = std::unique_ptr<FooThread>;

int main(std::span<std::string_view> args) {
    // Check arguments
    auto arg_count = args.size();

    if (arg_count < 2) {
        printfmt("Usage: {} <no_threads> <increment?>\n", args[0]);
        return 1;
    }

    const size_t no_threads = str_to_int(args[1]).value_or(0);

    // I can do this with a ternary but I like the flex
    const int increment = [&] {
        if (arg_count < 3)
            return 1;
        return str_to_int(args[2]).value_or(1);
    }();


    // Allocate array for the threads
    auto threads = std::make_unique<FooThreadUPtr[]>(no_threads);

    // Allocate each thread
    for (size_t i = 0; i < no_threads; ++i) {
        threads[i] = std::make_unique<FooThread>(
            // Lambda for the flex
            [](const int* inc) {
                return foo(inc);
            },
            &increment
        );
    }

    // Join them all
    for (size_t i = 0; i <no_threads; ++i) {
        threads[i]->join();
    }


    printfmt<DEC>("Atomic count: {}\n", atm_count.load());
    printfmt<DEC>("Non atomic count: {}\n", count);

    return 0;
}
