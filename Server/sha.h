<<<<<<< HEAD
// #include<array>
// void sha(unsigned char* input_chunk, std::array<unsigned char, 32> &hash_value);
#include <iostream>
#include <string>
void sha(std::string input_chunk, unsigned char* output_hash);
=======
#include <iostream>
#include<array>
#include<vector>

typedef unsigned char data_block_8;
typedef unsigned int data_block_32;
typedef std::array<unsigned char,64> data_chunk;//each data chunk is a 512 block
typedef std::array<unsigned int,8> hash_part;

void sha_pre_processing(std::string& input_chunk,std::vector<data_chunk>& M);
void sha_compute(std::vector<data_chunk>& M,hash_part& Hash_final);
void sha(std::string& input_chunk,std::array<unsigned int,8>& output_hash);
>>>>>>> Xingjian
