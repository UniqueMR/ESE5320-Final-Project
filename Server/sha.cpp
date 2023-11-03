#include "sha.h"
#include <iostream>

void sha(std::string input_chunk, unsigned char* output_hash){
    int chunk_length;
    *output_hash = 0;

    chunk_length=input_chunk.length();

    
    for (size_t i = 0; i < chunk_length; ++i) {
        
        *output_hash = (*output_hash << 8) + input_chunk[i];
        *output_hash %= (1ULL << 64);  // addition modulo 2^64
    }

}