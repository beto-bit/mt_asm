#include "fmt/print.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    printfmt<DEC>("Hi mum. My magic number is: {}\n", 42);
    return 0;
}
