#ifndef SRC_UTILITIES_
#define SRC_UTILITIES_
#endif

#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

//this value should be more carefully defined afterwards
#define MAX_CHUNK_SIZE 100000
#define MAX_FILENAME_SIZE 100

#include "utils.h"
#include "EventTimer.h"
#include "../Server/encoder.h"

