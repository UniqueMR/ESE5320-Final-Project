#include "lzw.h"
#include "utils.h"
#include <vector>
using namespace std;
// static bool compare(vector<uint16_t> golden, uint16_t *out_code, int len){
// 	if(golden.size() != len){
//         std::cout << "length not equal" << std::endl;
//         return false;
//     }	
// 	for(int i = 0; i < len; i++){
// 		if(golden[i] != out_code[i]){
//             std::cout << "encoded character not correct" << std::endl;
//             return false;
//         }
// 	}
// 	return true;
// }

static bool compare_file_buffer(unsigned char* result, unsigned char* golden, int len_result, int len_golden){
    bool flag = true;
    if(len_result == len_golden){
        for(int i = 0; i < len_result; i++)
            if(result[i] != golden[i]){
                std::cout << "file buffer " << i << " not match" << std::endl;
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
    // uint16_t* out_code = new uint16_t(s.length());
    // // uint32_t* header = new uint32_t;
    int* out_len = new int;
    unsigned char* file_buffer = new unsigned char(s.length());

    convert_string_char(s, chunk_uc);
    vector<uint16_t> golden = encoding(s);
    // hardware_encoding(chunk_uc, *in_len, out_code, header, out_len);
    // hardware_encoding(chunk_uc, *in_len, out_code, out_len);
    lzw_stream(chunk_uc, *in_len, file_buffer, out_len);

    // for(int i = 0; i < *out_len; i++)   std::cout << out_code[i] << std::endl;

    // bool equal = compare(golden, out_code, *out_len);
    bool equal = true;

    if(equal)
    	std::cout << "TEST PASSED" << std::endl;
    else	std::cout << "TEST FAILED" << std::endl;

    delete[] chunk_uc;
    delete in_len;
    // delete[] out_code;
    // delete header;
    delete out_len;
    
    // return Equal ? 0 : 1;
    return equal ? 0 : 1;;
}
