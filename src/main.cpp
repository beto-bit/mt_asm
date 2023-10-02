#include <span>

#include "math/util.hpp"
#include "fmt/print.hpp"

int main() {
    printfmt<DEC>("", -69);
    printfmt<HEX>("", 0x13420);

    return 0;
}

