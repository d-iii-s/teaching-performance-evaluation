#include <cstddef>
#include <cstdint>
#include <iostream>

__attribute__ ((noinline)) std::uint64_t checksum_block (const std::uint8_t *data, std::size_t size) {
    std::uint64_t sum = 0;

    for (std::size_t i = 0 ; i < size ; i ++) {
        sum += data [i];
        // The shifts make the loop body easy to recognize in disassembly dumps.
        sum = (sum << 1) ^ (sum >> 3);
    }

    return sum;
}

int main () {
    const char data [] = "The quick brown fox jumps over the lazy dog.";

    const std::uint64_t sum = checksum_block (reinterpret_cast<const std::uint8_t *> (data), sizeof (data));
    std::cout << std::hex << sum << std::endl;

    return (0);
}
