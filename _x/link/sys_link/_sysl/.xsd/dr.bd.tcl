

#---------------------------
# Constant blocks
#---------------------------

#---------------------------
# Platform Parameters for u96v2_sbc_base
#---------------------------
set zynq_ultra_ps_e_0 [get_bd_cell /zynq_ultra_ps_e_0]
    
set_property -dict [ list \
  CONFIG.PSU__USE__M_AXI_GP1 1 \
  CONFIG.PSU__USE__S_AXI_GP2 1 \
  ] $zynq_ultra_ps_e_0

#---------------------------
# Instantiating hardware_encoding_1
#---------------------------
set hardware_encoding_1 [create_bd_cell -type ip -vlnv xilinx.com:hls:hardware_encoding:1.0 hardware_encoding_1]
  

#---------------------------
# Instantiating axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD
#---------------------------
set axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD [create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD]
  
set_property -dict [ list  \
  CONFIG.NUM_MI {1} \
  CONFIG.NUM_SI {1} \
  CONFIG.M00_HAS_REGSLICE {0} \
  CONFIG.S00_HAS_REGSLICE {0}  ] $axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD

#---------------------------
# Instantiating axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD
#---------------------------
set axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD [create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD]
  
set_property -dict [ list  \
  CONFIG.NUM_MI {1} \
  CONFIG.NUM_SI {1} \
  CONFIG.M00_HAS_REGSLICE {0} \
  CONFIG.S00_HAS_REGSLICE {0}  ] $axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD

#---------------------------
# Instantiating axi_intc_0_intr_1_interrupt_concat
#---------------------------
set axi_intc_0_intr_1_interrupt_concat [create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 axi_intc_0_intr_1_interrupt_concat]
  
set_property -dict [ list  \
  CONFIG.NUM_PORTS {32}  ] $axi_intc_0_intr_1_interrupt_concat

#---------------------------
# Instantiating irq_const_tieoff
#---------------------------
set irq_const_tieoff [create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 irq_const_tieoff]
  
set_property -dict [ list  \
  CONFIG.CONST_WIDTH {1} \
  CONFIG.CONST_VAL {0}  ] $irq_const_tieoff

#---------------------------
# Connectivity Phase 1
#---------------------------
connect_bd_intf_net \
  [get_bd_intf_pins -auto_enable /zynq_ultra_ps_e_0/M_AXI_HPM1_FPD] \
  [get_bd_intf_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD/S00_AXI] \

connect_bd_intf_net \
  [get_bd_intf_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD/M00_AXI] \
  [get_bd_intf_pins -auto_enable /zynq_ultra_ps_e_0/S_AXI_HP0_FPD] \

connect_bd_intf_net \
  [get_bd_intf_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD/M00_AXI] \
  [get_bd_intf_pins -auto_enable /hardware_encoding_1/s_axi_control] \

connect_bd_intf_net \
  [get_bd_intf_pins -auto_enable /hardware_encoding_1/m_axi_gmem] \
  [get_bd_intf_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD/S00_AXI] \

connect_bd_net  \
  [get_bd_pins -auto_enable /clk_wiz_0/clk_out1] \
  [get_bd_pins -auto_enable /zynq_ultra_ps_e_0/maxihpm1_fpd_aclk] \
  [get_bd_pins -auto_enable /zynq_ultra_ps_e_0/saxihp0_fpd_aclk] \
  [get_bd_pins -auto_enable /hardware_encoding_1/ap_clk] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD/S00_ACLK] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD/M00_ACLK] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD/ACLK] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD/S00_ACLK] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD/ACLK] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD/M00_ACLK] \

connect_bd_net  \
  [get_bd_pins -auto_enable /proc_sys_reset_0/interconnect_aresetn] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD/ARESETN] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD/S00_ARESETN] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_M_AXI_HPM1_FPD/M00_ARESETN] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD/ARESETN] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD/M00_ARESETN] \
  [get_bd_pins -auto_enable /axi_ic_zynq_ultra_ps_e_0_S_AXI_HP0_FPD/S00_ARESETN] \

