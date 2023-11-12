#include "cdc.h"
#include "sha.h"
#include "lzw.h"
#include "utils.h"
int main(int argc, char* argv[]) {
    // Specify the file path
    std::string filePath = "./LittlePrince.txt";

    // Open the binary file for reading
    std::ifstream inputFile(filePath, std::ios::binary);

    if (!inputFile) {
        std::cerr << "Failed to open the file for reading: " << filePath << std::endl;
        return 1;
    }

    // Determine the file size
    inputFile.seekg(0, std::ios::end);
    std::streampos fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    if (fileSize < 0) {
        std::cerr << "Failed to determine file size." << std::endl;
        return 1;
    }

    // Create an unsigned char buffer and read the file into it
    unsigned char* buffer = new unsigned char[fileSize];
    std::vector<std::string> chunks;
    inputFile.read(reinterpret_cast<char*>(buffer), fileSize);
    // Close the file
    inputFile.close();

    cdc(buffer, chunks, fileSize);

    // for(int i = 0; i < chunks.size(); i++){
    //     std::cout << "Chunk " << i << " has a size of " << chunks[i].size() << std::endl; 
    //     std::cout << chunks[i] << std::endl;
    // }

    // for(int i=0; i<chunks.size();i++){
	// 	printf("%d",chunks[i].size());
	// }
    for(int i = 0; i < chunks.size(); i++){
        std::cout << "raw chunk " << chunks[i] << std::endl;
        std::array<unsigned int,8> output_hash;
        sha(chunks[i], output_hash);
        std::string output_hash_str = toHexString(output_hash);
        unsigned char *chunk_uc = (unsigned char*)malloc((chunks[i].length()) * sizeof(unsigned char));
        convert_string_char(chunks[i], chunk_uc);
        // std:: cout << chunk_uc[chunks[i].length() - 3] << chunk_uc[chunks[i].length() - 2] << chunk_uc[chunks[i].length() - 1] << std::endl;
        uint16_t* out_code = (uint16_t*)malloc(sizeof(uint16_t) * chunks[i].size());
        uint32_t header;
        int out_len;
        //std::vector<uint16_t> output_code = encoding(chunks[i]);
        hardware_encoding(chunk_uc, chunks[i].size(), out_code, header, out_len, argv[1]);
        //printf("number of chunk is %d\n",i);
    }

    // for (int i = 0; i < f ileSize; ++i) {
    //     std::cout << chunk_boundary[i] << std::endl; // This will print 0 for false and 1 for true
    // }

    // Don't forget to free the memory when you're done with the buffer
    delete[] buffer;

    return 0;
}