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


void cdc(unsigned char* buffer, std::vector<std::string> &chunks, unsigned int buff_size){
    //do some operation to get the chunks 
    std::cout << "Using cdc to split the input into chunks ..." << std::endl;
    std::string chunk;
    //initialize the first chunk
    for(unsigned int i = 0; i < WIN_SIZE; i++){
        chunk.push_back(buffer[i]);
    }

	for(unsigned int i = WIN_SIZE; i < buff_size - WIN_SIZE; i++){
        chunk.push_back(buffer[i]);
        uint64_t hash = hash_func(buffer, i);
        if((hash % MODULUS) == TARGET){
            chunks.push_back(chunk);
            chunk.clear();
        }
	}

    //push the remaining characters into the last chunk
    //push the last chunk into chunks
    for(unsigned int i = buff_size - WIN_SIZE; i < buff_size; i++){
        chunk.push_back(buffer[i]);
    }
    chunks.push_back(chunk);
    chunk.clear();

    last_hash = 0;
    std::cout << "Finish generating chunks using cdc." << std::endl;
    std::cout << "The number of chunk is " << chunks.size() << std::endl;
}

