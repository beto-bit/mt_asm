#include <stddef.h>
#include <stdint.h>

#include "fmt/print.h"
#include "thr/thread.h"

int f(void *arg) {
    print_str("I'm running from another thread!\n");
    return 0;
}


int main(void) {
    struct Thread thrd;

    create_thread(&thrd, f, NULL);

    print_str("Thread ID: ");
    format_num(thrd.tid, DEC);
    print_char('\n');

    clean_thread(&thrd);

    return 0;
}
