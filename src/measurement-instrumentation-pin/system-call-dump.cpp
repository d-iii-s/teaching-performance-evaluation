#include <pin.H>

#include <iostream>

unsigned int calls = 0;

void display_call (THREADID thread, CONTEXT *context, SYSCALL_STANDARD standard, VOID *val) {

    LOG (decstr (PIN_GetSyscallNumber (context, standard)) + "\n");

    // Stop this after some number of system calls.
    if (++ calls > 100)
    {
        PIN_Detach ();
    }
}

int main (int argc, char *argv []) {
    PIN_Init (argc, argv);
    PIN_AddSyscallEntryFunction (display_call, NULL);
    PIN_StartProgram ();

    return (0);
}
