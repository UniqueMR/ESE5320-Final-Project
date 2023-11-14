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
    // for(int i =0;i<buff_size;i++){
    //     std::cout<<buffer[i];
    // }
    std::cout << "Using cdc to split the input into chunks ..." << std::endl;
    unsigned int start = 0;
    for (unsigned int i = WIN_SIZE; i < buff_size - WIN_SIZE; i++) {
        if ((hash_func(buffer, i) % MODULUS) == TARGET) {
            // Found a chunk boundary
            std::string chunk(buffer + start, buffer + i);
            chunks.push_back(chunk);
            start = i;
        }
    }

    // Add the last chunk
    if (start < buff_size) {
        std::string chunk(buffer + start, buffer + buff_size);
        chunks.push_back(chunk);
    }
    // for(int i=0; i<chunks.size();i++){
	// 	std::cout<<chunks[i] <<std::endl;
	// }
    last_hash = 0;
    std::cout << "Finish generating chunks using cdc." << std::endl;
    std::cout << "The number of chunk is " << chunks.size() << std::endl;
}


// void cdc(unsigned char* buffer, std::vector<std::string> &chunks, unsigned int buff_size){
//     // Define the size of each chunk
//     unsigned int chunk_size = 50 ;  // Set your desired chunk size here

//     // Loop through the buffer and create chunks
//     for(unsigned int i = 0; i < buff_size; i += chunk_size){
//         // Determine the size of the current chunk
//         unsigned int current_chunk_size = std::min(chunk_size, buff_size - i);

//         // Create a string from the current chunk of the buffer and add it to the vector
//         chunks.push_back(std::string(buffer + i, buffer + i + current_chunk_size));
//     }
// }
// int main(){
//     // Specify the file path
//     std::string filePath = "../test.txt";

//     // Open the binary file for reading
//     std::ifstream inputFile(filePath, std::ios::binary);

//     if (!inputFile) {
//         std::cerr << "Failed to open the file for reading: " << filePath << std::endl;
//         return 1;
//     }

//     // Determine the file size
//     inputFile.seekg(0, std::ios::end);
//     std::streampos fileSize = inputFile.tellg();
//     inputFile.seekg(0, std::ios::beg);

//     if (fileSize < 0) {
//         std::cerr << "Failed to determine file size." << std::endl;
//         return 1;
//     }

//     // Create an unsigned char buffer and read the file into it
//     unsigned char* buffer = new unsigned char[fileSize];
//     std::vector<std::string> chunks;
//     inputFile.read(reinterpret_cast<char*>(buffer), fileSize);
//     // Close the file
//     inputFile.close();

//     cdc(buffer, chunks, fileSize);
// }
