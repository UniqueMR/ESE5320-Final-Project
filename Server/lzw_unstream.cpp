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

static void assoc_init(assoc_mem_t* mem){
    
    for(int i = 0; i < 32; i++)
    {
        mem->quarter_0[i] = 0;
        mem->quarter_1[i] = 0;
        mem->quarter_2[i] = 0;
        mem->quarter_3[i] = 0;
    }

    for(int i = 0; i < 64; i++){
        mem->value[i] = 0;
    }

    mem->fill = 0;
    
    return;
}

static void assoc_insert(assoc_mem_t* mem, unsigned int key, unsigned int val, bool* wfull){
    // key and val alignment
    key &= 0xFFFFF; // 20 bits
    val &= 0xFFF; // 12 bits

    int key_quarter_0 = key & 0x1f;
    int key_quarter_1 = (key >> 5) & 0x1f;
    int key_quarter_2 = (key >> 10) & 0x1f;
    int key_quarter_3 = (key >> 15) & 0x1f;

    if(mem->fill < 64){
        mem->quarter_0[key_quarter_0] = 1UL << mem->fill;
        mem->quarter_1[key_quarter_1] = 1UL << mem->fill;
        mem->quarter_2[key_quarter_2] = 1UL << mem->fill;
        mem->quarter_3[key_quarter_3] = 1UL << mem->fill;
        mem->value[mem->fill] = val;
        mem->fill++;
        *wfull = 0;
    }

    else    *wfull = 1;
}


static int one_hot_decode(unsigned long one_hot) {
    if (one_hot == 0) return -1;

    int upper_ptr = 64;
    int lower_ptr = 0;
    int ptr;

    while (upper_ptr > lower_ptr) {
        ptr = (upper_ptr + lower_ptr) / 2;

        if ((one_hot >> ptr) != 0) lower_ptr = ptr + 1;   
        else  upper_ptr = ptr; 
    }

    return upper_ptr - 1;
}

static void assoc_lookup(assoc_mem_t* mem, unsigned int key, unsigned int* result, bool* rhit){
    // key alignmemt
    key &= 0xFFFFF; // 20 bits

    int key_quarter_0 = key & 0x1f;
    int key_quarter_1 = (key >> 5) & 0x1f;
    int key_quarter_2 = (key >> 10) & 0x1f;
    int key_quarter_3 = (key >> 15) & 0x1f;

    unsigned long match_quarter_0 = mem->quarter_0[key_quarter_0];
    unsigned long match_quarter_1 = mem->quarter_1[key_quarter_1];
    unsigned long match_quarter_2 = mem->quarter_2[key_quarter_2];
    unsigned long match_quarter_3 = mem->quarter_3[key_quarter_3];

    unsigned long match = match_quarter_0 & match_quarter_1 & match_quarter_2 & match_quarter_3;
    int addr = one_hot_decode(match);

    if(addr == -1) *rhit = 0;
    else{
        *rhit = 1;
        *result = mem->value[addr];
    }
    return;
}

//****************************************************************************************************************
static void insert(unsigned long* hash_table, assoc_mem_t* mem, unsigned int key, unsigned int value, bool* collision)
{
    hash_insert(hash_table, key, value, collision);
    if(*collision)
    {
        assoc_insert(mem, key, value, collision);
    }
}

static void lookup(unsigned long* hash_table, assoc_mem_t* mem, unsigned int key, bool* hit, unsigned int* result)
{
    hash_lookup(hash_table, key, hit, result);
    if(!*hit)
    {
        assoc_lookup(mem, key, result, hit);
    }
}

static void clear_hash_table(unsigned long hash_table[CAPACITY]){
    #pragma HLS array_partition variable=hash_table type=block factor=32
    for(int i = 0; i < CAPACITY; i++)
    {
        hash_table[i] = 0;
    }
}

static void clear_mem(unsigned long *hash_table, assoc_mem_t* my_assoc_mem){
    #pragma HLS DATAFLOW
    clear_hash_table(hash_table);
    assoc_init(my_assoc_mem);
}

