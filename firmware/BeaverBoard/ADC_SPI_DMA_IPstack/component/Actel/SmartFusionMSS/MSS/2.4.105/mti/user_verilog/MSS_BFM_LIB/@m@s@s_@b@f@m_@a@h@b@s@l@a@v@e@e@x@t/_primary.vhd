library verilog;
use verilog.vl_types.all;
entity MSS_BFM_AHBSLAVEEXT is
    generic(
        AWIDTH          : integer := 10;
        DEPTH           : integer := 256;
        EXT_SIZE        : integer := 2;
        INITFILE        : string  := " ";
        ID              : integer := 0;
        ENFUNC          : integer := 0;
        ENFIFO          : integer := 0;
        TPD             : integer := 1;
        DEBUG           : integer := 1;
        NAME            : string  := ""
    );
    port(
        HCLK            : in     vl_logic;
        HRESETN         : in     vl_logic;
        HSEL            : in     vl_logic;
        HWRITE          : in     vl_logic;
        HADDR           : in     vl_logic_vector;
        HWDATA          : in     vl_logic_vector(31 downto 0);
        HRDATA          : out    vl_logic_vector(31 downto 0);
        HREADYIN        : in     vl_logic;
        HREADYOUT       : out    vl_logic;
        HTRANS          : in     vl_logic_vector(1 downto 0);
        HSIZE           : in     vl_logic_vector(2 downto 0);
        HBURST          : in     vl_logic_vector(2 downto 0);
        HMASTLOCK       : in     vl_logic;
        HPROT           : in     vl_logic_vector(3 downto 0);
        HRESP           : out    vl_logic;
        EXT_EN          : in     vl_logic;
        EXT_WR          : in     vl_logic;
        EXT_RD          : in     vl_logic;
        EXT_ADDR        : in     vl_logic_vector;
        EXT_DATA        : inout  vl_logic_vector(31 downto 0);
        TXREADY         : out    vl_logic;
        RXREADY         : out    vl_logic
    );
end MSS_BFM_AHBSLAVEEXT;
