############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project test_1127
set_top lzw_stream
add_files Server/lzw.cpp
add_files Server/lzw.h
add_files Server/lzw_stream.cpp
add_files Server/utils.cpp
add_files Server/utils.h
add_files -tb Server/Testbench.cpp
open_solution "solution1" -flow_target vitis
set_part {xczu3eg-sbva484-1-i}
create_clock -period 10 -name default
#source "./test_1127/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
