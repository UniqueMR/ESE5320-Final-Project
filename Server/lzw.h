#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stdlib.h>
#include <stdint.h>
#include <cmath>
// #include <filesystem>

#define HARDWARE 1
#define CAPACITY 32768
// #define SOFTWARE 1

//****************************************************************************************************************
typedef struct
{   
    // Each key_mem has a 9 bit address (so capacity = 2^9 = 512)
    // and the key is 20 bits, so we need to use 3 key_mems to cover all the key bits.
    // The output width of each of these memories is 64 bits, so we can only store 64 key
    // value pairs in our associative memory map.

    unsigned long upper_key_mem[512]; // the output of these  will be 64 bits wide (size of unsigned long).
    unsigned long middle_key_mem[512];
    unsigned long lower_key_mem[512]; 
    unsigned int value[64];    // value store is 64 deep, because the lookup mems are 64 bits wide
    unsigned int fill;         // tells us how many entries we've currently stored 
} assoc_mem;


unsigned int my_hash(unsigned long key);
void hash_lookup(unsigned long* hash_table, unsigned int key, bool* hit, unsigned int* result);
void hash_insert(unsigned long* hash_table, unsigned int key, unsigned int value, bool* collision);
void assoc_insert(assoc_mem* mem,  unsigned int key, unsigned int value, bool* collision);
void assoc_lookup(assoc_mem* mem, unsigned int key, bool* hit, unsigned int* result);
void insert(unsigned long* hash_table, assoc_mem* mem, unsigned int key, unsigned int value, bool* collision);
void lookup(unsigned long* hash_table, assoc_mem* mem, unsigned int key, bool* hit, unsigned int* result);// void hardware_encoding(unsigned char* s1, int length, uint16_t* out_code, uint32_t &header, int &out_len, char *outputFile);
#ifdef SOFTWARE
    void hardware_encoding(unsigned char* s1, int length, uint16_t* out_code, uint32_t &header, int &out_len);
#endif
void decoding(std::vector<int> op);
std::vector<uint16_t> encoding(std::string s1);
#ifdef HARDWARE
extern "C"{
    // void hardware_encoding(unsigned char* s1, int length, uint16_t* out_code, uint32_t *header, int *out_len);
    // void hardware_encoding(unsigned char* s1, int length, uint16_t* out_code, int *out_len);
    void lzw_stream(unsigned char* s1, int length, unsigned char* file_buffer, int* total_bytes);
};
// void hardware_encoding(unsigned char* s1, int length, uint16_t* out_code, int *out_len);
// void lzw_stream(unsigned char* s1, int length, uint16_t* out_code, int *out_len);
// void lzw_stream(unsigned char* s1, int length, unsigned char* file_buffer, int* total_bytes);
#endif

#ifdef SOFTWARE
void write_encoded_file(uint16_t* out_code, uint32_t out_len, uint32_t &header, char* fileName);
#endif