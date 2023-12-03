#include "deduplication.h"

void duplicate_encoding(int duplicate_idx, uint32_t &dup_outcode, unsigned char* file_buffer){
    // unsigned char* file_buffer = (unsigned char*)malloc(sizeof(unsigned char) * 4);
    // std::ofstream outfile(outputFile, std::ios::app);

    std::cout << "deup idx: " << duplicate_idx << std::endl; 
    
    dup_outcode = static_cast<uint32_t>(duplicate_idx & 0xFFFFFFFF) << 1;

    std::cout << "dedup outcode: " << dup_outcode << std::endl; 

    dup_outcode |= static_cast<uint32_t>(0x1);

    std::cout << "dedup outcode: " << dup_outcode << std::endl; 


    file_buffer[0] = static_cast<int>(dup_outcode & 0xFF);
    file_buffer[1] = static_cast<int>((dup_outcode >> 8) & 0xFF);
    file_buffer[2] = static_cast<int>((dup_outcode >> 16) & 0xFF);
    file_buffer[3] = static_cast<int>(dup_outcode >> 24);
    std::cout << "file buffer 0: " << (dup_outcode & 0xFF) << std::endl;

    for(int i = 0; i < 4; i++)  std::cout << "dedup buf in: " << std::hex << static_cast<int>(file_buffer[i]) << std::endl;

    // if(!outfile.is_open()) {
    //     std::cerr << "Could not open the file for writing.\n";
    //     return;
    // }

    // // Write the data to the file
    // outfile.write(reinterpret_cast<const char*>(file_buffer), 4);

    // // Check for write errors
    // if (!outfile.good()) {
    //     std::cerr << "Error occurred while writing to the file.\n";
    // }

    // // Close the file
    // outfile.close();
}