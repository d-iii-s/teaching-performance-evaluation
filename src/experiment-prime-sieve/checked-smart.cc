// Inspired by a public domain sieve implementation from http://www.algorithmist.com.

#include <cstdint>
#include <cstring>
#include <iostream>

// Consider about 150 million numbers.
#define N (1<<27)

// We will only check the odd numbers.
#define N_HALF ((N + 1) / 2)

// For any pair X, Y where X < Y
// we only check X*Y and not Y*X.
// Hence we stop at CEIL(SQRT(N)).
#define N_CEIL_SQRT 11586

int64_t can_be_prime [(N_HALF + 63) / 64];

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
  memset (can_be_prime, 0xFF, sizeof (can_be_prime));

  // Check numbers from smallest to largest.
  // Remember that X represents number 2*X+1.
  for (int x = 1 ; x < N_CEIL_SQRT ; x ++) {
      if (get_flag (x)) {
          // All multiples of any prime are not prime.
          // All multiples smaller than square
          // were tested already.
          int from = 2 * x * (x + 1);
          int step = 2 * x + 1;
          for (int w = from ; w < N_HALF ; w += step) {
              if (get_flag (w)) {
                  clear_flag (w);
              }
          }
      }
  }

  // We include 2 as the first prime.
  int primes = 1;

  for (int x = 1 ; x < N_HALF ; x ++) {
      if (get_flag (x)) {
          primes ++;
      }
  }

  std::cout << "Counted " << primes << " primes from " << 2 << " to " << N << "." << std::endl;

  return (0);
}
