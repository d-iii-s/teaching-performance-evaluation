#include <stdlib.h>

#define SIZE 123

int main (void) {

    // Allocate an array on heap.
    int *array = (int *) malloc (sizeof (int) * SIZE);

    // Release the array.
    free (array);

    // Write into released array.
    array [0] = 0;
}
