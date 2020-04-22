#include <stdlib.h>

#define SIZE 123

int main (void) {

    // Allocate an array on heap.
    int *array = (int *) malloc (sizeof (int) * SIZE);

    // Release the array immediately.
    free (array);

    // Release the array again.
    free (array);
}
