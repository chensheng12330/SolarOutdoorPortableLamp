;AI8051U.INC

$SAVE
$NOLIST

/////////////////////////////////////////////////

P0          DATA        080H
P00         BIT         P0.0
P01         BIT         P0.1
P02         BIT         P0.2
P03         BIT         P0.3
P04         BIT         P0.4
P05         BIT         P0.5
P06         BIT         P0.6
P07         BIT         P0.7

SP          DATA        081H
DPL         DATA        082H
DPH         DATA        083H
DPXL        DATA        084H
SPH         DATA        085H

PCON        DATA        087H
SMOD        EQU         80H
SMOD0       EQU         40H
LVDF        EQU         20H
POF         EQU         10H
GF1         EQU         08H
GF0         EQU         04H
PD          EQU         02H
IDL         EQU         01H

TCON        DATA        088H
TF1         BIT         TCON.7
TR1         BIT         TCON.6
TF0         BIT         TCON.5
TR0         BIT         TCON.4
IE1         BIT         TCON.3
IT1         BIT         TCON.2
IE0         BIT         TCON.1
IT0         BIT         TCON.0

TMOD        DATA        089H
T1_GATE     EQU         80H
T1_CT       EQU         40H
T1_M1       EQU         20H
T1_M0       EQU         10H
T0_GATE     EQU         08H
T0_CT       EQU         04H
T0_M1       EQU         02H
T0_M0       EQU         01H

TL0         DATA        08AH
TL1         DATA        08BH
TH0         DATA        08CH
TH1         DATA        08DH

AUXR        DATA        08EH
T012        EQU         80H
T1X12       EQU         40H
S1M06       EQU         20H
T2R         EQU         10H
T2_CT       EQU         08H
T2X12       EQU         04H
EXTRAM      EQU         02H
S1BRT       EQU         01H

INTCLKO     DATA        08FH
EX4         EQU         40H
EX3         EQU         20H
EX2         EQU         10H
T2CLKO      EQU         04H
T1CLKO      EQU         02H
T0CLKO      EQU         01H

P1          DATA        090H
P10         BIT         P1.0
P11         BIT         P1.1
P12         BIT         P1.2
P13         BIT         P1.3
P14         BIT         P1.4
P15         BIT         P1.5
P16         BIT         P1.6
P17         BIT         P1.7

P1M1        DATA        091H
P1M0        DATA        092H
P0M1        DATA        093H
P0M0        DATA        094H
P2M1        DATA        095H
P2M0        DATA        096H

AUXR2       DATA        097H
RAMTINY     EQU         80H
CPUMODE     EQU         40H
RAMEXE      EQU         20H
CANFD       EQU         10H
CANSEL      EQU         08H
CAN2EN      EQU         04H
CANEN       EQU         02H
LINEN       EQU         01H

SCON        DATA        098H
SM0         BIT         SCON.7
SM1         BIT         SCON.6
SM2         BIT         SCON.5
REN         BIT         SCON.4
TB8         BIT         SCON.3
RB8         BIT         SCON.2
TI          BIT         SCON.1
RI          BIT         SCON.0

SBUF        DATA        099H

S2CON       DATA        09AH
S2SM0       EQU         80H
S2SM1       EQU         40H
S2SM2       EQU         20H
S2REN       EQU         10H
S2TB8       EQU         08H
S2RB8       EQU         04H
S2TI        EQU         02H
S2RI        EQU         01H

S2BUF       DATA        09BH

IRCBAND     DATA        09DH
USBCKS      EQU         80H
USBCKS2     EQU         40H
HIRCSEL1    EQU         02H
HIRCSEL0    EQU         01H

LIRTRIM     DATA        09EH
IRTRIM      DATA        09FH

P2          DATA        0A0H
P20         BIT         P2.0
P21         BIT         P2.1
P22         BIT         P2.2
P23         BIT         P2.3
P24         BIT         P2.4
P25         BIT         P2.5
P26         BIT         P2.6
P27         BIT         P2.7

BUS_SPEED   DATA        0A1H

P_SW1       DATA        0A2H
S1_S1       RQU         80H
S1_S0       RQU         40H
CAN_S1      RQU         20H
CAN_S0      RQU         10H
SPI_S1      RQU         08H
SPI_S0      RQU         04H
LIN_S1      RQU         02H
LIN_S0      RQU         01H

VRTRIM      DATA        0A6H

IE          DATA        0A8H
EA          BIT         IE.7
ELVD        BIT         IE.6
EADC        BIT         IE.5
ES          BIT         IE.4
ET1         BIT         IE.3
EX1         BIT         IE.2
ET0         BIT         IE.1
EX0         BIT         IE.0

SADDR       DATA        0A9H
WKTCL       DATA        0AAH
WKTCH       DATA        0ABH
WKTEN       EQU         80H

S3CON       DATA        0ACH
S3SM0       EQU         80H
S3ST3       EQU         40H
S3SM2       EQU         20H
S3REN       EQU         10H
S3TB8       EQU         08H
S3RB8       EQU         04H
S3TI        EQU         02H
S3RI        EQU         01H

S3BUF       DATA        0ADH
TA          DATA        0AEH

IE2         DATA        0AFH
EUSB        EQU         80H
ET4         EQU         40H
ET3         EQU         20H
ES4         EQU         10H
ES3         EQU         08H
ET2         EQU         04H
ESPI        EQU         02H
ES2         EQU         01H

P3          DATA        0B0H
P30         BIT         P3.0
P31         BIT         P3.1
P32         BIT         P3.2
P33         BIT         P3.3
P34         BIT         P3.4
P35         BIT         P3.5
P36         BIT         P3.6
P37         BIT         P3.7

RD          BIT         P3.7
WR          BIT         P3.6
T1          BIT         P3.5
T0          BIT         P3.4
INT1        BIT         P3.3
INT0        BIT         P3.2
TXD         BIT         P3.1
RXD         BIT         P3.0

P3M1        DATA        0B1H
P3M0        DATA        0B2H
P4M1        DATA        0B3H
P4M0        DATA        0B4H

