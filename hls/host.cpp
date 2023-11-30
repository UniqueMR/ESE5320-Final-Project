#include "host.h"
using namespace std;
int offset = 0;
unsigned char* file;

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

static void write_file(unsigned char* file_buffer, int total_bytes, char* fileName){
    std::ofstream outfile(fileName, std::ios::app);
    
    if(!outfile.is_open()) {
        std::cerr << "Could not open the file for writing.\n";
        return;
    }

    // Write the data to the file
    outfile.write(reinterpret_cast<const char*>(file_buffer), total_bytes + 4);

    // Check for write errors
    if (!outfile.good()) {
        std::cerr << "Error occurred while writing to the file.\n";
    }

    // Close the file
    outfile.close();
}

int main(int argc, char** argv)
{
// Initialize an event timer we'll use for monitoring the application
    EventTimer timer;
// ------------------------------------------------------------------------------------
// Step 1: Initialize the OpenCL environment 
// ------------------------------------------------------------------------------------ 
    timer.add("OpenCL Initialization");
    cl_int err;
    std::string binaryFile = argv[1];
    unsigned fileBufSize;    
    std::vector<cl::Device> devices = get_xilinx_devices();
    devices.resize(1);
    cl::Device device = devices[0];
    cl::Context context(device, NULL, NULL, NULL, &err);
    char* fileBuf = read_binary_file(binaryFile, fileBufSize);
    cl::Program::Binaries bins{{fileBuf, fileBufSize}};
    cl::Program program(context, devices, bins, NULL, &err);
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE, &err);
    // cl::Kernel krnl_hardware_encoding(program,"hardware_encoding", &err);
    cl::Kernel krnl_hardware_encoding(program,"lzw_stream", &err);
	timer.finish();

// ------------------------------------------------------------------------------------
// Step 2: Create buffers and initialize test values
// ------------------------------------------------------------------------------------
    timer.add("Allocate contiguous OpenCL buffers");
    // Create the buffers and allocate memory   
    cl::Buffer chunk_content_buf(context, CL_MEM_ALLOC_HOST_PTR | CL_MEM_READ_ONLY,  sizeof(unsigned char) * MAX_CHUNK_SIZE, NULL, &err);
    cl::Buffer file_buffer_buf(context, CL_MEM_ALLOC_HOST_PTR | CL_MEM_WRITE_ONLY,  sizeof(unsigned char) * (std::ceil(MAX_CHUNK_SIZE * 3 / 2) + 4), NULL, &err);
    // cl::Buffer out_code_buf(context, CL_MEM_ALLOC_HOST_PTR | CL_MEM_WRITE_ONLY,  sizeof(uint16_t) * MAX_CHUNK_SIZE, NULL, &err);
    // cl::Buffer header_buf(context, CL_MEM_ALLOC_HOST_PTR | CL_MEM_WRITE_ONLY,  sizeof(uint32_t), NULL, &err);
    cl::Buffer total_bytes_buf(context, CL_MEM_ALLOC_HOST_PTR | CL_MEM_WRITE_ONLY,  sizeof(int), NULL, &err);
	timer.finish();

    timer.add("Map buffers to userspace pointers");
    // Map host-side buffer memory to user-space pointers
    unsigned char* chunk_content = (unsigned char *)q.enqueueMapBuffer(chunk_content_buf, CL_TRUE, CL_MAP_WRITE, 0, sizeof(unsigned char) * MAX_CHUNK_SIZE);
	unsigned char* file_buffer = (unsigned char *)q.enqueueMapBuffer(file_buffer_buf, CL_TRUE, CL_MAP_READ, 0, sizeof(unsigned char) * (std::ceil(MAX_CHUNK_SIZE * 3 / 2) + 4));
    // uint16_t* out_code = (uint16_t*)q.enqueueMapBuffer(out_code_buf, CL_TRUE, CL_MAP_READ, 0, sizeof(uint16_t) * MAX_CHUNK_SIZE);
    timer.finish();

