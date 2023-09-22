#include <stddef.h>
#include <stdint.h>

#include "fmt/print.h"
#include "thr/thread.h"


#define NO_THREADS 10
int count = 0;


int f(void *arg) {
    int* inc = (int*) arg;

    for (int i = 0; i < 1000000; ++i) {
        count += *inc;
    }

    return 0;
}


int main(void) {
    struct Thread thrd[NO_THREADS];

    int inc = 10;

    // Create threads
    for (size_t i = 0; i < NO_THREADS; ++i)
        create_thread(thrd + i, f, &inc);

    // Wait for threads
    for (size_t i = 0; i < NO_THREADS; ++i)
        clean_thread(thrd + i);

    print_str("Total count: ");
    format_num(count, DEC);
    print_char('\n');

    return 0;
}