IP2         DATA        0B5H
PUSB        EQU         80H
PI2C        EQU         40H
PCMP        EQU         20H
PX4         EQU         10H
PPWMB       EQU         08H
PPWMA       EQU         04H
PSPI        EQU         02H
PS2         EQU         01H

IP2H        DATA        0B6H
PUSBH       EQU         80H
PI2CH       EQU         40H
PCMPH       EQU         20H
PX4H        EQU         10H
PPWMBH      EQU         08H
PPWMAH      EQU         04H
PSPIH       EQU         02H
PS2H        EQU         01H

IPH         DATA        0B7H
PPCAH       EQU         40H
PLVDH       EQU         40H
PADCH       EQU         20H
PSH         EQU         10H
PT1H        EQU         08H
PX1H        EQU         04H
PT0H        EQU         02H
PX0H        EQU         01H

IP          DATA        0B8H
PPCA        BIT         IP.7
PLVD        BIT         IP.6
PADC        BIT         IP.5
PS          BIT         IP.4
PT1         BIT         IP.3
PX1         BIT         IP.2
PT0         BIT         IP.1
PX0         BIT         IP.0

SADEN       DATA        0B9H

P_SW2       DATA        0BAH
EAXFR       EQU         80H
I2C_S1      EQU         20H
I2C_S0      EQU         10H
CMPO_S      EQU         08H
S4_S        EQU         04H
S3_S        EQU         02H
S2_S        EQU         01H

P_SW3       DATA        0BBH
I2S_S1      EQU         80H
I2S_S0      EQU         40H
S2SPI_S1    EQU         20H
S2SPI_S0    EQU         10H
S1SPI_S1    EQU         08H
S1SPI_S0    EQU         04H
CAN2_S1     EQU         02H
CAN2_S0     EQU         01H

ADC_CONTR   DATA        0BCH
ADC_POWER   EQU         80H
ADC_START   EQU         40H
ADC_FLAG    EQU         20H
ADC_EPWMT   EQU         10H

ADC_RES     DATA        0BDH
ADC_RESL    DATA        0BEH

P_SW4       DATA        0BFH
QSPI_S1     EQU         02H
QSPI_S0     EQU         01H

P4          DATA        0C0H
P40         BIT         P4.0
P41         BIT         P4.1
P42         BIT         P4.2
P43         BIT         P4.3
P44         BIT         P4.4
P45         BIT         P4.5
P46         BIT         P4.6
P47         BIT         P4.7

WDT_CONTR   DATA        0C1H
WDT_FLAG    EQU         80H
EN_WDT      EQU         20H
CLR_WDT     EQU         10H
IDL_WDT     EQU         08H

IAP_DATA    DATA        0C2H
IAP_ADDRH   DATA        0C3H
IAP_ADDRL   DATA        0C4H
IAP_CMD     DATA        0C5H
IAP_TRIG    DATA        0C6H

IAP_CONTR   DATA        0C7H
IAPEN       EQU         80H
SWBS        EQU         40H
SWRST       EQU         20H
CMD_FAIL    EQU         10H
SWBS2       EQU         08H

P5          DATA        0C8H
P50         BIT         P5.0
P51         BIT         P5.1
P52         BIT         P5.2
P53         BIT         P5.3
P54         BIT         P5.4
P55         BIT         P5.5
P56         BIT         P5.6
P57         BIT         P5.7

P5M1        DATA        0C9H
P5M0        DATA        0CAH
P6M1        DATA        0CBH
P6M0        DATA        0CCH

SPSTAT      DATA        0CDH
SPIF        EQU         80H
WCOL        EQU         40H

SPCTL       DATA        0CEH
SSIG        EQU         80H
SPEN        EQU         40H
DORD        EQU         20H
MSTR        EQU         10H
CPOL        EQU         08H
CPHA        EQU         04H
SPR1        EQU         02H
SPR0        EQU         01H

SPDAT       DATA        0CFH

PSW         DATA        0D0H
CY          BIT         PSW.7
AC          BIT         PSW.6
F0          BIT         PSW.5
RS1         BIT         PSW.4
RS0         BIT         PSW.3
OV          BIT         PSW.2
F1          BIT         PSW.1
P           BIT         PSW.0

PSW1        DATA        0D1H
N           EQU         20H
Z           EQU         02H

T4H         DATA        0D2H
T4L         DATA        0D3H
T3H         DATA        0D4H
T3L         DATA        0D5H
T2H         DATA        0D6H
T2L         DATA        0D7H

USBCLK      DATA        0DCH

T4T3M       DATA        0DDH
T4R         EQU         80H
T4_CT       EQU         40H
T4X12       EQU         20H
T4CLKO      EQU         10H
T3R         EQU         08H
T3_CT       EQU         04H
T3X12       EQU         02H
T3CLKO      EQU         01H

ADCCFG      DATA        0DEH
RESFMT      EQU         20H

IP3         DATA        0DFH
PI2S        EQU         08H
PRTC        EQU         04H
PS4         EQU         02H
PS3         EQU         01H

ACC         DATA        0E0H
P7M1        DATA        0E1H
P7M0        DATA        0E2H
DPS         DATA        0E3H

CMPCR1      DATA        0E6H
CMPEN       EQU         80H
CMPIF       EQU         40H
PIE         EQU         20H
NIE         EQU         10H
CMPOE       EQU         02H
CMPRES      EQU         01H

CMPCR2      DATA        0E7H
INVCMPO     EQU         80H
DISFLT      EQU         40H

P6          DATA        0E8H
P60         BIT         P6.0
P61         BIT         P6.1
P62         BIT         P6.2
P63         BIT         P6.3
P64         BIT         P6.4
P65         BIT         P6.5
P66         BIT         P6.6
P67         BIT         P6.7

WTST        DATA        0E9H
CKCON       DATA        0EAH
MXAX        DATA        0EBH
USBDAT      DATA        0ECH
DMAIR       DATA        0EDH

