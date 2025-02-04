-- -------------------------------------------------------------
--
-- Module: FILTER_RRC
--
-- Generated by MATLAB(R) 7.14 and the Filter Design HDL Coder 2.9.1.
--
-- Generated on: 2013-06-18 16:47:30
--
-- -------------------------------------------------------------

-- -------------------------------------------------------------
-- HDL Code Generation Options:
--
-- TargetLanguage: VHDL
-- ClockEnableInputPort: en
-- ResetInputPort: rst
-- UseRisingEdge: on
-- Name: FILTER_RRC
-- TestBenchName: Hps_tb
-- TestBenchStimulus: impulse step ramp chirp noise 
-- GenerateHDLTestBench: off

-- Filter Specifications:
--
-- Sampling Frequency : 20 MHz
-- Response           : Pulse Shaping
-- Specification      : Nsym,Beta
-- PulseShape         : Square Root Raised Cosine
-- SamplesPerSymbol   : 10 Hz
-- NumberOfSymbols    : 3 Hz
-- RolloffFactor      : 500 mHz
-- -------------------------------------------------------------

-- -------------------------------------------------------------
-- HDL Implementation    : Fully parallel
-- Multipliers           : 31
-- Folding Factor        : 1
-- -------------------------------------------------------------
-- Filter Settings:
--
-- Discrete-Time FIR Filter (real)
-- -------------------------------
-- Filter Structure  : Direct-Form FIR
-- Filter Length     : 31
-- Stable            : Yes
-- Linear Phase      : Yes (Type 1)
-- Arithmetic        : fixed
-- Numerator         : s16,18 -> [-1.250000e-01 1.250000e-01)
-- Input             : s10,9 -> [-1 1)
-- Filter Internals  : Specify Precision
--   Output          : s10,9 -> [-1 1)
--   Product         : s20,17 -> [-4 4)
--   Accumulator     : s28,17 -> [-1024 1024)
--   Round Mode      : convergent
--   Overflow Mode   : wrap
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.all;
USE IEEE.numeric_std.ALL;
ENTITY FILTER_RRC IS
   PORT( clk                             :   IN    std_logic; 
         en                              :   IN    std_logic; 
         rst                             :   IN    std_logic; 
         filter_in                       :   IN    std_logic_vector(9 DOWNTO 0); -- sfix10_En9
         filter_out                      :   OUT   std_logic_vector(9 DOWNTO 0)  -- sfix10_En9
         );

END FILTER_RRC;


