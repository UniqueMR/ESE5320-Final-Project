// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xlzw_stream.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XLzw_stream_CfgInitialize(XLzw_stream *InstancePtr, XLzw_stream_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XLzw_stream_Start(XLzw_stream *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_AP_CTRL) & 0x80;
    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XLzw_stream_IsDone(XLzw_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XLzw_stream_IsIdle(XLzw_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XLzw_stream_IsReady(XLzw_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XLzw_stream_Continue(XLzw_stream *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_AP_CTRL) & 0x80;
    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XLzw_stream_EnableAutoRestart(XLzw_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XLzw_stream_DisableAutoRestart(XLzw_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_AP_CTRL, 0);
}

void XLzw_stream_Set_s1(XLzw_stream *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_S1_DATA, (u32)(Data));
    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_S1_DATA + 4, (u32)(Data >> 32));
}

u64 XLzw_stream_Get_s1(XLzw_stream *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_S1_DATA);
    Data += (u64)XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_S1_DATA + 4) << 32;
    return Data;
}

void XLzw_stream_Set_length_r(XLzw_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_LENGTH_R_DATA, Data);
}

u32 XLzw_stream_Get_length_r(XLzw_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_LENGTH_R_DATA);
    return Data;
}

void XLzw_stream_Set_file_buffer(XLzw_stream *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_FILE_BUFFER_DATA, (u32)(Data));
    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_FILE_BUFFER_DATA + 4, (u32)(Data >> 32));
}

u64 XLzw_stream_Get_file_buffer(XLzw_stream *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_FILE_BUFFER_DATA);
    Data += (u64)XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_FILE_BUFFER_DATA + 4) << 32;
    return Data;
}

void XLzw_stream_Set_total_bytes(XLzw_stream *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_TOTAL_BYTES_DATA, (u32)(Data));
    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_TOTAL_BYTES_DATA + 4, (u32)(Data >> 32));
}

u64 XLzw_stream_Get_total_bytes(XLzw_stream *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_TOTAL_BYTES_DATA);
    Data += (u64)XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_TOTAL_BYTES_DATA + 4) << 32;
    return Data;
}

void XLzw_stream_InterruptGlobalEnable(XLzw_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_GIE, 1);
}

void XLzw_stream_InterruptGlobalDisable(XLzw_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_GIE, 0);
}

void XLzw_stream_InterruptEnable(XLzw_stream *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_IER);
    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_IER, Register | Mask);
}

void XLzw_stream_InterruptDisable(XLzw_stream *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_IER);
    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_IER, Register & (~Mask));
}

void XLzw_stream_InterruptClear(XLzw_stream *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLzw_stream_WriteReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_ISR, Mask);
}

u32 XLzw_stream_InterruptGetEnabled(XLzw_stream *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_IER);
}

u32 XLzw_stream_InterruptGetStatus(XLzw_stream *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XLzw_stream_ReadReg(InstancePtr->Control_BaseAddress, XLZW_STREAM_CONTROL_ADDR_ISR);
}

