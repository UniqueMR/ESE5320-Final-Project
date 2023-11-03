#include "sha.h"

void sha(std::string input_chunk, unsigned char* output_hash){
    int chunk_length;
    *output_hash = 0;

    chunk_length=input_chunk.length();

    
    for (size_t i = 0; i < static_cast<size_t>(chunk_length); ++i) {
        
        // *output_hash = (*output_hash << 8) + input_chunk[i];
        // *output_hash %= (1ULL << 64);  // addition modulo 2^64
    }
    std::cout << "calculate hash value for a certain chunk" << std::endl;

}

// void sha(unsigned char* input_chunk, std::array<unsigned char, 32> &hash_value){

// }

