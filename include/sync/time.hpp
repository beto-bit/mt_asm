#pragma once

namespace syn {


/// Sleeps for the given ammount of seconds
int sleep(float sec);

/// Sleeps for the given ammount of seconds (integer version)
int sleep_seconds(long sec);

/// Sleeps for the given ammount of millis
int sleep_millis(long millis);

/// Sleeps for the given ammount of micros
int sleep_micros(long micros);

/// Sleeps for the given ammount of nanos
int sleep_nanos(long nanos);


} // namespace syncs
