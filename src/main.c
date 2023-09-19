#include "calls.h"
#include "fmt/print.h"
#include "utils.h"

void _start(void) {
    print_str("Hola mamá\n");

    print_char(num_to_hex(log(69420, 4)));
    print_char('\n');


    exit(0);
}
