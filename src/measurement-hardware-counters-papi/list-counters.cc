#include <cstring>
#include <iostream>

#include "shared.h"


// This is a poor cousin to `papi_native_avail` which is easier to integrate into scripts.


int main (void) {

    // Initialize the library.
    PAPI_library_init (PAPI_VER_CURRENT);

    // Get the first event index and iterate from that.
    int event_code = 0 | PAPI_NATIVE_MASK;
    checked (PAPI_enum_cmp_event (&event_code, PAPI_ENUM_FIRST, 0));
    do {
        PAPI_event_info_t event_info;
        memset (&event_info, 0, sizeof (event_info));
        checked (PAPI_get_event_info (event_code, &event_info));
        std::cout << event_info.symbol << std::endl;
    } while (PAPI_enum_cmp_event (&event_code, PAPI_ENUM_ALL, 0) == PAPI_OK);

    PAPI_shutdown ();

    return (0);
}