// ------------------------------------------------------------------------------------
// Step 3: Run the kernel
// ------------------------------------------------------------------------------------
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
	float sum_lzw_raw_length = 0, sum_lzw_cmprs_len = 0, sum_dedup_raw_length = 0, sum_dedup_cmprs_len = 0;

	int base = 0;
	int ticks = 0;

	//last message
	while (!done) {
		ticks++;
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
		cdc(&buffer[2], chunks, NUM_ELEMENTS + HEADER);

		//calculate hash value and chunk id for each chunk
		//add those key-value pairs to chunks map
		//Question: do we need to consider the situation that different chunks share the same hash value calculated by SHA at this point
		for(std::vector<std::string>::size_type i = 0; i < chunks.size(); i++){
		// for(std::vector<std::string>::size_type i = 0; i < 10; i++){
			hash_part hash_value;
			sha(chunks[i], hash_value);
			std::string hash_hex_string = toHexString(hash_value);
			
			if(chunks_map.find(hash_hex_string) == chunks_map.end()){
				chunks_map.insert({hash_hex_string, base + i});
                convert_string_char(chunks[i], chunk_content);
                int chunk_len = chunks[i].length();
				int total_bytes = 0;
				
				//running hardware implementation on cpu
				unsigned char* chunk_content_cpu = (unsigned char*)malloc(sizeof(unsigned char) * MAX_CHUNK_SIZE);
				memcpy(chunk_content_cpu, chunk_content, chunks[i].length());
				int chunk_len_cpu = chunk_len;
				int total_bytes_cpu = 0;
				unsigned char* file_buffer_cpu = (unsigned char*)malloc((std::ceil(MAX_CHUNK_SIZE * 1.5) + 4) * sizeof(unsigned char));
				lzw_stream(chunk_content_cpu, chunk_len_cpu, file_buffer_cpu, &total_bytes_cpu);

				//the actual software implementation
				vector<uint16_t> golden = encoding(chunks[i]);
				// uint16_t* golden_buf = new uint16_t(golden.size());
				uint16_t* golden_buf = (uint16_t*)malloc(golden.size()*sizeof(uint16_t));
				int golden_len; 
				vector_to_array(golden, golden_buf, golden_len);
				// unsigned char* golden_file_buf = new unsigned char(std::ceil(golden_len * 3 / 2) + 4);
				unsigned char* golden_file_buf = (unsigned char*)malloc((std::ceil(golden_len * 3 / 2) + 4) * sizeof(unsigned char));
				int golden_file_buf_len;
				write_encoded_file_buf(golden_buf, golden_len, golden_file_buf, golden_file_buf_len);

				// // q.enqueueWriteBuffer(header_buf, CL_TRUE, 0, sizeof(uint32_t), &header);
				q.enqueueWriteBuffer(total_bytes_buf, CL_TRUE, 0, sizeof(int), &total_bytes);

				timer.add("Set kernel arguments");  
				// // Map buffers to kernel arguments, thereby assigning them to specific device memory banks
				krnl_hardware_encoding.setArg(0, chunk_content_buf);
				krnl_hardware_encoding.setArg(1, chunk_len);
				krnl_hardware_encoding.setArg(2, file_buffer_buf);
				krnl_hardware_encoding.setArg(3, total_bytes_buf);
				timer.finish();
				std::cout << "finished setting kernel arguments" << std::endl;

                timer.add("Memory object migration enqueue host->device");
                cl::Event event_sp;
                q.enqueueMigrateMemObjects({chunk_content_buf}, 0 /* 0 means from host*/, NULL, &event_sp); 
                clWaitForEvents(1, (const cl_event *)&event_sp);
				timer.finish();
				std::cout << "chunk_content_buf is migrated to device" << std::endl;

                timer.add("Launch kernel");
                q.enqueueTask(krnl_hardware_encoding, NULL, &event_sp);
                timer.add("Wait for kernel to finish running");
                clWaitForEvents(1, (const cl_event *)&event_sp);
				timer.finish();
				std::cout << "kernel is launched" << std::endl;
				// // hardware_encoding(chunk_content, chunks[i].length(), out_code, header, out_len);

                timer.add("Read back computation results (implicit device->host migration)");
                // q.enqueueMigrateMemObjects({out_code_buf, header_buf, out_len_buf}, CL_MIGRATE_MEM_OBJECT_HOST, NULL, &event_sp); 
                q.enqueueMigrateMemObjects({file_buffer_buf}, CL_MIGRATE_MEM_OBJECT_HOST, NULL, &event_sp); 
				// q.enqueueReadBuffer(header_buf, CL_TRUE, 0, sizeof(uint32_t), &header);
				q.enqueueReadBuffer(total_bytes_buf, CL_TRUE, 0, sizeof(int), &total_bytes);
                timer.finish();
				std::cout << "file_buffer_buf and total_bytes_buf are migrated back to host" << std::endl;

				std::cout << "len kernel: " << total_bytes << std::endl;
				std::cout << "len cpu: " << total_bytes_cpu << std::endl;
				std::cout << "len golden: " << golden_file_buf_len << std::endl;


				for(int i = 0; i < total_bytes_cpu; i++)
				// 	std::cout << "kernel: " << std::hex << static_cast<int>(file_buffer[i]) << "; cpu: " << std::hex << static_cast<int>(file_buffer_cpu[i]) << "; golden: " << std::hex << static_cast<int>(golden_file_buf[i]) << std::endl;
					std::cout << "cpu: " << std::hex << static_cast<int>(file_buffer_cpu[i]) << "; golden: " << std::hex << static_cast<int>(golden_file_buf[i]) << std::endl;
				// 	// std::cout << "; golden: " << std::hex << static_cast<int>(golden_file_buf[i]) << std::endl;

				std::cout << "kernel has been executed" << std::endl;

				// write_file(file_buffer, total_bytes, "encoded.bin");
				write_file(file_buffer_cpu, total_bytes_cpu, "encoded.bin");

				std::cout << "already written into file" << std::endl;

				sum_lzw_raw_length += chunks[i].length() * 1.5;
				sum_lzw_cmprs_len += total_bytes;
				// free(out_code);
				// free(chunk_content); 

				std::cout << "release space" << std::endl;
				free(chunk_content_cpu);
				free(file_buffer_cpu);
				free(golden_buf);
				free(golden_file_buf);
				std::cout << "space released" << std::endl;
			}

			else{
				uint32_t out_code;
				duplicate_encoding(chunks_map.at(hash_hex_string), out_code, "encoded.bin");
				std::cout << "Duplicate chunk " << i << ": " << out_code << std::endl;
				sum_dedup_raw_length += chunks[i].length() * 1.5;
				sum_dedup_cmprs_len += 4;
			}
		}
		base += chunks.size();
	}
	
	float lzw_compress_ratio = sum_lzw_raw_length / sum_lzw_cmprs_len;
	float dedup_compress_ratio = sum_dedup_raw_length / sum_dedup_cmprs_len;
	float total_compress_ratio = (sum_dedup_raw_length + sum_lzw_raw_length) / (sum_dedup_cmprs_len + sum_lzw_cmprs_len);

	std::cout << "LZW compress ratio: " << lzw_compress_ratio << std::endl;
	std::cout << "Deduplication compress ratio: " << dedup_compress_ratio << std::endl;
	std::cout << "Total compress ratio: " << total_compress_ratio << std::endl;

	std::cout << "Loop times: " << ticks << std::endl;

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

// ------------------------------------------------------------------------------------
// Step 4: Check Results and Release Allocated Resources
// ------------------------------------------------------------------------------------
    // multiply_gold(in1, in2, out_sw);
    // bool match = Compare_matrices(out_sw, out_hw);
    // Destroy_matrix(out_sw);
    delete[] fileBuf;
    q.enqueueUnmapMemObject(chunk_content_buf, chunk_content);
    q.enqueueUnmapMemObject(file_buffer_buf, file_buffer);
    q.finish();

    // std::cout << "--------------- Key execution times ---------------" << std::endl;
    // timer.print();

    // std::cout << "TEST " << (match ? "PASSED" : "FAILED") << std::endl; 
    // return (match ? EXIT_SUCCESS : EXIT_FAILURE);
    return 0;
}
