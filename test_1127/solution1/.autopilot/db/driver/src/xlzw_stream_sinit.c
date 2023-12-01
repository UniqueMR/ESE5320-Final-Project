// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xlzw_stream.h"

extern XLzw_stream_Config XLzw_stream_ConfigTable[];

XLzw_stream_Config *XLzw_stream_LookupConfig(u16 DeviceId) {
	XLzw_stream_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XLZW_STREAM_NUM_INSTANCES; Index++) {
		if (XLzw_stream_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XLzw_stream_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XLzw_stream_Initialize(XLzw_stream *InstancePtr, u16 DeviceId) {
	XLzw_stream_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XLzw_stream_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XLzw_stream_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

