#include "low/calls.h"
#include "time.h"


#define MAX_NANOS 999999999


int sleep(float sec) {
    long nanos = (sec - (int) sec) * 1000 * 1000 * 1000;

    return nanosleep(
        &(struct timespec) {
            .tv_sec = sec,
            .tv_nsec = nanos
        },
        NULL
    );
}

int sleep_seconds(long sec) {
    return nanosleep(
        &(struct timespec) {
            .tv_sec = sec,
            .tv_nsec = 0
        },
        NULL
    );
}

int sleep_millis(long millis) {
    long nanos = millis * (1000 * 1000);
    long seconds = 0;

    // Clamp the value and add that to seconds
    while (nanos > MAX_NANOS) {
        nanos -= (1000 * 1000 * 1000);
        seconds += 1;
    }

    return nanosleep(
        &(struct timespec) {
            .tv_sec = seconds,
            .tv_nsec = nanos
        },
        NULL
    );
}

int sleep_micros(long micros) {
    long nanos = micros * 1000;
    long seconds = 0;

    // Clamp the value
    while (nanos > MAX_NANOS) {
        nanos -= (1000 * 1000 * 1000);
        seconds += 1;
    }

    return nanosleep(
        &(struct timespec) {
            .tv_sec = seconds,
            .tv_nsec = nanos
        },
        NULL
    );
}

int sleep_nanos(long nanos) {
    long seconds = 0;

    // Clamp the value
    while (nanos > MAX_NANOS) {
        nanos -= (1000 * 1000 * 1000);
        seconds += 1;
    }

    return nanosleep(
        &(struct timespec) {
            .tv_sec = seconds,
            .tv_nsec = nanos
        },
        NULL
    );
}