static void lzw(hls::stream<unsigned char>& input_stream, hls::stream<int>& length, hls::stream<unsigned char>& output_stream, hls::stream<int>& total_bytes){
    unsigned long hash_table[CAPACITY];
    assoc_mem_t my_assoc_mem;

    clear_mem(hash_table, &my_assoc_mem);

    uint16_t out_code[MAX_CHUNK_SIZE];

    int next_code = 256;

    int prefix_code = input_stream.read();
    unsigned int code = 0;
    char next_char = 0;

    int i = 0, j = 0;
    int local_len = length.read();
    while(i < local_len)
    {
        if(i + 1 == local_len){
            out_code[j++] = prefix_code;
            break;
        }

        next_char = input_stream.read();

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
    int local_total_bytes = (total_bits + 7) / 8;
    uint32_t header = static_cast<uint32_t>(local_total_bytes & 0xFFFFFFFF) << 1;
    total_bytes.write(local_total_bytes);

    for (int i = 0; i < 4; ++i) {
        #pragma HLS UNROLL
        output_stream.write(static_cast<unsigned char>((header >> (i * 8)) & 0xFF));
    }

    int m = 0, n = 4;

    for(m = 0; m + 1 < out_len; m += 2){
        #pragma HLS pipeline II=1
        output_stream.write(static_cast<unsigned char>(out_code[m] >> 4));
        output_stream.write(static_cast<unsigned char>(((out_code[m] << 4) & 0xF0) | ((out_code[m+1] >> 8) & 0x0F)));
        output_stream.write(static_cast<unsigned char>(out_code[m+1] & 0xFF));
        n += 3;
    }

    if(m != out_len){
        // std::cout << out_code_0 << std::endl;
        output_stream.write(static_cast<unsigned char>(out_code[m] >> 4));
        output_stream.write(static_cast<unsigned char>((out_code[m] << 4) & 0xF0));
    }

    return;
}


void lzw_multi_chunks(unsigned char multi_chunks[CHUNKS_IN_SINGLE_KERNEL * MAX_CHUNK_SIZE], int length[CHUNKS_IN_SINGLE_KERNEL], unsigned char file_buffer[CHUNKS_IN_SINGLE_KERNEL * MAX_FILE_BUFFER_SIZE], int total_bytes[CHUNKS_IN_SINGLE_KERNEL]){
#pragma HLS INTERFACE m_axi port=multi_chunks bundle=aximm1
#pragma HLS INTERFACE m_axi port=length bundle=aximm2
#pragma HLS INTERFACE m_axi port=file_buffer bundle=aximm3
#pragma HLS INTERFACE m_axi port=total_bytes bundle=aximm4

#pragma HLS dataflow

    hls::stream<unsigned char> stream_input[CHUNKS_IN_SINGLE_KERNEL];
    hls::stream<unsigned char> stream_output[CHUNKS_IN_SINGLE_KERNEL];
    hls::stream<int> len_input[CHUNKS_IN_SINGLE_KERNEL];
    hls::stream<int> len_output[CHUNKS_IN_SINGLE_KERNEL];

#pragma HLS stream variable=stream_input depth=250
#pragma HLS stream variable=stream_output depth=375
#pragma HLS stream variable=len_input depth=50
#pragma HLS stream variable=len_output depth=50

#pragma HLS array_partition variable=stream_input complete
#pragma HLS array_partition variable=stream_output complete
#pragma HLS array_partition variable=len_input complete
#pragma HLS array_partition variable=len_output complete

    Init_loop_i: for(int i = 0; i < CHUNKS_IN_SINGLE_KERNEL; i++){
        len_input[i].write(length[i]);
        Init_loop_j: for(int j = 0; j < length[i]; j++){
            #pragma HLS pipeline II=1
            stream_input[i].write(multi_chunks[i * MAX_CHUNK_SIZE + j]);
        }
    }

    Main_loop_i: for(int i = 0; i < CHUNKS_IN_SINGLE_KERNEL; i++){
        #pragma HLS unroll
        lzw(stream_input[i], len_input[i], stream_output[i], len_output[i]);
    }

    Epi_loop_i: for(int i = 0; i < CHUNKS_IN_SINGLE_KERNEL; i++){
        total_bytes[i] = len_output[i].read();
        Epi_loop_j: for(int j = 0; j < total_bytes[i] + 4; j++){
            #pragma HLS pipeline II=1
            file_buffer[i * MAX_FILE_BUFFER_SIZE + j] = stream_output[i].read();
        }
    }
    return;
}