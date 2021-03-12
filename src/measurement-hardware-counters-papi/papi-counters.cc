#include <cstdlib>
#include <iostream>

#include "shared.h"


int main (void) {

    // Initialize the library.
    PAPI_library_init (PAPI_VER_CURRENT);

    // Create set of events to count.
    int events = PAPI_NULL;
    checked (PAPI_create_eventset (&events));
    checked (PAPI_add_event (events, PAPI_TOT_INS));
    checked (PAPI_add_event (events, PAPI_TOT_CYC));

    // Measure some code.
    long long values [2];
    checked (PAPI_start (events));

    volatile int x;
    for (int i = 0 ; i < 1000000000 ; i ++) x = x + i;

    checked (PAPI_stop (events, values));

    // Display the results.
    std::cout << "Total instructions " << values [0] << std::endl;
    std::cout << "Total cycles " << values [1] << std::endl;
    std::cout << "IPC " << ((double) values [0] / (double) values [1]) << std::endl;

    checked (PAPI_cleanup_eventset (events));
    checked (PAPI_destroy_eventset (&events));

    PAPI_shutdown ();

    return (0);
}
