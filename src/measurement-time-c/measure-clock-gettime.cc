#include <time.h>
#include <iostream>


#define CYCLES 1000000

struct timespec clock_array [CYCLES];


int main (void) {
    std::cout << "index,time" << std::endl;
    for (int i = 0 ; i < CYCLES ; i ++) clock_gettime (CLOCK_MONOTONIC_RAW, &clock_array [i]);
    long base = clock_array [0].tv_sec * 1000000000ull + clock_array [0].tv_nsec;
    for (int i = 0 ; i < CYCLES ; i ++) std::cout << i << "," << clock_array [i].tv_sec * 1000000000ull + clock_array [i].tv_nsec - base << std::endl;
    return (0);
}
