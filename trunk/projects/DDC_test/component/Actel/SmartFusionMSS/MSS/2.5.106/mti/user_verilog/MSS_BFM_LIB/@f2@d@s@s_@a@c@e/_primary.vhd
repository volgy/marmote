library verilog;
use verilog.vl_types.all;
entity F2DSS_ACE is
    port(
        HCLK            : in     vl_logic;
        PCLK            : in     vl_logic;
        PRESETN         : in     vl_logic;
        PADDR           : in     vl_logic_vector(12 downto 0);
        PSEL            : in     vl_logic;
        PENABLE         : in     vl_logic;
        PWRITE          : in     vl_logic;
        PWDATA          : in     vl_logic_vector(31 downto 0);
        PRDATA          : out    vl_logic_vector(31 downto 0);
        PREADY          : out    vl_logic;
        PSLVERR         : out    vl_logic;
        INTERRUPT       : out    vl_logic_vector(85 downto 0);
        ADC0_TVC        : out    vl_logic_vector(7 downto 0);
        ADC1_TVC        : out    vl_logic_vector(7 downto 0);
        ADC2_TVC        : out    vl_logic_vector(7 downto 0);
        ADC0_STC        : out    vl_logic_vector(7 downto 0);
        ADC1_STC        : out    vl_logic_vector(7 downto 0);
        ADC2_STC        : out    vl_logic_vector(7 downto 0);
        ADC0_MODE       : out    vl_logic_vector(3 downto 0);
        ADC1_MODE       : out    vl_logic_vector(3 downto 0);
        ADC2_MODE       : out    vl_logic_vector(3 downto 0);
        ADC_VAREFSEL    : out    vl_logic;
        ABPOWERON       : out    vl_logic;
        ADC0_CHNUMBER   : out    vl_logic_vector(4 downto 0);
        ADC1_CHNUMBER   : out    vl_logic_vector(4 downto 0);
        ADC2_CHNUMBER   : out    vl_logic_vector(4 downto 0);
        ADC0_ADCSTART   : out    vl_logic;
        ADC1_ADCSTART   : out    vl_logic;
        ADC2_ADCSTART   : out    vl_logic;
        ADC0_PWRDWN     : out    vl_logic;
        ADC1_PWRDWN     : out    vl_logic;
        ADC2_PWRDWN     : out    vl_logic;
        ADC0_ADCRESET   : out    vl_logic;
        ADC1_ADCRESET   : out    vl_logic;
        ADC2_ADCRESET   : out    vl_logic;
        ADC0_BUSY       : in     vl_logic;
        ADC1_BUSY       : in     vl_logic;
        ADC2_BUSY       : in     vl_logic;
        ADC0_CALIBRATE  : in     vl_logic;
        ADC1_CALIBRATE  : in     vl_logic;
        ADC2_CALIBRATE  : in     vl_logic;
        ADC0_DATAVALID  : in     vl_logic;
        ADC1_DATAVALID  : in     vl_logic;
        ADC2_DATAVALID  : in     vl_logic;
        ADC0_SAMPLE     : in     vl_logic;
        ADC1_SAMPLE     : in     vl_logic;
        ADC2_SAMPLE     : in     vl_logic;
        ADC0_RESULT     : in     vl_logic_vector(11 downto 0);
        ADC1_RESULT     : in     vl_logic_vector(11 downto 0);
        ADC2_RESULT     : in     vl_logic_vector(11 downto 0);
        ACB_ADDR        : out    vl_logic_vector(7 downto 0);
        ACB_WRE         : out    vl_logic;
        ACB_WDATA       : out    vl_logic_vector(7 downto 0);
        ACB_RDATA       : in     vl_logic_vector(7 downto 0);
        ACB_RESETN      : out    vl_logic;
        COMPARATOR      : in     vl_logic_vector(11 downto 0);
        OBD_DOUT        : out    vl_logic_vector(2 downto 0);
        OBD_CLKOUT      : out    vl_logic_vector(2 downto 0);
        OBD_ENABLE      : out    vl_logic_vector(2 downto 0);
        FPGA_OBD_DOUT   : in     vl_logic_vector(2 downto 0);
        FPGA_OBD_CLKOUT : in     vl_logic_vector(2 downto 0);
        FPGA_TRIGGER    : in     vl_logic;
        FPGA_FLAGS      : out    vl_logic_vector(31 downto 0);
        ACE_INREADY     : out    vl_logic;
        ACE_OUTREADY    : out    vl_logic;
        TESTMODE        : in     vl_logic;
        RB_TEST         : in     vl_logic;
        PPE_CSBA        : in     vl_logic;
        PPE_CSBB        : in     vl_logic;
        PPE_RWBA        : in     vl_logic;
        PPE_RWBB        : in     vl_logic;
        PPE_ADA         : in     vl_logic_vector(8 downto 0);
        PPE_ADB         : in     vl_logic_vector(8 downto 0);
        PPE_WDA         : in     vl_logic_vector(31 downto 0);
        PPE_WDB         : in     vl_logic_vector(31 downto 0);
        PPE_RDA         : out    vl_logic_vector(31 downto 0);
        PPE_RDB         : out    vl_logic_vector(31 downto 0)
    );
end F2DSS_ACE;
