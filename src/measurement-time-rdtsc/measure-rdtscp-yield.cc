#include <stdint.h>
#include <pthread.h>

#include <iostream>


#define CYCLES 1000000

uint64_t clock_array [CYCLES];
uint32_t magic_array [CYCLES];


inline void rdtscp (uint64_t *clock, uint32_t *magic) {
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtscp" : "=a" (lo), "=d" (hi), "=c" (*magic) : : );
    (*clock) = (uint64_t) hi << 32 | (uint64_t) lo;
}


int main (void) {
    std::cout << "index,time,magic" << std::endl;
    for (int i = 0 ; i < CYCLES ; i ++) {
        pthread_yield ();
        rdtscp (&clock_array [i], &magic_array [i]);
    }
    for (int i = 0 ; i < CYCLES ; i ++) std::cout << i << "," << clock_array [i] << "," << magic_array [i] << std::endl;
}
