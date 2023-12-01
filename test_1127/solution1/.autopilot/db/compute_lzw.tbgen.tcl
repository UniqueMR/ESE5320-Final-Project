set moduleName compute_lzw
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {compute_lzw}
set C_modelType { void 0 }
set C_modelArgList {
	{ chr_stream1 int 8 regular {fifo 0 volatile }  }
	{ cmprs_stream2 int 16 regular {fifo 1 volatile }  }
	{ cmprs_len_stream3 int 32 regular {fifo 1 volatile }  }
	{ length_r int 32 regular  }
	{ hash_table int 33 regular {array 32768 { 2 3 } 1 1 }  }
	{ my_assoc_mem_upper_key_mem int 64 regular {array 512 { 2 3 } 1 1 }  }
	{ my_assoc_mem_middle_key_mem int 64 regular {array 512 { 2 3 } 1 1 }  }
	{ my_assoc_mem_lower_key_mem int 64 regular {array 512 { 2 3 } 1 1 }  }
	{ my_assoc_mem_value int 12 regular {array 64 { 2 3 } 1 1 }  }
	{ my_assoc_mem_fill_read int 32 regular  }
}
set C_modelArgMapList {[ 
	{ "Name" : "chr_stream1", "interface" : "fifo", "bitwidth" : 8, "direction" : "READONLY"} , 
 	{ "Name" : "cmprs_stream2", "interface" : "fifo", "bitwidth" : 16, "direction" : "WRITEONLY"} , 
 	{ "Name" : "cmprs_len_stream3", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "length_r", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "hash_table", "interface" : "memory", "bitwidth" : 33, "direction" : "READWRITE"} , 
 	{ "Name" : "my_assoc_mem_upper_key_mem", "interface" : "memory", "bitwidth" : 64, "direction" : "READWRITE"} , 
 	{ "Name" : "my_assoc_mem_middle_key_mem", "interface" : "memory", "bitwidth" : 64, "direction" : "READWRITE"} , 
 	{ "Name" : "my_assoc_mem_lower_key_mem", "interface" : "memory", "bitwidth" : 64, "direction" : "READWRITE"} , 
 	{ "Name" : "my_assoc_mem_value", "interface" : "memory", "bitwidth" : 12, "direction" : "READWRITE"} , 
 	{ "Name" : "my_assoc_mem_fill_read", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} ]}
