#include "sha.h"

#include <iostream>
#include <string>
#include <cstring>

void sha(std::string input_chunk, unsigned char* output_hash){
    // Placeholder 256-bit hash value (32 bytes)
    unsigned char fixed_hash[32] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
    };

    // Copy the fixed hash value to the output_hash
    std::memcpy(output_hash, fixed_hash, sizeof(fixed_hash));

    std::cout << "Placeholder: calculate hash value for a certain chunk" << std::endl;
}

// void sha(unsigned char* input_chunk, std::array<unsigned char, 32> &hash_value){

// }

