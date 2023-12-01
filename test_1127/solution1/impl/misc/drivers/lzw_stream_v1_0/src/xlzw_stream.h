// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XLZW_STREAM_H
#define XLZW_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xlzw_stream_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XLzw_stream_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XLzw_stream;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XLzw_stream_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XLzw_stream_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XLzw_stream_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XLzw_stream_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XLzw_stream_Initialize(XLzw_stream *InstancePtr, u16 DeviceId);
XLzw_stream_Config* XLzw_stream_LookupConfig(u16 DeviceId);
int XLzw_stream_CfgInitialize(XLzw_stream *InstancePtr, XLzw_stream_Config *ConfigPtr);
#else
int XLzw_stream_Initialize(XLzw_stream *InstancePtr, const char* InstanceName);
int XLzw_stream_Release(XLzw_stream *InstancePtr);
#endif

void XLzw_stream_Start(XLzw_stream *InstancePtr);
u32 XLzw_stream_IsDone(XLzw_stream *InstancePtr);
u32 XLzw_stream_IsIdle(XLzw_stream *InstancePtr);
u32 XLzw_stream_IsReady(XLzw_stream *InstancePtr);
void XLzw_stream_Continue(XLzw_stream *InstancePtr);
void XLzw_stream_EnableAutoRestart(XLzw_stream *InstancePtr);
void XLzw_stream_DisableAutoRestart(XLzw_stream *InstancePtr);

void XLzw_stream_Set_s1(XLzw_stream *InstancePtr, u64 Data);
u64 XLzw_stream_Get_s1(XLzw_stream *InstancePtr);
void XLzw_stream_Set_length_r(XLzw_stream *InstancePtr, u32 Data);
u32 XLzw_stream_Get_length_r(XLzw_stream *InstancePtr);
void XLzw_stream_Set_file_buffer(XLzw_stream *InstancePtr, u64 Data);
u64 XLzw_stream_Get_file_buffer(XLzw_stream *InstancePtr);
void XLzw_stream_Set_total_bytes(XLzw_stream *InstancePtr, u64 Data);
u64 XLzw_stream_Get_total_bytes(XLzw_stream *InstancePtr);

void XLzw_stream_InterruptGlobalEnable(XLzw_stream *InstancePtr);
void XLzw_stream_InterruptGlobalDisable(XLzw_stream *InstancePtr);
void XLzw_stream_InterruptEnable(XLzw_stream *InstancePtr, u32 Mask);
void XLzw_stream_InterruptDisable(XLzw_stream *InstancePtr, u32 Mask);
void XLzw_stream_InterruptClear(XLzw_stream *InstancePtr, u32 Mask);
u32 XLzw_stream_InterruptGetEnabled(XLzw_stream *InstancePtr);
u32 XLzw_stream_InterruptGetStatus(XLzw_stream *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
