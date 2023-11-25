#include "lzw.h"
#include <hls_stream.h>
#include <ap_int.h>

static void read_input(unsigned char *s1, hls::stream<unsigned char>& chr_stream, int length){
mem_rd:
    for(int i = 1; i < length; i++){
// #pragma HLS LOOP_TRIPCOUNT min = MAX max = length
        chr_stream << s1[i];
    }
}

static void write_result(uint16_t* out_code, hls::stream<uint16_t>& cmprs_stream, int *out_len){
mem_wr:
    for(int i = 0; i < *out_len; i++){
// #pragma HLS LOOP_TRIPCOUNT min = *out_len max = *out_len
        out_code[i] = cmprs_stream.read();
    }
}

static void compute_lzw(hls::stream<unsigned char>& chr_stream, hls::stream<uint16_t>& cmprs_stream, int length, int *out_len, unsigned long *hash_table, assoc_mem* my_assoc_mem){
    int nxt_code = 256, prefix_code = chr_stream.read();
    unsigned int code = 0;
    char nxt_char = 0;
    *out_len = 0;

    for(int i = 1; i < length; i++){
// #pragma HLS LOOP_TRIPCOUNT min = length max = length
        nxt_char = chr_stream.read();
        
        // detect hit or not
        bool hit = 0;
        lookup(hash_table, my_assoc_mem, (prefix_code << 8) + nxt_char, &hit, &code);
        
        if(!hit){
            cmprs_stream << prefix_code;
            (*out_len) += 1;

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
            if(i + 1 == length) cmprs_stream << prefix_code;
        }
    }
}

static void init_mem(unsigned long *hash_table, assoc_mem* my_assoc_mem){
    // make sure the memories are clear
    for(int i = 0; i < CAPACITY; i++)
    {
        #pragma HLS PIPELINE II=1
        hash_table[i] = 0;
    }
    my_assoc_mem->fill = 0;
    for(int i = 0; i < 512; i++)
    {
        #pragma HLS PIPELINE II=1
        my_assoc_mem->upper_key_mem[i] = 0;
        my_assoc_mem->middle_key_mem[i] = 0;
        my_assoc_mem->lower_key_mem[i] = 0;
    }

    // init the memories with the first 256 codes
    for(unsigned long i = 0; i < 256; i++)
    {
        #pragma HLS PIPELINE II=1
        bool collision = 0;
        unsigned int key = (i << 8) + 0UL; // lower 8 bits are the next char, the upper bits are the prefix code
        insert(hash_table, my_assoc_mem, key, i, &collision);
    }
}

static void hardware_encoder(unsigned char* s1, int length, uint16_t* out_code, int *out_len, unsigned long* hash_table, assoc_mem* my_assoc_mem){
    hls::stream<unsigned char> chr_stream("char_stream");
    hls::stream<uint16_t> cmprs_stream("compress_stream");

#pragma HLS STREAM variable = chr_stream depth = 32
#pragma HLS STREAM variable = cmprs_stream depth = 32

#pragma HLS dataflow
    read_input(s1, chr_stream, length);
    compute_lzw(chr_stream, cmprs_stream, length, out_len, hash_table, &my_assoc_mem);
    write_result(out_code, cmprs_stream, out_len);
}

void lzw_stream(unsigned char* s1, int length, uint16_t* out_code, int *out_len){
    unsigned long hash_table[CAPACITY];
    assoc_mem my_assoc_mem;

    init_mem(hash_table, &my_assoc_mem);
    hardware_encoder(s1, length, out_code, out_len, hash_table, &my_assoc_mem);
}