library verilog;
use verilog.vl_types.all;
entity DSSAB is
    generic(
        DAC_RESOLUTION  : integer := 0
    );
    port(
        DIGEN0          : in     vl_logic;
        DIGEN1          : in     vl_logic;
        DIGEN2          : in     vl_logic;
        DIGEN3          : in     vl_logic;
        DIGEN4          : in     vl_logic;
        DIGEN5          : in     vl_logic;
        DIGEN6          : in     vl_logic;
        DIGEN7          : in     vl_logic;
        DIGEN8          : in     vl_logic;
        DIGEN9          : in     vl_logic;
        DIGEN10         : in     vl_logic;
        DIGEN11         : in     vl_logic;
        DIGOUT0         : out    vl_logic;
        DIGOUT1         : out    vl_logic;
        DIGOUT2         : out    vl_logic;
        DIGOUT3         : out    vl_logic;
        DIGOUT4         : out    vl_logic;
        DIGOUT5         : out    vl_logic;
        DIGOUT6         : out    vl_logic;
        DIGOUT7         : out    vl_logic;
        DIGOUT8         : out    vl_logic;
        DIGOUT9         : out    vl_logic;
        DIGOUT10        : out    vl_logic;
        DIGOUT11        : out    vl_logic;
        ADCIN0          : in     vl_logic;
        ADCIN1          : in     vl_logic;
        ADCIN2          : in     vl_logic;
        ADCIN3          : in     vl_logic;
        ADCIN4          : in     vl_logic;
        ADCIN5          : in     vl_logic;
        ADCIN6          : in     vl_logic;
        ADCIN7          : in     vl_logic;
        ADCIN8          : in     vl_logic;
        ADCIN9          : in     vl_logic;
        ADCIN10         : in     vl_logic;
        ADCIN11         : in     vl_logic;
        DACOUT0         : out    vl_logic;
        DACOUT1         : out    vl_logic;
        DACOUT2         : out    vl_logic;
        AV1Q0           : in     vl_logic;
        AV1Q1           : in     vl_logic;
        AV1Q2           : in     vl_logic;
        AV1Q3           : in     vl_logic;
        AV1Q4           : in     vl_logic;
        AV1Q5           : in     vl_logic;
        AV2Q0           : in     vl_logic;
        AV2Q1           : in     vl_logic;
        AV2Q2           : in     vl_logic;
        AV2Q3           : in     vl_logic;
        AV2Q4           : in     vl_logic;
        AV2Q5           : in     vl_logic;
        ATQ0            : in     vl_logic;
        ATQ1            : in     vl_logic;
        ATQ2            : in     vl_logic;
        ATQ3            : in     vl_logic;
        ATQ4            : in     vl_logic;
        ATQ5            : in     vl_logic;
        ACQ0            : in     vl_logic;
        ACQ1            : in     vl_logic;
        ACQ2            : in     vl_logic;
        ACQ3            : in     vl_logic;
        ACQ4            : in     vl_logic;
        ACQ5            : in     vl_logic;
        ATRTN01         : in     vl_logic;
        ATRTN23         : in     vl_logic;
        ATRTN45         : in     vl_logic;
        VAREF0          : in     vl_logic;
        VAREF1          : in     vl_logic;
        VAREF2          : in     vl_logic;
        VAREFOUT        : out    vl_logic;
        GNDREF          : in     vl_logic;
        TVC0            : in     vl_logic_vector(7 downto 0);
        TVC1            : in     vl_logic_vector(7 downto 0);
        TVC2            : in     vl_logic_vector(7 downto 0);
        STC0            : in     vl_logic_vector(7 downto 0);
        STC1            : in     vl_logic_vector(7 downto 0);
        STC2            : in     vl_logic_vector(7 downto 0);
        MODE0           : in     vl_logic_vector(3 downto 0);
        MODE1           : in     vl_logic_vector(3 downto 0);
        MODE2           : in     vl_logic_vector(3 downto 0);
        VAREFSEL        : in     vl_logic;
        START0          : in     vl_logic;
        START1          : in     vl_logic;
        START2          : in     vl_logic;
        PWRDWN0         : in     vl_logic;
        PWRDWN1         : in     vl_logic;
        PWRDWN2         : in     vl_logic;
        ADCRESET0       : in     vl_logic;
        ADCRESET1       : in     vl_logic;
        ADCRESET2       : in     vl_logic;
        CHNUMBER0       : in     vl_logic_vector(4 downto 0);
        CHNUMBER1       : in     vl_logic_vector(4 downto 0);
        CHNUMBER2       : in     vl_logic_vector(4 downto 0);
        BUSY0           : out    vl_logic;
        BUSY1           : out    vl_logic;
        BUSY2           : out    vl_logic;
        CALIBRATE0      : out    vl_logic;
        CALIBRATE1      : out    vl_logic;
        CALIBRATE2      : out    vl_logic;
        DATAVALID0      : out    vl_logic;
        DATAVALID1      : out    vl_logic;
        DATAVALID2      : out    vl_logic;
        SAMPLE0         : out    vl_logic;
        SAMPLE1         : out    vl_logic;
        SAMPLE2         : out    vl_logic;
        RESULT0         : out    vl_logic_vector(11 downto 0);
        RESULT1         : out    vl_logic_vector(11 downto 0);
        RESULT2         : out    vl_logic_vector(11 downto 0);
        ADCCLK0         : in     vl_logic;
        ADCCLK1         : in     vl_logic;
        ADCCLK2         : in     vl_logic;
        OBDIN0          : in     vl_logic;
        OBDIN1          : in     vl_logic;
        OBDIN2          : in     vl_logic;
        OBDCLK0         : in     vl_logic;
        OBDCLK1         : in     vl_logic;
        OBDCLK2         : in     vl_logic;
        OBDEN0          : in     vl_logic;
        OBDEN1          : in     vl_logic;
        OBDEN2          : in     vl_logic;
        ACMPOUT0        : out    vl_logic;
        ACMPOUT1        : out    vl_logic;
        ACMPOUT2        : out    vl_logic;
        ACMPOUT3        : out    vl_logic;
        ACMPOUT4        : out    vl_logic;
        ACMPOUT5        : out    vl_logic;
        ACMPOUT6        : out    vl_logic;
        ACMPOUT7        : out    vl_logic;
        ACMPOUT8        : out    vl_logic;
        ACMPOUT9        : out    vl_logic;
        ACMPOUT10       : out    vl_logic;
        ACMPOUT11       : out    vl_logic;
        ABPWRON         : in     vl_logic;
        ACBRESET        : in     vl_logic;
        ACBADDR         : in     vl_logic_vector(7 downto 0);
        ACBWRE          : in     vl_logic;
        ACBWDATA        : in     vl_logic_vector(7 downto 0);
        ACBRDATA        : out    vl_logic_vector(7 downto 0)
    );
end DSSAB;
