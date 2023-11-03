#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

void convert_string_char(std::string chunk_s, unsigned char* chunk_uc);

std::string toHexString(const unsigned char* data, int length);