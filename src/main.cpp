#include "fmt/print.hpp"

int main() {
    printfmt<DEC>("Well, this works about {} percent of the time\n", 95);
    return 0;
}

