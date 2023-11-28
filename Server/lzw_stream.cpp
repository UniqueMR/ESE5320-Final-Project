#include "lzw.h"
#include <hls_stream.h>
#include <ap_int.h>
#include <ap_fixed.h>

static unsigned int my_hash(unsigned long key)
{
    key &= 0xFFFFF; // make sure the key is only 20 bits

    unsigned int hashed = 0;

    // #pragma HLS UNROLL (no effect)
    for(int i = 0; i < 20; i++)
    {
        // #pragma HLS UNROLL (not successful, the time consumed on insert gets longer)
        hashed += (key >> i)&0x01;
        hashed += hashed << 10;
        hashed ^= hashed >> 6;
    }
    hashed += hashed << 3;
    hashed ^= hashed >> 11;
    hashed += hashed << 15;
    return hashed & 0x7FFF;          // hash output is 15 bits
    //return hashed & 0xFFF;   
}

static void hash_lookup(unsigned long* hash_table, unsigned int key, bool* hit, unsigned int* result)
{
    //std::cout << "hash_lookup():" << std::endl;
    key &= 0xFFFFF; // make sure key is only 20 bits 

    unsigned long lookup = hash_table[my_hash(key)];

    // [valid][value][key]
    unsigned int stored_key = lookup&0xFFFFF;       // stored key is 20 bits
    unsigned int value = (lookup >> 20)&0xFFF;      // value is 12 bits
    unsigned int valid = (lookup >> (20 + 12))&0x1; // valid is 1 bit
    
    if(valid && (key == stored_key))
    {
        *hit = 1;
        *result = value;
        //std::cout << "\thit the hash" << std::endl;
        //std::cout << "\t(k,v,h) = " << key << " " << value << " " << my_hash(key) << std::endl;
    }
    else
    {
        *hit = 0;
        *result = 0;
        //std::cout << "\tmissed the hash" << std::endl;
    }
}

static void hash_insert(unsigned long* hash_table, unsigned int key, unsigned int value, bool* collision)
{
    //std::cout << "hash_insert():" << std::endl;
    key &= 0xFFFFF;   // make sure key is only 20 bits
    value &= 0xFFF;   // value is only 12 bits

    unsigned long lookup = hash_table[my_hash(key)];
    unsigned int valid = (lookup >> (20 + 12))&0x1;

    if(valid)
    {
        *collision = 1;
        //std::cout << "\tcollision in the hash" << std::endl;
    }
    else
    {
        hash_table[my_hash(key)] = (1UL << (20 + 12)) | (value << 20) | key;
        *collision = 0;
        //std::cout << "\tinserted into the hash table" << std::endl;
        //std::cout << "\t(k,v,h) = " << key << " " << value << " " << my_hash(key) << std::endl;
    }
}

// cast to struct and use ap types to pull out various feilds.

static void assoc_insert(assoc_mem* mem,  unsigned int key, unsigned int value, bool* collision)
{
    //std::cout << "assoc_insert():" << std::endl;
    key &= 0xFFFFF; // make sure key is only 20 bits
    value &= 0xFFF;   // value is only 12 bits

    if(mem->fill < 64)
    {
        mem->upper_key_mem[(key >> 18)%512] |= (1 << mem->fill);  // set the fill'th bit to 1, while preserving everything else
        mem->middle_key_mem[(key >> 9)%512] |= (1 << mem->fill);  // set the fill'th bit to 1, while preserving everything else
        mem->lower_key_mem[(key >> 0)%512] |= (1 << mem->fill);   // set the fill'th bit to 1, while preserving everything else
        mem->value[mem->fill] = value;
        mem->fill++;
        *collision = 0;
        //std::cout << "\tinserted into the assoc mem" << std::endl;
        //std::cout << "\t(k,v) = " << key << " " << value << std::endl;
    }
    else
    {
        *collision = 1;
        //std::cout << "\tcollision in the assoc mem" << std::endl;
    }
}

