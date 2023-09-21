#include <stddef.h>

#include "calls.h"
#include "mem/flags.h"
#include "fmt/print.h"

#include "errno.h"

#define STACK_SIZE 1024 * 1000  // 1 MB

int main(void) {
    void *stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    int ret = munmap(stack, STACK_SIZE);

    format_num(ret, DEC);
    print_char('\n');

    return 0;
}
