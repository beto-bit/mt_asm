#include "fmt/print.hpp"
#include "sync/time.hpp"

int main() {
    printfmt<DEC>("Well, this works about {} percent of the time\n", 95);

    sync::sleep(2.5);

    return 0;
}

