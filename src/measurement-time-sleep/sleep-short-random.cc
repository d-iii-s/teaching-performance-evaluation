#include <time.h>
#include <stdlib.h>

#include <iostream>

volatile int x = 0;

unsigned long long time (void) {
    struct timespec sClock;
    clock_gettime (CLOCK_MONOTONIC, &sClock);
    return (sClock.tv_sec * 1000000000ull + sClock.tv_nsec);
};

int main (void) {
    std::cout << "sleep,time" << std::endl;

    for (int iSleep = 0 ; iSleep < 1000 ; iSleep ++) {
        for (int iRepeat = 0 ; iRepeat < 10 ; iRepeat ++) {
            x = rand () & 65535;
            while (x) x --;

            struct timespec sSleep;
            sSleep.tv_sec = 0;
            sSleep.tv_nsec = iSleep;

            unsigned long long iTimeBefore = time ();
            nanosleep (&sSleep, NULL);
            unsigned long long iTimeAfter = time ();

            std::cout << iSleep << "," << (iTimeAfter - iTimeBefore) << std::endl;
        }
    }

    return (0);
};