----------------------------------------------------------------
--Module Architecture: FILTER_RRC
----------------------------------------------------------------
ARCHITECTURE rtl OF FILTER_RRC IS
  -- Local Functions
  -- Type Definitions
  TYPE delay_pipeline_type IS ARRAY (NATURAL range <>) OF signed(9 DOWNTO 0); -- sfix10_En9
  -- Constants
  CONSTANT coeff1                         : signed(15 DOWNTO 0) := to_signed(-1967, 16); -- sfix16_En18
  CONSTANT coeff2                         : signed(15 DOWNTO 0) := to_signed(-3025, 16); -- sfix16_En18
  CONSTANT coeff3                         : signed(15 DOWNTO 0) := to_signed(-3855, 16); -- sfix16_En18
  CONSTANT coeff4                         : signed(15 DOWNTO 0) := to_signed(-4226, 16); -- sfix16_En18
  CONSTANT coeff5                         : signed(15 DOWNTO 0) := to_signed(-3924, 16); -- sfix16_En18
  CONSTANT coeff6                         : signed(15 DOWNTO 0) := to_signed(-2781, 16); -- sfix16_En18
  CONSTANT coeff7                         : signed(15 DOWNTO 0) := to_signed(-706, 16); -- sfix16_En18
  CONSTANT coeff8                         : signed(15 DOWNTO 0) := to_signed(2296, 16); -- sfix16_En18
  CONSTANT coeff9                         : signed(15 DOWNTO 0) := to_signed(6106, 16); -- sfix16_En18
  CONSTANT coeff10                        : signed(15 DOWNTO 0) := to_signed(10502, 16); -- sfix16_En18
  CONSTANT coeff11                        : signed(15 DOWNTO 0) := to_signed(15169, 16); -- sfix16_En18
  CONSTANT coeff12                        : signed(15 DOWNTO 0) := to_signed(19735, 16); -- sfix16_En18
  CONSTANT coeff13                        : signed(15 DOWNTO 0) := to_signed(23810, 16); -- sfix16_En18
  CONSTANT coeff14                        : signed(15 DOWNTO 0) := to_signed(27026, 16); -- sfix16_En18
  CONSTANT coeff15                        : signed(15 DOWNTO 0) := to_signed(29086, 16); -- sfix16_En18
  CONSTANT coeff16                        : signed(15 DOWNTO 0) := to_signed(29796, 16); -- sfix16_En18
  CONSTANT coeff17                        : signed(15 DOWNTO 0) := to_signed(29086, 16); -- sfix16_En18
  CONSTANT coeff18                        : signed(15 DOWNTO 0) := to_signed(27026, 16); -- sfix16_En18
  CONSTANT coeff19                        : signed(15 DOWNTO 0) := to_signed(23810, 16); -- sfix16_En18
  CONSTANT coeff20                        : signed(15 DOWNTO 0) := to_signed(19735, 16); -- sfix16_En18
  CONSTANT coeff21                        : signed(15 DOWNTO 0) := to_signed(15169, 16); -- sfix16_En18
  CONSTANT coeff22                        : signed(15 DOWNTO 0) := to_signed(10502, 16); -- sfix16_En18
  CONSTANT coeff23                        : signed(15 DOWNTO 0) := to_signed(6106, 16); -- sfix16_En18
  CONSTANT coeff24                        : signed(15 DOWNTO 0) := to_signed(2296, 16); -- sfix16_En18
  CONSTANT coeff25                        : signed(15 DOWNTO 0) := to_signed(-706, 16); -- sfix16_En18
  CONSTANT coeff26                        : signed(15 DOWNTO 0) := to_signed(-2781, 16); -- sfix16_En18
  CONSTANT coeff27                        : signed(15 DOWNTO 0) := to_signed(-3924, 16); -- sfix16_En18
  CONSTANT coeff28                        : signed(15 DOWNTO 0) := to_signed(-4226, 16); -- sfix16_En18
  CONSTANT coeff29                        : signed(15 DOWNTO 0) := to_signed(-3855, 16); -- sfix16_En18
  CONSTANT coeff30                        : signed(15 DOWNTO 0) := to_signed(-3025, 16); -- sfix16_En18
  CONSTANT coeff31                        : signed(15 DOWNTO 0) := to_signed(-1967, 16); -- sfix16_En18

  -- Signals
  SIGNAL delay_pipeline                   : delay_pipeline_type(0 TO 30); -- sfix10_En9
  SIGNAL product31                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp                         : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product30                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_1                       : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product29                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_2                       : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product28                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_3                       : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product27                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_4                       : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product26                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_5                       : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product25                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_6                       : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product24                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_7                       : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product23                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_8                       : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product22                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_9                       : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product21                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_10                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product20                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_11                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product19                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_12                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product18                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_13                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product17                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_14                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product16                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_15                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product15                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_16                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product14                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_17                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product13                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_18                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product12                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_19                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product11                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_20                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product10                        : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_21                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product9                         : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_22                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product8                         : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_23                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product7                         : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_24                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product6                         : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_25                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product5                         : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_26                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product4                         : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_27                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product3                         : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_28                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product2                         : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_29                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL product1_cast                    : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL product1                         : signed(19 DOWNTO 0); -- sfix20_En17
  SIGNAL mul_temp_30                      : signed(25 DOWNTO 0); -- sfix26_En27
  SIGNAL sum1                             : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp                         : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum2                             : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_1                       : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum3                             : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_2                       : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum4                             : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_3                       : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum5                             : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_4                       : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum6                             : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_5                       : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum7                             : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_6                       : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum8                             : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_7                       : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum9                             : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_8                       : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum10                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_9                       : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum11                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_10                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum12                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_11                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum13                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_12                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum14                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_13                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum15                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_14                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum16                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_15                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum17                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_16                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum18                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_17                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum19                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_18                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum20                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_19                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum21                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_20                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum22                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_21                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum23                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_22                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum24                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_23                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum25                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_24                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum26                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_25                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum27                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_26                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum28                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_27                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum29                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_28                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL sum30                            : signed(27 DOWNTO 0); -- sfix28_En17
  SIGNAL add_temp_29                      : signed(28 DOWNTO 0); -- sfix29_En17
  SIGNAL output_typeconvert               : signed(9 DOWNTO 0); -- sfix10_En9
  SIGNAL output_register                  : signed(9 DOWNTO 0); -- sfix10_En9