IP3H        DATA        0EEH
PI2SH       EQU         08H
PRTCH       EQU         04H
PS4H        EQU         02H
PS3H        EQU         01H

AUXINTIF    DATA        0EFH
INT4IF      EQU         40H
INT3IF      EQU         20H
INT2IF      EQU         10H
T4IF        EQU         04H
T3IF        EQU         02H
T2IF        EQU         01H

B           DATA        0F0H

USBCON      DATA        0F4H
ENUSB       EQU         80H
ENUSBRST    EQU         40H
PS2M        EQU         20H
PUEN        EQU         10H
PDEN        EQU         08H
DFREC       EQU         04H
DP          EQU         02H
DM          EQU         01H

IAP_TPS     DATA        0F5H
IAP_ADDRE   DATA        0F6H

P7          DATA        0F8H
P70         BIT         P7.0
P71         BIT         P7.1
P72         BIT         P7.2
P73         BIT         P7.3
P74         BIT         P7.4
P75         BIT         P7.5
P76         BIT         P7.6
P77         BIT         P7.7

USBADR      DATA        0FCH

S4CON       DATA        0FDH
S4SM0       EQU         80H
S4ST4       EQU         40H
S4SM2       EQU         20H
S4REN       EQU         10H
S4TB8       EQU         08H
S4RB8       EQU         04H
S4TI        EQU         02H
S4RI        EQU         01H

S4BUF       DATA        0FEH

RSTCFG      DATA        0FFH
ENLVR       EQU         40H
P47RST      EQU         10H

;
;如下特殊功能寄存器位于扩展RAM区域
;访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写
;

CLKSEL          EQU     0FE00H
CLKDIV          EQU     0FE01H
HIRCCR          EQU     0FE02H
XOSCCR          EQU     0FE03H
IRC32KCR        EQU     0FE04H
MCLKOCR         EQU     0FE05H
IRCDB           EQU     0FE06H
IRC48MCR        EQU     0FE07H
X32KCR          EQU     0FE08H
HSCLKDIV        EQU     0FE0BH

P0PU            EQU     0FE10H
P1PU            EQU     0FE11H
P2PU            EQU     0FE12H
P3PU            EQU     0FE13H
P4PU            EQU     0FE14H
P5PU            EQU     0FE15H
P6PU            EQU     0FE16H
P7PU            EQU     0FE17H
P0NCS           EQU     0FE18H
P1NCS           EQU     0FE19H
P2NCS           EQU     0FE1AH
P3NCS           EQU     0FE1BH
P4NCS           EQU     0FE1CH
P5NCS           EQU     0FE1DH
P6NCS           EQU     0FE1EH
P7NCS           EQU     0FE1FH
P0SR            EQU     0FE20H
P1SR            EQU     0FE21H
P2SR            EQU     0FE22H
P3SR            EQU     0FE23H
P4SR            EQU     0FE24H
P5SR            EQU     0FE25H
P6SR            EQU     0FE26H
P7SR            EQU     0FE27H
P0DR            EQU     0FE28H
P1DR            EQU     0FE29H
P2DR            EQU     0FE2AH
P3DR            EQU     0FE2BH
P4DR            EQU     0FE2CH
P5DR            EQU     0FE2DH
P6DR            EQU     0FE2EH
P7DR            EQU     0FE2FH
P0IE            EQU     0FE30H
P1IE            EQU     0FE31H
P2IE            EQU     0FE32H
P3IE            EQU     0FE33H
P4IE            EQU     0FE34H
P5IE            EQU     0FE35H
P6IE            EQU     0FE36H
P7IE            EQU     0FE37H
P0PD            EQU     0FE40H
P1PD            EQU     0FE41H
P2PD            EQU     0FE42H
P3PD            EQU     0FE43H
P4PD            EQU     0FE44H
P5PD            EQU     0FE45H
P6PD            EQU     0FE46H
P7PD            EQU     0FE47H
P0BP            EQU		0FE48H
P1BP            EQU		0FE49H
P2BP            EQU		0FE4AH
P3BP            EQU		0FE4BH
P4BP            EQU		0FE4CH
P5BP            EQU		0FE4DH
P6BP            EQU		0FE4EH
P7BP            EQU		0FE4FH

LCMIFCFG        EQU     0FE50H
LCMIFCFG2       EQU     0FE51H
LCMIFCR         EQU     0FE52H
LCMIFSTA        EQU     0FE53H
LCMIFDATL       EQU     0FE54H
LCMIFDATH       EQU     0FE55H
LCMIFPSCR       EQU     0FE56H

RTCCR           EQU     0FE60H
RTCCFG          EQU     0FE61H
RTCIEN          EQU     0FE62H
RTCIF           EQU     0FE63H
ALAHOUR         EQU     0FE64H
ALAMIN          EQU     0FE65H
ALASEC          EQU     0FE66H
ALASSEC         EQU     0FE67H
INIYEAR         EQU     0FE68H
INIMONTH        EQU     0FE69H
INIDAY          EQU     0FE6AH
INIHOUR         EQU     0FE6BH
INIMIN          EQU     0FE6CH
INISEC          EQU     0FE6DH
INISSEC         EQU     0FE6EH
INIWEEK         EQU     0FE6FH
WEEK            EQU     0FE6FH
YEAR            EQU     0FE70H
MONTH           EQU     0FE71H
DAY             EQU     0FE72H
HOUR            EQU     0FE73H
MIN             EQU     0FE74H
SEC             EQU     0FE75H
SSEC            EQU     0FE76H

T11CR           EQU     0FE78H
T11PS           EQU     0FE79H
T11H            EQU     0FE7AH
T11L            EQU     0FE7BH

I2CCFG          EQU     0FE80H
I2CMSCR         EQU     0FE81H
I2CMSST         EQU     0FE82H
I2CSLCR         EQU     0FE83H
I2CSLST         EQU     0FE84H
I2CSLADR        EQU     0FE85H
I2CTXD          EQU     0FE86H
I2CRXD          EQU     0FE87H
I2CMSAUX        EQU     0FE88H
I2CPSCR         EQU     0FE89H

