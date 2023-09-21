#include <stddef.h>
#include "fmt/print.h"

int main(size_t argc, char *argv[]) {
    for (size_t idx = 0; idx < argc; ++idx) {
        print_str(argv[idx]);
        print_char('\n');
    }

    return 0;
}
