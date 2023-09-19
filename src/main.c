#include <stddef.h>
#include <stdint.h>
#include "calls.h"
#include "fmt/print.h"
#include "utils.h"

void _start(void) {
    int64_t num = 0x69420;

    format_num(num, HEX);
    print_char('\n');

    exit(0);
}