static void assoc_lookup(assoc_mem* mem, unsigned int key, bool* hit, unsigned int* result)
{
    //std::cout << "assoc_lookup():" << std::endl;
    key &= 0xFFFFF; // make sure key is only 20 bits

    unsigned int match_high = mem->upper_key_mem[(key >> 18)%512];
    unsigned int match_middle = mem->middle_key_mem[(key >> 9)%512];
    unsigned int match_low  = mem->lower_key_mem[(key >> 0)%512];

    unsigned int match = match_high & match_middle & match_low;

    unsigned int address = 0;
    for(; address < 64; address++)
    {
        if((match >> address) & 0x1)
        {   
            break;
        }
    }
    if(address != 64)
    {
        *result = mem->value[address];
        *hit = 1;
        //std::cout << "\thit the assoc" << std::endl;
        //std::cout << "\t(k,v) = " << key << " " << *result << std::endl;
    }
    else
    {
        *hit = 0;
        //std::cout << "\tmissed the assoc" << std::endl;
    }
}
//****************************************************************************************************************
static void insert(unsigned long* hash_table, assoc_mem* mem, unsigned int key, unsigned int value, bool* collision)
{
    hash_insert(hash_table, key, value, collision);
    if(*collision)
    {
        assoc_insert(mem, key, value, collision);
    }
}

static void lookup(unsigned long* hash_table, assoc_mem* mem, unsigned int key, bool* hit, unsigned int* result)
{
    hash_lookup(hash_table, key, hit, result);
    if(!*hit)
    {
        assoc_lookup(mem, key, hit, result);
    }
}


static void read_input(unsigned char *s1, hls::stream<unsigned char>& chr_stream, int length){
mem_rd:
    for(int i = 0; i < length; i++){
// #pragma HLS LOOP_TRIPCOUNT min = MAX max = length
        chr_stream.write(s1[i]);
    }
}

// static void write_result(uint16_t* out_code, hls::stream<uint16_t>& cmprs_stream, hls::stream<int> &cmprs_len_stream, int *out_len){
// mem_wr:
//     *out_len = cmprs_len_stream.read();
//     for(int i = 0; i < *out_len; i++){
// // #pragma HLS LOOP_TRIPCOUNT min = *out_len max = *out_len
//         out_code[i] = cmprs_stream.read();
//     }
// }

static int ceil_fixed(float num){
    int inum = (int)num;
    if (num == (float)inum) {
        return inum;
    } else {
        return inum + ((num > 0) ? 1 : 0);
    }
}

static void write_header(unsigned char* file_buffer, uint32_t header) {
    //using HLS UNROLL to fully unroll the loop, hoping to make all j executed concurrently
    #pragma HLS UNROLL
    for (int i = 0; i < 4; ++i) {
        file_buffer[i] = static_cast<unsigned char>((header >> (i * 8)) & 0xFF);
    }
}

static void write_file_buffer(unsigned char* file_buffer, int j, uint16_t out_code_0, uint16_t out_code_1){
    file_buffer[j] = static_cast<unsigned char>(out_code_0 >> 4);
    // std::cout << std::hex << static_cast<int>(file_buffer[j]) << std::endl;
    file_buffer[j+1] = static_cast<unsigned char>(((out_code_0 << 4) & 0xF0) | ((out_code_1 >> 8) & 0x0F));
    // std::cout << std::hex << static_cast<int>(file_buffer[j+1]) << std::endl;
    file_buffer[j+2] = static_cast<unsigned char>(out_code_1 & 0xFF);
    // std::cout << std::hex << static_cast<int>(file_buffer[j+2]) << std::endl;
}

static void write_result(hls::stream<uint16_t>& cmprs_stream, hls::stream<int> &cmprs_len_stream, unsigned char* file_buffer, int* total_bytes){
mem_wr:
    int out_len = cmprs_len_stream.read();
    int total_bits = out_len * 12;
    *total_bytes = static_cast<int>(ceil_fixed(total_bits / 8.0));
    uint32_t header = static_cast<uint32_t>(*total_bytes & 0xFFFFFFFF) << 1;

    write_header(file_buffer, header);

    int i = 0, j = 4;

    for(i = 0; i + 1 < out_len; i += 2){
// #pragma HLS LOOP_TRIPCOUNT min = *out_len max = *out_len
        uint16_t out_code_0 = cmprs_stream.read();
        // std::cout << out_code_0 << std::endl;
        uint16_t out_code_1 = cmprs_stream.read();
        // std::cout << out_code_1 << std::endl;
        write_file_buffer(file_buffer, j, out_code_0, out_code_1);
        j += 3;
    }
    if(i != out_len){
        uint16_t out_code_0 = cmprs_stream.read();
        // std::cout << out_code_0 << std::endl;
        file_buffer[j] = static_cast<unsigned char>(out_code_0 >> 4);
        file_buffer[j+1] = static_cast<unsigned char>((out_code_0 << 4) & 0xF0);
    }
    return;
}

