-- APB_IF.VHD
------------------------------------------------------------------------------
-- MODULE: Marmote Main Board
-- AUTHORS: Sandor Szilvasi
-- AUTHOR CONTACT INFO.: Sandor Szilvasi <sandor.szilvasi@vanderbilt.edu>
-- TOOL VERSIONS: Libero 10.0
-- TARGET DEVICE: A2F500M3G (256 FBGA)
--   
-- Copyright (c) 2006-2012, Vanderbilt University
-- All rights reserved.
--
-- Permission to use, copy, modify, and distribute this software and its
-- documentation for any purpose, without fee, and without written agreement is
-- hereby granted, provided that the above copyright notice, the following
-- two paragraphs and the author appear in all copies of this software.
--
-- IN NO EVENT SHALL THE VANDERBILT UNIVERSITY BE LIABLE TO ANY PARTY FOR
-- DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
-- OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE VANDERBILT
-- UNIVERSITY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--
-- THE VANDERBILT UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,
-- INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
-- AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
-- ON AN "AS IS" BASIS, AND THE VANDERBILT UNIVERSITY HAS NO OBLIGATION TO
-- PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
------------------------------------------------------------------------------


------------------------------------------------------------------------------
-- Description: This is an interface module for the MAX19706 analog front-end
--              (AFE) data signals.
--
-- Design considerations:
--    -Block uses software radio-specific signal names (e.g. I/Q suffices)
--    -No APB inteface included
--    -Parallel data interface complying with datasheet timing requirements
--     (TBD: constarints on input clock)
--    -Single clock domain operation
--       -CLK_pin is simply connected to CLK
--       -Data is transmitted/received on every clock cycle
--          -TX holds last value if not updated
--          -RX reads data continuously when enabled and in RX mode
--    -Enable input puts the MAX19706 either in RX or SHDN mode (TBD)
--    -DDR primitives are instantiated to interface the AFE
--
------------------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

library smartfusion;
use smartfusion.all;

entity AFE_IF is
	port (
         -- Internal interface
         CLK        : in  std_logic;
         RST        : in  std_logic;

         SHDN       : in  std_logic;
         TX_RX_n    : in  std_logic; -- Tx/Rxn mode select
    
         RX_STROBE  : out std_logic;
	     RX_I       : out std_logic_vector(9 downto 0);
	     RX_Q       : out std_logic_vector(9 downto 0);
         TX_STROBE  : in  std_logic;
	     TX_I       : in  std_logic_vector(9 downto 0);
	     TX_Q       : in  std_logic_vector(9 downto 0);

		 -- MAX19706 interface
         CLK_pin    : out std_logic; -- output clock
         SHDN_n_pin : out std_logic; -- shutdown
         T_R_n_pin  : out std_logic; -- T/Rn (transmit/receive) mode select
         DATA_pin   : inout std_logic_vector(9 downto 0)
		 );
end entity;

architecture Behavioral of AFE_IF is

    -- Components
    component BIBUF_LVCMOS33
        port( PAD : inout   std_logic;
              D   : in    std_logic := 'U';
              E   : in    std_logic := 'U';
              Y   : out   std_logic
          );
    end component;

    component DDR_OUT
        port( DR  : in    std_logic := 'U';
              DF  : in    std_logic := 'U';
              CLK : in    std_logic := 'U';
              CLR : in    std_logic := 'U';
              Q   : out   std_logic
          );
    end component;

    component DDR_REG
        port( D   : in    std_logic := 'U';
              CLK : in    std_logic := 'U';
              CLR : in    std_logic := 'U';
              QR  : out   std_logic;
              QF  : out   std_logic
          );
    end component;

    component INV
        port( A : in    std_logic := 'U';
              Y : out   std_logic
          );
    end component;
    
	-- Constants

    constant c_ENABLE_DELAY : integer := 5;
    constant c_AFE_ZERO     : std_logic_vector(9 downto 0) := "1000000000";

	-- Signals

    signal s_enable_d   : std_logic_vector(c_ENABLE_DELAY-1 downto 0);
    signal s_obuf   : std_logic_vector(9 downto 0); -- Bi-directional buffer output
    signal s_ibuf   : std_logic_vector(9 downto 0); -- Bi-directional buffer input
    signal s_oe     : std_logic;                    -- Bi-directional buffer enable

    signal s_tx_rx_n : std_logic;
    signal s_tx_i   : std_logic_vector(9 downto 0);
    signal s_tx_q   : std_logic_vector(9 downto 0);
    signal s_rx_strobe : std_logic;
    signal s_rx_i   : std_logic_vector(9 downto 0);
    signal s_rx_q   : std_logic_vector(9 downto 0);

begin

    g_DDR_INTERFACE : for i in 0 to 9 generate

        u_BIBUF_LVCMOS33 : BIBUF_LVCMOS33
        port map (
            PAD => DATA_pin(i),
            D   => s_obuf(i),
            E   => s_oe,
            Y   => s_ibuf(i)
        );

        u_DDR_OUT : DDR_OUT
        port map (
            CLK => CLK,
            CLR => RST,
            DR  => s_tx_i(i), -- Swap DR and DF if the clock can be delayed by at least 11 ns
            DF  => s_tx_q(i),
            Q   => s_obuf(i)
        );

        u_DDR_REG : DDR_REG
        port map (
            CLK => CLK,
            CLR => RST,
            D   => s_ibuf(i),
            QF  => s_rx_i(i),
            QR  => s_rx_q(i)
        );
            
    end generate g_DDR_INTERFACE;

    p_reg_update : process (rst, clk)
    begin
        if rst = '1' then
            s_tx_rx_n   <= '1'; -- Make it TX so to avoid driving from both sides
            s_rx_strobe <= '0';
            s_tx_i      <= c_AFE_ZERO;
            s_tx_q      <= c_AFE_ZERO;
            s_oe        <= '0';
        elsif rising_edge(clk) then
            if SHDN = '1' then
                s_tx_rx_n   <= '1'; -- Make it TX so to avoid driving from both sides
                s_rx_strobe <= '0';
                s_tx_i      <= c_AFE_ZERO;
                s_tx_q      <= c_AFE_ZERO;
                s_oe        <= '0';
            else
                s_oe        <= TX_RX_n;
                s_tx_rx_n   <= TX_RX_n;
                s_rx_strobe <= s_enable_d(c_ENABLE_DELAY-1) and not s_tx_rx_n;
                if TX_STROBE = '1' then
                    s_tx_i      <= TX_I;
                    s_tx_q      <= TX_Q;
                end if;
            end if;
        end if;
    end process p_reg_update;

    -- p_ready_gen process
    --
    -- Generates a ready signal based on when the AFE was released from
    -- shutdown.
    -- TODO: check if this delay is really necessary
    p_ready_gen : process (rst, clk)
    begin
        if rst = '1' then
            s_enable_d <= (others => '0');
        elsif rising_edge(clk) then
            if SHDN = '1' then
                s_enable_d <= (others => '0');
            else
                s_enable_d(c_ENABLE_DELAY-1 downto 0) <=
                s_enable_d(c_ENABLE_DELAY-2 downto 0) & '1';
            end if;
        end if;
    end process p_ready_gen;

    CLK_pin     <= CLK;
    T_R_n_pin   <= s_tx_rx_n;
    SHDN_n_pin  <= not SHDN;

    RX_STROBE   <= s_rx_strobe;
    RX_I        <= s_rx_i;
    RX_Q        <= s_rx_q;


end Behavioral;

