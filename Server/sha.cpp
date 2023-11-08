#include "sha.h"
#include <stdlib.h>




static const data_block_32 k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};


//pre process the input chunk so that make sure the data length can be divided by 512
void sha_pre_processing(std::string& input_chunk,std::vector<data_chunk>& M){
    unsigned long long total_data_len = input_chunk.length(); 
    unsigned long long total_bits = total_data_len*8; 
    unsigned long long remain_data_len=total_data_len;
    int chunk_num=total_data_len/64;//find how many chunks required
    int position=0;
    
    data_chunk current_chunk;
   
    while(position<total_data_len)
    {
        if (remain_data_len<64)//if the input is shorter than 64 byte, than only 1 or 2 block
        {
            for (size_t i = 0; i < remain_data_len; i++)
                {
                    current_chunk[i]=input_chunk[position+i];
                }
                current_chunk[remain_data_len]=0x80;


                if (remain_data_len<56)//last 8 byte is to indicate the input length, if the input is shorter than 56 than 1 block is enough
                {
                    for (size_t i = remain_data_len+1; i < 56; i++)
                    {
                        current_chunk[i]=0x00;
                    }
                    current_chunk[63]=total_bits;
                    current_chunk[62]=total_bits>>8;
                    current_chunk[61]=total_bits>>16;
                    current_chunk[60]=total_bits>>24;
                    current_chunk[59]=total_bits>>32;
                    current_chunk[58]=total_bits>>40;
                    current_chunk[57]=total_bits>>48;
                    current_chunk[56]=total_bits>>56;  
                    M.push_back(current_chunk);
                }
                else  //if not, we need to fill the rest of the blcok with all zero and open a new block, fill zero until last 8 byte
                {
                    for (size_t i = remain_data_len; i < 64; i++)
                    {
                        current_chunk[i]=0x00;
                    }
                    
                    
                    for (size_t i = 0; i < 56; i++)
                    {
                        current_chunk[i]=0x00;
                    }
                    current_chunk[63]=total_bits;
                    current_chunk[62]=total_bits>>8;
                    current_chunk[61]=total_bits>>16;
                    current_chunk[60]=total_bits>>24;
                    current_chunk[59]=total_bits>>32;
                    current_chunk[58]=total_bits>>40;
                    current_chunk[57]=total_bits>>48;
                    current_chunk[56]=total_bits>>56; 
                    M.push_back(current_chunk);
                }
        }     
        else//if input is longer than 64, warp up for each 64 byte
        {
            for (size_t i = 0; i < 64; i++)
            {
                current_chunk[i]=input_chunk[position+i];
            }
            M.push_back(current_chunk);
            remain_data_len-=64;  
        }
        position+=64;
    }
}


/*
//initialized the hash value of each 512 bits block
void sha_ini(std::vector<data_chunk>& M,std::vector<hash_part>& H_ini){
     hash_part current_hash;

        current_hash[0]=0x6a09e667;
        current_hash[1]=0xbb67ae85;
        current_hash[2]=0x3c6ef372;
        current_hash[3]=0xa54ff53a;
        current_hash[4]=0x510e527f;
        current_hash[5]=0x9b05688c;
        current_hash[6]=0x1f83d9ab;
        current_hash[7]=0x5be0cd19;
        H_ini.push_back(current_hash);
}
*/

//some logic function in SHA computation
//reference from https://github.com/james-ben/mpsoc-crypto/blob/master/sha256/software/sha256.c
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))


void sha_compute(std::vector<data_chunk>& M,hash_part& Hash_final){
    std::vector<hash_part> H;
    hash_part current_hash;
    data_block_32 a, b, c, d, e, f, g, h, i, j, t1, t2, w[64];//what is i,j?

        current_hash[0]=0x6a09e667;
        current_hash[1]=0xbb67ae85;
        current_hash[2]=0x3c6ef372;
        current_hash[3]=0xa54ff53a;
        current_hash[4]=0x510e527f;
        current_hash[5]=0x9b05688c;
        current_hash[6]=0x1f83d9ab;
        current_hash[7]=0x5be0cd19;
        H.push_back(current_hash);


    for (size_t p = 0; p < M.size(); p++)
    {
        //if we stream the block, we dont need to consider whether it is the first block
        if (p!=0){
            a=H[p-1][0];
            b=H[p-1][1];
            c=H[p-1][2];
            d=H[p-1][3];
            e=H[p-1][4];
            f=H[p-1][5];
            g=H[p-1][6];
            h=H[p-1][7];
        }
        else{
            a=H[0][0];
            b=H[0][1];
            c=H[0][2];
            d=H[0][3];
            e=H[0][4];
            f=H[0][5];
            g=H[0][6];
            h=H[0][7];
        }
             


        for (i = 0; i < 64; ++i) {
            if (i<16){
                w[i]= (M[p][0] << 24) | (M[p][1]<< 16) | (M[p][2] << 8) | (M[p][3]);
            }
            else{
                w[i] = SIG1(w[i - 2]) + w[i - 7] + SIG0(w[i - 15]) + w[i - 16];
            }
            
            t1 = h + EP1(e) + CH(e,f,g) + k[i] + w[i];
            t2 = EP0(a) + MAJ(a,b,c);
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }

        current_hash[0]+=a;
        current_hash[1]+=b;
        current_hash[2]+=c;
        current_hash[3]+=d;
        current_hash[4]+=e;
        current_hash[5]+=f;
        current_hash[6]+=g;
        current_hash[7]+=h;
        H.push_back(current_hash);
    }
    Hash_final=H.back();
}





void sha(std::string& input_chunk,std::array<unsigned int,8>& output_hash){
    std::vector<data_chunk> M;//the data block of the input chunk, each block is 64 byte
    hash_part final_hash;
    sha_pre_processing(input_chunk,M);

    sha_compute(M,final_hash);
}



// int main(){

//     std::string test_input;
//     std::array<unsigned int,8> hash256_value;
//     test_input="abc";
//     //test_input="The quick brown fox jumps over the lazy dog twice. The quick brown fox jumps over the lazy dog twice.";
//     std::vector<data_chunk> M;
//     sha_pre_processing(test_input,M);
//     sha(test_input,hash256_value);
//     std::cout <<std::hex<<"hash value is: "<<hash256_value[0]<<hash256_value[1]<<hash256_value[2]<<hash256_value[3]<< hash256_value[4]<<hash256_value[5]<<hash256_value[6]<<hash256_value[7]<<std::endl;

/*
//---------------------------------------------------------------------------------------
//test data preprocessing result
    for (size_t k = 0; k< M.size(); k++)
    {
         std::cout<<"Data block number "<<k<<" : ------------------------------"<<std::endl;
        for (size_t i = 0; i < 64; i++)
        {
            if (!M.empty() && !M[0].empty()) {
                //std::cout << std::hex << static_cast<int>(M[0][i]) << std::endl;
                std::bitset<8> bits(M[k][i]);
                std::cout <<"byte "<<i<<" is: "<<bits<< std::endl;
            } else {
                std::cerr << "Error: Attempt to access empty vector or data_chunk." << std::endl;
            }
        }
        std::cout<<std::endl;
    }
//-------------------------------------------------------------------------------------- 
*/





