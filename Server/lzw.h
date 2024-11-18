#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stdlib.h>
#include <stdint.h>
#include <cmath>
// #include <filesystem>

#define HARDWARE 1
// #define SOFTWARE 1
#define MAX_CHUNK_SIZE 25000
#define MAX_FILE_BUFFER_SIZE 37504
#define CHUNKS_IN_SINGLE_KERNEL 4

//****************************************************************************************************************
typedef struct 
{
    // from LSB to MSB
    unsigned long quarter_0[32]; 
    unsigned long quarter_1[32];
    unsigned long quarter_2[32];
    unsigned long quarter_3[32]; 
    unsigned int value[64];    
    unsigned int fill;
    
} assoc_mem_t;



// unsigned int my_hash(unsigned long key);
// void hash_lookup(unsigned long* hash_table, unsigned int key, bool* hit, unsigned int* result);
// void hash_insert(unsigned long* hash_table, unsigned int key, unsigned int value, bool* collision);
// void assoc_insert(assoc_mem* mem,  unsigned int key, unsigned int value, bool* collision);
// void assoc_lookup(assoc_mem* mem, unsigned int key, bool* hit, unsigned int* result);
// void insert(unsigned long* hash_table, assoc_mem* mem, unsigned int key, unsigned int value, bool* collision);
// void lookup(unsigned long* hash_table, assoc_mem* mem, unsigned int key, bool* hit, unsigned int* result);// void hardware_encoding(unsigned char* s1, int length, uint16_t* out_code, uint32_t &header, int &out_len, char *outputFile);
#ifdef SOFTWARE
    void hardware_encoding(unsigned char* s1, int length, uint16_t* out_code, uint32_t &header, int &out_len);
#endif
void decoding(std::vector<int> op);
std::vector<uint16_t> encoding(std::string s1);
#ifdef HARDWARE
extern "C"{
    void hardware_encoding(unsigned char* s1, int length, uint16_t* out_code, uint32_t *header, int *out_len);
    // void lzw(unsigned char* s1, int length, unsigned char* file_buffer, int* total_bytes);
    void lzw_multi_chunks(unsigned char multi_chunks[CHUNKS_IN_SINGLE_KERNEL * MAX_CHUNK_SIZE], int length[CHUNKS_IN_SINGLE_KERNEL], unsigned char file_buffer[CHUNKS_IN_SINGLE_KERNEL * MAX_FILE_BUFFER_SIZE], int total_bytes[CHUNKS_IN_SINGLE_KERNEL]);
};
void write_encoded_file(uint16_t* out_code, int out_len, uint32_t *header, char* fileName);
void assoc_init(assoc_mem_t* mem);
void insert(unsigned long* hash_table, assoc_mem_t* mem, unsigned int key, unsigned int value, bool* collision);
void lookup(unsigned long* hash_table, assoc_mem_t* mem, unsigned int key, bool* hit, unsigned int* result);
#endif

#ifdef SOFTWARE
void write_encoded_file(uint16_t* out_code, uint32_t out_len, uint32_t &header, char* fileName);
#endif