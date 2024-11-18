	#include "MMult.h"
	#include <hls_stream.h>
	/**
	 *
	 * Design principles to achieve II = 1
	 * 1. Stream data into local RAM for inputs (multiple access required)
	 * 2. Partition local RAMs into N/2 sub-arrays for fully parallel access
	 * (dual-port read)
	 * 3. Pipeline the dot-product loop, to fully unroll it
	 * 4. Separate multiply-accumulate in inner loop to force two FP operators
	 *
	 */


/*	void read_input(const float A[CHUNKS * N * N], const float B[CHUNKS * N * N], hls::stream<float>& inStream_A, hls::stream<float>& inStream_B) {
		for (int c = 0; c < CHUNKS; c++) {
			// Stream all data for matrix A first
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					inStream_A << A[c * N * N + i * N + j];
					inStream_B << B[c * N * N + i * N + j];
				}
			}
		}
	}
*/
	void read_input(float A[CHUNKS * N * N], float B[CHUNKS * N * N], hls::stream<float>& inStream) {
		for (int c = 0; c < CHUNKS; c++) {
			// Stream all data for matrix A first
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					inStream << A[c * N * N + i * N + j];
					//inStream_B << B[c * N * N + i * N + j];
				}
			}
		}
		for (int c = 0; c < CHUNKS; c++) {
			// Stream all data for matrix A first
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					inStream << B[c * N * N + i * N + j];
					//inStream_B << B[c * N * N + i * N + j];
				}
			}
		}
	}
	//void compute_mmult(hls::stream<float>& inStream_A, hls::stream<float>& inStream_B, hls::stream<float>& outStream) {
	void compute_mmult(hls::stream<float>& inStream, hls::stream<float>& outStream) {
		//float term[N];
		float A_tmp[N][N], B_tmp[N][N];
	    	#pragma HLS array_partition variable=A_tmp cyclic factor=32 dim=2
	    	#pragma HLS array_partition variable=B_tmp block factor=32 dim=1
		for (int c = 0; c < CHUNKS; c++) {
			// Read matrix A data first from the stream
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					A_tmp[i][j] = inStream.read();
					//B_tmp[i][j] = inStream_B.read();
				}
			}
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					B_tmp[i][j] = inStream.read();
					//B_tmp[i][j] = inStream_B.read();
				}
			}

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					float result = 0;
					for (int k = 0; k < N; k++) {
						float term = 0;
						term = A_tmp[i][k] * B_tmp[k][j];
						result += term;
					}
					outStream << result;
				}
			}
		}
	}

	 void write_result(hls::stream<float>& outStream, float C[CHUNKS * N * N]){
		  //#pragma HLS INTERFACE m_axi port=C bundle=hp2 //depth=512
		for (int c = 0; c < CHUNKS; c++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					C[c * N * N + i * N + j] = outStream.read();
				}
			}
		}
	}

	void mmult_fpga(float A[CHUNKS * N * N], float B[CHUNKS * N * N],
					float C[CHUNKS * N * N]) {
		  #pragma HLS INTERFACE m_axi port=A bundle=g0
		  #pragma HLS INTERFACE m_axi port=B bundle=g1
		  #pragma HLS INTERFACE m_axi port=C bundle=g0
		  static hls::stream<float> inStream("input__stream");
		  //static hls::stream<float> inStream_B("input_B_stream");
		  static hls::stream<float> outStream("output_stream");
		  #pragma HLS stream variable=inStream depth=1024
		  //#pragma HLS stream variable=inStream_B depth=1024
		  #pragma HLS stream variable=outStream depth=1024
		  #pragma HLS dataflow
		  //read_input(A, B, inStream_A, inStream_B);
		  read_input(A, B, inStream);
		  //compute_mmult(inStream_A, inStream_B, outStream);
		  compute_mmult(inStream, outStream);
		  write_result(outStream, C);
	}