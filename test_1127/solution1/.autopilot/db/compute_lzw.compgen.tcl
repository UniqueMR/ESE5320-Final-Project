# This script segment is generated automatically by AutoPilot

# clear list
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_begin
    cg_default_interface_gen_bundle_begin
    AESL_LIB_XILADAPTER::native_axis_begin
}

# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 5 \
    name hash_table \
    reset_level 1 \
    sync_rst true \
    dir IO \
    corename hash_table \
    op interface \
    ports { hash_table_address0 { O 15 vector } hash_table_ce0 { O 1 bit } hash_table_we0 { O 1 bit } hash_table_d0 { O 33 vector } hash_table_q0 { I 33 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'hash_table'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 6 \
    name my_assoc_mem_upper_key_mem \
    reset_level 1 \
    sync_rst true \
    dir IO \
    corename my_assoc_mem_upper_key_mem \
    op interface \
    ports { my_assoc_mem_upper_key_mem_address0 { O 9 vector } my_assoc_mem_upper_key_mem_ce0 { O 1 bit } my_assoc_mem_upper_key_mem_we0 { O 1 bit } my_assoc_mem_upper_key_mem_d0 { O 64 vector } my_assoc_mem_upper_key_mem_q0 { I 64 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'my_assoc_mem_upper_key_mem'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 7 \
    name my_assoc_mem_middle_key_mem \
    reset_level 1 \
    sync_rst true \
    dir IO \
    corename my_assoc_mem_middle_key_mem \
    op interface \
    ports { my_assoc_mem_middle_key_mem_address0 { O 9 vector } my_assoc_mem_middle_key_mem_ce0 { O 1 bit } my_assoc_mem_middle_key_mem_we0 { O 1 bit } my_assoc_mem_middle_key_mem_d0 { O 64 vector } my_assoc_mem_middle_key_mem_q0 { I 64 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'my_assoc_mem_middle_key_mem'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 8 \
    name my_assoc_mem_lower_key_mem \
    reset_level 1 \
    sync_rst true \
    dir IO \
    corename my_assoc_mem_lower_key_mem \
    op interface \
    ports { my_assoc_mem_lower_key_mem_address0 { O 9 vector } my_assoc_mem_lower_key_mem_ce0 { O 1 bit } my_assoc_mem_lower_key_mem_we0 { O 1 bit } my_assoc_mem_lower_key_mem_d0 { O 64 vector } my_assoc_mem_lower_key_mem_q0 { I 64 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'my_assoc_mem_lower_key_mem'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 9 \
    name my_assoc_mem_value \
    reset_level 1 \
    sync_rst true \
    dir IO \
    corename my_assoc_mem_value \
    op interface \
    ports { my_assoc_mem_value_address0 { O 6 vector } my_assoc_mem_value_ce0 { O 1 bit } my_assoc_mem_value_we0 { O 1 bit } my_assoc_mem_value_d0 { O 12 vector } my_assoc_mem_value_q0 { I 12 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'my_assoc_mem_value'"
}
}


# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 1 \
    name chr_stream1 \
    type fifo \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_chr_stream1 \
    op interface \
    ports { chr_stream1_dout { I 8 vector } chr_stream1_empty_n { I 1 bit } chr_stream1_read { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 2 \
    name cmprs_stream2 \
    type fifo \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_cmprs_stream2 \
    op interface \
    ports { cmprs_stream2_din { O 16 vector } cmprs_stream2_full_n { I 1 bit } cmprs_stream2_write { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 3 \
    name cmprs_len_stream3 \
    type fifo \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_cmprs_len_stream3 \
    op interface \
    ports { cmprs_len_stream3_din { O 32 vector } cmprs_len_stream3_full_n { I 1 bit } cmprs_len_stream3_write { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 4 \
    name length_r \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_length_r \
    op interface \
    ports { length_r { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 10 \
    name my_assoc_mem_fill_read \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_my_assoc_mem_fill_read \
    op interface \
    ports { my_assoc_mem_fill_read { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id -1 \
    name ap_ctrl \
    type ap_ctrl \
    reset_level 1 \
    sync_rst true \
    corename ap_ctrl \
    op interface \
    ports { ap_start { I 1 bit } ap_ready { O 1 bit } ap_done { O 1 bit } ap_idle { O 1 bit } } \
} "
}


# Adapter definition:
set PortName ap_clk
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_clock] == "cg_default_interface_gen_clock"} {
eval "cg_default_interface_gen_clock { \
    id -2 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_clk \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-113\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}


# Adapter definition:
set PortName ap_rst
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_reset] == "cg_default_interface_gen_reset"} {
eval "cg_default_interface_gen_reset { \
    id -3 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_rst \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-114\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}



# merge
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_end
    cg_default_interface_gen_bundle_end
    AESL_LIB_XILADAPTER::native_axis_end
}


