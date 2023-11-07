#include "cdc.h"
#include <vector>
#include <string>
static uint64_t last_hash = 0;

static uint64_t hash_func(unsigned char *input, unsigned int pos)
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

        // for(int i = 0; i < buff_size; i++){
        //     std::cout << chunk_boundary[i];
        // }
	}
    last_hash = 0;
}


void cdc(unsigned char* buffer, std::vector<std::string> &chunks, unsigned int buff_size){
    // Define the size of each chunk
    unsigned int chunk_size = 50 ;  // Set your desired chunk size here

    // Loop through the buffer and create chunks
    for(unsigned int i = 0; i < buff_size; i += chunk_size){
        // Determine the size of the current chunk
        unsigned int current_chunk_size = std::min(chunk_size, buff_size - i);

        // Create a string from the current chunk of the buffer and add it to the vector
        chunks.push_back(std::string(buffer + i, buffer + i + current_chunk_size));
    }
}