SPI_CLKDIV      EQU     0FE90H
PWMA_CLKDIV     EQU     0FE91H
PWMB_CLKDIV     EQU     0FE92H
TFPU_CLKDIV     EQU     0FE93H
I2S_CLKDIV      EQU     0FE94H

RSTFLAG         EQU     0FE99H
RSTCR0          EQU     0FE9AH
RSTCR1          EQU     0FE9BH
RSTCR2          EQU     0FE9CH
RSTCR3          EQU     0FE9DH
RSTCR4          EQU     0FE9EH
RSTCR5          EQU     0FE9FH

TM0PS           EQU     0FEA0H
TM1PS           EQU     0FEA1H
TM2PS           EQU     0FEA2H
TM3PS           EQU     0FEA3H
TM4PS           EQU     0FEA4H
ADCTIM          EQU     0FEA8H
ADCEXCFG        EQU     0FEADH
CMPEXCFG        EQU     0FEAEH

PWMA_ETRPS      EQU     0FEB0H
PWMA_ENO        EQU     0FEB1H
PWMA_PS         EQU     0FEB2H
PWMA_IOAUX      EQU     0FEB3H
PWMB_ETRPS      EQU     0FEB4H
PWMB_ENO        EQU     0FEB5H
PWMB_PS         EQU     0FEB6H
PWMB_IOAUX      EQU     0FEB7H
PWMA_PS2        EQU     0FEB8H
PWMA_RCRH       EQU     0FEB9H
PWMB_RCRH       EQU     0FEBAH

PWMA_CR1        EQU     0FEC0H
PWMA_CR2        EQU     0FEC1H
PWMA_SMCR       EQU     0FEC2H
PWMA_ETR        EQU     0FEC3H
PWMA_IER        EQU     0FEC4H
PWMA_SR1        EQU     0FEC5H
PWMA_SR2        EQU     0FEC6H
PWMA_EGR        EQU     0FEC7H
PWMA_CCMR1      EQU     0FEC8H
PWMA_CCMR2      EQU     0FEC9H
PWMA_CCMR3      EQU     0FECAH
PWMA_CCMR4      EQU     0FECBH
PWMA_CCER1      EQU     0FECCH
PWMA_CCER2      EQU     0FECDH
PWMA_CNTRH      EQU     0FECEH
PWMA_CNTRL      EQU     0FECFH
PWMA_PSCRH      EQU     0FED0H
PWMA_PSCRL      EQU     0FED1H
PWMA_ARRH       EQU     0FED2H
PWMA_ARRL       EQU     0FED3H
PWMA_RCR        EQU     0FED4H
PWMA_CCR1H      EQU     0FED5H
PWMA_CCR1L      EQU     0FED6H
PWMA_CCR2H      EQU     0FED7H
PWMA_CCR2L      EQU     0FED8H
PWMA_CCR3H      EQU     0FED9H
PWMA_CCR3L      EQU     0FEDAH
PWMA_CCR4H      EQU     0FEDBH
PWMA_CCR4L      EQU     0FEDCH
PWMA_BKR        EQU     0FEDDH
PWMA_DTR        EQU     0FEDEH
PWMA_OISR       EQU     0FEDFH

PWMB_CR1        EQU     0FEE0H
PWMB_CR2        EQU     0FEE1H
PWMB_SMCR       EQU     0FEE2H
PWMB_ETR        EQU     0FEE3H
PWMB_IER        EQU     0FEE4H
PWMB_SR1        EQU     0FEE5H
PWMB_SR2        EQU     0FEE6H
PWMB_EGR        EQU     0FEE7H
PWMB_CCMR1      EQU     0FEE8H
PWMB_CCMR2      EQU     0FEE9H
PWMB_CCMR3      EQU     0FEEAH
PWMB_CCMR4      EQU     0FEEBH
PWMB_CCER1      EQU     0FEECH
PWMB_CCER2      EQU     0FEEDH
PWMB_CNTRH      EQU     0FEEEH
PWMB_CNTRL      EQU     0FEEFH
PWMB_PSCRH      EQU     0FEF0H
PWMB_PSCRL      EQU     0FEF1H
PWMB_ARRH       EQU     0FEF2H
PWMB_ARRL       EQU     0FEF3H
PWMB_RCR        EQU     0FEF4H
PWMB_CCR5H      EQU     0FEF5H
PWMB_CCR5L      EQU     0FEF6H
PWMB_CCR6H      EQU     0FEF7H
PWMB_CCR6L      EQU     0FEF8H
PWMB_CCR7H      EQU     0FEF9H
PWMB_CCR7L      EQU     0FEFAH
PWMB_CCR8H      EQU     0FEFBH
PWMB_CCR8L      EQU     0FEFCH
PWMB_BKR        EQU     0FEFDH
PWMB_DTR        EQU     0FEFEH
PWMB_OISR       EQU     0FEFFH

P0INTE          EQU     0FD00H
P1INTE          EQU     0FD01H
P2INTE          EQU     0FD02H
P3INTE          EQU     0FD03H
P4INTE          EQU     0FD04H
P5INTE          EQU     0FD05H
P6INTE          EQU     0FD06H
P7INTE          EQU     0FD07H
P0INTF          EQU     0FD10H
P1INTF          EQU     0FD11H
P2INTF          EQU     0FD12H
P3INTF          EQU     0FD13H
P4INTF          EQU     0FD14H
P5INTF          EQU     0FD15H
P6INTF          EQU     0FD16H
P7INTF          EQU     0FD17H
P0IM0           EQU     0FD20H
P1IM0           EQU     0FD21H
P2IM0           EQU     0FD22H
P3IM0           EQU     0FD23H
P4IM0           EQU     0FD24H
P5IM0           EQU     0FD25H
P6IM0           EQU     0FD26H
P7IM0           EQU     0FD27H
P0IM1           EQU     0FD30H
P1IM1           EQU     0FD31H
P2IM1           EQU     0FD32H
P3IM1           EQU     0FD33H
P4IM1           EQU     0FD34H
P5IM1           EQU     0FD35H
P6IM1           EQU     0FD36H
P7IM1           EQU     0FD37H
P0WKUE          EQU     0FD40H
P1WKUE          EQU     0FD41H
P2WKUE          EQU     0FD42H
P3WKUE          EQU     0FD43H
P4WKUE          EQU     0FD44H
P5WKUE          EQU     0FD45H
P6WKUE          EQU     0FD46H
P7WKUE          EQU     0FD47H

