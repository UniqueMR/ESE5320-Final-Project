#include <stdlib.h>
#include <iostream>

// The arrays are 512 bits deep because we are pretending the key will be 18 bits wide
// and each mem gets half the key, (2^9 == 512).
unsigned long upper_key_mem[512]; // the output of these  will be 64 bits wide (size of unsigned long).
unsigned long lower_key_mem[512]; 
unsigned int value[64];    // value store is 64 deep, because the lookup mems are 64 bits wide
unsigned int fill = 0;  // tells us how many entries we've currently stored 

void insert(unsigned int key, unsigned int val)
{
    std::cout << "insert(key=" << key << ",val=" << val << ")" << std::endl;
    upper_key_mem[(key >> 9)%512] |= (1 << fill);  // set the fill'th bit to 1, while preserving everything else
    lower_key_mem[(key >> 0)%512] |= (1 << fill);  // set the fill'th bit to 1, while preserving everything else
    value[fill] = val;
    fill++;
}

void lookup(unsigned int key)
{
    std::cout << "lookup(key=" << key << "):" << std::endl;
    unsigned int match_high = upper_key_mem[(key >> 9)%512];
    unsigned int match_low  = lower_key_mem[(key >> 0)%512];

    unsigned int match = match_high & match_low;

    unsigned int address = 0;
    for(; address < 64; address++)
    {
        if((match >> address) & 0x1)
        {   
            // exit the loop when address equals
            // the bit possition of the bit that
            // is flipped high
            break;
        }
    }
    if(address != 64)
    {
        std::cout << "\taddress = " << address << std::endl;
        std::cout << "\tvalue = " << value[address] <<std::endl;
    }
    else
    {
        std::cout << "\tmiss" << std::endl;
    }
}

int main()
{    
    // make sure the memories are clear
    for(int i = 0; i < 512; i++)
    {
        upper_key_mem[i] = 0;
        lower_key_mem[i] = 0;
    }

    // run some tests
    insert(3,5);
    insert(0,8);
    lookup(0);
    lookup(3);
    lookup(23);

    return 0;
}