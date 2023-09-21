#include <stddef.h>
#include <stdint.h>

#include "calls.h"
#include "mem/flags.h"
#include "fmt/print.h"

#include "errno.h"

#define STACK_SIZE 1024 * 1024  // 1 MB

const int FLAGS 
    = CLONE_VM          // Share same adress space
    | CLONE_FS          // Share file system information (i.e. where is this called)
    | CLONE_THREAD      // Make this in the same thread group (aka appear as a child thread)
    | CLONE_SIGHAND;    // Share signal handler (required by CLONE_THREAD)

int main(void) {
    void *stack = mmap(
        NULL,
        STACK_SIZE, 
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANON,
        -1,
        0
    );

    int ret = bare_clone(
        FLAGS,
        (uint8_t*) stack + STACK_SIZE,
        NULL,
        NULL,
        NULL
    );

    // Child
    if (ret == 0) {
        print_str("Hi, I'm your kid!\n");
        exit(0);
    }

    print_str("Thread created\tID: ");
    format_num(ret, DEC);
    print_char('\n');

    return 0;
}
