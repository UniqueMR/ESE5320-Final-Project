#include "lzw.h"
#include <hls_stream.h>
#include <ap_int.h>
#include <ap_fixed.h>

#define CAPACITY 32768

static unsigned int my_hash(unsigned long key)
{
    key &= 0xFFFFF; // make sure the key is only 20 bits

    unsigned int hashed = 0;

    for(int i = 0; i < 20; i++)
    {
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

static unsigned int findAddr(uint64_t match){
    #pragma HLS INLINE

    if(match == 0)  return 64; //find address failed

    uint8_t segment[8]; // split 64-bits match into 8 x 8 bits
    #pragma HLS array_partition variable=segment complete
    // initialize all the segments in parallel
    for(int i = 0; i < 8; i++){
        #pragma HLS UNROLL
        segment[i] = (match >> (8 * i)) & 0xFF;
    }

    uint8_t mask[8];
    #pragma HLS array_partition variable=mask complete
    for(int j = 0; j < 8; j++){
        #pragma HLS UNROLL
        mask[j] = 0x1 << j;
    }

    // check each segment in parallel
    for(int i = 0; i < 8; i++){
        #pragma HLS UNROLL
        if(segment[i] != 0){
            for(int j = 0; j < 8; j++){
                #pragma HLS UNROLL
                if(segment[i] & mask[j]){
                    return 8 * i + j;
                }
            }
        }
    }
    return 64;
}

static void assoc_lookup(assoc_mem* mem, unsigned int key, bool* hit, unsigned int* result)
{
    //std::cout << "assoc_lookup():" << std::endl;
    key &= 0xFFFFF; // make sure key is only 20 bits

    unsigned int match_high = mem->upper_key_mem[(key >> 18)%512];
    unsigned int match_middle = mem->middle_key_mem[(key >> 9)%512];
    unsigned int match_low  = mem->lower_key_mem[(key >> 0)%512];

    unsigned int match = match_high & match_middle & match_low;

    unsigned int address = findAddr(match);

    // for(; address < 64; address++)
    // {
    //     if((match >> address) & 0x1)
    //     {   
    //         break;
    //     }
    // }
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

// static void write_header(unsigned char file_buffer[4], uint32_t header) {
//     // #pragma HLS array_partition variable=file_buffer complete
//     for (int i = 0; i < 4; ++i) {
//         #pragma HLS UNROLL
//         file_buffer[i] = static_cast<unsigned char>((header >> (i * 8)) & 0xFF);
//     }
// }

// // static void write_file_buffer(unsigned char* file_buffer, int j, uint16_t out_code_0, uint16_t out_code_1){
// //     file_buffer[j] = static_cast<unsigned char>(out_code_0 >> 4);
// //     file_buffer[j+1] = static_cast<unsigned char>(((out_code_0 << 4) & 0xF0) | ((out_code_1 >> 8) & 0x0F));
// //     file_buffer[j+2] = static_cast<unsigned char>(out_code_1 & 0xFF);
// // }

// static void clear_hash_table(unsigned long hash_table[CAPACITY]){
//     // #pragma HLS array_partition variable=hash_table complete
//     for(int i = 0; i < CAPACITY; i++)
//     {
//         #pragma HLS UNROLL
//         hash_table[i] = 0;
//     }
// }

// static void clear_assoc_mem(assoc_mem my_assoc_mem[512]){
//     // #pragma HLS array_partition variable=my_assoc_mem complete
//     my_assoc_mem->fill = 0;
//     for(int i = 0; i < 512; i++)
//     {
//         #pragma HLS UNROLL
//         my_assoc_mem->upper_key_mem[i] = 0;
//         my_assoc_mem->middle_key_mem[i] = 0;
//         my_assoc_mem->lower_key_mem[i] = 0;
//     }
// }

// static void clear_mem(unsigned long *hash_table, assoc_mem* my_assoc_mem){
//     #pragma HLS DATAFLOW
//     clear_hash_table(hash_table);
//     clear_assoc_mem(my_assoc_mem);
// }

static int ceil_fixed(float num){
    int inum = (int)num;
    if (num == (float)inum) {
        return inum;
    } else {
        return inum + ((num > 0) ? 1 : 0);
    }
}

// static void write_result(uint16_t out_code[MAX_CHUNK_SIZE], int out_len, unsigned char file_buffer[MAX_FILE_BUFFER_SIZE], int* total_bytes){
// mem_wr:
// // #pragma HLS array_partition variable=out_code complete
// // #pragma HLS array_partition variable=file_buffer complete
//     int total_bits = out_len * 12;
//     *total_bytes = static_cast<int>(ceil_fixed(total_bits / 8.0));
//     uint32_t header = static_cast<uint32_t>(*total_bytes & 0xFFFFFFFF) << 1;

//     write_header(file_buffer, header);

//     int i = 0, j = 4;

//     for(i = 0; i + 1 < out_len; i += 2){
//         #pragma HLS unroll
//         file_buffer[j] = static_cast<unsigned char>(out_code[i] >> 4);
//         file_buffer[j+1] = static_cast<unsigned char>(((out_code[i] << 4) & 0xF0) | ((out_code[i+1] >> 8) & 0x0F));
//         file_buffer[j+2] = static_cast<unsigned char>(out_code[i+1] & 0xFF);
//         j += 3;
//     }

//     if(i != out_len){
//         uint16_t out_code_0 = out_code[i];
//         // std::cout << out_code_0 << std::endl;
//         file_buffer[j] = static_cast<unsigned char>(out_code_0 >> 4);
//         file_buffer[j+1] = static_cast<unsigned char>((out_code_0 << 4) & 0xF0);
//     }
//     return;
// }

static void lzw(unsigned char* s1, int length, unsigned char* file_buffer, int* total_bytes){
    unsigned long hash_table[CAPACITY];
    assoc_mem my_assoc_mem;

    for(int i = 0; i < CAPACITY; i++)
    {
        #pragma HLS pipeline II=1
        hash_table[i] = 0;
    }

    my_assoc_mem.fill = 0;
    for(int i = 0; i < 512; i++)
    {
        #pragma HLS pipeline II=1
        my_assoc_mem.upper_key_mem[i] = 0;
        my_assoc_mem.middle_key_mem[i] = 0;
        my_assoc_mem.lower_key_mem[i] = 0;
    }

    // uint16_t* out_code = (uint16_t*)malloc(length * sizeof(uint16_t));
    uint16_t out_code[MAX_CHUNK_SIZE];

    int next_code = 256;

    int prefix_code = s1[0];
    unsigned int code = 0;
    char next_char = 0;

    int i = 0, j = 0;
    while(i < length)
    {
        if(i + 1 == length){
            out_code[j++] = prefix_code;
            break;
        }

        next_char = s1[i + 1];

        bool hit = 0;
        //std::cout << "prefix_code " << prefix_code << " next_char " << next_char << std::endl;
        lookup(hash_table, &my_assoc_mem, (prefix_code << 8) + next_char, &hit, &code);
        if(!hit)
        {
            // std::cout << prefix_code;
            out_code[j++] = prefix_code;
            // out_code[i]=prefix_code;
            // std::cout << "\n";

            bool collision = 0;
            insert(hash_table, &my_assoc_mem, (prefix_code << 8) + next_char, next_code, &collision);
            if(collision)
            {
                std::cout << "ERROR: FAILED TO INSERT! NO MORE ROOM IN ASSOC MEM!" << std::endl;
                return;
            }
            next_code += 1;

            prefix_code = next_char;
        }
        else
        {
            prefix_code = code;
        }
        i += 1;
    }

    int out_len = j;

    int total_bits = out_len * 12;
    *total_bytes = static_cast<int>(ceil_fixed(total_bits / 8.0));
    uint32_t header = static_cast<uint32_t>(*total_bytes & 0xFFFFFFFF) << 1;

    for (int i = 0; i < 4; ++i) {
        #pragma HLS UNROLL
        file_buffer[i] = static_cast<unsigned char>((header >> (i * 8)) & 0xFF);
    }

    int m = 0, n = 4;

    for(m = 0; m + 1 < out_len; m += 2){
        #pragma HLS pipeline II=1
        file_buffer[n] = static_cast<unsigned char>(out_code[m] >> 4);
        file_buffer[n+1] = static_cast<unsigned char>(((out_code[m] << 4) & 0xF0) | ((out_code[m+1] >> 8) & 0x0F));
        file_buffer[n+2] = static_cast<unsigned char>(out_code[m+1] & 0xFF);
        n += 3;
    }

    if(m != out_len){
        // std::cout << out_code_0 << std::endl;
        file_buffer[n] = static_cast<unsigned char>(out_code[m] >> 4);
        file_buffer[n+1] = static_cast<unsigned char>((out_code[m] << 4) & 0xF0);
    }

    return;
}

// static void lzw(unsigned char* s1, int length, unsigned char* file_buffer, int* total_bytes){
//     unsigned long hash_table[CAPACITY];
//     assoc_mem my_assoc_mem;

//     clear_mem(hash_table, &my_assoc_mem);

//     // uint16_t* out_code = (uint16_t*)malloc(length * sizeof(uint16_t));
//     uint16_t out_code[8192];

//     int next_code = 256;

//     int prefix_code = s1[0];
//     unsigned int code = 0;
//     char next_char = 0;

//     int i = 0, j = 0;
//     while(i < length)
//     {
//         next_char = s1[i + 1];

//         bool hit = 0;
//         //std::cout << "prefix_code " << prefix_code << " next_char " << next_char << std::endl;
//         lookup(hash_table, &my_assoc_mem, (prefix_code << 8) + next_char, &hit, &code);
//         if(!hit)
//         {
//             // std::cout << prefix_code;
//             out_code[j++] = prefix_code;
//             // out_code[i]=prefix_code;
//             // std::cout << "\n";

//             bool collision = 0;
//             insert(hash_table, &my_assoc_mem, (prefix_code << 8) + next_char, next_code, &collision);
//             if(collision)
//             {
//                 std::cout << "ERROR: FAILED TO INSERT! NO MORE ROOM IN ASSOC MEM!" << std::endl;
//                 return;
//             }
//             next_code += 1;

//             prefix_code = next_char;
//         }
//         else
//         {
//             prefix_code = code;
//             if(i + 1 == length){
//                 out_code[j++] = prefix_code;
//             }

//         }
//         i += 1;
//     }

//     int out_len = j;
//     write_result(out_code, out_len, file_buffer, total_bytes);
//     return;
// }

void lzw_multi_chunks(unsigned char multi_chunks[CHUNKS_IN_SINGLE_KERNEL * MAX_CHUNK_SIZE], int length[CHUNKS_IN_SINGLE_KERNEL], unsigned char file_buffer[CHUNKS_IN_SINGLE_KERNEL * MAX_FILE_BUFFER_SIZE], int total_bytes[CHUNKS_IN_SINGLE_KERNEL]){
#pragma HLS INTERFACE m_axi port=multi_chunks bundle=aximm1
#pragma HLS INTERFACE m_axi port=length bundle=aximm2
#pragma HLS INTERFACE m_axi port=file_buffer bundle=aximm3
#pragma HLS INTERFACE m_axi port=total_bytes bundle=aximm4

// #pragma HLS array_partition variable=multi_chunks block factor=4
// #pragma HLS array_partition variable=file_buffer block factor=4
    unsigned char input_buffer[CHUNKS_IN_SINGLE_KERNEL][MAX_CHUNK_SIZE];
    unsigned char output_buffer[CHUNKS_IN_SINGLE_KERNEL][MAX_FILE_BUFFER_SIZE];

#pragma HLS array_partition variable=input_buffer complete
#pragma HLS array_partition variable=output_buffer complete

    Init_loop_i: for(int i = 0; i < CHUNKS_IN_SINGLE_KERNEL; i++){
        Init_loop_j: for(int j = 0; j < length[i]; j++){
            #pragma HLS pipeline II=1
            input_buffer[i][j] = multi_chunks[i * MAX_CHUNK_SIZE + j];
        }
    }

    Main_loop_i: for(int i = 0; i < CHUNKS_IN_SINGLE_KERNEL; i++){
        #pragma HLS unroll
        // lzw(&multi_chunks[i * MAX_CHUNK_SIZE], length[i], &file_buffer[i * MAX_FILE_BUFFER_SIZE], &total_bytes[i]);
        lzw(input_buffer[i], length[i], output_buffer[i], total_bytes + i);
    }

    Epi_loop_i: for(int i = 0; i < CHUNKS_IN_SINGLE_KERNEL; i++){
        Epi_loop_j: for(int j = 0; j < total_bytes[i]; j++){
            #pragma HLS pipeline II=1
            file_buffer[i * MAX_FILE_BUFFER_SIZE + j] = output_buffer[i][j];
        }
    }
    
    return;
}