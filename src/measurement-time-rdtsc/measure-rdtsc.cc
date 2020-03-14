#include <stdint.h>
#include <iostream>


#define CYCLES 1000000

uint64_t clock_array [CYCLES];


inline uint64_t rdtsc () {
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi) : : );
    return ((uint64_t) hi << 32 | (uint64_t) lo);
}


int main (void) {
    std::cout << "index,time" << std::endl;
    for (int i = 0 ; i < CYCLES ; i ++) clock_array [i] = rdtsc ();
    for (int i = 0 ; i < CYCLES ; i ++) std::cout << i << "," << clock_array [i] << std::endl;
}
