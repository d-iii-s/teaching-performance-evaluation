#include <cstdlib>
#include <iostream>

#include "shared.h"


int main (void) {

    // Initialize the library.
    PAPI_library_init (PAPI_VER_CURRENT);
    checked (PAPI_multiplex_init ());

    // Create set of events to count.
    int events = PAPI_NULL;
    checked (PAPI_create_eventset (&events));
    checked (PAPI_assign_eventset_component (events, 0));
    checked (PAPI_set_multiplex (events));
    checked (PAPI_add_event (events, PAPI_TOT_INS));
    checked (PAPI_add_event (events, PAPI_TOT_CYC));
    int event;
    checked (PAPI_event_name_to_code ("RESOURCE_STALLS:ANY", &event));
    checked (PAPI_add_event (events, event));
    checked (PAPI_event_name_to_code ("HW_INTERRUPTS:RECEIVED", &event));
    checked (PAPI_add_event (events, event));
    checked (PAPI_event_name_to_code ("BR_INST_RETIRED", &event));
    checked (PAPI_add_event (events, event));
    checked (PAPI_event_name_to_code ("BR_INST_RETIRED:CONDITIONAL", &event));
    checked (PAPI_add_event (events, event));

    // Measure some code.
    long long values [6];
    checked (PAPI_start (events));

    volatile int x;
    for (int i = 0 ; i < 1000000000 ; i ++) x = x + i;

    checked (PAPI_stop (events, values));

    // Display the results.
    std::cout << "Total instructions " << values [0] << std::endl;
    std::cout << "Total cycles " << values [1] << std::endl;
    std::cout << "Resource stalls " << values [2] << std::endl;
    std::cout << "Interrupts " << values [3] << std::endl;
    std::cout << "Branches retired " << values [4] << std::endl;
    std::cout << "Branches retired conditional " << values [5] << std::endl;

    checked (PAPI_cleanup_eventset (events));
    checked (PAPI_destroy_eventset (&events));

    PAPI_shutdown ();

    return (0);
}
