#include "sync/time.hpp"
#include "unlibc++/calls.hpp"

constexpr int MAX_NANOS = 999999999;


namespace syncs {


int sleep(float sec) {
    long nanos = (sec - (int) sec) * 1000 * 1000 * 1000;

    const low::own_timespec req {
        .tv_sec = static_cast<time_t>(sec),
        .tv_nsec = nanos
    };

    return low::own_nanosleep(&req, nullptr);
}


int sleep_seconds(long sec) {
    const low::own_timespec req {
        .tv_sec = sec,
        .tv_nsec = 0
    };

    return low::own_nanosleep(&req, nullptr);
}

int sleep_millis(long millis) {
    long nanos = millis * (1000 * 1000);
    long seconds = 0;

    // Clamp the value and add that to seconds
    while (nanos > MAX_NANOS) {
        nanos -= (1000 * 1000 * 1000);
        seconds += 1;
    }

    const low::own_timespec req {
        .tv_sec = seconds,
        .tv_nsec = nanos
    };

    return low::own_nanosleep(&req, nullptr);
}

int sleep_micros(long micros) {
    long nanos = micros * 1000;
    long seconds = 0;

    // Clamp the value
    while (nanos > MAX_NANOS) {
        nanos -= (1000 * 1000 * 1000);
        seconds += 1;
    }

    const low::own_timespec req {
        .tv_sec = seconds,
        .tv_nsec = nanos
    };

    return low::own_nanosleep(&req, nullptr);
}

int sleep_nanos(long nanos) {
    long seconds = 0;

    // Clamp the value
    while (nanos > MAX_NANOS) {
        nanos -= (1000 * 1000 * 1000);
        seconds += 1;
    }

    const low::own_timespec req {
        .tv_sec = seconds,
        .tv_nsec = nanos
    };

    return low::own_nanosleep(&req, nullptr);
}

} // namespace syncs
