#include<iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <stdint.h>
#include <math.h>
#include <unordered_map>

void printBinary(unsigned char*out_code, int codelen){
    for (int i = 0; i < codelen; i++) {
        printf("Binary of %d: ", out_code[i]);
        for (int bit = 15; bit >= 0; bit--) {
            uint16_t mask = 1 << bit;
            putchar((out_code[i] & mask) ? '1' : '0');
        }
        putchar('\n');
    }
}
#define CODE_LENGTH (13)

typedef std::vector<std::string> code_table;
typedef std::vector<std::string> chunk_list;

static code_table Code_table;

static std::ifstream Input;
static size_t Input_position;

static int Read_code(void)
{
  static unsigned char Byte;

  int Code = 0;
  int Length = CODE_LENGTH;
  for (int i = 0; i < Length; i++)
  {
    if (Input_position % 8 == 0)
      Byte = Input.get();
    Code = (Code << 1) | ((Byte >> (7 - Input_position % 8)) & 1);
    Input_position++;
  }
  return Code;
}
std::vector<uint16_t> encoding(std::string s1)
{
    std::cout << "Encoding\n";
    std::unordered_map<std::string, int> table;
    for (int i = 0; i <= 255; i++) {
        std::string ch = "";
        ch += char(i);
        table[ch] = i;
    }
 
    std::string p = "", c = "";
    p += s1[0];
    int code = 256;
    std::vector<uint16_t> output_code;
    std::cout << "String\tOutput_Code\tAddition\n";
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            std::cout << p << "\t" << table[p] << "\t\t"
                 << p + c << "\t" << code << std::endl;
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    std::cout << p << "\t" << table[p] << std::endl;
    output_code.push_back(table[p]);
    return output_code;
}
static const std::string Decompress(size_t Size)
{
    Input_position = 0;

    Code_table.clear();
    for (int i = 0; i < 256; i++)
        Code_table.push_back(std::string(1, (char) i));

    int Old = Read_code();
    std::string Symbol(1, Old);
    std::string Output = Symbol;
    while (Input_position / 8 < Size - 1)
    {
        int New = Read_code();
        std::string Symbols;
        if (New >= (int) Code_table.size())
        Symbols = Code_table[Old] + Symbol;
        else
        Symbols = Code_table[New];
        Output += Symbols;
        Symbol = std::string(1, Symbols[0]);
        Code_table.push_back(Code_table[Old] + Symbol);
        Old = New;
    }

    return Output;
}
int main(){
    // // typedef std::vector<std::string> code_table;
    // // typedef std::vector<std::string> chunk_list;
    // // static code_table Code_table;
    // // Code_table.clear();
    // // for (int i = 0; i < 256; i++){
    // //     if (!std::isprint(i)) { // Check if character is not printable
    // //         Code_table.push_back(".");
    // //     } else {
    // //         Code_table.push_back(std::string(1, (char)(i)));
    // //     }
    // //     std::cout << i << ": " << Code_table[i] << std::endl;
    // // }
    // std::string s = "WYS*WYGWYS*WYSWYSG";

    // std::vector<uint16_t> out_code = encoding(s);
    // int out_len = out_code.size();
    // // uint16_t* out_code = (uint16_t*)malloc(sizeof(uint16_t)*out_len);
    // // for (int i=0; i<out_len;i++){
    // //     out_code[i]=0;
    // // }      
    // //uint16_t out_code[12] = {87, 89, 83, 42, 256, 71, 256, 83, 259, 257, 262,71};
    
    // //uint16_t out_code[10] = {8191,8191,8191,8191,8191,8191,8191,8191,8191,8191};
    
    // int total_bits = out_len * 13;
    // int total_bytes = static_cast<int>(std::ceil(total_bits / 8.0));
    // //printf("total_bytes = %d\n",total_bytes);
    // uint32_t header;
    // header = static_cast<uint32_t>(total_bytes & 0xFFFFFFFF) << 1;

    // unsigned char* file_buffer = (unsigned char*)malloc(sizeof(unsigned char) * (total_bytes + 4));

    // int i, j = 0;
    // file_buffer[j++] = static_cast<unsigned char>(header & 0xFF);
    // file_buffer[j++] = static_cast<unsigned char>((header >> 8) & 0xFF);
    // file_buffer[j++] = static_cast<unsigned char>((header >> 16) & 0xFF);
    // file_buffer[j++] = static_cast<unsigned char>(header >> 24 & 0xFF);
    // // for(i = 0; i + 1 < out_len; i += 2){
    // //     file_buffer[j++] = static_cast<unsigned char>(out_code[i] >> 4);
    // //     file_buffer[j++] = static_cast<unsigned char>(((out_code[i] << 4) & 0xF0) | ((out_code[i + 1] >> 8) & 0x0F));
    // //     file_buffer[j++] = static_cast<unsigned char>(out_code[i + 1] & 0xFF);
    // // }
    // // if(i != out_len){
    // //     file_buffer[j++] = static_cast<unsigned char>(out_code[i] >> 4);
    // //     file_buffer[j++] = static_cast<unsigned char>((out_code[i] << 4) & 0xF0);
    // // }
    // int bit_position = 0;
    // uint32_t current_word = 0; // Use uint32_t to have enough space for bit manipulation
    // int shift = 8;
    // int flag=0;
    // for (i = 0; i < out_len; i++) {
    //     if(flag)
    //         current_word>>=8;
    //     // Load the 12-bit code into the MSB side of current_word
    //     if (3 - bit_position >= 0){
    //         current_word |= (static_cast<uint32_t>(out_code[i] & 0x1FFF) << (3 - bit_position));
    //         flag = 0;
    //     }
    //     else{
    //         current_word<<=8;
    //         //out_code[i]<<=8;
    //         flag = 1;
    //         current_word |= (static_cast<uint32_t>(out_code[i] & 0x1FFF) << (-bit_position + 11));
    //     }
    //     bit_position += 13; // Increment the bit position by 12

    //     // Write bytes to the file buffer while there are at least 8 bits from MSB side
    //     while (bit_position >= 8) {
    //         if(flag)
    //             file_buffer[j++] = static_cast<unsigned char>((current_word >> 16) & 0xFF); // Extract the highest 8 bits
    //         else
    //             file_buffer[j++] = static_cast<unsigned char>((current_word >> 8) & 0xFF); // Extract the highest 8 bits
    //         bit_position -= 8; // Adjust the bit position
    //         current_word <<= 8;
    //         }
    //     }
    // // Handle remaining bits, if any
    // if (bit_position > 0) {
    //     file_buffer[j++] = static_cast<unsigned char>((current_word >> (16 - 8)) & 0xFF);
    // }

    // // std::cout << std::endl;
    // // for (int i = 0; i <  total_bytes +4; i++) {
    // //     printf("Binary of %d: ", out_code[i]);

    // //     // for (int bit = 7; bit >= 0; bit--) {
    // //     //     uint16_t mask = 1 << bit;
    // //     //     putchar((out_code[i] & mask) ? '1' : '0');
    // //     // }
    // //     // putchar(' ');
    // //     printf("Binary of %d: ", file_buffer[i]);
    // //     for (int bit = 7; bit >= 0; bit--) {
    // //         uint16_t mask = 1 << bit;
    // //         putchar((file_buffer[i] & mask) ? '1' : '0');
    // //     }
    // //     putchar('\n');
    // // }
    // //printBinary(file_buffer, total_bytes + 4);
    // std::ofstream outfile("encoded_data.bin", std::ios::binary);
    // if (!outfile.is_open()) {
    //     std::cerr << "Could not open the file for writing.\n";
    //     return 0;
    // }

    // // Write the data to the file
    // outfile.write(reinterpret_cast<const char*>(file_buffer), total_bytes + 4);

    // // Check for write errors
    // if (!outfile.good()) {
    //     std::cerr << "Error occurred while writing to the file.\n";
    // }

    // // Close the file
    // outfile.close();
    Input.open("../Server/encoded_data.bin", std::ios::binary);
    if (!Input.good()){
    std::cerr << "Could not open input file.\n";
    return EXIT_FAILURE;
    }
    // uint32_t Header;
    // Input.read((char *) &Header, sizeof(int32_t));
    // printf("Header = %d\n",Header>>1);
    // int *code=new int[out_len];
    // for (int i = 0; i <  out_len; i++) {
    //     code[i] = Read_code();
    //     printf("Code[%d] = %d\n",i,code[i]);
    // }   
    std::ofstream Output("decoded_data.bin", std::ios::binary);
    if (!Output.good())
    {
        std::cerr << "Could not open output file.\n";
        return EXIT_FAILURE;
    }
    Input_position = 0;
    chunk_list Chunks;
    int i = 0;
    while (true)
    {
    uint32_t Header;
    Input.read((char *) &Header, sizeof(int32_t));
    if (Input.eof())
      break;

    if ((Header & 1) == 0)
    {
      int Chunk_size = Header >> 1;
      const std::string & Chunk = Decompress(Chunk_size);
      Chunks.push_back(Chunk);
      std::cout << "Decompressed chunk of size " << Chunk.length() << ".\n";
      Output.write(&Chunk[0], Chunk.length());
    }
    else
    {
     int Location = Header >> 1;
      if (Location<Chunks.size()) {  // defensive programming to avoid out-of-bounds reference
          const std::string & Chunk = Chunks[Location];
          std::cout << "Found chunk of size " << Chunk.length() << " in database.\n";
          Output.write(&Chunk[0], Chunk.length());
	  }
      else
      {
       std::cerr << "Location " << Location << " not in database of length " << Chunks.size() << " ignoring block.  Likely encoder error.\n";
       }
    }
    i++;
  }
}
