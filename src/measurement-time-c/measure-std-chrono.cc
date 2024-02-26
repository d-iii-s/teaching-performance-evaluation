#include <chrono>
#include <iostream>


#define CYCLES 1000000

std::chrono::steady_clock::time_point clock_array [CYCLES];


int main (void) {
    std::cout << "index,time" << std::endl;
    for (int i = 0 ; i < CYCLES ; i ++) clock_array [i] = std::chrono::steady_clock::now ();
    long base = clock_array [0].time_since_epoch ().count ();
    for (int i = 0 ; i < CYCLES ; i ++) std::cout << i << "," << clock_array [i].time_since_epoch ().count () - base << std::endl;
    return (0);
}