CCAPM2          EQU     0FD50H
CCAP2L          EQU     0FD51H
CCAP2H          EQU     0FD52H
PCA_PWM2        EQU     0FD53H
CCAPM3          EQU     0FD54H
CCAP3L          EQU     0FD55H
CCAP3H          EQU     0FD56H
PCA_PWM3        EQU     0FD57H
CCAPM0          EQU     0FD58H
CCAP0L          EQU     0FD59H
CCAP0H          EQU     0FD5AH
PCA_PWM0        EQU     0FD5BH
CCAPM1          EQU     0FD5CH
CCAP1L          EQU     0FD5DH
CCAP1H          EQU     0FD5EH
PCA_PWM1        EQU     0FD5FH

PINIPL          EQU     0FD60H
PINIPH          EQU     0FD61H

CCON            EQU     0FD64H
CF              EQU     80H
CR              EQU     40H
CCF2            EQU     04H
CCF1            EQU     02H
CCF0            EQU     01H

CL              EQU     0FD65H
CH              EQU     0FD66H

CMOD            EQU     0FD67H
CIDL            EQU     80H
ECF             EQU     01H

UR1TOCR         EQU     0FD70H
UR1TOSR         EQU     0FD71H
UR1TOTH         EQU     0FD72H
UR1TOTL         EQU     0FD73H
UR2TOCR         EQU     0FD74H
UR2TOSR         EQU     0FD75H
UR2TOTH         EQU     0FD76H
UR2TOTL         EQU     0FD77H
UR3TOCR         EQU     0FD78H
UR3TOSR         EQU     0FD79H
UR3TOTH         EQU     0FD7AH
UR3TOTL         EQU     0FD7BH
UR4TOCR         EQU     0FD7CH
UR4TOSR         EQU     0FD7DH
UR4TOTH         EQU     0FD7EH
UR4TOTL         EQU     0FD7FH
SPITOCR         EQU     0FD80H
SPITOSR         EQU     0FD81H
SPITOTH         EQU     0FD82H
SPITOTL         EQU     0FD83H
I2CTOCR         EQU     0FD84H
I2CTOSR         EQU     0FD85H
I2CTOTH         EQU     0FD86H
I2CTOTL         EQU     0FD87H

UR1TOTE         EQU     0FD88H
UR2TOTE         EQU     0FD89H
UR3TOTE         EQU     0FD8AH
UR4TOTE         EQU     0FD8BH
SPITOTE         EQU     0FD8CH
I2CTOTE         EQU     0FD8DH

I2SCR           EQU     0FD98H
I2SSR           EQU     0FD99H
I2SDRH          EQU     0FD9AH
I2SDRL          EQU     0FD9BH
I2SPRH          EQU     0FD9CH
I2SPRL          EQU     0FD9DH
I2SCFGH         EQU     0FD9EH
I2SCFGL         EQU     0FD9FH
I2SMD           EQU     0FDA0H
I2SMCKDIV       EQU     0FDA1H

CRECR           EQU     0FDA8H
CRECNTH         EQU     0FDA9H
CRECNTL         EQU     0FDAAH
CRERES          EQU     0FDABH

S2CFG           EQU     0FDB4H
S2ADDR          EQU     0FDB5H
S2ADEN          EQU     0FDB6H
USARTCR1        EQU     0FDC0H
USARTCR2        EQU     0FDC1H
USARTCR3        EQU     0FDC2H
USARTCR4        EQU     0FDC3H
USARTCR5        EQU     0FDC4H
USARTGTR        EQU     0FDC5H
USARTBRH        EQU     0FDC6H
USARTBRL        EQU     0FDC7H
USART2CR1       EQU     0FDC8H
USART2CR2       EQU     0FDC9H
USART2CR3       EQU     0FDCAH
USART2CR4       EQU     0FDCBH
USART2CR5       EQU     0FDCCH
USART2GTR       EQU     0FDCDH
USART2BRH       EQU     0FDCEH
USART2BRL       EQU     0FDCFH

CHIPID          EQU     0FDE0H

CHIPID0         EQU     0FDE0H
CHIPID1         EQU     0FDE1H
CHIPID2         EQU     0FDE2H
CHIPID3         EQU     0FDE3H
CHIPID4         EQU     0FDE4H
CHIPID5         EQU     0FDE5H
CHIPID6         EQU     0FDE6H
CHIPID7         EQU     0FDE7H
CHIPID8         EQU     0FDE8H
CHIPID9         EQU     0FDE9H
CHIPID10        EQU     0FDEAH
CHIPID11        EQU     0FDEBH
CHIPID12        EQU     0FDECH
CHIPID13        EQU     0FDEDH
CHIPID14        EQU     0FDEEH
CHIPID15        EQU     0FDEFH
CHIPID16        EQU     0FDF0H
CHIPID17        EQU     0FDF1H
CHIPID18        EQU     0FDF2H
CHIPID19        EQU     0FDF3H
CHIPID20        EQU     0FDF4H
CHIPID21        EQU     0FDF5H
CHIPID22        EQU     0FDF6H
CHIPID23        EQU     0FDF7H
CHIPID24        EQU     0FDF8H
CHIPID25        EQU     0FDF9H
CHIPID26        EQU     0FDFAH
CHIPID27        EQU     0FDFBH
CHIPID28        EQU     0FDFCH
CHIPID29        EQU     0FDFDH
CHIPID30        EQU     0FDFEH
CHIPID31        EQU     0FDFFH

CHIPIDX         EQU     0FBD0H