BEGIN

  -- Block Statements
  Delay_Pipeline_process : PROCESS (clk, rst)
  BEGIN
    IF rst = '1' THEN
      delay_pipeline(0 TO 30) <= (OTHERS => (OTHERS => '0'));
    ELSIF rising_edge(clk) THEN
      IF en = '1' THEN
        delay_pipeline(0) <= signed(filter_in);
        delay_pipeline(1 TO 30) <= delay_pipeline(0 TO 29);
      END IF;
    END IF; 
  END PROCESS Delay_Pipeline_process;


  mul_temp <= delay_pipeline(30) * coeff31;
  product31 <= resize(shift_right(mul_temp(25) & mul_temp(25 DOWNTO 0) + ( "0" & (mul_temp(10) & NOT mul_temp(10) & NOT mul_temp(10) & NOT mul_temp(10) & NOT mul_temp(10) & NOT mul_temp(10) & NOT mul_temp(10) & NOT mul_temp(10) & NOT mul_temp(10) & NOT mul_temp(10))), 10), 20);

  mul_temp_1 <= delay_pipeline(29) * coeff30;
  product30 <= resize(shift_right(mul_temp_1(25) & mul_temp_1(25 DOWNTO 0) + ( "0" & (mul_temp_1(10) & NOT mul_temp_1(10) & NOT mul_temp_1(10) & NOT mul_temp_1(10) & NOT mul_temp_1(10) & NOT mul_temp_1(10) & NOT mul_temp_1(10) & NOT mul_temp_1(10) & NOT mul_temp_1(10) & NOT mul_temp_1(10))), 10), 20);

  mul_temp_2 <= delay_pipeline(28) * coeff29;
  product29 <= resize(shift_right(mul_temp_2(25) & mul_temp_2(25 DOWNTO 0) + ( "0" & (mul_temp_2(10) & NOT mul_temp_2(10) & NOT mul_temp_2(10) & NOT mul_temp_2(10) & NOT mul_temp_2(10) & NOT mul_temp_2(10) & NOT mul_temp_2(10) & NOT mul_temp_2(10) & NOT mul_temp_2(10) & NOT mul_temp_2(10))), 10), 20);

  mul_temp_3 <= delay_pipeline(27) * coeff28;
  product28 <= resize(shift_right(mul_temp_3(25) & mul_temp_3(25 DOWNTO 0) + ( "0" & (mul_temp_3(10) & NOT mul_temp_3(10) & NOT mul_temp_3(10) & NOT mul_temp_3(10) & NOT mul_temp_3(10) & NOT mul_temp_3(10) & NOT mul_temp_3(10) & NOT mul_temp_3(10) & NOT mul_temp_3(10) & NOT mul_temp_3(10))), 10), 20);

  mul_temp_4 <= delay_pipeline(26) * coeff27;
  product27 <= resize(shift_right(mul_temp_4(25) & mul_temp_4(25 DOWNTO 0) + ( "0" & (mul_temp_4(10) & NOT mul_temp_4(10) & NOT mul_temp_4(10) & NOT mul_temp_4(10) & NOT mul_temp_4(10) & NOT mul_temp_4(10) & NOT mul_temp_4(10) & NOT mul_temp_4(10) & NOT mul_temp_4(10) & NOT mul_temp_4(10))), 10), 20);

  mul_temp_5 <= delay_pipeline(25) * coeff26;
  product26 <= resize(shift_right(mul_temp_5(25) & mul_temp_5(25 DOWNTO 0) + ( "0" & (mul_temp_5(10) & NOT mul_temp_5(10) & NOT mul_temp_5(10) & NOT mul_temp_5(10) & NOT mul_temp_5(10) & NOT mul_temp_5(10) & NOT mul_temp_5(10) & NOT mul_temp_5(10) & NOT mul_temp_5(10) & NOT mul_temp_5(10))), 10), 20);

  mul_temp_6 <= delay_pipeline(24) * coeff25;
  product25 <= resize(shift_right(mul_temp_6(25) & mul_temp_6(25 DOWNTO 0) + ( "0" & (mul_temp_6(10) & NOT mul_temp_6(10) & NOT mul_temp_6(10) & NOT mul_temp_6(10) & NOT mul_temp_6(10) & NOT mul_temp_6(10) & NOT mul_temp_6(10) & NOT mul_temp_6(10) & NOT mul_temp_6(10) & NOT mul_temp_6(10))), 10), 20);

  mul_temp_7 <= delay_pipeline(23) * coeff24;
  product24 <= resize(shift_right(mul_temp_7(25) & mul_temp_7(25 DOWNTO 0) + ( "0" & (mul_temp_7(10) & NOT mul_temp_7(10) & NOT mul_temp_7(10) & NOT mul_temp_7(10) & NOT mul_temp_7(10) & NOT mul_temp_7(10) & NOT mul_temp_7(10) & NOT mul_temp_7(10) & NOT mul_temp_7(10) & NOT mul_temp_7(10))), 10), 20);

  mul_temp_8 <= delay_pipeline(22) * coeff23;
  product23 <= resize(shift_right(mul_temp_8(25) & mul_temp_8(25 DOWNTO 0) + ( "0" & (mul_temp_8(10) & NOT mul_temp_8(10) & NOT mul_temp_8(10) & NOT mul_temp_8(10) & NOT mul_temp_8(10) & NOT mul_temp_8(10) & NOT mul_temp_8(10) & NOT mul_temp_8(10) & NOT mul_temp_8(10) & NOT mul_temp_8(10))), 10), 20);

  mul_temp_9 <= delay_pipeline(21) * coeff22;
  product22 <= resize(shift_right(mul_temp_9(25) & mul_temp_9(25 DOWNTO 0) + ( "0" & (mul_temp_9(10) & NOT mul_temp_9(10) & NOT mul_temp_9(10) & NOT mul_temp_9(10) & NOT mul_temp_9(10) & NOT mul_temp_9(10) & NOT mul_temp_9(10) & NOT mul_temp_9(10) & NOT mul_temp_9(10) & NOT mul_temp_9(10))), 10), 20);

  mul_temp_10 <= delay_pipeline(20) * coeff21;
  product21 <= resize(shift_right(mul_temp_10(25) & mul_temp_10(25 DOWNTO 0) + ( "0" & (mul_temp_10(10) & NOT mul_temp_10(10) & NOT mul_temp_10(10) & NOT mul_temp_10(10) & NOT mul_temp_10(10) & NOT mul_temp_10(10) & NOT mul_temp_10(10) & NOT mul_temp_10(10) & NOT mul_temp_10(10) & NOT mul_temp_10(10))), 10), 20);

  mul_temp_11 <= delay_pipeline(19) * coeff20;
  product20 <= resize(shift_right(mul_temp_11(25) & mul_temp_11(25 DOWNTO 0) + ( "0" & (mul_temp_11(10) & NOT mul_temp_11(10) & NOT mul_temp_11(10) & NOT mul_temp_11(10) & NOT mul_temp_11(10) & NOT mul_temp_11(10) & NOT mul_temp_11(10) & NOT mul_temp_11(10) & NOT mul_temp_11(10) & NOT mul_temp_11(10))), 10), 20);

  mul_temp_12 <= delay_pipeline(18) * coeff19;
  product19 <= resize(shift_right(mul_temp_12(25) & mul_temp_12(25 DOWNTO 0) + ( "0" & (mul_temp_12(10) & NOT mul_temp_12(10) & NOT mul_temp_12(10) & NOT mul_temp_12(10) & NOT mul_temp_12(10) & NOT mul_temp_12(10) & NOT mul_temp_12(10) & NOT mul_temp_12(10) & NOT mul_temp_12(10) & NOT mul_temp_12(10))), 10), 20);

  mul_temp_13 <= delay_pipeline(17) * coeff18;
  product18 <= resize(shift_right(mul_temp_13(25) & mul_temp_13(25 DOWNTO 0) + ( "0" & (mul_temp_13(10) & NOT mul_temp_13(10) & NOT mul_temp_13(10) & NOT mul_temp_13(10) & NOT mul_temp_13(10) & NOT mul_temp_13(10) & NOT mul_temp_13(10) & NOT mul_temp_13(10) & NOT mul_temp_13(10) & NOT mul_temp_13(10))), 10), 20);

  mul_temp_14 <= delay_pipeline(16) * coeff17;
  product17 <= resize(shift_right(mul_temp_14(25) & mul_temp_14(25 DOWNTO 0) + ( "0" & (mul_temp_14(10) & NOT mul_temp_14(10) & NOT mul_temp_14(10) & NOT mul_temp_14(10) & NOT mul_temp_14(10) & NOT mul_temp_14(10) & NOT mul_temp_14(10) & NOT mul_temp_14(10) & NOT mul_temp_14(10) & NOT mul_temp_14(10))), 10), 20);

  mul_temp_15 <= delay_pipeline(15) * coeff16;
  product16 <= resize(shift_right(mul_temp_15(25) & mul_temp_15(25 DOWNTO 0) + ( "0" & (mul_temp_15(10) & NOT mul_temp_15(10) & NOT mul_temp_15(10) & NOT mul_temp_15(10) & NOT mul_temp_15(10) & NOT mul_temp_15(10) & NOT mul_temp_15(10) & NOT mul_temp_15(10) & NOT mul_temp_15(10) & NOT mul_temp_15(10))), 10), 20);

  mul_temp_16 <= delay_pipeline(14) * coeff15;
  product15 <= resize(shift_right(mul_temp_16(25) & mul_temp_16(25 DOWNTO 0) + ( "0" & (mul_temp_16(10) & NOT mul_temp_16(10) & NOT mul_temp_16(10) & NOT mul_temp_16(10) & NOT mul_temp_16(10) & NOT mul_temp_16(10) & NOT mul_temp_16(10) & NOT mul_temp_16(10) & NOT mul_temp_16(10) & NOT mul_temp_16(10))), 10), 20);

  mul_temp_17 <= delay_pipeline(13) * coeff14;
  product14 <= resize(shift_right(mul_temp_17(25) & mul_temp_17(25 DOWNTO 0) + ( "0" & (mul_temp_17(10) & NOT mul_temp_17(10) & NOT mul_temp_17(10) & NOT mul_temp_17(10) & NOT mul_temp_17(10) & NOT mul_temp_17(10) & NOT mul_temp_17(10) & NOT mul_temp_17(10) & NOT mul_temp_17(10) & NOT mul_temp_17(10))), 10), 20);

  mul_temp_18 <= delay_pipeline(12) * coeff13;
  product13 <= resize(shift_right(mul_temp_18(25) & mul_temp_18(25 DOWNTO 0) + ( "0" & (mul_temp_18(10) & NOT mul_temp_18(10) & NOT mul_temp_18(10) & NOT mul_temp_18(10) & NOT mul_temp_18(10) & NOT mul_temp_18(10) & NOT mul_temp_18(10) & NOT mul_temp_18(10) & NOT mul_temp_18(10) & NOT mul_temp_18(10))), 10), 20);

  mul_temp_19 <= delay_pipeline(11) * coeff12;
  product12 <= resize(shift_right(mul_temp_19(25) & mul_temp_19(25 DOWNTO 0) + ( "0" & (mul_temp_19(10) & NOT mul_temp_19(10) & NOT mul_temp_19(10) & NOT mul_temp_19(10) & NOT mul_temp_19(10) & NOT mul_temp_19(10) & NOT mul_temp_19(10) & NOT mul_temp_19(10) & NOT mul_temp_19(10) & NOT mul_temp_19(10))), 10), 20);

  mul_temp_20 <= delay_pipeline(10) * coeff11;
  product11 <= resize(shift_right(mul_temp_20(25) & mul_temp_20(25 DOWNTO 0) + ( "0" & (mul_temp_20(10) & NOT mul_temp_20(10) & NOT mul_temp_20(10) & NOT mul_temp_20(10) & NOT mul_temp_20(10) & NOT mul_temp_20(10) & NOT mul_temp_20(10) & NOT mul_temp_20(10) & NOT mul_temp_20(10) & NOT mul_temp_20(10))), 10), 20);

  mul_temp_21 <= delay_pipeline(9) * coeff10;
  product10 <= resize(shift_right(mul_temp_21(25) & mul_temp_21(25 DOWNTO 0) + ( "0" & (mul_temp_21(10) & NOT mul_temp_21(10) & NOT mul_temp_21(10) & NOT mul_temp_21(10) & NOT mul_temp_21(10) & NOT mul_temp_21(10) & NOT mul_temp_21(10) & NOT mul_temp_21(10) & NOT mul_temp_21(10) & NOT mul_temp_21(10))), 10), 20);

  mul_temp_22 <= delay_pipeline(8) * coeff9;
  product9 <= resize(shift_right(mul_temp_22(25) & mul_temp_22(25 DOWNTO 0) + ( "0" & (mul_temp_22(10) & NOT mul_temp_22(10) & NOT mul_temp_22(10) & NOT mul_temp_22(10) & NOT mul_temp_22(10) & NOT mul_temp_22(10) & NOT mul_temp_22(10) & NOT mul_temp_22(10) & NOT mul_temp_22(10) & NOT mul_temp_22(10))), 10), 20);

  mul_temp_23 <= delay_pipeline(7) * coeff8;
  product8 <= resize(shift_right(mul_temp_23(25) & mul_temp_23(25 DOWNTO 0) + ( "0" & (mul_temp_23(10) & NOT mul_temp_23(10) & NOT mul_temp_23(10) & NOT mul_temp_23(10) & NOT mul_temp_23(10) & NOT mul_temp_23(10) & NOT mul_temp_23(10) & NOT mul_temp_23(10) & NOT mul_temp_23(10) & NOT mul_temp_23(10))), 10), 20);

  mul_temp_24 <= delay_pipeline(6) * coeff7;
  product7 <= resize(shift_right(mul_temp_24(25) & mul_temp_24(25 DOWNTO 0) + ( "0" & (mul_temp_24(10) & NOT mul_temp_24(10) & NOT mul_temp_24(10) & NOT mul_temp_24(10) & NOT mul_temp_24(10) & NOT mul_temp_24(10) & NOT mul_temp_24(10) & NOT mul_temp_24(10) & NOT mul_temp_24(10) & NOT mul_temp_24(10))), 10), 20);

  mul_temp_25 <= delay_pipeline(5) * coeff6;
  product6 <= resize(shift_right(mul_temp_25(25) & mul_temp_25(25 DOWNTO 0) + ( "0" & (mul_temp_25(10) & NOT mul_temp_25(10) & NOT mul_temp_25(10) & NOT mul_temp_25(10) & NOT mul_temp_25(10) & NOT mul_temp_25(10) & NOT mul_temp_25(10) & NOT mul_temp_25(10) & NOT mul_temp_25(10) & NOT mul_temp_25(10))), 10), 20);

  mul_temp_26 <= delay_pipeline(4) * coeff5;
  product5 <= resize(shift_right(mul_temp_26(25) & mul_temp_26(25 DOWNTO 0) + ( "0" & (mul_temp_26(10) & NOT mul_temp_26(10) & NOT mul_temp_26(10) & NOT mul_temp_26(10) & NOT mul_temp_26(10) & NOT mul_temp_26(10) & NOT mul_temp_26(10) & NOT mul_temp_26(10) & NOT mul_temp_26(10) & NOT mul_temp_26(10))), 10), 20);

  mul_temp_27 <= delay_pipeline(3) * coeff4;
  product4 <= resize(shift_right(mul_temp_27(25) & mul_temp_27(25 DOWNTO 0) + ( "0" & (mul_temp_27(10) & NOT mul_temp_27(10) & NOT mul_temp_27(10) & NOT mul_temp_27(10) & NOT mul_temp_27(10) & NOT mul_temp_27(10) & NOT mul_temp_27(10) & NOT mul_temp_27(10) & NOT mul_temp_27(10) & NOT mul_temp_27(10))), 10), 20);

  mul_temp_28 <= delay_pipeline(2) * coeff3;
  product3 <= resize(shift_right(mul_temp_28(25) & mul_temp_28(25 DOWNTO 0) + ( "0" & (mul_temp_28(10) & NOT mul_temp_28(10) & NOT mul_temp_28(10) & NOT mul_temp_28(10) & NOT mul_temp_28(10) & NOT mul_temp_28(10) & NOT mul_temp_28(10) & NOT mul_temp_28(10) & NOT mul_temp_28(10) & NOT mul_temp_28(10))), 10), 20);

  mul_temp_29 <= delay_pipeline(1) * coeff2;
  product2 <= resize(shift_right(mul_temp_29(25) & mul_temp_29(25 DOWNTO 0) + ( "0" & (mul_temp_29(10) & NOT mul_temp_29(10) & NOT mul_temp_29(10) & NOT mul_temp_29(10) & NOT mul_temp_29(10) & NOT mul_temp_29(10) & NOT mul_temp_29(10) & NOT mul_temp_29(10) & NOT mul_temp_29(10) & NOT mul_temp_29(10))), 10), 20);

  product1_cast <= resize(product1, 28);

  mul_temp_30 <= delay_pipeline(0) * coeff1;
  product1 <= resize(shift_right(mul_temp_30(25) & mul_temp_30(25 DOWNTO 0) + ( "0" & (mul_temp_30(10) & NOT mul_temp_30(10) & NOT mul_temp_30(10) & NOT mul_temp_30(10) & NOT mul_temp_30(10) & NOT mul_temp_30(10) & NOT mul_temp_30(10) & NOT mul_temp_30(10) & NOT mul_temp_30(10) & NOT mul_temp_30(10))), 10), 20);

  add_temp <= resize(product1_cast, 29) + resize(product2, 29);
  sum1 <= add_temp(27 DOWNTO 0);

  add_temp_1 <= resize(sum1, 29) + resize(product3, 29);
  sum2 <= add_temp_1(27 DOWNTO 0);

  add_temp_2 <= resize(sum2, 29) + resize(product4, 29);
  sum3 <= add_temp_2(27 DOWNTO 0);

  add_temp_3 <= resize(sum3, 29) + resize(product5, 29);
  sum4 <= add_temp_3(27 DOWNTO 0);

  add_temp_4 <= resize(sum4, 29) + resize(product6, 29);
  sum5 <= add_temp_4(27 DOWNTO 0);

  add_temp_5 <= resize(sum5, 29) + resize(product7, 29);
  sum6 <= add_temp_5(27 DOWNTO 0);

  add_temp_6 <= resize(sum6, 29) + resize(product8, 29);
  sum7 <= add_temp_6(27 DOWNTO 0);

  add_temp_7 <= resize(sum7, 29) + resize(product9, 29);
  sum8 <= add_temp_7(27 DOWNTO 0);

  add_temp_8 <= resize(sum8, 29) + resize(product10, 29);
  sum9 <= add_temp_8(27 DOWNTO 0);

  add_temp_9 <= resize(sum9, 29) + resize(product11, 29);
  sum10 <= add_temp_9(27 DOWNTO 0);

  add_temp_10 <= resize(sum10, 29) + resize(product12, 29);
  sum11 <= add_temp_10(27 DOWNTO 0);

  add_temp_11 <= resize(sum11, 29) + resize(product13, 29);
  sum12 <= add_temp_11(27 DOWNTO 0);

  add_temp_12 <= resize(sum12, 29) + resize(product14, 29);
  sum13 <= add_temp_12(27 DOWNTO 0);

  add_temp_13 <= resize(sum13, 29) + resize(product15, 29);
  sum14 <= add_temp_13(27 DOWNTO 0);

  add_temp_14 <= resize(sum14, 29) + resize(product16, 29);
  sum15 <= add_temp_14(27 DOWNTO 0);

  add_temp_15 <= resize(sum15, 29) + resize(product17, 29);
  sum16 <= add_temp_15(27 DOWNTO 0);

  add_temp_16 <= resize(sum16, 29) + resize(product18, 29);
  sum17 <= add_temp_16(27 DOWNTO 0);

  add_temp_17 <= resize(sum17, 29) + resize(product19, 29);
  sum18 <= add_temp_17(27 DOWNTO 0);

  add_temp_18 <= resize(sum18, 29) + resize(product20, 29);
  sum19 <= add_temp_18(27 DOWNTO 0);

  add_temp_19 <= resize(sum19, 29) + resize(product21, 29);
  sum20 <= add_temp_19(27 DOWNTO 0);

  add_temp_20 <= resize(sum20, 29) + resize(product22, 29);
  sum21 <= add_temp_20(27 DOWNTO 0);

  add_temp_21 <= resize(sum21, 29) + resize(product23, 29);
  sum22 <= add_temp_21(27 DOWNTO 0);

  add_temp_22 <= resize(sum22, 29) + resize(product24, 29);
  sum23 <= add_temp_22(27 DOWNTO 0);

  add_temp_23 <= resize(sum23, 29) + resize(product25, 29);
  sum24 <= add_temp_23(27 DOWNTO 0);

  add_temp_24 <= resize(sum24, 29) + resize(product26, 29);
  sum25 <= add_temp_24(27 DOWNTO 0);

  add_temp_25 <= resize(sum25, 29) + resize(product27, 29);
  sum26 <= add_temp_25(27 DOWNTO 0);

  add_temp_26 <= resize(sum26, 29) + resize(product28, 29);
  sum27 <= add_temp_26(27 DOWNTO 0);

  add_temp_27 <= resize(sum27, 29) + resize(product29, 29);
  sum28 <= add_temp_27(27 DOWNTO 0);

  add_temp_28 <= resize(sum28, 29) + resize(product30, 29);
  sum29 <= add_temp_28(27 DOWNTO 0);

  add_temp_29 <= resize(sum29, 29) + resize(product31, 29);
  sum30 <= add_temp_29(27 DOWNTO 0);

  output_typeconvert <= resize(shift_right(sum30(17 DOWNTO 0) + ( "0" & (sum30(8) & NOT sum30(8) & NOT sum30(8) & NOT sum30(8) & NOT sum30(8) & NOT sum30(8) & NOT sum30(8) & NOT sum30(8))), 8), 10);

  Output_Register_process : PROCESS (clk, rst)
  BEGIN
    IF rst = '1' THEN
      output_register <= (OTHERS => '0');
    ELSIF rising_edge(clk) THEN
      IF en = '1' THEN
        output_register <= output_typeconvert;
      END IF;
    END IF; 
  END PROCESS Output_Register_process;

  -- Assignment Statements
  filter_out <= std_logic_vector(output_register);
END rtl;
