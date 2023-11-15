#include <vector>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <CL/cl2.hpp>

std::vector<cl::Device> get_xilinx_devices();
char* read_binary_file(const std::string &xclbin_file_name, unsigned &nb);