CHIPIDX0        EQU     0FBD0H
CHIPIDX1        EQU     0FBD1H
CHIPIDX2        EQU     0FBD2H
CHIPIDX3        EQU     0FBD3H
CHIPIDX4        EQU     0FBD4H
CHIPIDX5        EQU     0FBD5H
CHIPIDX6        EQU     0FBD6H
CHIPIDX7        EQU     0FBD7H
CHIPIDX8        EQU     0FBD8H
CHIPIDX9        EQU     0FBD9H
CHIPIDX10       EQU     0FBDAH
CHIPIDX11       EQU     0FBDBH
CHIPIDX12       EQU     0FBDCH
CHIPIDX13       EQU     0FBDDH
CHIPIDX14       EQU     0FBDEH
CHIPIDX15       EQU     0FBDFH
CHIPIDX16       EQU     0FBE0H
CHIPIDX17       EQU     0FBE1H
CHIPIDX18       EQU     0FBE2H
CHIPIDX19       EQU     0FBE3H
CHIPIDX20       EQU     0FBE4H
CHIPIDX21       EQU     0FBE5H
CHIPIDX22       EQU     0FBE6H
CHIPIDX23       EQU     0FBE7H
CHIPIDX24       EQU     0FBE8H
CHIPIDX25       EQU     0FBE9H
CHIPIDX26       EQU     0FBEAH
CHIPIDX27       EQU     0FBEBH
CHIPIDX28       EQU     0FBECH
CHIPIDX29       EQU     0FBEDH
CHIPIDX30       EQU     0FBEEH
CHIPIDX31       EQU     0FBEFH

HSPWMA_CFG      EQU     0FBF0H
HSPWMA_ADR      EQU     0FBF1H
HSPWMA_DAT      EQU     0FBF2H
HSPWMA_ADRH     EQU     0FBF3H
HSPWMB_CFG      EQU     0FBF4H
HSPWMB_ADR      EQU     0FBF5H
HSPWMB_DAT      EQU     0FBF6H
HSPWMB_ADRH     EQU     0FBF7H
HSSPI_CFG       EQU     0FBF8H
HSSPI_CFG2      EQU     0FBF9H
HSSPI_STA       EQU     0FBFAH
HSSPI_PSCR      EQU     0FBFBH

DMA_M2M_CFG     EQU     0FA00H
DMA_M2M_CR      EQU     0FA01H
DMA_M2M_STA     EQU     0FA02H
DMA_M2M_AMT     EQU     0FA03H
DMA_M2M_DONE    EQU     0FA04H
DMA_M2M_TXAH    EQU     0FA05H
DMA_M2M_TXAL    EQU     0FA06H
DMA_M2M_RXAH    EQU     0FA07H
DMA_M2M_RXAL    EQU     0FA08H

DMA_ADC_CFG     EQU     0FA10H
DMA_ADC_CR      EQU     0FA11H
DMA_ADC_STA     EQU     0FA12H
DMA_ADC_AMT     EQU     0FA13H
DMA_ADC_DONE    EQU     0FA14H
DMA_ADC_RXAH    EQU     0FA17H
DMA_ADC_RXAL    EQU     0FA18H
DMA_ADC_CFG2    EQU     0FA19H
DMA_ADC_CHSW0   EQU     0FA1AH
DMA_ADC_CHSW1   EQU     0FA1BH
DMA_ADC_ITVH    EQU     0FA1EH
DMA_ADC_ITVL    EQU     0FA1FH

DMA_SPI_CFG     EQU     0FA20H
DMA_SPI_CR      EQU     0FA21H
DMA_SPI_STA     EQU     0FA22H
DMA_SPI_AMT     EQU     0FA23H
DMA_SPI_DONE    EQU     0FA24H
DMA_SPI_TXAH    EQU     0FA25H
DMA_SPI_TXAL    EQU     0FA26H
DMA_SPI_RXAH    EQU     0FA27H
DMA_SPI_RXAL    EQU     0FA28H
DMA_SPI_CFG2    EQU     0FA29H
DMA_SPI_ITVH    EQU     0FA2EH
DMA_SPI_ITVL    EQU     0FA2FH

DMA_UR1T_CFG    EQU     0FA30H
DMA_UR1T_CR     EQU     0FA31H
DMA_UR1T_STA    EQU     0FA32H
DMA_UR1T_AMT    EQU     0FA33H
DMA_UR1T_DONE   EQU     0FA34H
DMA_UR1T_TXAH   EQU     0FA35H
DMA_UR1T_TXAL   EQU     0FA36H
DMA_UR1R_CFG    EQU     0FA38H
DMA_UR1R_CR     EQU     0FA39H
DMA_UR1R_STA    EQU     0FA3AH
DMA_UR1R_AMT    EQU     0FA3BH
DMA_UR1R_DONE   EQU     0FA3CH
DMA_UR1R_RXAH   EQU     0FA3DH
DMA_UR1R_RXAL   EQU     0FA3EH

DMA_UR2T_CFG    EQU     0FA40H
DMA_UR2T_CR     EQU     0FA41H
DMA_UR2T_STA    EQU     0FA42H
DMA_UR2T_AMT    EQU     0FA43H
DMA_UR2T_DONE   EQU     0FA44H
DMA_UR2T_TXAH   EQU     0FA45H
DMA_UR2T_TXAL   EQU     0FA46H
DMA_UR2R_CFG    EQU     0FA48H
DMA_UR2R_CR     EQU     0FA49H
DMA_UR2R_STA    EQU     0FA4AH
DMA_UR2R_AMT    EQU     0FA4BH
DMA_UR2R_DONE   EQU     0FA4CH
DMA_UR2R_RXAH   EQU     0FA4DH
DMA_UR2R_RXAL   EQU     0FA4EH

