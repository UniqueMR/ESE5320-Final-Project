create_project prj -part xczu3eg-sbva484-1-i -force
set_property target_language verilog [current_project]
set vivado_ver [version -short]
set COE_DIR "../../syn/verilog"
source "/mnt/castor/seas_home/c/chen3xn/ese532_code/project_1127/ESE5320-Final-Project/test_1127/solution1/syn/verilog/lzw_stream_ap_sitofp_2_no_dsp_32_ip.tcl"
source "/mnt/castor/seas_home/c/chen3xn/ese532_code/project_1127/ESE5320-Final-Project/test_1127/solution1/syn/verilog/lzw_stream_ap_fptrunc_0_no_dsp_64_ip.tcl"
source "/mnt/castor/seas_home/c/chen3xn/ese532_code/project_1127/ESE5320-Final-Project/test_1127/solution1/syn/verilog/lzw_stream_ap_fcmp_0_no_dsp_32_ip.tcl"
source "/mnt/castor/seas_home/c/chen3xn/ese532_code/project_1127/ESE5320-Final-Project/test_1127/solution1/syn/verilog/lzw_stream_ap_dmul_4_max_dsp_64_ip.tcl"
source "/mnt/castor/seas_home/c/chen3xn/ese532_code/project_1127/ESE5320-Final-Project/test_1127/solution1/syn/verilog/lzw_stream_ap_sitodp_2_no_dsp_32_ip.tcl"
