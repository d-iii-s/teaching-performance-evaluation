#include <stdlib.h>

#define SIZE 123

int *function (void) {

    // Allocate an array on stack.
    int array [SIZE];

    // Write into the array.
    array [0] = 0;

    // Return array address.
    return (array);
}

int main (void) {

    // Allocate an array on stack.
    int *array = function ();

    // Read from the array.
    return (array [0]);
}
