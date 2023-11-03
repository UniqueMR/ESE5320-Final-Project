#include "utils.h"

void convert_string_char(std::string chunk_s, unsigned char* chunk_uc){
    chunk_uc = (unsigned char*)malloc(chunk_s.length() * sizeof(unsigned char));
    // do something to get chunk_uc as output
}

std::string toHexString(const unsigned char* data, int length){
    std::ostringstream oss;
    for (size_t i = 0; i < static_cast<size_t>(length); ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }
    return oss.str();
}