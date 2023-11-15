#include "encoder.h"

#define NUM_PACKETS 8
// #define pipe_depth 4
#define DONE_BIT_L (1 << 7)
#define DONE_BIT_H (1 << 15)

int offset = 0;
unsigned char* file;

void handle_input(int argc, char* argv[], int* blocksize) {
	int x;
	extern char *optarg;

	while ((x = getopt(argc, argv, ":b:")) != -1) {
		switch (x) {
		case 'b':
			*blocksize = atoi(optarg);
			printf("blocksize is set to %d optarg\n", *blocksize);
			break;
		case ':':
			printf("-%c without parameter\n", optopt);
			break;
		}
	}
}

int main(int argc, char* argv[]) {
	std::cout << "11:05am" << std::endl;
	std::cout << argv[1] << std::endl;
	stopwatch ethernet_timer;
	unsigned char* input[NUM_PACKETS];
	int writer = 0;
	int done = 0;
	int length = 0;
	int count = 0;
	ESE532_Server server;

	// default is 2k
	int blocksize = BLOCKSIZE;

	// set blocksize if decalred through command line
	handle_input(argc, argv, &blocksize);

	file = (unsigned char*) malloc(sizeof(unsigned char) * 70000000);
	if (file == NULL) {
		printf("help\n");
	}

	for (int i = 0; i < NUM_PACKETS; i++) {
		input[i] = (unsigned char*) malloc(
				sizeof(unsigned char) * (NUM_ELEMENTS + HEADER));
		if (input[i] == NULL) {
			std::cout << "aborting " << std::endl;
			return 1;
		}
	}

	server.setup_server(blocksize);

	writer = 0;

	// initialize the map for deduplication
	std::unordered_map<std::string, int> chunks_map;
	int sum_raw_length = 0, sum_lzw_cmprs_len = 0;

	//last message
	while (!done) {
		// reset ring buffer
		if (writer == NUM_PACKETS) {
			writer = 0;
		}

		ethernet_timer.start();
		server.get_packet(input[writer]);
		ethernet_timer.stop();

		count++;

		// get packet
		unsigned char* buffer = input[writer];

		// decode
		done = buffer[1] & DONE_BIT_L;
		length = buffer[0] | (buffer[1] << 8);
		length &= ~DONE_BIT_H;
		//printf("length: %d offset %d\n",length,offset);
		memcpy(&file[offset], &buffer[HEADER], length);

		offset += length;
		writer++;

		// encode the obtained information in buffer

		// initialize the vector to store the obtained chunks
		std::vector<std::string> chunks;
		// get the chunked result
		cdc(buffer, chunks, NUM_ELEMENTS + HEADER);

		//calculate hash value and chunk id for each chunk
		//add those key-value pairs to chunks map
		//Question: do we need to consider the situation that different chunks share the same hash value calculated by SHA at this point
		for(std::vector<std::string>::size_type i = 0; i < chunks.size(); i++){
		// for(std::vector<std::string>::size_type i = 0; i < 10; i++){
			hash_part hash_value;
			sha(chunks[i], hash_value);
			std::string hash_hex_string = toHexString(hash_value);
			
			if(chunks_map.find(hash_hex_string) == chunks_map.end()){
				chunks_map.insert({hash_hex_string, i});
				unsigned char* chunk_content = (unsigned char*)malloc(sizeof(unsigned char) * (chunks[i].length() + 1));
				convert_string_char(chunks[i], chunk_content);
				uint32_t header;
				uint16_t* out_code = (uint16_t*)malloc(sizeof(uint16_t) * chunks[i].length() + 32);
				int out_len;
				hardware_encoding(chunk_content, chunks[i].length(), out_code, header, out_len, argv[1]);
				std::cout << "New chunk " << i << ": " << out_code << std::endl;
				sum_raw_length += chunks[i].length();
				sum_lzw_cmprs_len += out_len;
				free(out_code);
				free(chunk_content); 
			}

			else{
				uint32_t out_code;
				duplicate_encoding(chunks_map.at(hash_hex_string), out_code, argv[1]);
				std::cout << "Duplicate chunk " << i << ": " << out_code << std::endl;
			}
		}
	}
	float lzw_compress_ratio = sum_raw_length / sum_lzw_cmprs_len;
	std::cout << "LZW compress ratio: " << lzw_compress_ratio << std::endl;


	// write file to root and you can use diff tool on board
	FILE *outfd = fopen("output_cpu.bin", "wb");
	int bytes_written = fwrite(&file[0], 1, offset, outfd);
	printf("write file with %d\n", bytes_written);
	fclose(outfd);

	for (int i = 0; i < NUM_PACKETS; i++) {
		free(input[i]);
	}

	free(file);
	std::cout << "--------------- Key Throughputs ---------------" << std::endl;
	float ethernet_latency = ethernet_timer.latency() / 1000.0;
	float input_throughput = (bytes_written * 8 / 1000000.0) / ethernet_latency; // Mb/s
	std::cout << "Input Throughput to Encoder: " << input_throughput << " Mb/s."
			<< " (Latency: " << ethernet_latency << "s)." << std::endl;

	return 0;
}

