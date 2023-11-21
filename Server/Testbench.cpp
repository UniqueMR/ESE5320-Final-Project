#include "lzw.h"
#include "utils.h"
#include <vector>
using namespace std;
static bool compare(vector<uint16_t> golden, uint16_t *out_code, int len){
	if(golden.size() != len)	return false;
	for(int i = 0; i < len; i++){
		if(golden[i] != out_code[i])	return false;
	}
	return true;
}

int main()
{
    std::string s = "WYS*WYGWYS*WYSWYSG";
    unsigned char* chunk_uc = new unsigned char(s.length());
    int* in_len = new int;
    *in_len = s.length();
    uint16_t* out_code = new uint16_t(s.length());
    // uint32_t* header = new uint32_t;
    int* out_len = new int;

    convert_string_char(s, chunk_uc);
    vector<uint16_t> golden = encoding(s);
    // hardware_encoding(chunk_uc, *in_len, out_code, header, out_len);
    hardware_encoding(chunk_uc, *in_len, out_code, out_len);


    if(compare(golden, out_code, *out_len))
    	std::cout << "TEST PASSED" << std::endl;
    else	std::cout << "TEST FAILED" << std::endl;

    delete[] chunk_uc;
    delete in_len;
    delete[] out_code;
    // delete header;
    delete out_len;
    
    // return Equal ? 0 : 1;
    return 1;
}
