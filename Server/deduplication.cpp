#include "deduplication.h"

void duplicate_encoding(int duplicate_idx, uint32_t &dup_outcode, unsigned char* file_buffer){
    // unsigned char* file_buffer = (unsigned char*)malloc(sizeof(unsigned char) * 4);
    // std::ofstream outfile(outputFile, std::ios::app);
    
    dup_outcode = static_cast<uint32_t>(duplicate_idx & 0xFFFFFFFF) << 1;
    dup_outcode |= static_cast<uint32_t>(0x1);

    file_buffer[0] = static_cast<unsigned char>(dup_outcode & 0xFF);
    file_buffer[1] = static_cast<unsigned char>((dup_outcode >> 8) & 0xFF);
    file_buffer[2] = static_cast<unsigned char>((dup_outcode >> 16) & 0xFF);
    file_buffer[3] = static_cast<unsigned char>(dup_outcode >> 24);

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