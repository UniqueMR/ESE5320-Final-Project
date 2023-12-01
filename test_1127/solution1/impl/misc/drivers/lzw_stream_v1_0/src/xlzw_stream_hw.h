// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 4  - ap_continue (Read/Write/SC)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - enable ap_done interrupt (Read/Write)
//        bit 1  - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - ap_done (COR/TOW)
//        bit 1  - ap_ready (COR/TOW)
//        others - reserved
// 0x10 : Data signal of s1
//        bit 31~0 - s1[31:0] (Read/Write)
// 0x14 : Data signal of s1
//        bit 31~0 - s1[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of length_r
//        bit 31~0 - length_r[31:0] (Read/Write)
// 0x20 : reserved
// 0x24 : Data signal of file_buffer
//        bit 31~0 - file_buffer[31:0] (Read/Write)
// 0x28 : Data signal of file_buffer
//        bit 31~0 - file_buffer[63:32] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of total_bytes
//        bit 31~0 - total_bytes[31:0] (Read/Write)
// 0x34 : Data signal of total_bytes
//        bit 31~0 - total_bytes[63:32] (Read/Write)
// 0x38 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XLZW_STREAM_CONTROL_ADDR_AP_CTRL          0x00
#define XLZW_STREAM_CONTROL_ADDR_GIE              0x04
#define XLZW_STREAM_CONTROL_ADDR_IER              0x08
#define XLZW_STREAM_CONTROL_ADDR_ISR              0x0c
#define XLZW_STREAM_CONTROL_ADDR_S1_DATA          0x10
#define XLZW_STREAM_CONTROL_BITS_S1_DATA          64
#define XLZW_STREAM_CONTROL_ADDR_LENGTH_R_DATA    0x1c
#define XLZW_STREAM_CONTROL_BITS_LENGTH_R_DATA    32
#define XLZW_STREAM_CONTROL_ADDR_FILE_BUFFER_DATA 0x24
#define XLZW_STREAM_CONTROL_BITS_FILE_BUFFER_DATA 64
#define XLZW_STREAM_CONTROL_ADDR_TOTAL_BYTES_DATA 0x30
#define XLZW_STREAM_CONTROL_BITS_TOTAL_BYTES_DATA 64
