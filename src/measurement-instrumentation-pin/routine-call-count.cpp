#include <pin.H>

int call_count = 0;

void increment_count () {
    ATOMIC::OPS::Increment (&call_count, 1);
}

void instrument_routine (RTN routine, VOID *val) {
    RTN_Open (routine);
    RTN_InsertCall (routine, IPOINT_BEFORE, increment_count, IARG_END);
    RTN_Close (routine);
}

void print_results (INT32 code, VOID *val) {
    LOG ("Routine call count " + decstr (call_count) + "\n");
}

int main (int argc, char *argv []) {
    PIN_Init (argc, argv);
    RTN_AddInstrumentFunction (instrument_routine, NULL);
    PIN_AddFiniFunction (print_results, NULL);
    PIN_StartProgram ();

    return (0);
}
