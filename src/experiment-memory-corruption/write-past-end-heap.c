#include <stdlib.h>

#define SIZE 123

int main (void) {

    // Allocate an array on heap.
    int *array = (int *) malloc (sizeof (int) * SIZE);

    // Write just past the end of the array.
    array [SIZE] = 0;

    // Release the array.
    free (array);
}
