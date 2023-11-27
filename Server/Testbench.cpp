#include "lzw.h"
#include "utils.h"
#include <vector>
using namespace std;

static void write_encoded_file_buf(uint16_t* out_code, int out_len, unsigned char* file_buffer, int &total_bytes){
    int total_bits = out_len * 12;
    total_bytes = static_cast<int>(std::ceil(total_bits / 8.0));
    uint32_t header = static_cast<uint32_t>(total_bytes & 0xFFFFFFFF) << 1;

    int i = 0, j = 0;

    file_buffer[j++] = static_cast<unsigned char>(header & 0xFF);
    file_buffer[j++] = static_cast<unsigned char>((header >> 8) & 0xFF);
    file_buffer[j++] = static_cast<unsigned char>((header >> 16) & 0xFF);
    file_buffer[j++] = static_cast<unsigned char>(header >> 24);
    for(i = 0; i + 1 < out_len; i += 2){
        file_buffer[j++] = static_cast<unsigned char>(out_code[i] >> 4);
        file_buffer[j++] = static_cast<unsigned char>(((out_code[i] << 4) & 0xF0) | ((out_code[i + 1] >> 8) & 0x0F));
        file_buffer[j++] = static_cast<unsigned char>(out_code[i + 1] & 0xFF);
    }
    if(i != out_len){
        file_buffer[j++] = static_cast<unsigned char>(out_code[i] >> 4);
        file_buffer[j++] = static_cast<unsigned char>((out_code[i] << 4) & 0xF0);
    }
    return;
}

static void vector_to_array(vector<uint16_t> vec, uint16_t* arr, int &len){
    len = vec.size();
    for(int i = 0; i < len; i++){
        arr[i] = vec[i];
    }
    return;
}

static bool compare_file_buffer(unsigned char* result, unsigned char* golden, int len_result, int len_golden){
    bool flag = true;
    if(len_result == len_golden){
        for(int i = 0; i < len_result; i++)
            if(result[i] != golden[i]){
                std::cout << "file buffer " << i << " not match" << std::endl;
                std::cout << "result: " << std::hex << static_cast<int>(result[i]) << " ;golden: " << std::hex << static_cast<int>(golden[i]) << std::endl;
                flag = false;
            } 
        return flag;
    }
    else{
        std::cout << "length not match" << std::endl;
        return false;
    }
}

int main()
{
    std::string s = "WYS*WYGWYS*WYSWYSG";
    unsigned char* chunk_uc = new unsigned char(s.length());
    int* in_len = new int;
    *in_len = s.length();
    int* out_len = new int;
    unsigned char* file_buffer = new unsigned char(100);

    convert_string_char(s, chunk_uc);
    vector<uint16_t> golden = encoding(s);
    uint16_t* golden_buf = new uint16_t(golden.size());
    int golden_len; 
    vector_to_array(golden, golden_buf, golden_len);
    unsigned char* golden_file_buf = new unsigned char(std::ceil(golden_len * 3 / 2) + 4);
    int golden_file_buf_len;
    write_encoded_file_buf(golden_buf, golden_len, golden_file_buf, golden_file_buf_len);
    lzw_stream(chunk_uc, *in_len, file_buffer, out_len);

    bool equal = compare_file_buffer(file_buffer, golden_file_buf, *out_len, golden_file_buf_len);

    if(equal)
    	std::cout << "TEST PASSED" << std::endl;
    else	std::cout << "TEST FAILED" << std::endl;

    delete[] chunk_uc;
    delete in_len;
    delete out_len;
    
    return equal ? 0 : 1;;
}
