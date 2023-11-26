#include "lzw.h"
#include <hls_stream.h>
#include <ap_int.h>

static void read_input(unsigned char *s1, hls::stream<unsigned char>& chr_stream, int length){
mem_rd:
    for(int i = 0; i < length; i++){
// #pragma HLS LOOP_TRIPCOUNT min = MAX max = length
        chr_stream.write(s1[i]);
    }
}

static void write_result(uint16_t* out_code, hls::stream<uint16_t>& cmprs_stream, hls::stream<int> &cmprs_len_stream, int *out_len){
mem_wr:
    *out_len = cmprs_len_stream.read();
    for(int i = 0; i < *out_len; i++){
// #pragma HLS LOOP_TRIPCOUNT min = *out_len max = *out_len
        out_code[i] = cmprs_stream.read();
    }
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
    #pragma HLS dataflow
    clear_hash_table(hash_table);
    clear_assoc_mem(my_assoc_mem);
}

static void init_mem(unsigned long *hash_table, assoc_mem* my_assoc_mem){
    clear_mem(hash_table, my_assoc_mem);

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
    hls::stream<int> cmprs_len_stream("compress_length_stream");

#pragma HLS STREAM variable = chr_stream depth = 32
#pragma HLS STREAM variable = cmprs_stream depth = 32
#pragma HLS STREAM variable = cmprs_len_stream depth = 32

#pragma HLS dataflow
    read_input(s1, chr_stream, length);
    compute_lzw(chr_stream, cmprs_stream, length, cmprs_len_stream, hash_table, my_assoc_mem);
    write_result(out_code, cmprs_stream, cmprs_len_stream, out_len);
}

void lzw_stream(unsigned char* s1, int length, uint16_t* out_code, int *out_len){
    unsigned long hash_table[CAPACITY];
    assoc_mem my_assoc_mem;

    init_mem(hash_table, &my_assoc_mem);
    hardware_encoder(s1, length, out_code, out_len, hash_table, &my_assoc_mem);
}