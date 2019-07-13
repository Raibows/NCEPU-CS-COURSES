--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.20131013
--  \   \         Application: netgen
--  /   /         Filename: controller_translate.vhd
-- /___/   /\     Timestamp: Mon Jul 08 09:51:05 2019
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -rpw 100 -tpw 0 -ar Structure -tm controller -w -dir netgen/translate -ofmt vhdl -sim controller.ngd controller_translate.vhd 
-- Device	: 3s1200efg320-4
-- Input file	: controller.ngd
-- Output file	: C:\CO exps\2 ALU\netgen\translate\controller_translate.vhd
-- # of Entities	: 1
-- Design Name	: controller
-- Xilinx	: C:\Xilinx\14.7\ISE_DS\ISE\
--             
-- Purpose:    
--     This VHDL netlist is a verification model and uses simulation 
--     primitives which may not represent the true implementation of the 
--     device, however the netlist is functionally correct and should not 
--     be modified. This file cannot be synthesized and should only be used 
--     with supported simulation tools.
--             
-- Reference:  
--     Command Line Tools User Guide, Chapter 23
--     Synthesis and Simulation Design Guide, Chapter 6
--             
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library SIMPRIM;
use SIMPRIM.VCOMPONENTS.ALL;
use SIMPRIM.VPACKAGE.ALL;

entity controller is
  port (
    clk : in STD_LOGIC := 'X'; 
    rst : in STD_LOGIC := 'X'; 
    showCtrl : in STD_LOGIC := 'X'; 
    bZero_ctrl : in STD_LOGIC := 'X'; 
    stateCnt : out STD_LOGIC_VECTOR ( 6 downto 0 ); 
    OUTPUT : out STD_LOGIC_VECTOR ( 15 downto 0 ); 
    INPUT : in STD_LOGIC_VECTOR ( 15 downto 0 ) 
  );
end controller;

