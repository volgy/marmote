library verilog;
use verilog.vl_types.all;
entity MSS_BFM_AHB2APB is
    generic(
        TPD             : real    := 0.100000;
        T0              : vl_logic_vector(2 downto 0) := (Hi0, Hi0, Hi0);
        T2              : vl_logic_vector(2 downto 0) := (Hi1, Hi0, Hi1);
        T345            : vl_logic_vector(2 downto 0) := (Hi1, Hi1, Hi0);
        TR0             : vl_logic_vector(2 downto 0) := (Hi1, Hi1, Hi1);
        WAIT1           : vl_logic_vector(2 downto 0) := (Hi0, Hi0, Hi1);
        WAIT2           : vl_logic_vector(2 downto 0) := (Hi0, Hi1, Hi0);
        WAIT3           : vl_logic_vector(2 downto 0) := (Hi0, Hi1, Hi1);
        WAIT4           : vl_logic_vector(2 downto 0) := (Hi1, Hi0, Hi0);
        idle            : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        waitone         : vl_logic_vector(1 downto 0) := (Hi0, Hi1);
        waittwo         : vl_logic_vector(1 downto 0) := (Hi1, Hi0);
        waitthree       : vl_logic_vector(1 downto 0) := (Hi1, Hi1)
    );
    port(
        HCLK            : in     vl_logic;
        HRESETN         : in     vl_logic;
        HSEL            : in     vl_logic;
        HWRITE          : in     vl_logic;
        HADDR           : in     vl_logic_vector(31 downto 0);
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
        PSEL            : out    vl_logic_vector(15 downto 0);
        PADDR           : out    vl_logic_vector(31 downto 0);
        PWRITE          : out    vl_logic;
        PENABLE         : out    vl_logic;
        PWDATA          : out    vl_logic_vector(31 downto 0);
        PRDATA          : in     vl_logic_vector(31 downto 0);
        PREADY          : in     vl_logic;
        PSLVERR         : in     vl_logic;
        PCLK_DIV        : in     vl_logic_vector(1 downto 0)
    );
    attribute T0_mti_vect_attrib : integer;
    attribute T0_mti_vect_attrib of T0 : constant is 0;
    attribute T2_mti_vect_attrib : integer;
    attribute T2_mti_vect_attrib of T2 : constant is 5;
    attribute T345_mti_vect_attrib : integer;
    attribute T345_mti_vect_attrib of T345 : constant is 6;
    attribute TR0_mti_vect_attrib : integer;
    attribute TR0_mti_vect_attrib of TR0 : constant is 7;
    attribute WAIT1_mti_vect_attrib : integer;
    attribute WAIT1_mti_vect_attrib of WAIT1 : constant is 1;
    attribute WAIT2_mti_vect_attrib : integer;
    attribute WAIT2_mti_vect_attrib of WAIT2 : constant is 2;
    attribute WAIT3_mti_vect_attrib : integer;
    attribute WAIT3_mti_vect_attrib of WAIT3 : constant is 3;
    attribute WAIT4_mti_vect_attrib : integer;
    attribute WAIT4_mti_vect_attrib of WAIT4 : constant is 4;
    attribute idle_mti_vect_attrib : integer;
    attribute idle_mti_vect_attrib of idle : constant is 0;
    attribute waitone_mti_vect_attrib : integer;
    attribute waitone_mti_vect_attrib of waitone : constant is 1;
    attribute waittwo_mti_vect_attrib : integer;
    attribute waittwo_mti_vect_attrib of waittwo : constant is 2;
    attribute waitthree_mti_vect_attrib : integer;
    attribute waitthree_mti_vect_attrib of waitthree : constant is 3;
end MSS_BFM_AHB2APB;
