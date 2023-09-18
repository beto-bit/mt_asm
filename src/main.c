#include "calls.h"
#include "fmt/print.h"

void _start(void) {
    print_str("Hola mamá\n");

    char val = num_to_hex(10);
    print_char(val);
    print_char('\n');

    exit(0);
}