DMA_UR3T_CFG    EQU     0FA50H
DMA_UR3T_CR     EQU     0FA51H
DMA_UR3T_STA    EQU     0FA52H
DMA_UR3T_AMT    EQU     0FA53H
DMA_UR3T_DONE   EQU     0FA54H
DMA_UR3T_TXAH   EQU     0FA55H
DMA_UR3T_TXAL   EQU     0FA56H
DMA_UR3R_CFG    EQU     0FA58H
DMA_UR3R_CR     EQU     0FA59H
DMA_UR3R_STA    EQU     0FA5AH
DMA_UR3R_AMT    EQU     0FA5BH
DMA_UR3R_DONE   EQU     0FA5CH
DMA_UR3R_RXAH   EQU     0FA5DH
DMA_UR3R_RXAL   EQU     0FA5EH

DMA_UR4T_CFG    EQU     0FA60H
DMA_UR4T_CR     EQU     0FA61H
DMA_UR4T_STA    EQU     0FA62H
DMA_UR4T_AMT    EQU     0FA63H
DMA_UR4T_DONE   EQU     0FA64H
DMA_UR4T_TXAH   EQU     0FA65H
DMA_UR4T_TXAL   EQU     0FA66H
DMA_UR4R_CFG    EQU     0FA68H
DMA_UR4R_CR     EQU     0FA69H
DMA_UR4R_STA    EQU     0FA6AH
DMA_UR4R_AMT    EQU     0FA6BH
DMA_UR4R_DONE   EQU     0FA6CH
DMA_UR4R_RXAH   EQU     0FA6DH
DMA_UR4R_RXAL   EQU     0FA6EH

DMA_LCM_CFG     EQU     0FA70H
DMA_LCM_CR      EQU     0FA71H
DMA_LCM_STA     EQU     0FA72H
DMA_LCM_AMT     EQU     0FA73H
DMA_LCM_DONE    EQU     0FA74H
DMA_LCM_TXAH    EQU     0FA75H
DMA_LCM_TXAL    EQU     0FA76H
DMA_LCM_RXAH    EQU     0FA77H
DMA_LCM_RXAL    EQU     0FA78H
DMA_LCM_ITVH    EQU     0FA7EH
DMA_LCM_ITVL    EQU     0FA7FH

DMA_M2M_AMTH    EQU     0FA80H
DMA_M2M_DONEH   EQU     0FA81H
DMA_ADC_AMTH    EQU     0FA82H
DMA_ADC_DONEH   EQU     0FA83H
DMA_SPI_AMTH    EQU     0FA84H
DMA_SPI_DONEH   EQU     0FA85H
DMA_LCM_AMTH    EQU     0FA86H
DMA_LCM_DONEH   EQU     0FA87H
DMA_UR1T_AMTH   EQU     0FA88H
DMA_UR1T_DONEH  EQU     0FA89H
DMA_UR1R_AMTH   EQU     0FA8AH
DMA_UR1R_DONEH  EQU     0FA8BH
DMA_UR2T_AMTH   EQU     0FA8CH
DMA_UR2T_DONEH  EQU     0FA8DH
DMA_UR2R_AMTH   EQU     0FA8EH
DMA_UR2R_DONEH  EQU     0FA8FH
DMA_UR3T_AMTH   EQU     0FA90H
DMA_UR3T_DONEH  EQU     0FA91H
DMA_UR3R_AMTH   EQU     0FA92H
DMA_UR3R_DONEH  EQU     0FA93H
DMA_UR4T_AMTH   EQU     0FA94H
DMA_UR4T_DONEH  EQU     0FA95H
DMA_UR4R_AMTH   EQU     0FA96H
DMA_UR4R_DONEH  EQU     0FA97H

DMA_I2CT_CFG    EQU     0FA98H
DMA_I2CT_CR     EQU     0FA99H
DMA_I2CT_STA    EQU     0FA9AH
DMA_I2CT_AMT    EQU     0FA9BH
DMA_I2CT_DONE   EQU     0FA9CH
DMA_I2CT_TXAH   EQU     0FA9DH
DMA_I2CT_TXAL   EQU     0FA9EH
DMA_I2CR_CFG    EQU     0FAA0H
DMA_I2CR_CR     EQU     0FAA1H
DMA_I2CR_STA    EQU     0FAA2H
DMA_I2CR_AMT    EQU     0FAA3H
DMA_I2CR_DONE   EQU     0FAA4H
DMA_I2CR_RXAH   EQU     0FAA5H
DMA_I2CR_RXAL   EQU     0FAA6H

DMA_I2CT_AMTH   EQU     0FAA8H
DMA_I2CT_DONEH  EQU     0FAA9H
DMA_I2CR_AMTH   EQU     0FAAAH
DMA_I2CR_DONEH  EQU     0FAABH
DMA_I2C_CR      EQU     0FAADH
DMA_I2C_ST1     EQU     0FAAEH
DMA_I2C_ST2     EQU     0FAAFH

DMA_I2ST_CFG    EQU     0FAB0H
DMA_I2ST_CR     EQU     0FAB1H
DMA_I2ST_STA    EQU     0FAB2H
DMA_I2ST_AMT    EQU     0FAB3H
DMA_I2ST_DONE   EQU     0FAB4H
DMA_I2ST_TXAH   EQU     0FAB5H
DMA_I2ST_TXAL   EQU     0FAB6H
DMA_I2SR_CFG    EQU     0FAB8H
DMA_I2SR_CR     EQU     0FAB9H
DMA_I2SR_STA    EQU     0FABAH
DMA_I2SR_AMT    EQU     0FABBH
DMA_I2SR_DONE   EQU     0FABCH
DMA_I2SR_RXAH   EQU     0FABDH
DMA_I2SR_RXAL   EQU     0FABEH

DMA_I2ST_AMTH   EQU     0FAC0H
DMA_I2ST_DONEH  EQU     0FAC1H
DMA_I2SR_AMTH   EQU     0FAC2H
DMA_I2SR_DONEH  EQU     0FAC3H
DMA_I2C_ITVH    EQU     0FAC4H
DMA_I2C_ITVL    EQU     0FAC5H
DMA_I2S_ITVH    EQU     0FAC6H
DMA_I2S_ITVL    EQU     0FAC7H
DMA_UR1_ITVH    EQU     0FAC8H
DMA_UR1_ITVL    EQU     0FAC9H
DMA_UR2_ITVH    EQU     0FACAH
DMA_UR2_ITVL    EQU     0FACBH
DMA_UR3_ITVH    EQU     0FACCH
DMA_UR3_ITVL    EQU     0FACDH
DMA_UR4_ITVH    EQU     0FACEH
DMA_UR4_ITVL    EQU     0FACFH

