#include "lzw.h"
#include <hls_stream.h>
#include <ap_int.h>
#include <ap_fixed.h>

#define CAPACITY 32768

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