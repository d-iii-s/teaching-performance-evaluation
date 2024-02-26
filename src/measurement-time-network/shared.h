#include <time.h>

uint64_t get_time () {
    struct timespec clock;
    clock_gettime (CLOCK_MONOTONIC_RAW, &clock);
    return (clock.tv_sec * 1000000000ull + clock.tv_nsec);
}
