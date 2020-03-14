#include <cstdint>
#include <iostream>

#ifndef N
    // By default consider about 150 million numbers.
    #define N (1<<27)
#endif

int64_t can_be_prime [(N + 63) / 64];

static inline int get_index (int number) { return number / 64; }
static inline uint64_t get_mask (int number) { return ((uint64_t) 1) << (number % 64); }

static inline bool get_flag (int number) {
    int index = get_index (number);
    uint64_t mask = get_mask (number);
    return can_be_prime [index] & mask;
}

static inline void set_flag (int number) {
    int index = get_index (number);
    uint64_t mask = get_mask (number);
    can_be_prime [index] |= mask;
}

static inline void clear_flag (int number) {
    int index = get_index (number);
    uint64_t mask = get_mask (number);
    can_be_prime [index] &= ~mask;
}

int main () {

    // Mark all numbers as potentially prime.
    // Doing this with memset would be better.
    for (int i = 2 ; i < N ; i ++) {
        set_flag (i);
    }

    int primes = 0;

    // Check numbers from smallest to largest.
    for (int i = 2 ; i < N ; i ++) {
        // Any number that is still marked
        // as potentially prime is prime.
        if (get_flag (i)) {
            primes ++;
            // All multiples of any prime are not prime.
            for (int j = 2 * i ; j < N ; j += i) {
                if (get_flag (j)) {
                    clear_flag (j);
                }
              }
          }
    }

    std::cout << "Counted " << primes << " primes from " << 2 << " to " << N << "." << std::endl;

    return (0);
}