static void compute_lzw(hls::stream<unsigned char>& chr_stream, hls::stream<uint16_t>& cmprs_stream, int length, hls::stream<int> &cmprs_len_stream, unsigned long *hash_table, assoc_mem* my_assoc_mem){
execute:
    int nxt_code = 256, prefix_code = chr_stream.read();
    unsigned int code = 0;
    char nxt_char = 0;
    int local_cmprs_len = 0;

    for(int i = 0; i < length; i++){
// #pragma HLS LOOP_TRIPCOUNT min = length max = length
        if(i + 1 == length){
            cmprs_stream.write(prefix_code);
            local_cmprs_len += 1;
            cmprs_len_stream.write(local_cmprs_len);
            return;
        }

        nxt_char = chr_stream.read();
        
        // detect hit or not
        bool hit = 0;
        lookup(hash_table, my_assoc_mem, (prefix_code << 8) + nxt_char, &hit, &code);
        
        if(!hit){
            cmprs_stream.write(prefix_code);
            local_cmprs_len += 1;

            //detect hash collision
            //add to assoc_mem in the case of detecting hash collision
            bool collision = 0;
            insert(hash_table, my_assoc_mem, (prefix_code << 8) + nxt_char, nxt_code, &collision);
            if(collision)    return;
            nxt_code += 1;
            prefix_code = nxt_char;
        }
        else{
            prefix_code = code;
        }
    }
    // cmprs_len_stream.write(local_cmprs_len);
}

static void clear_hash_table(unsigned long *hash_table){
    for(int i = 0; i < CAPACITY; i++)
    {
        #pragma HLS PIPELINE II=1
        hash_table[i] = 0;
    }
}

static void clear_assoc_mem(assoc_mem* my_assoc_mem){
    my_assoc_mem->fill = 0;
    for(int i = 0; i < 512; i++)
    {
        #pragma HLS PIPELINE II=1
        my_assoc_mem->upper_key_mem[i] = 0;
        my_assoc_mem->middle_key_mem[i] = 0;
        my_assoc_mem->lower_key_mem[i] = 0;
    }
}

static void clear_mem(unsigned long *hash_table, assoc_mem* my_assoc_mem){
    // #pragma HLS dataflow
    clear_hash_table(hash_table);
    clear_assoc_mem(my_assoc_mem);
}

static void init_mem(unsigned long *hash_table, assoc_mem* my_assoc_mem){
    clear_mem(hash_table, my_assoc_mem);

    // init the memories with the first 256 codes
    // for(unsigned long i = 0; i < 256; i++)
    // {
    //     #pragma HLS PIPELINE II=1
    //     bool collision = 0;
    //     unsigned int key = (i << 8) + 0UL; // lower 8 bits are the next char, the upper bits are the prefix code
    //     insert(hash_table, my_assoc_mem, key, i, &collision);
    // }
}

static void hardware_encoder(unsigned char* s1, int length, unsigned char* file_buffer, int* total_bytes, unsigned long* hash_table, assoc_mem* my_assoc_mem){
    hls::stream<unsigned char> chr_stream("char_stream");
    hls::stream<uint16_t> cmprs_stream("compress_stream");
    hls::stream<int> cmprs_len_stream("compress_length_stream");

#pragma HLS STREAM variable = chr_stream depth = 32
#pragma HLS STREAM variable = cmprs_stream depth = 32
#pragma HLS STREAM variable = cmprs_len_stream depth = 32

// #pragma HLS dataflow
    read_input(s1, chr_stream, length);
    compute_lzw(chr_stream, cmprs_stream, length, cmprs_len_stream, hash_table, my_assoc_mem);
    write_result(cmprs_stream, cmprs_len_stream, file_buffer, total_bytes);
}

void lzw_stream(unsigned char* s1, int length, unsigned char* file_buffer, int* total_bytes){
// #pragma HLS INTERFACE m_axi port=s1 bundle=aximm1 depth=32
// #pragma HLS INTERFACE m_axi port=length bundle=aximm2 depth=32
// #pragma HLS INTERFACE m_axi port=file_buffer bundle=aximm3 depth=32
// #pragma HLS INTERFACE m_axi port=total_bytes bundle=aximm4 depth=32

    unsigned long hash_table[CAPACITY];
    assoc_mem my_assoc_mem;

    init_mem(hash_table, &my_assoc_mem);
    hardware_encoder(s1, length, file_buffer, total_bytes, hash_table, &my_assoc_mem);
}