DMA_QSPI_CFG    EQU     0FAD0H
DMA_QSPI_CR     EQU     0FAD1H
DMA_QSPI_STA    EQU     0FAD2H
DMA_QSPI_AMT    EQU     0FAD3H
DMA_QSPI_DONE   EQU     0FAD4H
DMA_QSPI_TXAH   EQU     0FAD5H
DMA_QSPI_TXAL   EQU     0FAD6H
DMA_QSPI_RXAH   EQU     0FAD7H
DMA_QSPI_RXAL   EQU     0FAD8H
DMA_QSPI_AMTH   EQU     0FADBH
DMA_QSPI_DONEH  EQU     0FADCH
DMA_QSPI_ITVH   EQU     0FADEH
DMA_QSPI_ITVL   EQU     0FADFH

DMA_P2P_CR1     EQU     0FAF0H
DMA_P2P_CR2     EQU     0FAF1H
DMA_ARB_CFG     EQU     0FAF8H
DMA_ARB_STA     EQU     0FAF9H

QSPI_CR1        EQU     0F900H
QSPI_CR2        EQU     0F901H
QSPI_CR3        EQU     0F902H
QSPI_CR4        EQU     0F903H
QSPI_DCR1       EQU     0F904H
QSPI_DCR2       EQU     0F905H
QSPI_SR1        EQU     0F906H
QSPI_SR2        EQU     0F907H
QSPI_FCR        EQU     0F908H
QSPI_HCR1       EQU     0F909H
QSPI_HCR2       EQU     0F90AH
QSPI_DLR1       EQU     0F910H
QSPI_DLR2       EQU     0F911H
QSPI_CCR1       EQU     0F914H
QSPI_CCR2       EQU     0F915H
QSPI_CCR3       EQU     0F916H
QSPI_CCR4       EQU     0F917H
QSPI_AR1        EQU     0F918H
QSPI_AR2        EQU     0F919H
QSPI_AR3        EQU     0F91AH
QSPI_AR4        EQU     0F91BH
QSPI_ABR        EQU     0F91CH
QSPI_DR         EQU     0F920H
QSPI_PSMKR1     EQU     0F924H
QSPI_PSMAR1     EQU     0F928H
QSPI_PIR1       EQU     0F92CH
QSPI_PIR2       EQU     0F92DH

PWMA_ENO2       EQU     0F930H
PWMA_IOAUX2     EQU     0F931H
PWMA_CR3        EQU     0F932H
PWMA_SR3        EQU     0F933H
PWMA_CCER3      EQU     0F934H
PWMA_CCMR1X     EQU     0F938H
PWMA_CCMR2X     EQU     0F939H
PWMA_CCMR3X     EQU     0F93AH
PWMA_CCMR4X     EQU     0F93BH
PWMA_CCMR5      EQU     0F93CH
PWMA_CCMR5X     EQU     0F93DH
PWMA_CCMR6      EQU     0F93EH
PWMA_CCMR6X     EQU     0F93FH
PWMA_CCR5H      EQU     0F940H
PWMA_CCR5L      EQU     0F941H
PWMA_CCR5X      EQU     0F942H
PWMA_CCR6H      EQU     0F943H
PWMA_CCR6L      EQU     0F944H
PWMA_DER        EQU     0F948H
PWMA_DBA        EQU     0F949H
PWMA_DBL        EQU     0F94AH
PWMA_DMACR      EQU     0F94BH

DMA_PWMAT_CFG   EQU     0F980H
DMA_PWMAT_CR    EQU     0F981H
DMA_PWMAT_STA   EQU     0F982H
DMA_PWMAT_AMTH  EQU     0F984H
DMA_PWMAT_AMT   EQU     0F985H
DMA_PWMAT_DONEH EQU     0F986H
DMA_PWMAT_DONE  EQU     0F987H
DMA_PWMAT_TXAH  EQU     0F988H
DMA_PWMAT_TXAL  EQU     0F989H
DMA_PWMA_ITVH   EQU     0F98EH
DMA_PWMA_ITVL   EQU     0F98FH

DMA_PWMAR_CFG   EQU     0F990H
DMA_PWMAR_CR    EQU     0F991H
DMA_PWMAR_STA   EQU     0F992H
DMA_PWMAR_AMTH  EQU     0F994H
DMA_PWMAR_AMT   EQU     0F995H
DMA_PWMAR_DONEH EQU     0F996H
DMA_PWMAR_DONE  EQU     0F997H
DMA_PWMAR_RXAH  EQU     0F998H
DMA_PWMAR_RXAL  EQU     0F999H

/////////////////////////////////////////////////

;USB Control Regiter

FADDR           EQU     0
POWER           EQU     1
INTRIN1         EQU     2
INTROUT1        EQU     4
INTRUSB         EQU     6
INTRIN1E        EQU     7
INTROUT1E       EQU     9
INTRUSBE        EQU     11
FRAME1          EQU     12
FRAME2          EQU     13
INDEX           EQU     14
INMAXP          EQU     16
CSR0            EQU     17
INCSR1          EQU     17
INCSR2          EQU     18
OUTMAXP         EQU     19
OUTCSR1         EQU     20
OUTCSR2         EQU     21
COUNT0          EQU     22
OUTCOUNT1       EQU     22
OUTCOUNT2       EQU     23
FIFO0           EQU     32
FIFO1           EQU     33
FIFO2           EQU     34
FIFO3           EQU     35
FIFO4           EQU     36
FIFO5           EQU     37
UTRKCTL         EQU     48
UTRKSTS         EQU     49

/////////////////////////////////////////////////

$RESTORE

