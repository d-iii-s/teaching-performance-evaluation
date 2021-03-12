#include <cstdlib>
#include <iostream>

#include "shared.h"


int main (void) {

    // Initialize the library.
    PAPI_library_init (PAPI_VER_CURRENT);

    // Create set of events to count.
    int events = PAPI_NULL;
    checked (PAPI_create_eventset (&events));
    int event;
    checked (PAPI_event_name_to_code ("RESOURCE_STALLS:ANY", &event));
    checked (PAPI_add_event (events, event));
    checked (PAPI_event_name_to_code ("HW_INTERRUPTS:RECEIVED", &event));
    checked (PAPI_add_event (events, event));

    // Display event information just for fun.
    PAPI_event_info_t info;
    checked (PAPI_get_event_info (event, &info));
    std::cout << info.symbol << std::endl;
    std::cout << info.short_descr << std::endl;
    std::cout << info.long_descr << std::endl;
    std::cout << info.note << std::endl;

    // Measure some code.
    long long values [2];
    checked (PAPI_start (events));

    volatile int x;
    for (int i = 0 ; i < 1000000000 ; i ++) x = x + i;

    checked (PAPI_stop (events, values));

    // Display the results.
    std::cout << "Resource stalls " << values [0] << std::endl;
    std::cout << "Interrupts " << values [1] << std::endl;

    checked (PAPI_cleanup_eventset (events));
    checked (PAPI_destroy_eventset (&events));

    PAPI_shutdown ();

    return (0);
}