connect_bd_net  \
  [get_bd_pins -auto_enable /proc_sys_reset_0/peripheral_aresetn] \
  [get_bd_pins -auto_enable /hardware_encoding_1/ap_rst_n] \

connect_bd_net  \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/dout] \
  [get_bd_pins -auto_enable /axi_intc_0/intr] \

connect_bd_net  \
  [get_bd_pins -auto_enable /hardware_encoding_1/interrupt] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In1] \

connect_bd_net  \
  [get_bd_pins -auto_enable /irq_const_tieoff/dout] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In0] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In2] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In3] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In4] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In5] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In6] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In7] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In8] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In9] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In10] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In11] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In12] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In13] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In14] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In15] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In16] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In17] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In18] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In19] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In20] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In21] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In22] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In23] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In24] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In25] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In26] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In27] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In28] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In29] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In30] \
  [get_bd_pins -auto_enable /axi_intc_0_intr_1_interrupt_concat/In31] \


#---------------------------
# Connectivity Phase 2
#---------------------------

#---------------------------
# Create Stream Map file
#---------------------------
set stream_subsystems [get_bd_cells * -hierarchical -quiet -filter {VLNV =~ "*:*:sdx_stream_subsystem:*"}]
if {[string length $stream_subsystems] > 0} {    
  set xmlFile $vpl_output_dir/qdma_stream_map.xml
  set fp [open ${xmlFile} w]
  puts $fp "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  puts $fp "<xd:streamMap xmlns:xd=\"http://www.xilinx.com/xd\">"
  foreach streamSS [get_bd_cells * -hierarchical -quiet -filter {VLNV =~ "*:*:sdx_stream_subsystem:*"}] {
    set ssInstance [string trimleft $streamSS /]
    set ssRegion [get_property CONFIG.SLR_ASSIGNMENTS $streamSS]
    foreach ssIntf [get_bd_intf_pins $streamSS/* -quiet -filter {NAME=~"S??_AXIS"}] {
      set pinName [get_property NAME $ssIntf]
      set routeId [sdx_stream_subsystem::get_routeid $ssIntf]
      set flowId [sdx_stream_subsystem::get_flowid $ssIntf]
      puts $fp "  <xd:streamRoute xd:instanceRef=\"$ssInstance\" xd:portRef=\"$pinName\" xd:route=\"$routeId\" xd:flow=\"$flowId\" xd:region=\"$ssRegion\">"
      foreach connection [find_bd_objs -relation connected_to $ssIntf -thru_hier] {
        set connectedRegion [get_property CONFIG.SLR_ASSIGNMENTS [bd::utils::get_parent $connection]]
        set connectedPort [bd::utils::get_short_name $connection]
        set connectedInst [string trimleft [bd::utils::get_parent $connection] /]
        puts $fp "    <xd:connection xd:instanceRef=\"$connectedInst\" xd:portRef=\"$connectedPort\" xd:region=\"$connectedRegion\"/>"
      }
      puts $fp "  </xd:streamRoute>"
    }
    foreach ssIntf [get_bd_intf_pins $streamSS/* -quiet -filter {NAME=~"M??_AXIS"}] {
      set pinName [get_property NAME $ssIntf]
      set routeId [sdx_stream_subsystem::get_routeid $ssIntf]
      set flowId [sdx_stream_subsystem::get_flowid $ssIntf]
      puts $fp "  <xd:streamRoute xd:instanceRef=\"$ssInstance\" xd:portRef=\"$pinName\" xd:route=\"$routeId\" xd:flow=\"$flowId\" xd:region=\"$ssRegion\">"
      foreach connection [find_bd_objs -relation connected_to $ssIntf -thru_hier] {
        set connectedRegion [get_property CONFIG.SLR_ASSIGNMENTS [bd::utils::get_parent $connection]]
        set connectedPort [bd::utils::get_short_name $connection]
        set connectedInst [string trimleft [bd::utils::get_parent $connection] /]
        puts $fp "    <xd:connection xd:instanceRef=\"$connectedInst\" xd:portRef=\"$connectedPort\" xd:region=\"$connectedRegion\"/>"
      }
      puts $fp "  </xd:streamRoute>"
    }
  }
  puts $fp "</xd:streamMap>"
  close $fp
}

