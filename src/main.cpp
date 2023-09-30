#include "fmt/print.hpp"
#include "sync/thread.hpp"

int foo(int arg) {
    printfmt<DEC>("This works: {}\n", arg);
    return 0;
}

int main() {
    syncs::Thread th { foo, 69 };
    th.join();

    return 0;
}

