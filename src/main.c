#include <stddef.h>
#include <stdint.h>

#include "calls.h"
#include "mem/flags.h"
#include "fmt/print.h"

#include "errno.h"

#define STACK_SIZE 1024 * 1024  // 1 MB

int f(void *arg) {
    print_str("Hi from child!\n");
    return 0;
}

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

    int tid = bare_clone2(FLAGS, (uint8_t*)stack + STACK_SIZE, f, NULL);

    print_str("Child's TID: ");
    format_num(tid, DEC);
    print_char('\n');

    // Doesn't work quite yet because we don't have ways of waiting the thread
    // munmap(stack, STACK_SIZE);

    return 0;
}
