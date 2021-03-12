#include <cstdlib>
#include <iomanip>
#include <iostream>

#include <time.h>

#include "shared.h"


void display_results (long long results [6]) {
    std::cout
        << " Clock " << std::setw (10) << results [0]
        << " Ins " << std::setw (10) << results [1]
        << " ILD " << std::setw (10) << results [2]
        << " IST " << std::setw (10) << results [3]
        << " L1DM " << std::setw (10) << results [4]
        << " L1IM " << std::setw (10) << results [5]
        << std::endl;
}


int main (void) {

    // Initialize the library.
    PAPI_library_init (PAPI_VER_CURRENT);

    // Create set of events to count.
    int events = PAPI_NULL;
    checked (PAPI_create_eventset (&events));
    checked (PAPI_add_event (events, PAPI_TOT_CYC));
    checked (PAPI_add_event (events, PAPI_TOT_INS));
    checked (PAPI_add_event (events, PAPI_LD_INS));
    checked (PAPI_add_event (events, PAPI_SR_INS));
    checked (PAPI_add_event (events, PAPI_L1_DCM));
    checked (PAPI_add_event (events, PAPI_L1_ICM));

    // Empty warm up measurement.
    long long warmup [6];
    struct timespec warmup_time;
    checked (PAPI_start (events));
    clock_gettime (CLOCK_MONOTONIC_RAW, &warmup_time);
    checked (PAPI_stop (events, warmup));

    // Estimate overheads.
    long long overheads [6];
    checked (PAPI_start (events));
    checked (PAPI_stop (events, overheads));

    // Measure single call.
    long long single [6];
    struct timespec single_time;
    checked (PAPI_start (events));
    clock_gettime (CLOCK_MONOTONIC_RAW, &single_time);
    checked (PAPI_stop (events, single));

    // Measure multiple calls.
    long long multiple [6];
    struct timespec multiple_time;
    checked (PAPI_start (events));
    for (int i = 0 ; i < 1000 ; i ++) clock_gettime (CLOCK_MONOTONIC_RAW, &multiple_time);
    checked (PAPI_stop (events, multiple));

    // Display the results.
    std::cout << "Warm up        - "; display_results (warmup);
    std::cout << "Overheads      - "; display_results (overheads);
    std::cout << "Single call    - "; display_results (single);
    std::cout << "Multiple calls - "; display_results (multiple);

    checked (PAPI_cleanup_eventset (events));
    checked (PAPI_destroy_eventset (&events));

    PAPI_shutdown ();

    return (0);
}
