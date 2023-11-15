#ifndef _ENCODER_H_
#define _ENCODER_H_

// max number of elements we can get from ethernet
#define NUM_ELEMENTS 16384
#define HEADER 2

#endif

#include "cdc.h"
#include "sha.h"
#include "lzw.h"
#include "utils.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "server.h"
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unordered_map>
#include <vector>
#include "stopwatch.h"
#include "deduplication.h"

#define NUM_PACKETS 8
// #define pipe_depth 4
#define DONE_BIT_L (1 << 7)
#define DONE_BIT_H (1 << 15)

void handle_input(int argc, char* argv[], int* blocksize);