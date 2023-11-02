#include "cdc.h"

static uint64_t last_hash = 0;

uint64_t hash_func(unsigned char *input, unsigned int pos)
{
	uint64_t hash = 0; 
    if(last_hash == 0){
        for(int i = 0; i < WIN_SIZE; i++){
        	hash += static_cast<uint64_t>(input[pos + WIN_SIZE - 1 - i]) * std::pow(PRIME, i + 1);
        }
    }
    else{
        hash = last_hash * PRIME - static_cast<uint64_t>(input[pos - 1]) * std::pow(PRIME, WIN_SIZE + 1) + static_cast<uint64_t>(input[pos + WIN_SIZE - 1]) * PRIME;
    }
	// std::cout << hash << std::endl;
    last_hash = hash;

	return hash;
}


void cdc(unsigned char* buffer, bool* chunk_boundary, unsigned int buff_size){
	for(unsigned int i = WIN_SIZE; i < buff_size - WIN_SIZE; i++){
        uint64_t hash = hash_func(buffer, i);
        chunk_boundary[i] = ((hash % MODULUS) == TARGET) ? true : false;
        // if(i < 8200)
    // std::cout << buffer[i]  << std::endl;
        if((hash % MODULUS) == TARGET)
            std::cout << i << std::endl;
	}
    last_hash = 0;
}
