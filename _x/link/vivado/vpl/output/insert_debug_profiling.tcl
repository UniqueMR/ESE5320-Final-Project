# Monitor points

# Call debug/profiling automation
set dpa_dict [list \
             ]
set dpa_opts [list \
              AIE_TRACE  {PACKET_RATE 0 CLK_SELECT default PROFILE_STREAMS 0 MEM_SPACE {} MEM_INDEX {}} \
             ]

set_param bd.enable_dpa 1
set_param bd.debug_profile.script /mnt/castor/seas_home/c/chen3xn/ese532_code/project_1127/ESE5320-Final-Project/_x/link/vivado/vpl/.local/debug_profile_automation.tcl
apply_bd_automation -rule xilinx.com:bd_rule:debug_profile -opts $dpa_opts -dict $dpa_dict

# Write debug_ip_layout
debug_profile::write_debug_ip_layout false "avnet.com:u96v2_sbc_base:u96v2_sbc_base:1.0" "/mnt/castor/seas_home/c/chen3xn/ese532_code/project_1127/ESE5320-Final-Project/_x/link/int"
