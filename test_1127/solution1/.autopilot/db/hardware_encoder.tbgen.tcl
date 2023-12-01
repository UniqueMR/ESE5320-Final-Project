set moduleName hardware_encoder
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
set C_modelName {hardware_encoder}
set C_modelType { void 0 }
set C_modelArgList {
	{ gmem int 32 regular {axi_master 2}  }
	{ s1 int 64 regular  }
	{ length_r int 32 regular  }
	{ file_buffer int 64 regular  }
	{ total_bytes int 64 regular  }
	{ hash_table int 33 regular {array 32768 { 2 3 } 1 1 }  }
	{ my_assoc_mem_upper_key_mem int 64 regular {array 512 { 2 3 } 1 1 }  }
	{ my_assoc_mem_middle_key_mem int 64 regular {array 512 { 2 3 } 1 1 }  }
	{ my_assoc_mem_lower_key_mem int 64 regular {array 512 { 2 3 } 1 1 }  }
	{ my_assoc_mem_value int 12 regular {array 64 { 2 3 } 1 1 }  }
	{ my_assoc_mem_fill_read int 32 regular  }
}
set C_modelArgMapList {[ 
	{ "Name" : "gmem", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READWRITE"} , 
 	{ "Name" : "s1", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "length_r", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "file_buffer", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "total_bytes", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "hash_table", "interface" : "memory", "bitwidth" : 33, "direction" : "READWRITE"} , 
 	{ "Name" : "my_assoc_mem_upper_key_mem", "interface" : "memory", "bitwidth" : 64, "direction" : "READWRITE"} , 
 	{ "Name" : "my_assoc_mem_middle_key_mem", "interface" : "memory", "bitwidth" : 64, "direction" : "READWRITE"} , 
 	{ "Name" : "my_assoc_mem_lower_key_mem", "interface" : "memory", "bitwidth" : 64, "direction" : "READWRITE"} , 
 	{ "Name" : "my_assoc_mem_value", "interface" : "memory", "bitwidth" : 12, "direction" : "READWRITE"} , 
 	{ "Name" : "my_assoc_mem_fill_read", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} ]}
# RTL Port declarations: 
set portNum 81
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ m_axi_gmem_AWVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem_AWREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem_AWADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_gmem_AWID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem_AWLEN sc_out sc_lv 32 signal 0 } 
	{ m_axi_gmem_AWSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem_AWBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem_AWLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem_AWCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem_AWPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem_AWQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem_AWREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem_AWUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem_WVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem_WREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem_WDATA sc_out sc_lv 32 signal 0 } 
	{ m_axi_gmem_WSTRB sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem_WLAST sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem_WID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem_WUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem_ARVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem_ARREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem_ARADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_gmem_ARID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem_ARLEN sc_out sc_lv 32 signal 0 } 
	{ m_axi_gmem_ARSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem_ARBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem_ARLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem_ARCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem_ARPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem_ARQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem_ARREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem_ARUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem_RVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem_RREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem_RDATA sc_in sc_lv 32 signal 0 } 
	{ m_axi_gmem_RLAST sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem_RID sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem_RUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem_RRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_gmem_BVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem_BREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem_BRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_gmem_BID sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem_BUSER sc_in sc_lv 1 signal 0 } 
	{ s1 sc_in sc_lv 64 signal 1 } 
	{ length_r sc_in sc_lv 32 signal 2 } 
	{ file_buffer sc_in sc_lv 64 signal 3 } 
	{ total_bytes sc_in sc_lv 64 signal 4 } 
	{ hash_table_address0 sc_out sc_lv 15 signal 5 } 
	{ hash_table_ce0 sc_out sc_logic 1 signal 5 } 
	{ hash_table_we0 sc_out sc_logic 1 signal 5 } 
	{ hash_table_d0 sc_out sc_lv 33 signal 5 } 
	{ hash_table_q0 sc_in sc_lv 33 signal 5 } 
	{ my_assoc_mem_upper_key_mem_address0 sc_out sc_lv 9 signal 6 } 
	{ my_assoc_mem_upper_key_mem_ce0 sc_out sc_logic 1 signal 6 } 
	{ my_assoc_mem_upper_key_mem_we0 sc_out sc_logic 1 signal 6 } 
	{ my_assoc_mem_upper_key_mem_d0 sc_out sc_lv 64 signal 6 } 
	{ my_assoc_mem_upper_key_mem_q0 sc_in sc_lv 64 signal 6 } 
	{ my_assoc_mem_middle_key_mem_address0 sc_out sc_lv 9 signal 7 } 
	{ my_assoc_mem_middle_key_mem_ce0 sc_out sc_logic 1 signal 7 } 
	{ my_assoc_mem_middle_key_mem_we0 sc_out sc_logic 1 signal 7 } 
	{ my_assoc_mem_middle_key_mem_d0 sc_out sc_lv 64 signal 7 } 
	{ my_assoc_mem_middle_key_mem_q0 sc_in sc_lv 64 signal 7 } 
	{ my_assoc_mem_lower_key_mem_address0 sc_out sc_lv 9 signal 8 } 
	{ my_assoc_mem_lower_key_mem_ce0 sc_out sc_logic 1 signal 8 } 
	{ my_assoc_mem_lower_key_mem_we0 sc_out sc_logic 1 signal 8 } 
	{ my_assoc_mem_lower_key_mem_d0 sc_out sc_lv 64 signal 8 } 
	{ my_assoc_mem_lower_key_mem_q0 sc_in sc_lv 64 signal 8 } 
	{ my_assoc_mem_value_address0 sc_out sc_lv 6 signal 9 } 
	{ my_assoc_mem_value_ce0 sc_out sc_logic 1 signal 9 } 
	{ my_assoc_mem_value_we0 sc_out sc_logic 1 signal 9 } 
	{ my_assoc_mem_value_d0 sc_out sc_lv 12 signal 9 } 
	{ my_assoc_mem_value_q0 sc_in sc_lv 12 signal 9 } 
	{ my_assoc_mem_fill_read sc_in sc_lv 32 signal 10 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "m_axi_gmem_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "AWVALID" }} , 
 	{ "name": "m_axi_gmem_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "AWREADY" }} , 
 	{ "name": "m_axi_gmem_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem", "role": "AWADDR" }} , 
 	{ "name": "m_axi_gmem_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "AWID" }} , 
 	{ "name": "m_axi_gmem_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem", "role": "AWLEN" }} , 
 	{ "name": "m_axi_gmem_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_gmem_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "AWBURST" }} , 
 	{ "name": "m_axi_gmem_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_gmem_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_gmem_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem", "role": "AWPROT" }} , 
 	{ "name": "m_axi_gmem_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "AWQOS" }} , 
 	{ "name": "m_axi_gmem_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "AWREGION" }} , 
 	{ "name": "m_axi_gmem_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "AWUSER" }} , 
 	{ "name": "m_axi_gmem_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "WVALID" }} , 
 	{ "name": "m_axi_gmem_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "WREADY" }} , 
 	{ "name": "m_axi_gmem_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem", "role": "WDATA" }} , 
 	{ "name": "m_axi_gmem_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "WSTRB" }} , 
 	{ "name": "m_axi_gmem_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "WLAST" }} , 
 	{ "name": "m_axi_gmem_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "WID" }} , 
 	{ "name": "m_axi_gmem_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "WUSER" }} , 
 	{ "name": "m_axi_gmem_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "ARVALID" }} , 
 	{ "name": "m_axi_gmem_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "ARREADY" }} , 
 	{ "name": "m_axi_gmem_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem", "role": "ARADDR" }} , 
 	{ "name": "m_axi_gmem_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "ARID" }} , 
 	{ "name": "m_axi_gmem_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem", "role": "ARLEN" }} , 
 	{ "name": "m_axi_gmem_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_gmem_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "ARBURST" }} , 
 	{ "name": "m_axi_gmem_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_gmem_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_gmem_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem", "role": "ARPROT" }} , 
 	{ "name": "m_axi_gmem_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "ARQOS" }} , 
 	{ "name": "m_axi_gmem_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem", "role": "ARREGION" }} , 
 	{ "name": "m_axi_gmem_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "ARUSER" }} , 
 	{ "name": "m_axi_gmem_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "RVALID" }} , 
 	{ "name": "m_axi_gmem_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "RREADY" }} , 
 	{ "name": "m_axi_gmem_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem", "role": "RDATA" }} , 
 	{ "name": "m_axi_gmem_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "RLAST" }} , 
 	{ "name": "m_axi_gmem_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "RID" }} , 
 	{ "name": "m_axi_gmem_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "RUSER" }} , 
 	{ "name": "m_axi_gmem_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "RRESP" }} , 
 	{ "name": "m_axi_gmem_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BVALID" }} , 
 	{ "name": "m_axi_gmem_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BREADY" }} , 
 	{ "name": "m_axi_gmem_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem", "role": "BRESP" }} , 
 	{ "name": "m_axi_gmem_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BID" }} , 
 	{ "name": "m_axi_gmem_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem", "role": "BUSER" }} , 
 	{ "name": "s1", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "s1", "role": "default" }} , 
 	{ "name": "length_r", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "length_r", "role": "default" }} , 
 	{ "name": "file_buffer", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "file_buffer", "role": "default" }} , 
 	{ "name": "total_bytes", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "total_bytes", "role": "default" }} , 
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
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"],
		"CDFG" : "hardware_encoder",
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
			{"Name" : "gmem", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_R", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem_blk_n_B", "Type" : "RtlSignal"}]},
			{"Name" : "s1", "Type" : "None", "Direction" : "I"},
			{"Name" : "length_r", "Type" : "None", "Direction" : "I"},
			{"Name" : "file_buffer", "Type" : "None", "Direction" : "I"},
			{"Name" : "total_bytes", "Type" : "None", "Direction" : "I"},
			{"Name" : "hash_table", "Type" : "Memory", "Direction" : "IO",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_compute_lzw_fu_430", "Port" : "hash_table"}]},
			{"Name" : "my_assoc_mem_upper_key_mem", "Type" : "Memory", "Direction" : "IO",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_compute_lzw_fu_430", "Port" : "my_assoc_mem_upper_key_mem"}]},
			{"Name" : "my_assoc_mem_middle_key_mem", "Type" : "Memory", "Direction" : "IO",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_compute_lzw_fu_430", "Port" : "my_assoc_mem_middle_key_mem"}]},
			{"Name" : "my_assoc_mem_lower_key_mem", "Type" : "Memory", "Direction" : "IO",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_compute_lzw_fu_430", "Port" : "my_assoc_mem_lower_key_mem"}]},
			{"Name" : "my_assoc_mem_value", "Type" : "Memory", "Direction" : "IO",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_compute_lzw_fu_430", "Port" : "my_assoc_mem_value"}]},
			{"Name" : "my_assoc_mem_fill_read", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_compute_lzw_fu_430", "Parent" : "0",
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
			{"Name" : "my_assoc_mem_fill_read", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.sitofp_32ns_32_4_no_dsp_1_U11", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fptrunc_64ns_32_2_no_dsp_1_U12", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fcmp_32ns_32ns_1_2_no_dsp_1_U13", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fcmp_32ns_32ns_1_2_no_dsp_1_U14", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dmul_64ns_64ns_64_6_max_dsp_1_U15", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.sitodp_32ns_64_4_no_dsp_1_U16", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.chr_stream_fifo_U", "Parent" : "0"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cmprs_stream_fifo_U", "Parent" : "0"},
	{"ID" : "10", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cmprs_len_stream_fifo_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	hardware_encoder {
		gmem {Type IO LastRead 171 FirstWrite 24}
		s1 {Type I LastRead 0 FirstWrite -1}
		length_r {Type I LastRead 0 FirstWrite -1}
		file_buffer {Type I LastRead 0 FirstWrite -1}
		total_bytes {Type I LastRead 0 FirstWrite -1}
		hash_table {Type IO LastRead 8 FirstWrite 10}
		my_assoc_mem_upper_key_mem {Type IO LastRead 9 FirstWrite 10}
		my_assoc_mem_middle_key_mem {Type IO LastRead 9 FirstWrite 10}
		my_assoc_mem_lower_key_mem {Type IO LastRead 9 FirstWrite 10}
		my_assoc_mem_value {Type IO LastRead 10 FirstWrite 10}
		my_assoc_mem_fill_read {Type I LastRead 0 FirstWrite -1}}
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
	{"Pipeline" : "2", "EnableSignal" : "ap_enable_pp2"}
]}

set Spec2ImplPortList { 
	gmem { m_axi {  { m_axi_gmem_AWVALID VALID 1 1 }  { m_axi_gmem_AWREADY READY 0 1 }  { m_axi_gmem_AWADDR ADDR 1 64 }  { m_axi_gmem_AWID ID 1 1 }  { m_axi_gmem_AWLEN LEN 1 32 }  { m_axi_gmem_AWSIZE SIZE 1 3 }  { m_axi_gmem_AWBURST BURST 1 2 }  { m_axi_gmem_AWLOCK LOCK 1 2 }  { m_axi_gmem_AWCACHE CACHE 1 4 }  { m_axi_gmem_AWPROT PROT 1 3 }  { m_axi_gmem_AWQOS QOS 1 4 }  { m_axi_gmem_AWREGION REGION 1 4 }  { m_axi_gmem_AWUSER USER 1 1 }  { m_axi_gmem_WVALID VALID 1 1 }  { m_axi_gmem_WREADY READY 0 1 }  { m_axi_gmem_WDATA DATA 1 32 }  { m_axi_gmem_WSTRB STRB 1 4 }  { m_axi_gmem_WLAST LAST 1 1 }  { m_axi_gmem_WID ID 1 1 }  { m_axi_gmem_WUSER USER 1 1 }  { m_axi_gmem_ARVALID VALID 1 1 }  { m_axi_gmem_ARREADY READY 0 1 }  { m_axi_gmem_ARADDR ADDR 1 64 }  { m_axi_gmem_ARID ID 1 1 }  { m_axi_gmem_ARLEN LEN 1 32 }  { m_axi_gmem_ARSIZE SIZE 1 3 }  { m_axi_gmem_ARBURST BURST 1 2 }  { m_axi_gmem_ARLOCK LOCK 1 2 }  { m_axi_gmem_ARCACHE CACHE 1 4 }  { m_axi_gmem_ARPROT PROT 1 3 }  { m_axi_gmem_ARQOS QOS 1 4 }  { m_axi_gmem_ARREGION REGION 1 4 }  { m_axi_gmem_ARUSER USER 1 1 }  { m_axi_gmem_RVALID VALID 0 1 }  { m_axi_gmem_RREADY READY 1 1 }  { m_axi_gmem_RDATA DATA 0 32 }  { m_axi_gmem_RLAST LAST 0 1 }  { m_axi_gmem_RID ID 0 1 }  { m_axi_gmem_RUSER USER 0 1 }  { m_axi_gmem_RRESP RESP 0 2 }  { m_axi_gmem_BVALID VALID 0 1 }  { m_axi_gmem_BREADY READY 1 1 }  { m_axi_gmem_BRESP RESP 0 2 }  { m_axi_gmem_BID ID 0 1 }  { m_axi_gmem_BUSER USER 0 1 } } }
	s1 { ap_none {  { s1 in_data 0 64 } } }
	length_r { ap_none {  { length_r in_data 0 32 } } }
	file_buffer { ap_none {  { file_buffer in_data 0 64 } } }
	total_bytes { ap_none {  { total_bytes in_data 0 64 } } }
	hash_table { ap_memory {  { hash_table_address0 mem_address 1 15 }  { hash_table_ce0 mem_ce 1 1 }  { hash_table_we0 mem_we 1 1 }  { hash_table_d0 mem_din 1 33 }  { hash_table_q0 mem_dout 0 33 } } }
	my_assoc_mem_upper_key_mem { ap_memory {  { my_assoc_mem_upper_key_mem_address0 mem_address 1 9 }  { my_assoc_mem_upper_key_mem_ce0 mem_ce 1 1 }  { my_assoc_mem_upper_key_mem_we0 mem_we 1 1 }  { my_assoc_mem_upper_key_mem_d0 mem_din 1 64 }  { my_assoc_mem_upper_key_mem_q0 mem_dout 0 64 } } }
	my_assoc_mem_middle_key_mem { ap_memory {  { my_assoc_mem_middle_key_mem_address0 mem_address 1 9 }  { my_assoc_mem_middle_key_mem_ce0 mem_ce 1 1 }  { my_assoc_mem_middle_key_mem_we0 mem_we 1 1 }  { my_assoc_mem_middle_key_mem_d0 mem_din 1 64 }  { my_assoc_mem_middle_key_mem_q0 mem_dout 0 64 } } }
	my_assoc_mem_lower_key_mem { ap_memory {  { my_assoc_mem_lower_key_mem_address0 mem_address 1 9 }  { my_assoc_mem_lower_key_mem_ce0 mem_ce 1 1 }  { my_assoc_mem_lower_key_mem_we0 mem_we 1 1 }  { my_assoc_mem_lower_key_mem_d0 mem_din 1 64 }  { my_assoc_mem_lower_key_mem_q0 mem_dout 0 64 } } }
	my_assoc_mem_value { ap_memory {  { my_assoc_mem_value_address0 mem_address 1 6 }  { my_assoc_mem_value_ce0 mem_ce 1 1 }  { my_assoc_mem_value_we0 mem_we 1 1 }  { my_assoc_mem_value_d0 mem_din 1 12 }  { my_assoc_mem_value_q0 mem_dout 0 12 } } }
	my_assoc_mem_fill_read { ap_none {  { my_assoc_mem_fill_read in_data 0 32 } } }
}
