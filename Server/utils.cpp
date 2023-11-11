#include "utils.h"


void convert_string_char(const std::string& chunk_s, unsigned char* chunk_uc) {
    // Allocate memory for the unsigned char array
    // *chunk_uc = (unsigned char*)malloc((chunk_s.length() + 1) * sizeof(unsigned char));
    if (chunk_uc) {
        // Copy each character from the string to the unsigned char array
        std::copy(chunk_s.begin(), chunk_s.end(), chunk_uc);
        // Add a null character at the end for a proper C-style string
        // (*chunk_uc)[chunk_s.length()] = '\0';
    }
}

std::string toHexString(const unsigned char* data, int length){
    std::ostringstream oss;
    for (size_t i = 0; i < static_cast<size_t>(length); ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }
    return oss.str();
}

std::string toHexString(const std::array<unsigned int, 8>& hash_arr) {
    std::stringstream ss;
    for (auto elem : hash_arr) {
        // Convert each element to a hex string.
        ss << std::hex << std::setfill('0') << std::setw(8) << elem;
    }
    return ss.str();
}
