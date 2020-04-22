#include <stdlib.h>

#define SIZE 123

int main (void) {

    // Allocate an array on stack.
    int array [SIZE];

    // Release the array.
    free (array);
}
