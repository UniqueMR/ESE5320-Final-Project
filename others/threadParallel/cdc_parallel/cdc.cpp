#include "App.h"
#include <math.h>

#define WIN_SIZE 16
#define PRIME 3
#define MODULUS 256
#define TARGET 0
#define NUM_THREADS 4

stopwatch time_cdc;

uint64_t hash_func(unsigned char *input, unsigned int pos){
	uint64_t hash = 0;
	for(int i = 0; i < WIN_SIZE; i++){
		hash += static_cast<uint64_t>(input[pos + WIN_SIZE - 1 - i]) * std::pow(PRIME, i + 1);
	}
	return hash;
}

void cdc_coarse(unsigned char *buff, unsigned int buff_size, unsigned int begin, unsigned int end, unsigned int* &res, int &length){
    int idx = 0;
	uint64_t hash = 0;

	//new algorithm
	for(unsigned int i = begin; i < end; i++){
		if(i == begin)
        	hash = hash_func(buff, i);
		else
			hash = hash * PRIME - static_cast<uint64_t>(buff[i - 1]) * std::pow(PRIME, WIN_SIZE + 1) + static_cast<uint64_t>(buff[i - 1 + WIN_SIZE]) * PRIME;
        if((hash % MODULUS) == TARGET){
         res[idx] = i;
		 idx++;
        }
    }

	// //original algorithm
	// for(unsigned int i = begin; i < end; i++){
    //     hash = hash_func(buff, i);
    //     if((hash % MODULUS) == TARGET){
    //      res[idx] = i;
	// 	 idx++;
    //     }
    // }

	length = idx;
}

void cdc(unsigned char *buff, unsigned int buff_size)
{
	// // unparallelized
	// unsigned int begin = WIN_SIZE;
	// unsigned int end = buff_size - WIN_SIZE;
	// int len;
	// unsigned int* res = (unsigned int*)malloc((end - begin) * sizeof(int));

	// cdc_coarse(buff, buff_size, begin, end, res, len);

	// for(int i = 0; i < len; i++)
	// 	std::cout << res[i] << std::endl;

	// parallelized
	unsigned int begin = WIN_SIZE;
	unsigned int end = buff_size - WIN_SIZE;
	unsigned int mid_gap = (end - begin) / 4;
	unsigned int mid[3] = {begin + mid_gap, begin + 2 * mid_gap, begin + 3 * mid_gap};

	unsigned int* res_0 = (unsigned int*)malloc((mid[0] - begin) * sizeof(int));
	unsigned int* res_1 = (unsigned int*)malloc((mid[1] - mid[0]) * sizeof(int));
	unsigned int* res_2 = (unsigned int*)malloc((mid[2] - mid[1]) * sizeof(int));
	unsigned int* res_3 = (unsigned int*)malloc((end - mid[2]) * sizeof(int));

	int len_0, len_1, len_2, len_3;

    std::vector<std::thread> ths;
    ths.push_back(std::thread(&cdc_coarse, buff, buff_size, begin, mid[0], std::ref(res_0), std::ref(len_0)));
    ths.push_back(std::thread(&cdc_coarse, buff, buff_size, mid[0], mid[1], std::ref(res_1), std::ref(len_1)));
    ths.push_back(std::thread(&cdc_coarse, buff, buff_size, mid[1], mid[2], std::ref(res_2), std::ref(len_2)));
    ths.push_back(std::thread(&cdc_coarse, buff, buff_size, mid[2], end, std::ref(res_3), std::ref(len_3)));

    pin_thread_to_cpu(ths[0], 0);
    pin_thread_to_cpu(ths[1], 1);
	pin_thread_to_cpu(ths[2], 2);
	pin_thread_to_cpu(ths[3], 3);

    for (auto &th : ths)
    {
      th.join();
    }

	for(int i = 0; i < len_0; i++)
		std::cout << res_0[i] << std::endl;
	for(int i = 0; i < len_1; i++)
		std::cout << res_1[i] << std::endl;
	for(int i = 0; i < len_2; i++)
		std::cout << res_2[i] << std::endl;
	for(int i = 0; i < len_3; i++)
		std::cout << res_3[i] << std::endl;
}

void test_cdc( const char* file )
{
	FILE* fp = fopen(file,"r" );
	if(fp == NULL ){
		perror("fopen error");
		return;
	}

	fseek(fp, 0, SEEK_END); // seek to end of file
	int file_size = ftell(fp); // get current file pointer
	fseek(fp, 0, SEEK_SET); // seek back to beginning of file

	unsigned char* buff = (unsigned char *)malloc((sizeof(unsigned char) * file_size ));	
	if(buff == NULL)
	{
		perror("not enough space");
		fclose(fp);
		return;
	}

	int bytes_read = fread(&buff[0],sizeof(unsigned char),file_size,fp);

	//parallelize cdc over 4 threads here
	time_cdc.start();
	cdc(buff, file_size);
	time_cdc.stop();

	// std::cout << "The total execution time of cdc:" << time_cdc.latency() << " ns" << std::endl;

    free(buff);
    return;
}

int main()
{
	test_cdc("../data/prince.txt");
	return 0;
}