# RTL Port declarations: 
set portNum 42
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ chr_stream1_dout sc_in sc_lv 8 signal 0 } 
	{ chr_stream1_empty_n sc_in sc_logic 1 signal 0 } 
	{ chr_stream1_read sc_out sc_logic 1 signal 0 } 
	{ cmprs_stream2_din sc_out sc_lv 16 signal 1 } 
	{ cmprs_stream2_full_n sc_in sc_logic 1 signal 1 } 
	{ cmprs_stream2_write sc_out sc_logic 1 signal 1 } 
	{ cmprs_len_stream3_din sc_out sc_lv 32 signal 2 } 
	{ cmprs_len_stream3_full_n sc_in sc_logic 1 signal 2 } 
	{ cmprs_len_stream3_write sc_out sc_logic 1 signal 2 } 
	{ length_r sc_in sc_lv 32 signal 3 } 
	{ hash_table_address0 sc_out sc_lv 15 signal 4 } 
	{ hash_table_ce0 sc_out sc_logic 1 signal 4 } 
	{ hash_table_we0 sc_out sc_logic 1 signal 4 } 
	{ hash_table_d0 sc_out sc_lv 33 signal 4 } 
	{ hash_table_q0 sc_in sc_lv 33 signal 4 } 
	{ my_assoc_mem_upper_key_mem_address0 sc_out sc_lv 9 signal 5 } 
	{ my_assoc_mem_upper_key_mem_ce0 sc_out sc_logic 1 signal 5 } 
	{ my_assoc_mem_upper_key_mem_we0 sc_out sc_logic 1 signal 5 } 
	{ my_assoc_mem_upper_key_mem_d0 sc_out sc_lv 64 signal 5 } 
	{ my_assoc_mem_upper_key_mem_q0 sc_in sc_lv 64 signal 5 } 
	{ my_assoc_mem_middle_key_mem_address0 sc_out sc_lv 9 signal 6 } 
	{ my_assoc_mem_middle_key_mem_ce0 sc_out sc_logic 1 signal 6 } 
	{ my_assoc_mem_middle_key_mem_we0 sc_out sc_logic 1 signal 6 } 
	{ my_assoc_mem_middle_key_mem_d0 sc_out sc_lv 64 signal 6 } 
	{ my_assoc_mem_middle_key_mem_q0 sc_in sc_lv 64 signal 6 } 
	{ my_assoc_mem_lower_key_mem_address0 sc_out sc_lv 9 signal 7 } 
	{ my_assoc_mem_lower_key_mem_ce0 sc_out sc_logic 1 signal 7 } 
	{ my_assoc_mem_lower_key_mem_we0 sc_out sc_logic 1 signal 7 } 
	{ my_assoc_mem_lower_key_mem_d0 sc_out sc_lv 64 signal 7 } 
	{ my_assoc_mem_lower_key_mem_q0 sc_in sc_lv 64 signal 7 } 
	{ my_assoc_mem_value_address0 sc_out sc_lv 6 signal 8 } 
	{ my_assoc_mem_value_ce0 sc_out sc_logic 1 signal 8 } 
	{ my_assoc_mem_value_we0 sc_out sc_logic 1 signal 8 } 
	{ my_assoc_mem_value_d0 sc_out sc_lv 12 signal 8 } 
	{ my_assoc_mem_value_q0 sc_in sc_lv 12 signal 8 } 
	{ my_assoc_mem_fill_read sc_in sc_lv 32 signal 9 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "chr_stream1_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "chr_stream1", "role": "dout" }} , 
 	{ "name": "chr_stream1_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "chr_stream1", "role": "empty_n" }} , 
 	{ "name": "chr_stream1_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "chr_stream1", "role": "read" }} , 
 	{ "name": "cmprs_stream2_din", "direction": "out", "datatype": "sc_lv", "bitwidth":16, "type": "signal", "bundle":{"name": "cmprs_stream2", "role": "din" }} , 
 	{ "name": "cmprs_stream2_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cmprs_stream2", "role": "full_n" }} , 
 	{ "name": "cmprs_stream2_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cmprs_stream2", "role": "write" }} , 
 	{ "name": "cmprs_len_stream3_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "cmprs_len_stream3", "role": "din" }} , 
 	{ "name": "cmprs_len_stream3_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cmprs_len_stream3", "role": "full_n" }} , 
 	{ "name": "cmprs_len_stream3_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cmprs_len_stream3", "role": "write" }} , 
 	{ "name": "length_r", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "length_r", "role": "default" }} , 
 	{ "name": "hash_table_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "hash_table", "role": "address0" }} , 
 	{ "name": "hash_table_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "hash_table", "role": "ce0" }} , 
 	{ "name": "hash_table_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "hash_table", "role": "we0" }} , 
 	{ "name": "hash_table_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":33, "type": "signal", "bundle":{"name": "hash_table", "role": "d0" }} , 
 	{ "name": "hash_table_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":33, "type": "signal", "bundle":{"name": "hash_table", "role": "q0" }} , 
 	{ "name": "my_assoc_mem_upper_key_mem_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":9, "type": "signal", "bundle":{"name": "my_assoc_mem_upper_key_mem", "role": "address0" }} , 
 	{ "name": "my_assoc_mem_upper_key_mem_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "my_assoc_mem_upper_key_mem", "role": "ce0" }} , 
 	{ "name": "my_assoc_mem_upper_key_mem_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "my_assoc_mem_upper_key_mem", "role": "we0" }} , 
 	{ "name": "my_assoc_mem_upper_key_mem_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "my_assoc_mem_upper_key_mem", "role": "d0" }} , 
 	{ "name": "my_assoc_mem_upper_key_mem_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "my_assoc_mem_upper_key_mem", "role": "q0" }} , 
 	{ "name": "my_assoc_mem_middle_key_mem_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":9, "type": "signal", "bundle":{"name": "my_assoc_mem_middle_key_mem", "role": "address0" }} , 
 	{ "name": "my_assoc_mem_middle_key_mem_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "my_assoc_mem_middle_key_mem", "role": "ce0" }} , 
 	{ "name": "my_assoc_mem_middle_key_mem_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "my_assoc_mem_middle_key_mem", "role": "we0" }} , 
 	{ "name": "my_assoc_mem_middle_key_mem_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "my_assoc_mem_middle_key_mem", "role": "d0" }} , 
 	{ "name": "my_assoc_mem_middle_key_mem_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "my_assoc_mem_middle_key_mem", "role": "q0" }} , 
 	{ "name": "my_assoc_mem_lower_key_mem_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":9, "type": "signal", "bundle":{"name": "my_assoc_mem_lower_key_mem", "role": "address0" }} , 
 	{ "name": "my_assoc_mem_lower_key_mem_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "my_assoc_mem_lower_key_mem", "role": "ce0" }} , 
 	{ "name": "my_assoc_mem_lower_key_mem_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "my_assoc_mem_lower_key_mem", "role": "we0" }} , 
 	{ "name": "my_assoc_mem_lower_key_mem_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "my_assoc_mem_lower_key_mem", "role": "d0" }} , 
 	{ "name": "my_assoc_mem_lower_key_mem_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "my_assoc_mem_lower_key_mem", "role": "q0" }} , 
 	{ "name": "my_assoc_mem_value_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "my_assoc_mem_value", "role": "address0" }} , 
 	{ "name": "my_assoc_mem_value_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "my_assoc_mem_value", "role": "ce0" }} , 
 	{ "name": "my_assoc_mem_value_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "my_assoc_mem_value", "role": "we0" }} , 
 	{ "name": "my_assoc_mem_value_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":12, "type": "signal", "bundle":{"name": "my_assoc_mem_value", "role": "d0" }} , 
 	{ "name": "my_assoc_mem_value_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":12, "type": "signal", "bundle":{"name": "my_assoc_mem_value", "role": "q0" }} , 
 	{ "name": "my_assoc_mem_fill_read", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "my_assoc_mem_fill_read", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "",
		"CDFG" : "compute_lzw",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "-1", "EstimateLatencyMax" : "-1",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "chr_stream1", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "chr_stream1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cmprs_stream2", "Type" : "Fifo", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "cmprs_stream2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cmprs_len_stream3", "Type" : "Fifo", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "cmprs_len_stream3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "length_r", "Type" : "None", "Direction" : "I"},
			{"Name" : "hash_table", "Type" : "Memory", "Direction" : "IO"},
			{"Name" : "my_assoc_mem_upper_key_mem", "Type" : "Memory", "Direction" : "IO"},
			{"Name" : "my_assoc_mem_middle_key_mem", "Type" : "Memory", "Direction" : "IO"},
			{"Name" : "my_assoc_mem_lower_key_mem", "Type" : "Memory", "Direction" : "IO"},
			{"Name" : "my_assoc_mem_value", "Type" : "Memory", "Direction" : "IO"},
			{"Name" : "my_assoc_mem_fill_read", "Type" : "None", "Direction" : "I"}]}]}


set ArgLastReadFirstWriteLatency {
	compute_lzw {
		chr_stream1 {Type I LastRead 1 FirstWrite -1}
		cmprs_stream2 {Type O LastRead -1 FirstWrite 11}
		cmprs_len_stream3 {Type O LastRead -1 FirstWrite 11}
		length_r {Type I LastRead 0 FirstWrite -1}
		hash_table {Type IO LastRead 8 FirstWrite 10}
		my_assoc_mem_upper_key_mem {Type IO LastRead 9 FirstWrite 10}
		my_assoc_mem_middle_key_mem {Type IO LastRead 9 FirstWrite 10}
		my_assoc_mem_lower_key_mem {Type IO LastRead 9 FirstWrite 10}
		my_assoc_mem_value {Type IO LastRead 10 FirstWrite 10}
		my_assoc_mem_fill_read {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "-1", "Max" : "-1"}
	, {"Name" : "Interval", "Min" : "-1", "Max" : "-1"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	chr_stream1 { ap_fifo {  { chr_stream1_dout fifo_data 0 8 }  { chr_stream1_empty_n fifo_status 0 1 }  { chr_stream1_read fifo_update 1 1 } } }
	cmprs_stream2 { ap_fifo {  { cmprs_stream2_din fifo_data 1 16 }  { cmprs_stream2_full_n fifo_status 0 1 }  { cmprs_stream2_write fifo_update 1 1 } } }
	cmprs_len_stream3 { ap_fifo {  { cmprs_len_stream3_din fifo_data 1 32 }  { cmprs_len_stream3_full_n fifo_status 0 1 }  { cmprs_len_stream3_write fifo_update 1 1 } } }
	length_r { ap_none {  { length_r in_data 0 32 } } }
	hash_table { ap_memory {  { hash_table_address0 mem_address 1 15 }  { hash_table_ce0 mem_ce 1 1 }  { hash_table_we0 mem_we 1 1 }  { hash_table_d0 mem_din 1 33 }  { hash_table_q0 mem_dout 0 33 } } }
	my_assoc_mem_upper_key_mem { ap_memory {  { my_assoc_mem_upper_key_mem_address0 mem_address 1 9 }  { my_assoc_mem_upper_key_mem_ce0 mem_ce 1 1 }  { my_assoc_mem_upper_key_mem_we0 mem_we 1 1 }  { my_assoc_mem_upper_key_mem_d0 mem_din 1 64 }  { my_assoc_mem_upper_key_mem_q0 mem_dout 0 64 } } }
	my_assoc_mem_middle_key_mem { ap_memory {  { my_assoc_mem_middle_key_mem_address0 mem_address 1 9 }  { my_assoc_mem_middle_key_mem_ce0 mem_ce 1 1 }  { my_assoc_mem_middle_key_mem_we0 mem_we 1 1 }  { my_assoc_mem_middle_key_mem_d0 mem_din 1 64 }  { my_assoc_mem_middle_key_mem_q0 mem_dout 0 64 } } }
	my_assoc_mem_lower_key_mem { ap_memory {  { my_assoc_mem_lower_key_mem_address0 mem_address 1 9 }  { my_assoc_mem_lower_key_mem_ce0 mem_ce 1 1 }  { my_assoc_mem_lower_key_mem_we0 mem_we 1 1 }  { my_assoc_mem_lower_key_mem_d0 mem_din 1 64 }  { my_assoc_mem_lower_key_mem_q0 mem_dout 0 64 } } }
	my_assoc_mem_value { ap_memory {  { my_assoc_mem_value_address0 mem_address 1 6 }  { my_assoc_mem_value_ce0 mem_ce 1 1 }  { my_assoc_mem_value_we0 mem_we 1 1 }  { my_assoc_mem_value_d0 mem_din 1 12 }  { my_assoc_mem_value_q0 mem_dout 0 12 } } }
	my_assoc_mem_fill_read { ap_none {  { my_assoc_mem_fill_read in_data 0 32 } } }
}
