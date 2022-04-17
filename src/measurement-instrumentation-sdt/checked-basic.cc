#include <sys/sdt.h>

#include <iostream>

#ifndef N
    // By default consider about 150 million numbers.
    #define N (1 << 27)
#endif

bool can_be_prime[N];

int main () {

    STAP_PROBE (primes, init);

    // Mark all numbers as potentially prime.
    for (int i = 2; i < N; i++) {
        can_be_prime [i] = true;
    }

    int primes = 0;

    // Check numbers from smallest to largest.
    for (int i = 2 ; i < N ; i++) {
        // Any number that is still marked
        // as potentially prime is prime.
        if (can_be_prime [i]) {
            STAP_PROBE1 (primes, found, i);
            primes ++;
            // All multiples of any prime are not prime.
            for (int j = 2 * i ; j < N ; j += i) {
                if (can_be_prime [j]) {
                    STAP_PROBE1 (primes, discarded, j);
                    can_be_prime [j] = false;
                }
            }
        }
    }

    STAP_PROBE1 (primes, counted, primes);

    std::cout << "Counted " << primes << " primes from " << 2 << " to " << N << "." << std::endl;

    return (0);
}