architecture Structure of controller is
  signal ALUOp_mux0000_0_0 : STD_LOGIC; 
  signal ALUOp_mux0000_0_110_10 : STD_LOGIC; 
  signal ALUOp_mux0000_0_116_11 : STD_LOGIC; 
  signal ALUOp_mux0000_0_21_12 : STD_LOGIC; 
  signal ALUOp_mux0000_0_28_13 : STD_LOGIC; 
  signal ALUOp_mux0000_1_16_15 : STD_LOGIC; 
  signal ALUsrcA_0_mux0000 : STD_LOGIC; 
  signal ALUsrcB_Acst_inv : STD_LOGIC; 
  signal ALUsrcB_mux0000_0_17_22 : STD_LOGIC; 
  signal ALUsrcB_mux0000_0_5_23 : STD_LOGIC; 
  signal ALUsrcB_mux0000_1_12_25 : STD_LOGIC; 
  signal INPUT_0_IBUF_33 : STD_LOGIC; 
  signal INPUT_11_IBUF_34 : STD_LOGIC; 
  signal INPUT_12_IBUF_35 : STD_LOGIC; 
  signal INPUT_13_IBUF_36 : STD_LOGIC; 
  signal INPUT_14_IBUF_37 : STD_LOGIC; 
  signal INPUT_15_IBUF_38 : STD_LOGIC; 
  signal INPUT_1_IBUF_39 : STD_LOGIC; 
  signal IRWrite_0_mux0000 : STD_LOGIC; 
  signal IorD_0_mux0000 : STD_LOGIC; 
  signal IorD_0_mux000012_44 : STD_LOGIC; 
  signal IorD_0_mux00002_45 : STD_LOGIC; 
  signal MemRead_0_mux0000_47 : STD_LOGIC; 
  signal MemWrite_0_mux0000_49 : STD_LOGIC; 
  signal MemtoReg_mux0000_0_5_53 : STD_LOGIC; 
  signal N0 : STD_LOGIC; 
  signal N1 : STD_LOGIC; 
  signal N10 : STD_LOGIC; 
  signal N11 : STD_LOGIC; 
  signal N13 : STD_LOGIC; 
  signal N15 : STD_LOGIC; 
  signal N19 : STD_LOGIC; 
  signal N23 : STD_LOGIC; 
  signal N25 : STD_LOGIC; 
  signal N28 : STD_LOGIC; 
  signal N3 : STD_LOGIC; 
  signal N30 : STD_LOGIC; 
  signal N32 : STD_LOGIC; 
  signal N33 : STD_LOGIC; 
  signal N35 : STD_LOGIC; 
  signal N36 : STD_LOGIC; 
  signal N38 : STD_LOGIC; 
  signal N39 : STD_LOGIC; 
  signal N4 : STD_LOGIC; 
  signal N41 : STD_LOGIC; 
  signal N42 : STD_LOGIC; 
  signal N44 : STD_LOGIC; 
  signal N45 : STD_LOGIC; 
  signal N47 : STD_LOGIC; 
  signal N48 : STD_LOGIC; 
  signal N50 : STD_LOGIC; 
  signal N51 : STD_LOGIC; 
  signal N52 : STD_LOGIC; 
  signal N56 : STD_LOGIC; 
  signal N57 : STD_LOGIC; 
  signal N58 : STD_LOGIC; 
  signal N60 : STD_LOGIC; 
  signal N61 : STD_LOGIC; 
  signal N611 : STD_LOGIC; 
  signal N62 : STD_LOGIC; 
  signal N63 : STD_LOGIC; 
  signal N64 : STD_LOGIC; 
  signal N65 : STD_LOGIC; 
  signal N8 : STD_LOGIC; 
  signal N81 : STD_LOGIC; 
  signal PcWrite_0_mux0000 : STD_LOGIC; 
  signal RegWrite_mux0000_0_10_114 : STD_LOGIC; 
  signal RegWrite_mux0000_0_30_115 : STD_LOGIC; 
  signal clk_BUFGP : STD_LOGIC; 
  signal instr_0_Q : STD_LOGIC; 
  signal instr_1_Q : STD_LOGIC; 
  signal instr_11_Q : STD_LOGIC; 
  signal instr_12_Q : STD_LOGIC; 
  signal instr_13_Q : STD_LOGIC; 
  signal instr_14_Q : STD_LOGIC; 
  signal instr_15_Q : STD_LOGIC; 
  signal instr_and0000 : STD_LOGIC; 
  signal rst_IBUF_127 : STD_LOGIC; 
  signal showCtrl_BUFGP : STD_LOGIC; 
  signal show_state_FSM_FFd1_130 : STD_LOGIC; 
  signal show_state_FSM_FFd2_131 : STD_LOGIC; 
  signal show_state_FSM_FFd3_132 : STD_LOGIC; 
  signal show_state_FSM_FFd4_133 : STD_LOGIC; 
  signal stateCnt_1_OBUF_141 : STD_LOGIC; 
  signal stateCnt_2_142 : STD_LOGIC; 
  signal stateCnt_3_143 : STD_LOGIC; 
  signal stateCnt_4_144 : STD_LOGIC; 
  signal stateCnt_5_145 : STD_LOGIC; 
  signal stateCnt_6_146 : STD_LOGIC; 
  signal state_FSM_FFd1_147 : STD_LOGIC; 
  signal state_FSM_FFd2_148 : STD_LOGIC; 
  signal state_FSM_FFd3_149 : STD_LOGIC; 
  signal state_FSM_FFd4_150 : STD_LOGIC; 
  signal state_FSM_FFd5_151 : STD_LOGIC; 
  signal state_index0000 : STD_LOGIC; 
  signal state_index0001 : STD_LOGIC; 
  signal state_index0002 : STD_LOGIC; 
  signal state_index0003 : STD_LOGIC; 
  signal state_index0004 : STD_LOGIC; 
  signal to_output_11_Q : STD_LOGIC; 
  signal to_output_11_mux0000_158 : STD_LOGIC; 
  signal to_output_13_Q : STD_LOGIC; 
  signal to_output_14_Q : STD_LOGIC; 
  signal to_output_14_mux0000 : STD_LOGIC; 
  signal to_output_14_mux00001_162 : STD_LOGIC; 
  signal to_output_14_mux00002_163 : STD_LOGIC; 
  signal to_output_15_Q : STD_LOGIC; 
  signal to_output_15_mux0001_165 : STD_LOGIC; 
  signal to_output_2_Q : STD_LOGIC; 
  signal to_output_2_mux0000_167 : STD_LOGIC; 
  signal to_output_6_Q : STD_LOGIC; 
  signal to_output_7_Q : STD_LOGIC; 
  signal to_output_7_mux0001_170 : STD_LOGIC; 
  signal to_output_2_mux0000_SW0_O : STD_LOGIC; 
  signal to_output_7_mux0001_SW0_O : STD_LOGIC; 
  signal to_output_15_mux0001_SW0_O : STD_LOGIC; 
  signal to_output_11_mux0000_SW0_O : STD_LOGIC; 
  signal IorD_0_mux000012_O : STD_LOGIC; 
  signal RegWrite_mux0000_0_10_O : STD_LOGIC; 
  signal ALUOp_mux0000_0_211_O : STD_LOGIC; 
  signal ALUOp_mux0000_0_110_O : STD_LOGIC; 
  signal MemRead_0_mux0000_SW0_O : STD_LOGIC; 
  signal ALUsrcB_mux0000_1_11_SW0_SW0_O : STD_LOGIC; 
  signal ALUsrcB_mux0000_0_17_O : STD_LOGIC; 
  signal ALUsrcB_mux0000_1_28_SW1_O : STD_LOGIC; 
  signal ALUOp_mux0000_1_1_SW2_O : STD_LOGIC; 
  signal RegWrite_mux0000_0_30_O : STD_LOGIC; 
  signal ALUOp_mux0000_0_46_SW0_O : STD_LOGIC; 
  signal INPUT_10_IBUF_196 : STD_LOGIC; 
  signal INPUT_9_IBUF_197 : STD_LOGIC; 
  signal INPUT_8_IBUF_198 : STD_LOGIC; 
  signal INPUT_7_IBUF_199 : STD_LOGIC; 
  signal INPUT_6_IBUF_200 : STD_LOGIC; 
  signal INPUT_5_IBUF_201 : STD_LOGIC; 
  signal INPUT_4_IBUF_202 : STD_LOGIC; 
  signal INPUT_3_IBUF_203 : STD_LOGIC; 
  signal INPUT_2_IBUF_204 : STD_LOGIC; 
  signal clk_BUFGP_IBUFG_2 : STD_LOGIC; 
  signal showCtrl_BUFGP_IBUFG_5 : STD_LOGIC; 
  signal VCC : STD_LOGIC; 
  signal GND : STD_LOGIC; 
  signal ALUOp : STD_LOGIC_VECTOR ( 1 downto 0 ); 
  signal ALUOp_mux0000 : STD_LOGIC_VECTOR ( 1 downto 0 ); 
  signal ALUsrcA : STD_LOGIC_VECTOR ( 0 downto 0 ); 
  signal ALUsrcB : STD_LOGIC_VECTOR ( 1 downto 0 ); 
  signal ALUsrcB_mux0000 : STD_LOGIC_VECTOR ( 1 downto 0 ); 
  signal IRWrite : STD_LOGIC_VECTOR ( 0 downto 0 ); 
  signal IorD : STD_LOGIC_VECTOR ( 0 downto 0 ); 
  signal MemRead : STD_LOGIC_VECTOR ( 0 downto 0 ); 
  signal MemWrite : STD_LOGIC_VECTOR ( 0 downto 0 ); 
  signal MemtoReg : STD_LOGIC_VECTOR ( 1 downto 0 ); 
  signal MemtoReg_mux0000 : STD_LOGIC_VECTOR ( 0 downto 0 ); 
  signal PcWrite : STD_LOGIC_VECTOR ( 0 downto 0 ); 
  signal RegWrite : STD_LOGIC_VECTOR ( 0 downto 0 ); 
  signal RegWrite_mux0000 : STD_LOGIC_VECTOR ( 0 downto 0 ); 
