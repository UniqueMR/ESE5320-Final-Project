#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdlib.h>
#include <stdint.h>

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
void lookup(unsigned long* hash_table, assoc_mem* mem, unsigned int key, bool* hit, unsigned int* result);
void hardware_encoding(unsigned char* s1, int length, uint16_t* out_code);
void decoding(std::vector<int> op);
