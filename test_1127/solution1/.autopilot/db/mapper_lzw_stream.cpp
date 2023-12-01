#include <systemc>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
extern "C" void lzw_stream(int*, int, int, int, int);
extern "C" void apatb_lzw_stream_hw(volatile void * __xlx_apatb_param_s1, int __xlx_apatb_param_length, volatile void * __xlx_apatb_param_file_buffer, volatile void * __xlx_apatb_param_total_bytes) {
  // Collect __xlx_s1_file_buffer_total_bytes__tmp_vec
  vector<sc_bv<32> >__xlx_s1_file_buffer_total_bytes__tmp_vec;
  for (int j = 0, e = 1; j != e; ++j) {
    __xlx_s1_file_buffer_total_bytes__tmp_vec.push_back(((int*)__xlx_apatb_param_s1)[j]);
  }
  int __xlx_size_param_s1 = 1;
  int __xlx_offset_param_s1 = 0;
  int __xlx_offset_byte_param_s1 = 0*4;
  for (int j = 0, e = 1; j != e; ++j) {
    __xlx_s1_file_buffer_total_bytes__tmp_vec.push_back(((int*)__xlx_apatb_param_file_buffer)[j]);
  }
  int __xlx_size_param_file_buffer = 1;
  int __xlx_offset_param_file_buffer = 1;
  int __xlx_offset_byte_param_file_buffer = 1*4;
  for (int j = 0, e = 1; j != e; ++j) {
    __xlx_s1_file_buffer_total_bytes__tmp_vec.push_back(((int*)__xlx_apatb_param_total_bytes)[j]);
  }
  int __xlx_size_param_total_bytes = 1;
  int __xlx_offset_param_total_bytes = 2;
  int __xlx_offset_byte_param_total_bytes = 2*4;
  int* __xlx_s1_file_buffer_total_bytes__input_buffer= new int[__xlx_s1_file_buffer_total_bytes__tmp_vec.size()];
  for (int i = 0; i < __xlx_s1_file_buffer_total_bytes__tmp_vec.size(); ++i) {
    __xlx_s1_file_buffer_total_bytes__input_buffer[i] = __xlx_s1_file_buffer_total_bytes__tmp_vec[i].range(31, 0).to_uint64();
  }
  // DUT call
  lzw_stream(__xlx_s1_file_buffer_total_bytes__input_buffer, __xlx_offset_byte_param_s1, __xlx_apatb_param_length, __xlx_offset_byte_param_file_buffer, __xlx_offset_byte_param_total_bytes);
// print __xlx_apatb_param_s1
  sc_bv<32>*__xlx_s1_output_buffer = new sc_bv<32>[__xlx_size_param_s1];
  for (int i = 0; i < __xlx_size_param_s1; ++i) {
    __xlx_s1_output_buffer[i] = __xlx_s1_file_buffer_total_bytes__input_buffer[i+__xlx_offset_param_s1];
  }
  for (int i = 0; i < __xlx_size_param_s1; ++i) {
    ((int*)__xlx_apatb_param_s1)[i] = __xlx_s1_output_buffer[i].to_uint64();
  }
// print __xlx_apatb_param_file_buffer
  sc_bv<32>*__xlx_file_buffer_output_buffer = new sc_bv<32>[__xlx_size_param_file_buffer];
  for (int i = 0; i < __xlx_size_param_file_buffer; ++i) {
    __xlx_file_buffer_output_buffer[i] = __xlx_s1_file_buffer_total_bytes__input_buffer[i+__xlx_offset_param_file_buffer];
  }
  for (int i = 0; i < __xlx_size_param_file_buffer; ++i) {
    ((int*)__xlx_apatb_param_file_buffer)[i] = __xlx_file_buffer_output_buffer[i].to_uint64();
  }
// print __xlx_apatb_param_total_bytes
  sc_bv<32>*__xlx_total_bytes_output_buffer = new sc_bv<32>[__xlx_size_param_total_bytes];
  for (int i = 0; i < __xlx_size_param_total_bytes; ++i) {
    __xlx_total_bytes_output_buffer[i] = __xlx_s1_file_buffer_total_bytes__input_buffer[i+__xlx_offset_param_total_bytes];
  }
  for (int i = 0; i < __xlx_size_param_total_bytes; ++i) {
    ((int*)__xlx_apatb_param_total_bytes)[i] = __xlx_total_bytes_output_buffer[i].to_uint64();
  }
}
