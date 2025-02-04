--****************************************************************
--Actel Corporation Proprietary and Confidential
--Copyright 2009 Actel Corporation.  All rights reserved
--
--ANY USE OR REDISTRIBUTION IN PART OR IN WHOLE MUST BE HANDLED IN
--ACCORDANCE WITH THE ACTEL LICENSE AGREEMENT AND MUST BE APPROVED
--IN ADVANCE IN WRITING.
--
--Description: CoreCORDIC
--             Word-Serial Package File. Sine table test bench
--
--Rev:
--v3.0 12/16/09  Sana : Maintenance Update
--
--SVN Revision Information:
--SVN$Revision:$
--SVN$Date:$
--
--Resolved SARS
--19458 10/14/09 Sana No longer requires package directory
--19459 10/14/09 Sana No longer requires package directory
--
--Notes:
--
--****************************************************************
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_UNSIGNED.all;
use IEEE.STD_LOGIC_ARITH.all;
USE std.textio.all;
use ieee.numeric_std.all;

package CORDIC_DATA is
  CONSTANT abcd       : integer:=0;
  CONSTANT TABLEROWS  : integer:=16;
  CONSTANT RCPRGAIN   : std_logic_vector(15 DOWNTO 0) := "0010011011011101";
  CONSTANT ANGLEINIT  : std_logic_vector(15 DOWNTO 0) := "1100000000000000";
  CONSTANT DELANGLE   : std_logic_vector(15 DOWNTO 0) := "0000100000000000";
  CONSTANT SCALE      : real := 16384.0;
  CONSTANT PI         : real := 3.14159265358979;
  CONSTANT PIdivSCALE : real := 0.0000958737992428525730; --PI/2/SCALE
  CONSTANT RCPRSCALE  : real := 0.000061035156250000;
  TYPE GOLDARRAY IS ARRAY (0 to 33) OF std_logic_vector(15 DOWNTO 0);
  TYPE ROMARRAY IS ARRAY (0 to 16) OF std_logic_vector(15 DOWNTO 0);
    -- Gold Sine
  CONSTANT gold_sc: GOLDARRAY := (  --LUT of arctan
    "1011111111111110",
    "1100000100111011",
    "1100010011100001",
    "1100101011001100",
    "1101001010111110",
    "1101110001101110",
    "1110011110000101",
    "1111001110001001",
    "0000000000000100",
    "0000110001111101",
    "0001100010000000",
    "0010001110010000",
    "0010110101000001",
    "0011010100110100",
    "0011101100100011",
    "0011111011000111",
    -- Gold Cosine
    "0000000000000000",
    "0000110001111110",
    "0001100001111111",
    "0010001110010001",
    "0010110101000100",
    "0011010100110110",
    "0011101100100100",
    "0011111011000100",
    "0011111111111111",
    "0011111011000101",
    "0011101100011111",
    "0011010100110100",
    "0010110101000010",
    "0010001110010000",
    "0001100001111010",
    "0000110001110111",
    "0000000000000001", "0000000000000001");
    -- Gold Magnitude = sqrt(x^2+y^2)
  CONSTANT gold_mp: GOLDARRAY := (  --LUT of arctan
    "0100000000000101",
    "0100000000000010",
    "0100000000000011",
    "0100000000000100",
    "0100000000000100",
    "0100000000000100",
    "0100000000000001",
    "0100000000000100",
    "0100000000000101",
    "0100000000000010",
    "0100000000000011",
    "0100000000000100",
    "0100000000000100",
    "0100000000000100",
    "0100000000000001",
    "0100000000000100",
    -- Gold Phase = arctan(y/x)
    "1100000000000000",
    "1100100000000010",
    "1101000000000000",
    "1101011111111100",
    "1101111111111110",
    "1110100000000010",
    "1111000000000000",
    "1111100000000000",
    "0000000000000000",
    "0000100000000010",
    "0001000000000000",
    "0001011111111100",
    "0001111111111110",
    "0010100000000010",
    "0011000000000000",
    "0011100000000000",
    "0000000000000001", "0000000000000001");
    -- input X values
  CONSTANT test_input: GOLDARRAY := (  --LUT of arctan
    "0000000000000000",
    "0000011110010101",
    "0000111011011111",
    "0001010110010111",
    "0001101101111011",
    "0010000001010000",
    "0010001111101000",
    "0010011000011110",
    "0010011011011101",
    "0010011000011110",
    "0010001111101000",
    "0010000001010000",
    "0001101101111011",
    "0001010110010111",
    "0000111011011111",
    "0000011110010101",
    -- input Y values
    "1101100100100011",
    "1101100111100010",
    "1101110000011000",
    "1101111110110000",
    "1110010010000101",
    "1110101001101001",
    "1111000100100001",
    "1111100001101011",
    "0000000000000000",
    "0000011110010101",
    "0000111011011111",
    "0001010110010111",
    "0001101101111011",
    "0010000001010000",
    "0010001111101000",
    "0010011000011110",
    "0000000000000001", "0000000000000001");
end CORDIC_DATA;

package body CORDIC_DATA is
end CORDIC_DATA;