begin
  XST_GND : X_ZERO
    port map (
      O => MemtoReg(1)
    );
  XST_VCC : X_ONE
    port map (
      O => stateCnt_1_OBUF_141
    );
  MemtoReg_0 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => MemtoReg_mux0000(0),
      O => MemtoReg(0),
      CE => VCC,
      SET => GND
    );
  ALUsrcA_0 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => ALUsrcA_0_mux0000,
      O => ALUsrcA(0),
      CE => VCC,
      SET => GND
    );
  RegWrite_0 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => RegWrite_mux0000(0),
      O => RegWrite(0),
      CE => VCC,
      SET => GND
    );
  PcWrite_0 : X_FF
    generic map(
      INIT => '1'
    )
    port map (
      CLK => clk_BUFGP,
      I => PcWrite_0_mux0000,
      SET => ALUsrcB_Acst_inv,
      O => PcWrite(0),
      CE => VCC,
      RST => GND
    );
  ALUOp_0 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => ALUOp_mux0000(1),
      O => ALUOp(0),
      CE => VCC,
      SET => GND
    );
  ALUOp_1 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => ALUOp_mux0000(0),
      O => ALUOp(1),
      CE => VCC,
      SET => GND
    );
  MemRead_0 : X_FF
    generic map(
      INIT => '1'
    )
    port map (
      CLK => clk_BUFGP,
      I => MemRead_0_mux0000_47,
      SET => ALUsrcB_Acst_inv,
      O => MemRead(0),
      CE => VCC,
      RST => GND
    );
  IRWrite_0 : X_FF
    generic map(
      INIT => '1'
    )
    port map (
      CLK => clk_BUFGP,
      I => IRWrite_0_mux0000,
      SET => ALUsrcB_Acst_inv,
      O => IRWrite(0),
      CE => VCC,
      RST => GND
    );
  to_output_2 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => showCtrl_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => to_output_2_mux0000_167,
      O => to_output_2_Q,
      CE => VCC,
      SET => GND
    );
  to_output_11 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => showCtrl_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => to_output_11_mux0000_158,
      O => to_output_11_Q,
      CE => VCC,
      SET => GND
    );
  MemWrite_0 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => MemWrite_0_mux0000_49,
      O => MemWrite(0),
      CE => VCC,
      SET => GND
    );
  to_output_14 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => showCtrl_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => to_output_14_mux0000,
      O => to_output_14_Q,
      CE => VCC,
      SET => GND
    );
  to_output_7 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => showCtrl_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => to_output_7_mux0001_170,
      O => to_output_7_Q,
      CE => VCC,
      SET => GND
    );
  to_output_15 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => showCtrl_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => to_output_15_mux0001_165,
      O => to_output_15_Q,
      CE => VCC,
      SET => GND
    );
  instr_0 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      CE => instr_and0000,
      I => INPUT_0_IBUF_33,
      O => instr_0_Q,
      SET => GND,
      RST => GND
    );
  instr_1 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      CE => instr_and0000,
      I => INPUT_1_IBUF_39,
      O => instr_1_Q,
      SET => GND,
      RST => GND
    );
  instr_11 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      CE => instr_and0000,
      I => INPUT_11_IBUF_34,
      O => instr_11_Q,
      SET => GND,
      RST => GND
    );
  instr_12 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      CE => instr_and0000,
      I => INPUT_12_IBUF_35,
      O => instr_12_Q,
      SET => GND,
      RST => GND
    );
  instr_13 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      CE => instr_and0000,
      I => INPUT_13_IBUF_36,
      O => instr_13_Q,
      SET => GND,
      RST => GND
    );
  instr_14 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      CE => instr_and0000,
      I => INPUT_14_IBUF_37,
      O => instr_14_Q,
      SET => GND,
      RST => GND
    );
  instr_15 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      CE => instr_and0000,
      I => INPUT_15_IBUF_38,
      O => instr_15_Q,
      SET => GND,
      RST => GND
    );
  IorD_0 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => IorD_0_mux0000,
      O => IorD(0),
      CE => VCC,
      SET => GND
    );
  to_output_13 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => showCtrl_BUFGP,
      CE => show_state_FSM_FFd1_130,
      RST => ALUsrcB_Acst_inv,
      I => RegWrite(0),
      O => to_output_13_Q,
      SET => GND
    );
  to_output_6 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => showCtrl_BUFGP,
      CE => show_state_FSM_FFd3_132,
      RST => ALUsrcB_Acst_inv,
      I => ALUsrcB(0),
      O => to_output_6_Q,
      SET => GND
    );
  show_state_FSM_FFd4 : X_FF
    generic map(
      INIT => '1'
    )
    port map (
      CLK => showCtrl_BUFGP,
      I => show_state_FSM_FFd1_130,
      SET => ALUsrcB_Acst_inv,
      O => show_state_FSM_FFd4_133,
      CE => VCC,
      RST => GND
    );
  show_state_FSM_FFd3 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => showCtrl_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => show_state_FSM_FFd4_133,
      O => show_state_FSM_FFd3_132,
      CE => VCC,
      SET => GND
    );
  show_state_FSM_FFd2 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => showCtrl_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => show_state_FSM_FFd3_132,
      O => show_state_FSM_FFd2_131,
      CE => VCC,
      SET => GND
    );
  show_state_FSM_FFd1 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => showCtrl_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => show_state_FSM_FFd2_131,
      O => show_state_FSM_FFd1_130,
      CE => VCC,
      SET => GND
    );
  ALUsrcB_1 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => ALUsrcB_mux0000(0),
      O => ALUsrcB(1),
      CE => VCC,
      SET => GND
    );
  ALUsrcB_0 : X_FF
    generic map(
      INIT => '1'
    )
    port map (
      CLK => clk_BUFGP,
      I => ALUsrcB_mux0000(1),
      SET => ALUsrcB_Acst_inv,
      O => ALUsrcB(0),
      CE => VCC,
      RST => GND
    );
  state_FSM_FFd5 : X_FF
    generic map(
      INIT => '1'
    )
    port map (
      CLK => clk_BUFGP,
      I => state_FSM_FFd1_147,
      SET => ALUsrcB_Acst_inv,
      O => state_FSM_FFd5_151,
      CE => VCC,
      RST => GND
    );
  state_FSM_FFd4 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => state_FSM_FFd5_151,
      O => state_FSM_FFd4_150,
      CE => VCC,
      SET => GND
    );
  state_FSM_FFd3 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => state_FSM_FFd4_150,
      O => state_FSM_FFd3_149,
      CE => VCC,
      SET => GND
    );
  state_FSM_FFd2 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => state_FSM_FFd3_149,
      O => state_FSM_FFd2_148,
      CE => VCC,
      SET => GND
    );
  state_FSM_FFd1 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => state_FSM_FFd2_148,
      O => state_FSM_FFd1_147,
      CE => VCC,
      SET => GND
    );
  stateCnt_5 : X_FF
    generic map(
      INIT => '1'
    )
    port map (
      CLK => clk_BUFGP,
      I => state_index0001,
      SET => ALUsrcB_Acst_inv,
      O => stateCnt_5_145,
      CE => VCC,
      RST => GND
    );
  stateCnt_4 : X_FF
    generic map(
      INIT => '1'
    )
    port map (
      CLK => clk_BUFGP,
      I => state_index0002,
      SET => ALUsrcB_Acst_inv,
      O => stateCnt_4_144,
      CE => VCC,
      RST => GND
    );
  stateCnt_6 : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      CLK => clk_BUFGP,
      RST => ALUsrcB_Acst_inv,
      I => state_index0000,
      O => stateCnt_6_146,
      CE => VCC,
      SET => GND
    );
  stateCnt_3 : X_FF
    generic map(
      INIT => '1'
    )
    port map (
      CLK => clk_BUFGP,
      I => state_index0003,
      SET => ALUsrcB_Acst_inv,
      O => stateCnt_3_143,
      CE => VCC,
      RST => GND
    );
  stateCnt_2 : X_FF
    generic map(
      INIT => '1'
    )
    port map (
      CLK => clk_BUFGP,
      I => state_index0004,
      SET => ALUsrcB_Acst_inv,
      O => stateCnt_2_142,
      CE => VCC,
      RST => GND
    );
  state_FSM_Out71 : X_LUT2
    generic map(
      INIT => X"E"
    )
    port map (
      ADR0 => state_FSM_FFd1_147,
      ADR1 => state_FSM_FFd4_150,
      O => state_index0002
    );
  state_FSM_Out61 : X_LUT2
    generic map(
      INIT => X"E"
    )
    port map (
      ADR0 => state_FSM_FFd1_147,
      ADR1 => state_FSM_FFd2_148,
      O => state_index0001
    );
  state_Out81 : X_LUT3
    generic map(
      INIT => X"FE"
    )
    port map (
      ADR0 => state_FSM_FFd1_147,
      ADR1 => state_FSM_FFd3_149,
      ADR2 => state_FSM_FFd4_150,
      O => state_index0003
    );
  instr_and00001 : X_LUT2
    generic map(
      INIT => X"8"
    )
    port map (
      ADR0 => rst_IBUF_127,
      ADR1 => state_FSM_FFd5_151,
      O => instr_and0000
    );
  to_output_2_mux0000 : X_LUT4
    generic map(
      INIT => X"F888"
    )
    port map (
      ADR0 => show_state_FSM_FFd2_131,
      ADR1 => MemtoReg(0),
      ADR2 => to_output_2_Q,
      ADR3 => N0,
      O => to_output_2_mux0000_167
    );
  to_output_7_mux0001 : X_LUT3
    generic map(
      INIT => X"EA"
    )
    port map (
      ADR0 => N4,
      ADR1 => show_state_FSM_FFd1_130,
      ADR2 => IorD(0),
      O => to_output_7_mux0001_170
    );
  to_output_15_mux0001 : X_LUT3
    generic map(
      INIT => X"EA"
    )
    port map (
      ADR0 => N61,
      ADR1 => show_state_FSM_FFd2_131,
      ADR2 => MemRead(0),
      O => to_output_15_mux0001_165
    );
  to_output_11_mux0000 : X_LUT3
    generic map(
      INIT => X"EA"
    )
    port map (
      ADR0 => N81,
      ADR1 => show_state_FSM_FFd1_130,
      ADR2 => to_output_11_Q,
      O => to_output_11_mux0000_158
    );
  state_FSM_Out51 : X_LUT3
    generic map(
      INIT => X"FE"
    )
    port map (
      ADR0 => state_FSM_FFd2_148,
      ADR1 => state_FSM_FFd3_149,
      ADR2 => state_FSM_FFd4_150,
      O => state_index0000
    );
  IRWrite_0_mux00001 : X_LUT3
    generic map(
      INIT => X"EA"
    )
    port map (
      ADR0 => state_FSM_FFd1_147,
      ADR1 => IRWrite(0),
      ADR2 => state_index0000,
      O => IRWrite_0_mux0000
    );
  PcWrite_0_mux00002 : X_LUT3
    generic map(
      INIT => X"EA"
    )
    port map (
      ADR0 => state_FSM_FFd1_147,
      ADR1 => PcWrite(0),
      ADR2 => N611,
      O => PcWrite_0_mux0000
    );
  ALUsrcA_0_mux00001 : X_LUT4
    generic map(
      INIT => X"A0EC"
    )
    port map (
      ADR0 => ALUsrcA(0),
      ADR1 => state_FSM_FFd4_150,
      ADR2 => state_index0000,
      ADR3 => N3,
      O => ALUsrcA_0_mux0000
    );
  ALUOp_mux0000_0_21 : X_LUT4
    generic map(
      INIT => X"2000"
    )
    port map (
      ADR0 => instr_15_Q,
      ADR1 => instr_12_Q,
      ADR2 => instr_14_Q,
      ADR3 => instr_13_Q,
      O => N11
    );
  MemtoReg_mux0000_0_1_SW0 : X_LUT4
    generic map(
      INIT => X"DF0F"
    )
    port map (
      ADR0 => instr_1_Q,
      ADR1 => instr_0_Q,
      ADR2 => instr_14_Q,
      ADR3 => instr_11_Q,
      O => N13
    );
  ALUsrcB_mux0000_0_5 : X_LUT3
    generic map(
      INIT => X"AE"
    )
    port map (
      ADR0 => state_FSM_FFd5_151,
      ADR1 => state_FSM_FFd4_150,
      ADR2 => N60,
      O => ALUsrcB_mux0000_0_5_23
    );
  ALUsrcB_mux0000_0_33 : X_LUT4
    generic map(
      INIT => X"FFA8"
    )
    port map (
      ADR0 => ALUsrcB(1),
      ADR1 => ALUOp_mux0000_0_0,
      ADR2 => ALUsrcB_mux0000_0_17_22,
      ADR3 => ALUsrcB_mux0000_0_5_23,
      O => ALUsrcB_mux0000(0)
    );
  ALUOp_mux0000_0_28 : X_LUT4
    generic map(
      INIT => X"AAA8"
    )
    port map (
      ADR0 => instr_13_Q,
      ADR1 => instr_11_Q,
      ADR2 => instr_12_Q,
      ADR3 => ALUOp_mux0000_0_21_12,
      O => ALUOp_mux0000_0_28_13
    );
  ALUsrcB_mux0000_1_12 : X_LUT4
    generic map(
      INIT => X"11F1"
    )
    port map (
      ADR0 => instr_11_Q,
      ADR1 => instr_0_Q,
      ADR2 => instr_13_Q,
      ADR3 => instr_14_Q,
      O => ALUsrcB_mux0000_1_12_25
    );
  ALUOp_mux0000_1_112 : X_LUT4
    generic map(
      INIT => X"E3CF"
    )
    port map (
      ADR0 => instr_0_Q,
      ADR1 => instr_12_Q,
      ADR2 => instr_13_Q,
      ADR3 => instr_11_Q,
      O => N10
    );
  MemWrite_0_mux0000_SW0 : X_LUT3
    generic map(
      INIT => X"08"
    )
    port map (
      ADR0 => instr_14_Q,
      ADR1 => state_FSM_FFd3_149,
      ADR2 => N1,
      O => N19
    );
  rst_IBUF : X_BUF
    port map (
      I => rst,
      O => rst_IBUF_127
    );
  INPUT_15_IBUF : X_BUF
    port map (
      I => INPUT(15),
      O => INPUT_15_IBUF_38
    );
  INPUT_14_IBUF : X_BUF
    port map (
      I => INPUT(14),
      O => INPUT_14_IBUF_37
    );
  INPUT_13_IBUF : X_BUF
    port map (
      I => INPUT(13),
      O => INPUT_13_IBUF_36
    );
  INPUT_12_IBUF : X_BUF
    port map (
      I => INPUT(12),
      O => INPUT_12_IBUF_35
    );
  INPUT_11_IBUF : X_BUF
    port map (
      I => INPUT(11),
      O => INPUT_11_IBUF_34
    );
  INPUT_1_IBUF : X_BUF
    port map (
      I => INPUT(1),
      O => INPUT_1_IBUF_39
    );
  INPUT_0_IBUF : X_BUF
    port map (
      I => INPUT(0),
      O => INPUT_0_IBUF_33
    );
  ALUsrcB_mux0000_1_11 : X_LUT4
    generic map(
      INIT => X"F5FD"
    )
    port map (
      ADR0 => instr_15_Q,
      ADR1 => instr_13_Q,
      ADR2 => N10,
      ADR3 => N23,
      O => N8
    );
  RegWrite_mux0000_0_37 : X_LUT4
    generic map(
      INIT => X"FFA8"
    )
    port map (
      ADR0 => RegWrite(0),
      ADR1 => state_FSM_FFd5_151,
      ADR2 => N51,
      ADR3 => RegWrite_mux0000_0_30_115,
      O => RegWrite_mux0000(0)
    );
  MemtoReg_mux0000_0_1_SW1 : X_LUT3
    generic map(
      INIT => X"DF"
    )
    port map (
      ADR0 => instr_15_Q,
      ADR1 => instr_12_Q,
      ADR2 => instr_13_Q,
      O => N28
    );
  MemtoReg_mux0000_0_5 : X_LUT4
    generic map(
      INIT => X"FAF8"
    )
    port map (
      ADR0 => state_FSM_FFd2_148,
      ADR1 => N28,
      ADR2 => N62,
      ADR3 => N13,
      O => MemtoReg_mux0000_0_5_53
    );
  MemtoReg_mux0000_0_1_SW2 : X_LUT4
    generic map(
      INIT => X"CFDF"
    )
    port map (
      ADR0 => instr_0_Q,
      ADR1 => instr_12_Q,
      ADR2 => instr_13_Q,
      ADR3 => instr_11_Q,
      O => N30
    );
  ALUsrcB_mux0000_1_46 : X_LUT4
    generic map(
      INIT => X"FE02"
    )
    port map (
      ADR0 => N32,
      ADR1 => ALUsrcB_mux0000_1_12_25,
      ADR2 => N8,
      ADR3 => N33,
      O => ALUsrcB_mux0000(1)
    );
  MemRead_0_mux00001_SW0 : X_LUT4
    generic map(
      INIT => X"EEEC"
    )
    port map (
      ADR0 => MemRead(0),
      ADR1 => state_FSM_FFd1_147,
      ADR2 => state_FSM_FFd4_150,
      ADR3 => N65,
      O => N35
    );
  MemRead_0_mux00001_SW1 : X_LUT4
    generic map(
      INIT => X"EEEC"
    )
    port map (
      ADR0 => MemRead(0),
      ADR1 => state_FSM_FFd1_147,
      ADR2 => state_FSM_FFd4_150,
      ADR3 => N63,
      O => N36
    );
  MemRead_0_mux0000 : X_LUT4
    generic map(
      INIT => X"FFE2"
    )
    port map (
      ADR0 => N35,
      ADR1 => N8,
      ADR2 => N36,
      ADR3 => N15,
      O => MemRead_0_mux0000_47
    );
  MemRead_0_mux00001_SW2 : X_LUT4
    generic map(
      INIT => X"AAA8"
    )
    port map (
      ADR0 => MemWrite(0),
      ADR1 => state_FSM_FFd5_151,
      ADR2 => state_FSM_FFd4_150,
      ADR3 => N25,
      O => N38
    );
  MemRead_0_mux00001_SW3 : X_LUT4
    generic map(
      INIT => X"AAA8"
    )
    port map (
      ADR0 => MemWrite(0),
      ADR1 => state_FSM_FFd5_151,
      ADR2 => state_FSM_FFd4_150,
      ADR3 => ALUOp_mux0000_0_0,
      O => N39
    );
  MemWrite_0_mux0000 : X_LUT4
    generic map(
      INIT => X"FFE2"
    )
    port map (
      ADR0 => N38,
      ADR1 => N8,
      ADR2 => N39,
      ADR3 => N19,
      O => MemWrite_0_mux0000_49
    );
  ALUOp_mux0000_0_131 : X_LUT4
    generic map(
      INIT => X"FBF8"
    )
    port map (
      ADR0 => N42,
      ADR1 => ALUOp_mux0000_0_28_13,
      ADR2 => ALUOp_mux0000_0_116_11,
      ADR3 => N41,
      O => ALUOp_mux0000(0)
    );
  ALUOp_mux0000_1_1_SW3 : X_LUT4
    generic map(
      INIT => X"BF7C"
    )
    port map (
      ADR0 => instr_0_Q,
      ADR1 => instr_15_Q,
      ADR2 => instr_14_Q,
      ADR3 => instr_11_Q,
      O => N45
    );
  ALUOp_mux0000_1_1 : X_LUT4
    generic map(
      INIT => X"DF9B"
    )
    port map (
      ADR0 => instr_12_Q,
      ADR1 => instr_13_Q,
      ADR2 => N44,
      ADR3 => N45,
      O => N3
    );
  ALUOp_mux0000_1_4_SW1 : X_LUT3
    generic map(
      INIT => X"EA"
    )
    port map (
      ADR0 => ALUOp(0),
      ADR1 => N64,
      ADR2 => N11,
      O => N48
    );
  ALUOp_mux0000_1_23 : X_LUT4
    generic map(
      INIT => X"F780"
    )
    port map (
      ADR0 => state_FSM_FFd4_150,
      ADR1 => N3,
      ADR2 => N48,
      ADR3 => N47,
      O => ALUOp_mux0000(1)
    );
  ALUOp_mux0000_0_116 : X_LUT4
    generic map(
      INIT => X"0800"
    )
    port map (
      ADR0 => state_FSM_FFd4_150,
      ADR1 => instr_13_Q,
      ADR2 => instr_12_Q,
      ADR3 => ALUOp_mux0000_0_110_10,
      O => ALUOp_mux0000_0_116_11
    );
  IorD_0_mux000026 : X_LUT4
    generic map(
      INIT => X"F222"
    )
    port map (
      ADR0 => state_FSM_FFd3_149,
      ADR1 => N1,
      ADR2 => IorD(0),
      ADR3 => IorD_0_mux000012_44,
      O => IorD_0_mux0000
    );
  ALUsrcB_mux0000_1_28_SW0 : X_LUT4
    generic map(
      INIT => X"EEEA"
    )
    port map (
      ADR0 => state_FSM_FFd1_147,
      ADR1 => ALUsrcB(0),
      ADR2 => state_FSM_FFd3_149,
      ADR3 => state_FSM_FFd2_148,
      O => N32
    );
  ALUOp_mux0000_0_46_SW1 : X_LUT4
    generic map(
      INIT => X"AAA8"
    )
    port map (
      ADR0 => ALUOp(1),
      ADR1 => state_FSM_FFd3_149,
      ADR2 => state_FSM_FFd2_148,
      ADR3 => state_FSM_FFd4_150,
      O => N42
    );
  RegWrite_mux0000_0_30_SW0 : X_LUT4
    generic map(
      INIT => X"DFFF"
    )
    port map (
      ADR0 => instr_15_Q,
      ADR1 => instr_12_Q,
      ADR2 => instr_13_Q,
      ADR3 => RegWrite_mux0000_0_10_114,
      O => N50
    );
  MemtoReg_mux0000_0_20_SW0 : X_LUT2
    generic map(
      INIT => X"D"
    )
    port map (
      ADR0 => state_FSM_FFd2_148,
      ADR1 => instr_14_Q,
      O => N52
    );
  MemtoReg_mux0000_0_22 : X_LUT4
    generic map(
      INIT => X"F111"
    )
    port map (
      ADR0 => N1,
      ADR1 => N52,
      ADR2 => MemtoReg(0),
      ADR3 => MemtoReg_mux0000_0_5_53,
      O => MemtoReg_mux0000(0)
    );
  ALUOp_mux0000_1_4_SW0 : X_MUX2
    port map (
      IA => N56,
      IB => N57,
      SEL => N11,
      O => N47
    );
  ALUOp_mux0000_1_4_SW0_F : X_LUT3
    generic map(
      INIT => X"A8"
    )
    port map (
      ADR0 => ALUOp(0),
      ADR1 => state_FSM_FFd3_149,
      ADR2 => state_FSM_FFd2_148,
      O => N56
    );
  ALUOp_mux0000_1_4_SW0_G : X_LUT4
    generic map(
      INIT => X"FFA8"
    )
    port map (
      ADR0 => ALUOp(0),
      ADR1 => state_FSM_FFd2_148,
      ADR2 => state_FSM_FFd3_149,
      ADR3 => ALUOp_mux0000_1_16_15,
      O => N57
    );
  ALUOp_mux0000_0_46_SW0_SW0 : X_LUT4
    generic map(
      INIT => X"AA80"
    )
    port map (
      ADR0 => instr_15_Q,
      ADR1 => instr_11_Q,
      ADR2 => instr_12_Q,
      ADR3 => instr_13_Q,
      O => N58
    );
  ALUsrcB_Acst_inv1_INV_0 : X_INV
    port map (
      I => rst_IBUF_127,
      O => ALUsrcB_Acst_inv
    );
  state_FSM_Out91_INV_0 : X_INV
    port map (
      I => state_FSM_FFd4_150,
      O => state_index0004
    );
  to_output_14_mux00001 : X_LUT4
    generic map(
      INIT => X"FFEA"
    )
    port map (
      ADR0 => show_state_FSM_FFd2_131,
      ADR1 => show_state_FSM_FFd3_132,
      ADR2 => ALUOp(0),
      ADR3 => show_state_FSM_FFd4_133,
      O => to_output_14_mux00001_162
    );
  to_output_14_mux00002 : X_LUT2
    generic map(
      INIT => X"8"
    )
    port map (
      ADR0 => show_state_FSM_FFd3_132,
      ADR1 => ALUOp(0),
      O => to_output_14_mux00002_163
    );
  to_output_14_mux0000_f5 : X_MUX2
    port map (
      IA => to_output_14_mux00002_163,
      IB => to_output_14_mux00001_162,
      SEL => to_output_14_Q,
      O => to_output_14_mux0000
    );
  to_output_2_mux0000_SW0_LUT2_L_BUF : X_BUF
    port map (
      I => to_output_2_mux0000_SW0_O,
      O => N0
    );
  to_output_2_mux0000_SW0 : X_LUT2
    generic map(
      INIT => X"E"
    )
    port map (
      ADR0 => show_state_FSM_FFd3_132,
      ADR1 => show_state_FSM_FFd4_133,
      O => to_output_2_mux0000_SW0_O
    );
  to_output_7_mux0001_SW0_LUT4_L_BUF : X_BUF
    port map (
      I => to_output_7_mux0001_SW0_O,
      O => N4
    );
  to_output_7_mux0001_SW0 : X_LUT4
    generic map(
      INIT => X"F888"
    )
    port map (
      ADR0 => show_state_FSM_FFd2_131,
      ADR1 => IRWrite(0),
      ADR2 => show_state_FSM_FFd3_132,
      ADR3 => ALUsrcB(1),
      O => to_output_7_mux0001_SW0_O
    );
  to_output_15_mux0001_SW0_LUT4_L_BUF : X_BUF
    port map (
      I => to_output_15_mux0001_SW0_O,
      O => N61
    );
  to_output_15_mux0001_SW0 : X_LUT4
    generic map(
      INIT => X"F888"
    )
    port map (
      ADR0 => PcWrite(0),
      ADR1 => show_state_FSM_FFd4_133,
      ADR2 => ALUOp(1),
      ADR3 => show_state_FSM_FFd3_132,
      O => to_output_15_mux0001_SW0_O
    );
  to_output_11_mux0000_SW0_LUT4_L_BUF : X_BUF
    port map (
      I => to_output_11_mux0000_SW0_O,
      O => N81
    );
  to_output_11_mux0000_SW0 : X_LUT4
    generic map(
      INIT => X"F888"
    )
    port map (
      ADR0 => show_state_FSM_FFd2_131,
      ADR1 => MemWrite(0),
      ADR2 => show_state_FSM_FFd3_132,
      ADR3 => ALUsrcA(0),
      O => to_output_11_mux0000_SW0_O
    );
  RegWrite_mux0000_0_11_LUT4_D_BUF : X_BUF
    port map (
      I => N1,
      O => N60
    );
  RegWrite_mux0000_0_11 : X_LUT4
    generic map(
      INIT => X"F7FF"
    )
    port map (
      ADR0 => instr_15_Q,
      ADR1 => instr_12_Q,
      ADR2 => instr_13_Q,
      ADR3 => instr_11_Q,
      O => N1
    );
  PcWrite_0_mux000011_LUT4_D_BUF : X_BUF
    port map (
      I => N51,
      O => N611
    );
  PcWrite_0_mux000011 : X_LUT4
    generic map(
      INIT => X"FEFA"
    )
    port map (
      ADR0 => state_FSM_FFd2_148,
      ADR1 => state_FSM_FFd3_149,
      ADR2 => state_FSM_FFd4_150,
      ADR3 => N1,
      O => N51
    );
  IorD_0_mux00002_LUT3_D_BUF : X_BUF
    port map (
      I => IorD_0_mux00002_45,
      O => N62
    );
  IorD_0_mux00002 : X_LUT3
    generic map(
      INIT => X"FE"
    )
    port map (
      ADR0 => state_FSM_FFd5_151,
      ADR1 => state_FSM_FFd3_149,
      ADR2 => state_FSM_FFd4_150,
      O => IorD_0_mux00002_45
    );
  IorD_0_mux000012_LUT4_L_BUF : X_BUF
    port map (
      I => IorD_0_mux000012_O,
      O => IorD_0_mux000012_44
    );
  IorD_0_mux000012 : X_LUT4
    generic map(
      INIT => X"FCF4"
    )
    port map (
      ADR0 => instr_14_Q,
      ADR1 => state_FSM_FFd2_148,
      ADR2 => IorD_0_mux00002_45,
      ADR3 => N1,
      O => IorD_0_mux000012_O
    );
  RegWrite_mux0000_0_10_LUT3_L_BUF : X_BUF
    port map (
      I => RegWrite_mux0000_0_10_O,
      O => RegWrite_mux0000_0_10_114
    );
  RegWrite_mux0000_0_10 : X_LUT3
    generic map(
      INIT => X"2F"
    )
    port map (
      ADR0 => instr_1_Q,
      ADR1 => instr_0_Q,
      ADR2 => instr_11_Q,
      O => RegWrite_mux0000_0_10_O
    );
  ALUsrcB_mux0000_0_6_LUT2_D_BUF : X_BUF
    port map (
      I => ALUOp_mux0000_0_0,
      O => N63
    );
  ALUsrcB_mux0000_0_6 : X_LUT2
    generic map(
      INIT => X"E"
    )
    port map (
      ADR0 => state_FSM_FFd3_149,
      ADR1 => state_FSM_FFd2_148,
      O => ALUOp_mux0000_0_0
    );
  ALUOp_mux0000_1_16_LUT4_D_BUF : X_BUF
    port map (
      I => ALUOp_mux0000_1_16_15,
      O => N64
    );
  ALUOp_mux0000_1_16 : X_LUT4
    generic map(
      INIT => X"0800"
    )
    port map (
      ADR0 => instr_1_Q,
      ADR1 => instr_0_Q,
      ADR2 => instr_11_Q,
      ADR3 => state_FSM_FFd4_150,
      O => ALUOp_mux0000_1_16_15
    );
  ALUOp_mux0000_0_211_LUT2_L_BUF : X_BUF
    port map (
      I => ALUOp_mux0000_0_211_O,
      O => ALUOp_mux0000_0_21_12
    );
  ALUOp_mux0000_0_211 : X_LUT2
    generic map(
      INIT => X"7"
    )
    port map (
      ADR0 => instr_0_Q,
      ADR1 => instr_14_Q,
      O => ALUOp_mux0000_0_211_O
    );
  ALUOp_mux0000_0_110_LUT4_L_BUF : X_BUF
    port map (
      I => ALUOp_mux0000_0_110_O,
      O => ALUOp_mux0000_0_110_10
    );
  ALUOp_mux0000_0_110 : X_LUT4
    generic map(
      INIT => X"4003"
    )
    port map (
      ADR0 => instr_0_Q,
      ADR1 => instr_15_Q,
      ADR2 => instr_14_Q,
      ADR3 => instr_11_Q,
      O => ALUOp_mux0000_0_110_O
    );
  MemRead_0_mux0000_SW0_LUT3_L_BUF : X_BUF
    port map (
      I => MemRead_0_mux0000_SW0_O,
      O => N15
    );
  MemRead_0_mux0000_SW0 : X_LUT3
    generic map(
      INIT => X"02"
    )
    port map (
      ADR0 => state_FSM_FFd3_149,
      ADR1 => instr_14_Q,
      ADR2 => N1,
      O => MemRead_0_mux0000_SW0_O
    );
  ALUsrcB_mux0000_1_11_SW0_SW0_LUT2_L_BUF : X_BUF
    port map (
      I => ALUsrcB_mux0000_1_11_SW0_SW0_O,
      O => N23
    );
  ALUsrcB_mux0000_1_11_SW0_SW0 : X_LUT2
    generic map(
      INIT => X"B"
    )
    port map (
      ADR0 => instr_1_Q,
      ADR1 => instr_11_Q,
      O => ALUsrcB_mux0000_1_11_SW0_SW0_O
    );
  MemRead_0_mux00001_SW0_SW0_LUT4_D_BUF : X_BUF
    port map (
      I => N25,
      O => N65
    );
  MemRead_0_mux00001_SW0_SW0 : X_LUT4
    generic map(
      INIT => X"FF10"
    )
    port map (
      ADR0 => instr_12_Q,
      ADR1 => instr_14_Q,
      ADR2 => state_FSM_FFd2_148,
      ADR3 => state_FSM_FFd3_149,
      O => N25
    );
  ALUsrcB_mux0000_0_17_LUT4_L_BUF : X_BUF
    port map (
      I => ALUsrcB_mux0000_0_17_O,
      O => ALUsrcB_mux0000_0_17_22
    );
  ALUsrcB_mux0000_0_17 : X_LUT4
    generic map(
      INIT => X"CCC4"
    )
    port map (
      ADR0 => instr_15_Q,
      ADR1 => state_FSM_FFd4_150,
      ADR2 => N30,
      ADR3 => N13,
      O => ALUsrcB_mux0000_0_17_O
    );
  ALUsrcB_mux0000_1_28_SW1_LUT4_L_BUF : X_BUF
    port map (
      I => ALUsrcB_mux0000_1_28_SW1_O,
      O => N33
    );
  ALUsrcB_mux0000_1_28_SW1 : X_LUT4
    generic map(
      INIT => X"EEEC"
    )
    port map (
      ADR0 => ALUsrcB(0),
      ADR1 => state_FSM_FFd1_147,
      ADR2 => state_FSM_FFd4_150,
      ADR3 => ALUOp_mux0000_0_0,
      O => ALUsrcB_mux0000_1_28_SW1_O
    );
  ALUOp_mux0000_1_1_SW2_LUT2_L_BUF : X_BUF
    port map (
      I => ALUOp_mux0000_1_1_SW2_O,
      O => N44
    );
  ALUOp_mux0000_1_1_SW2 : X_LUT2
    generic map(
      INIT => X"8"
    )
    port map (
      ADR0 => instr_15_Q,
      ADR1 => instr_11_Q,
      O => ALUOp_mux0000_1_1_SW2_O
    );
  RegWrite_mux0000_0_30_LUT4_L_BUF : X_BUF
    port map (
      I => RegWrite_mux0000_0_30_O,
      O => RegWrite_mux0000_0_30_115
    );
  RegWrite_mux0000_0_30 : X_LUT4
    generic map(
      INIT => X"048C"
    )
    port map (
      ADR0 => instr_14_Q,
      ADR1 => state_FSM_FFd2_148,
      ADR2 => N1,
      ADR3 => N50,
      O => RegWrite_mux0000_0_30_O
    );
  ALUOp_mux0000_0_46_SW0_LUT4_L_BUF : X_BUF
    port map (
      I => ALUOp_mux0000_0_46_SW0_O,
      O => N41
    );
  ALUOp_mux0000_0_46_SW0 : X_LUT4
    generic map(
      INIT => X"AA20"
    )
    port map (
      ADR0 => ALUOp(1),
      ADR1 => N58,
      ADR2 => state_FSM_FFd4_150,
      ADR3 => ALUOp_mux0000_0_0,
      O => ALUOp_mux0000_0_46_SW0_O
    );
  INPUT_10_IBUF : X_BUF
    port map (
      I => INPUT(10),
      O => INPUT_10_IBUF_196
    );
  INPUT_9_IBUF : X_BUF
    port map (
      I => INPUT(9),
      O => INPUT_9_IBUF_197
    );
  INPUT_8_IBUF : X_BUF
    port map (
      I => INPUT(8),
      O => INPUT_8_IBUF_198
    );
  INPUT_7_IBUF : X_BUF
    port map (
      I => INPUT(7),
      O => INPUT_7_IBUF_199
    );
  INPUT_6_IBUF : X_BUF
    port map (
      I => INPUT(6),
      O => INPUT_6_IBUF_200
    );
  INPUT_5_IBUF : X_BUF
    port map (
      I => INPUT(5),
      O => INPUT_5_IBUF_201
    );
  INPUT_4_IBUF : X_BUF
    port map (
      I => INPUT(4),
      O => INPUT_4_IBUF_202
    );
  INPUT_3_IBUF : X_BUF
    port map (
      I => INPUT(3),
      O => INPUT_3_IBUF_203
    );
  INPUT_2_IBUF : X_BUF
    port map (
      I => INPUT(2),
      O => INPUT_2_IBUF_204
    );
  clk_BUFGP_BUFG : X_CKBUF
    port map (
      I => clk_BUFGP_IBUFG_2,
      O => clk_BUFGP
    );
  clk_BUFGP_IBUFG : X_CKBUF
    port map (
      I => clk,
      O => clk_BUFGP_IBUFG_2
    );
  showCtrl_BUFGP_BUFG : X_CKBUF
    port map (
      I => showCtrl_BUFGP_IBUFG_5,
      O => showCtrl_BUFGP
    );
  showCtrl_BUFGP_IBUFG : X_CKBUF
    port map (
      I => showCtrl,
      O => showCtrl_BUFGP_IBUFG_5
    );
  OUTPUT_0_OBUF : X_OBUF
    port map (
      I => MemtoReg(1),
      O => OUTPUT(0)
    );
  OUTPUT_10_OBUF : X_OBUF
    port map (
      I => MemtoReg(1),
      O => OUTPUT(10)
    );
  OUTPUT_11_OBUF : X_OBUF
    port map (
      I => to_output_11_Q,
      O => OUTPUT(11)
    );
  OUTPUT_12_OBUF : X_OBUF
    port map (
      I => MemtoReg(1),
      O => OUTPUT(12)
    );
  OUTPUT_13_OBUF : X_OBUF
    port map (
      I => to_output_13_Q,
      O => OUTPUT(13)
    );
  OUTPUT_14_OBUF : X_OBUF
    port map (
      I => to_output_14_Q,
      O => OUTPUT(14)
    );
  OUTPUT_15_OBUF : X_OBUF
    port map (
      I => to_output_15_Q,
      O => OUTPUT(15)
    );
  OUTPUT_1_OBUF : X_OBUF
    port map (
      I => MemtoReg(1),
      O => OUTPUT(1)
    );
  OUTPUT_2_OBUF : X_OBUF
    port map (
      I => to_output_2_Q,
      O => OUTPUT(2)
    );
  OUTPUT_3_OBUF : X_OBUF
    port map (
      I => MemtoReg(1),
      O => OUTPUT(3)
    );
  OUTPUT_4_OBUF : X_OBUF
    port map (
      I => MemtoReg(1),
      O => OUTPUT(4)
    );
  OUTPUT_5_OBUF : X_OBUF
    port map (
      I => MemtoReg(1),
      O => OUTPUT(5)
    );
  OUTPUT_6_OBUF : X_OBUF
    port map (
      I => to_output_6_Q,
      O => OUTPUT(6)
    );
  OUTPUT_7_OBUF : X_OBUF
    port map (
      I => to_output_7_Q,
      O => OUTPUT(7)
    );
  OUTPUT_8_OBUF : X_OBUF
    port map (
      I => MemtoReg(1),
      O => OUTPUT(8)
    );
  OUTPUT_9_OBUF : X_OBUF
    port map (
      I => MemtoReg(1),
      O => OUTPUT(9)
    );
  stateCnt_0_OBUF : X_OBUF
    port map (
      I => stateCnt_3_143,
      O => stateCnt(0)
    );
  stateCnt_1_OBUF : X_OBUF
    port map (
      I => stateCnt_1_OBUF_141,
      O => stateCnt(1)
    );
  stateCnt_2_OBUF : X_OBUF
    port map (
      I => stateCnt_2_142,
      O => stateCnt(2)
    );
  stateCnt_3_OBUF : X_OBUF
    port map (
      I => stateCnt_3_143,
      O => stateCnt(3)
    );
  stateCnt_4_OBUF : X_OBUF
    port map (
      I => stateCnt_4_144,
      O => stateCnt(4)
    );
  stateCnt_5_OBUF : X_OBUF
    port map (
      I => stateCnt_5_145,
      O => stateCnt(5)
    );
  stateCnt_6_OBUF : X_OBUF
    port map (
      I => stateCnt_6_146,
      O => stateCnt(6)
    );
  NlwBlock_controller_VCC : X_ONE
    port map (
      O => VCC
    );
  NlwBlock_controller_GND : X_ZERO
    port map (
      O => GND
    );
  NlwBlockROC : X_ROC
    generic map (ROC_WIDTH => 100 ns)
    port map (O => GSR);
  NlwBlockTOC : X_TOC
    port map (O => GTS);

end Structure;

