#include <cstdlib>
#include <iostream>

#include <time.h>

#include "shared.h"


void wait_a_tick (void) {
    long iDeadline = time (NULL) + 1;
    while (time (NULL) < iDeadline) { };
}


int main (void) {

    // Initialize the library.
    PAPI_library_init (PAPI_VER_CURRENT);

    // Create set of events to count.
    int events = PAPI_NULL;
    checked (PAPI_create_eventset (&events));
    int event;
    checked (PAPI_event_name_to_code ("UNHALTED_CORE_CYCLES", &event));
    checked (PAPI_add_event (events, event));

    // Measure one whole clock tick.
    long long values [1];
    wait_a_tick ();
    checked (PAPI_start (events));
    wait_a_tick ();
    checked (PAPI_stop (events, values));

    // Display the results.
    std::cout << "Cycles in single clock tick " << values [0] << std::endl;

    checked (PAPI_cleanup_eventset (events));
    checked (PAPI_destroy_eventset (&events));

    PAPI_shutdown ();

    return (0);
}
