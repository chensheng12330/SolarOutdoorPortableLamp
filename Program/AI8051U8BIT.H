#ifndef __AI8051U_H__
#define __AI8051U_H__

/////////////////////////////////////////////////

sfr         P0          =           0x80;
    sbit    P00         =           P0^0;
    sbit    P01         =           P0^1;
    sbit    P02         =           P0^2;
    sbit    P03         =           P0^3;
    sbit    P04         =           P0^4;
    sbit    P05         =           P0^5;
    sbit    P06         =           P0^6;
    sbit    P07         =           P0^7;

sfr         SP          =           0x81;
sfr         DPL         =           0x82;
sfr         DPH         =           0x83;
sfr         DPXL        =           0x84;
sfr         SPH         =           0x85;

sfr         PCON        =           0x87;
    #define SMOD                    0x80
    #define SMOD0                   0x40
    #define LVDF                    0x20
    #define POF                     0x10
    #define GF1                     0x08
    #define GF0                     0x04
    #define PD                      0x02
    #define IDL                     0x01

sfr         TCON        =           0x88;
    sbit    TF1         =           TCON^7;
    sbit    TR1         =           TCON^6;
    sbit    TF0         =           TCON^5;
    sbit    TR0         =           TCON^4;
    sbit    IE1         =           TCON^3;
    sbit    IT1         =           TCON^2;
    sbit    IE0         =           TCON^1;
    sbit    IT0         =           TCON^0;

sfr         TMOD        =           0x89;
    #define T1_GATE                 0x80
    #define T1_CT                   0x40
    #define T1_M1                   0x20
    #define T1_M0                   0x10
    #define T0_GATE                 0x08
    #define T0_CT                   0x04
    #define T0_M1                   0x02
    #define T0_M0                   0x01

sfr         TL0         =           0x8a;
sfr         TL1         =           0x8b;
sfr         TH0         =           0x8c;
sfr         TH1         =           0x8d;

sfr         AUXR        =           0x8e;
    #define T0x12                   0x80
    #define T1x12                   0x40
    #define S1M0x6                  0x20
    #define T2R                     0x10
    #define T2_CT                   0x08
    #define T2x12                   0x04
    #define EXTRAM                  0x02
    #define S1BRT                   0x01

sfr         INTCLKO     =           0x8f;
    #define EX4                     0x40
    #define EX3                     0x20
    #define EX2                     0x10
    #define T2CLKO                  0x04
    #define T1CLKO                  0x02
    #define T0CLKO                  0x01

sfr         P1          =           0x90;
    sbit    P10         =           P1^0;
    sbit    P11         =           P1^1;
    sbit    P12         =           P1^2;
    sbit    P13         =           P1^3;
    sbit    P14         =           P1^4;
    sbit    P15         =           P1^5;
    sbit    P16         =           P1^6;
    sbit    P17         =           P1^7;

sfr         P1M1        =           0x91;
sfr         P1M0        =           0x92;
sfr         P0M1        =           0x93;
sfr         P0M0        =           0x94;
sfr         P2M1        =           0x95;
sfr         P2M0        =           0x96;

sfr         AUXR2       =           0x97;
    #define RAMTINY                 0x80
    #define CPUMODE                 0x40
    #define RAMEXE                  0x20
    #define CANFD                   0x10
    #define CANSEL                  0x08
    #define CAN2EN                  0x04
    #define CANEN                   0x02
    #define LINEN                   0x01

sfr         SCON        =           0x98;
    sbit    SM0         =           SCON^7;
    sbit    SM1         =           SCON^6;
    sbit    SM2         =           SCON^5;
    sbit    REN         =           SCON^4;
    sbit    TB8         =           SCON^3;
    sbit    RB8         =           SCON^2;
    sbit    TI          =           SCON^1;
    sbit    RI          =           SCON^0;

sfr         SBUF        =           0x99;

sfr         S2CON       =           0x9a;
    #define S2SM0                   0x80
    #define S2SM1                   0x40
    #define S2SM2                   0x20
    #define S2REN                   0x10
    #define S2TB8                   0x08
    #define S2RB8                   0x04
    #define S2TI                    0x02
    #define S2RI                    0x01

sfr         S2BUF       =           0x9b;

sfr         IRCBAND     =           0x9d;
    #define USBCKS                  0x80
    #define USBCKS2                 0x40
    #define HIRCSEL1                0x02
    #define HIRCSEL0                0x01

sfr         LIRTRIM     =           0x9e;
sfr         IRTRIM      =           0x9f;

sfr         P2          =           0xa0;
    sbit    P20         =           P2^0;
    sbit    P21         =           P2^1;
    sbit    P22         =           P2^2;
    sbit    P23         =           P2^3;
    sbit    P24         =           P2^4;
    sbit    P25         =           P2^5;
    sbit    P26         =           P2^6;
    sbit    P27         =           P2^7;

sfr         BUS_SPEED   =           0xa1;

sfr         P_SW1       =           0xa2;
    #define S1_S1                   0x80
    #define S1_S0                   0x40
    #define CAN_S1                  0x20
    #define CAN_S0                  0x10
    #define SPI_S1                  0x08
    #define SPI_S0                  0x04
    #define LIN_S1                  0x02
    #define LIN_S0                  0x01

sfr         VRTRIM      =           0xa6;

sfr         IE          =           0xa8;
    sbit    EA          =           IE^7;
    sbit    ELVD        =           IE^6;
    sbit    EADC        =           IE^5;
    sbit    ES          =           IE^4;
    sbit    ET1         =           IE^3;
    sbit    EX1         =           IE^2;
    sbit    ET0         =           IE^1;
    sbit    EX0         =           IE^0;

sfr         SADDR       =           0xa9;
sfr         WKTCL       =           0xaa;
sfr         WKTCH       =           0xab;
    #define WKTEN                   0x80

sfr         S3CON       =           0xac;
    #define S3SM0                   0x80
    #define S3ST3                   0x40
    #define S3SM2                   0x20
    #define S3REN                   0x10
    #define S3TB8                   0x08
    #define S3RB8                   0x04
    #define S3TI                    0x02
    #define S3RI                    0x01

sfr         S3BUF       =           0xad;
sfr         TA          =           0xae;

sfr         IE2         =           0xaf;
    #define EUSB                    0x80
    #define ET4                     0x40
    #define ET3                     0x20
    #define ES4                     0x10
    #define ES3                     0x08
    #define ET2                     0x04
    #define ESPI                    0x02
    #define ES2                     0x01

sfr         P3          =           0xb0;
    sbit    P30         =           P3^0;
    sbit    P31         =           P3^1;
    sbit    P32         =           P3^2;
    sbit    P33         =           P3^3;
    sbit    P34         =           P3^4;
    sbit    P35         =           P3^5;
    sbit    P36         =           P3^6;
    sbit    P37         =           P3^7;

    sbit    RD          =           P3^7;
    sbit    WR          =           P3^6;
    sbit    T1          =           P3^5;
    sbit    T0          =           P3^4;
    sbit    INT1        =           P3^3;
    sbit    INT0        =           P3^2;
    sbit    TXD         =           P3^1;
    sbit    RXD         =           P3^0;

sfr         P3M1        =           0xb1;
sfr         P3M0        =           0xb2;
sfr         P4M1        =           0xb3;
sfr         P4M0        =           0xb4;

sfr         IP2         =           0xb5;
    #define PUSB                    0x80
    #define PI2C                    0x40
    #define PCMP                    0x20
    #define PX4                     0x10
    #define PPWMB                   0x08
    #define PPWMA                   0x04
    #define PSPI                    0x02
    #define PS2                     0x01

sfr         IP2H        =           0xb6;
    #define PUSBH                   0x80
    #define PI2CH                   0x40
    #define PCMPH                   0x20
    #define PX4H                    0x10
    #define PPWMBH                  0x08
    #define PPWMAH                  0x04
    #define PSPIH                   0x02
    #define PS2H                    0x01

sfr         IPH         =           0xb7;
    #define PPCAH                   0x80
    #define PLVDH                   0x40
    #define PADCH                   0x20
    #define PSH                     0x10
    #define PT1H                    0x08
    #define PX1H                    0x04
    #define PT0H                    0x02
    #define PX0H                    0x01

sfr         IP          =           0xb8;
    sbit    PPCA        =           IP^7;
    sbit    PLVD        =           IP^6;
    sbit    PADC        =           IP^5;
    sbit    PS          =           IP^4;
    sbit    PT1         =           IP^3;
    sbit    PX1         =           IP^2;
    sbit    PT0         =           IP^1;
    sbit    PX0         =           IP^0;

sfr         SADEN       =           0xb9;

sfr         P_SW2       =           0xba;
    #define EAXFR                   0x80
    #define I2C_S1                  0x20
    #define I2C_S0                  0x10
    #define CMPO_S                  0x08
    #define S4_S                    0x04
    #define S3_S                    0x02
    #define S2_S                    0x01

sfr         P_SW3       =           0xbb;
    #define I2S_S1                  0x80
    #define I2S_S0                  0x40
    #define S2SPI_S1                0x20
    #define S2SPI_S0                0x10
    #define S1SPI_S1                0x08
    #define S1SPI_S0                0x04
    #define CAN2_S1                 0x02
    #define CAN2_S0                 0x01

sfr         ADC_CONTR   =           0xbc;
    #define ADC_POWER	(1<<7)	//ADC 电源
		#define ADC_START	(1<<6)	//ADC 转换启动控制位。自动清0
		#define ADC_FLAG	(1<<5)	//ADC 转换结束标志位。软件清0
		#define ADC_EPWMT	(1<<4)	//使能 PWM 同步触发 ADC 功能

sfr         ADC_RES     =           0xbd;
sfr         ADC_RESL    =           0xbe;

sfr         P_SW4       =           0xbf;
    #define QSPI_S1                 0x02
    #define QSPI_S0                 0x01

sfr         P4          =           0xc0;
    sbit    P40         =           P4^0;
    sbit    P41         =           P4^1;
    sbit    P42         =           P4^2;
    sbit    P43         =           P4^3;
    sbit    P44         =           P4^4;
    sbit    P45         =           P4^5;
    sbit    P46         =           P4^6;
    sbit    P47         =           P4^7;

sfr         WDT_CONTR   =           0xc1;
    #define WDT_FLAG                0x80
    #define EN_WDT                  0x20
    #define CLR_WDT                 0x10
    #define IDL_WDT                 0x08

sfr         IAP_DATA    =           0xc2;
sfr         IAP_ADDRH   =           0xc3;
sfr         IAP_ADDRL   =           0xc4;
sfr         IAP_CMD     =           0xc5;
sfr         IAP_TRIG    =           0xc6;

sfr         IAP_CONTR   =           0xc7;
    #define IAPEN                   0x80
    #define SWBS                    0x40
    #define SWRST                   0x20
    #define CMD_FAIL                0x10
    #define SWBS2                   0x08

sfr         P5          =           0xc8;
    sbit    P50         =           P5^0;
    sbit    P51         =           P5^1;
    sbit    P52         =           P5^2;
    sbit    P53         =           P5^3;
    sbit    P54         =           P5^4;
    sbit    P55         =           P5^5;
    sbit    P56         =           P5^6;
    sbit    P57         =           P5^7;

sfr         P5M1        =           0xc9;
sfr         P5M0        =           0xca;
sfr         P6M1        =           0xcb;
sfr         P6M0        =           0xcc;

sfr         SPSTAT      =           0xcd;
    #define SPIF                    0x80
    #define WCOL                    0x40

sfr         SPCTL       =           0xce;
    #define SSIG                    0x80
    #define SPEN                    0x40
    #define DORD                    0x20
    #define MSTR                    0x10
    #define CPOL                    0x08
    #define CPHA                    0x04
    #define SPR1                    0x02
    #define SPR0                    0x01

sfr         SPDAT       =           0xcf;

sfr         PSW         =           0xd0;
    sbit    CY          =           PSW^7;
    sbit    AC          =           PSW^6;
    sbit    F0          =           PSW^5;
    sbit    RS1         =           PSW^4;
    sbit    RS0         =           PSW^3;
    sbit    OV          =           PSW^2;
    sbit    F1          =           PSW^1;
    sbit    P           =           PSW^0;

sfr         PSW1        =           0xd1;
    #define N                       0x20
    #define Z                       0x02

sfr         TH4         =           0xd2;
sfr         TL4         =           0xd3;
sfr         TH3         =           0xd4;
sfr         TL3         =           0xd5;
sfr         TH2         =           0xd6;
sfr         TL2         =           0xd7;

sfr         USBCLK      =           0xdc;

sfr         T4T3M       =           0xdd;
    #define T4R                     0x80
    #define T4_CT                   0x40
    #define T4x12                   0x20
    #define T4CLKO                  0x10
    #define T3R                     0x08
    #define T3_CT                   0x04
    #define T3x12                   0x02
    #define T3CLKO                  0x01

sfr         ADCCFG      =           0xde;
    #define RESFMT                  0x20

sfr         IP3         =           0xdf;
    #define PI2S                    0x08
    #define PRTC                    0x04
    #define PS4                     0x02
    #define PS3                     0x01

sfr         ACC         =           0xe0;
sfr         P7M1        =           0xe1;
sfr         P7M0        =           0xe2;
sfr         DPS         =           0xe3;

sfr         CMPCR1      =           0xe6;
    #define CMPEN                   0x80
    #define CMPIF                   0x40
    #define PIE                     0x20
    #define NIE                     0x10
    #define CMPOE                   0x02
    #define CMPRES                  0x01

sfr         CMPCR2      =           0xe7;
    #define INVCMPO                 0x80
    #define DISFLT                  0x40

sfr         P6          =           0xe8;
    sbit    P60         =           P6^0;
    sbit    P61         =           P6^1;
    sbit    P62         =           P6^2;
    sbit    P63         =           P6^3;
    sbit    P64         =           P6^4;
    sbit    P65         =           P6^5;
    sbit    P66         =           P6^6;
    sbit    P67         =           P6^7;

sfr         WTST        =           0xe9;
sfr         CKCON       =           0xea;
sfr         MXAX        =           0xeb;
sfr         USBDAT      =           0xec;
sfr         DMAIR       =           0xed;

sfr         IP3H        =           0xee;
    #define PI2SH                   0x08
    #define PRTCH                   0x04
    #define PS4H                    0x02
    #define PS3H                    0x01

sfr         AUXINTIF    =           0xef;
    #define INT4IF                  0x40
    #define INT3IF                  0x20
    #define INT2IF                  0x10
    #define T4IF                    0x04
    #define T3IF                    0x02
    #define T2IF                    0x01

sfr         B           =           0xf0;

sfr         USBCON      =           0xf4;
    #define ENUSB                   0x80
    #define ENUSBRST                0x40
    #define PS2M                    0x20
    #define PUEN                    0x10
    #define PDEN                    0x08
    #define DFREC                   0x04
    #define DP                      0x02
    #define DM                      0x01

sfr         IAP_TPS     =           0xf5;
sfr         IAP_ADDRE   =           0xf6;

sfr         P7          =           0xf8;
    sbit    P70         =           P7^0;
    sbit    P71         =           P7^1;
    sbit    P72         =           P7^2;
    sbit    P73         =           P7^3;
    sbit    P74         =           P7^4;
    sbit    P75         =           P7^5;
    sbit    P76         =           P7^6;
    sbit    P77         =           P7^7;

sfr         USBADR      =           0xfc;

sfr         S4CON       =           0xfd;
    #define S4SM0                   0x80
    #define S4ST4                   0x40
    #define S4SM2                   0x20
    #define S4REN                   0x10
    #define S4TB8                   0x08
    #define S4RB8                   0x04
    #define S4TI                    0x02
    #define S4RI                    0x01

sfr         S4BUF       =           0xfe;

sfr         RSTCFG      =           0xff;
    #define ENLVR                   0x40
    #define P47RST                  0x10

/////////////////////////////////////////////////
//
//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将EAXFR设置为1,才可正常读写
//    EAXFR = 1;
//或者
//    P_SW2 |= 0x80;
///////////////////////////////////////////////////

/////////////////////////////////////////////////
//7E:FF00H-7E:FFFFH
/////////////////////////////////////////////////



/////////////////////////////////////////////////
//7E:FE00H-7E:FEFFH
/////////////////////////////////////////////////

#define     CLKSEL                  (*(unsigned char volatile xdata *)0xfe00)
#define     CLKDIV                  (*(unsigned char volatile xdata *)0xfe01)
#define     HIRCCR                  (*(unsigned char volatile xdata *)0xfe02)
#define     XOSCCR                  (*(unsigned char volatile xdata *)0xfe03)
#define     IRC32KCR                (*(unsigned char volatile xdata *)0xfe04)
#define     MCLKOCR                 (*(unsigned char volatile xdata *)0xfe05)
#define     IRCDB                   (*(unsigned char volatile xdata *)0xfe06)
#define     IRC48MCR                (*(unsigned char volatile xdata *)0xfe07)
#define     X32KCR                  (*(unsigned char volatile xdata *)0xfe08)
#define     HSCLKDIV                (*(unsigned char volatile xdata *)0xfe0b)

#define     P0PU                    (*(unsigned char volatile xdata *)0xfe10)
#define     P1PU                    (*(unsigned char volatile xdata *)0xfe11)
#define     P2PU                    (*(unsigned char volatile xdata *)0xfe12)
#define     P3PU                    (*(unsigned char volatile xdata *)0xfe13)
#define     P4PU                    (*(unsigned char volatile xdata *)0xfe14)
#define     P5PU                    (*(unsigned char volatile xdata *)0xfe15)
#define     P6PU                    (*(unsigned char volatile xdata *)0xfe16)
#define     P7PU                    (*(unsigned char volatile xdata *)0xfe17)
#define     P0NCS                   (*(unsigned char volatile xdata *)0xfe18)
#define     P1NCS                   (*(unsigned char volatile xdata *)0xfe19)
#define     P2NCS                   (*(unsigned char volatile xdata *)0xfe1a)
#define     P3NCS                   (*(unsigned char volatile xdata *)0xfe1b)
#define     P4NCS                   (*(unsigned char volatile xdata *)0xfe1c)
#define     P5NCS                   (*(unsigned char volatile xdata *)0xfe1d)
#define     P6NCS                   (*(unsigned char volatile xdata *)0xfe1e)
#define     P7NCS                   (*(unsigned char volatile xdata *)0xfe1f)
#define     P0SR                    (*(unsigned char volatile xdata *)0xfe20)
#define     P1SR                    (*(unsigned char volatile xdata *)0xfe21)
#define     P2SR                    (*(unsigned char volatile xdata *)0xfe22)
#define     P3SR                    (*(unsigned char volatile xdata *)0xfe23)
#define     P4SR                    (*(unsigned char volatile xdata *)0xfe24)
#define     P5SR                    (*(unsigned char volatile xdata *)0xfe25)
#define     P6SR                    (*(unsigned char volatile xdata *)0xfe26)
#define     P7SR                    (*(unsigned char volatile xdata *)0xfe27)
#define     P0DR                    (*(unsigned char volatile xdata *)0xfe28)
#define     P1DR                    (*(unsigned char volatile xdata *)0xfe29)
#define     P2DR                    (*(unsigned char volatile xdata *)0xfe2a)
#define     P3DR                    (*(unsigned char volatile xdata *)0xfe2b)
#define     P4DR                    (*(unsigned char volatile xdata *)0xfe2c)
#define     P5DR                    (*(unsigned char volatile xdata *)0xfe2d)
#define     P6DR                    (*(unsigned char volatile xdata *)0xfe2e)
#define     P7DR                    (*(unsigned char volatile xdata *)0xfe2f)
#define     P0IE                    (*(unsigned char volatile xdata *)0xfe30)
#define     P1IE                    (*(unsigned char volatile xdata *)0xfe31)
#define     P2IE                    (*(unsigned char volatile xdata *)0xfe32)
#define     P3IE                    (*(unsigned char volatile xdata *)0xfe33)
#define     P4IE                    (*(unsigned char volatile xdata *)0xfe34)
#define     P5IE                    (*(unsigned char volatile xdata *)0xfe35)
#define     P6IE                    (*(unsigned char volatile xdata *)0xfe36)
#define     P7IE                    (*(unsigned char volatile xdata *)0xfe37)
#define     P0PD                    (*(unsigned char volatile xdata *)0xfe40)
#define     P1PD                    (*(unsigned char volatile xdata *)0xfe41)
#define     P2PD                    (*(unsigned char volatile xdata *)0xfe42)
#define     P3PD                    (*(unsigned char volatile xdata *)0xfe43)
#define     P4PD                    (*(unsigned char volatile xdata *)0xfe44)
#define     P5PD                    (*(unsigned char volatile xdata *)0xfe45)
#define     P6PD                    (*(unsigned char volatile xdata *)0xfe46)
#define     P7PD                    (*(unsigned char volatile xdata *)0xfe47)
#define     P0BP                    (*(unsigned char volatile xdata *)0xfe48)
#define     P1BP                    (*(unsigned char volatile xdata *)0xfe49)
#define     P2BP                    (*(unsigned char volatile xdata *)0xfe4a)
#define     P3BP                    (*(unsigned char volatile xdata *)0xfe4b)
#define     P4BP                    (*(unsigned char volatile xdata *)0xfe4c)
#define     P5BP                    (*(unsigned char volatile xdata *)0xfe4d)
#define     P6BP                    (*(unsigned char volatile xdata *)0xfe4e)
#define     P7BP                    (*(unsigned char volatile xdata *)0xfe4f)

#define     LCMIFCFG                (*(unsigned char volatile xdata *)0xfe50)
#define     LCMIFCFG2               (*(unsigned char volatile xdata *)0xfe51)
#define     LCMIFCR                 (*(unsigned char volatile xdata *)0xfe52)
#define     LCMIFSTA                (*(unsigned char volatile xdata *)0xfe53)
#define     LCMIFDATL               (*(unsigned char volatile xdata *)0xfe54)
#define     LCMIFDATH               (*(unsigned char volatile xdata *)0xfe55)
#define     LCMIFPSCR               (*(unsigned char volatile xdata *)0xfe56)

#define     RTCCR                   (*(unsigned char volatile xdata *)0xfe60)
#define     RTCCFG                  (*(unsigned char volatile xdata *)0xfe61)
#define     RTCIEN                  (*(unsigned char volatile xdata *)0xfe62)
#define     RTCIF                   (*(unsigned char volatile xdata *)0xfe63)
#define     ALAHOUR                 (*(unsigned char volatile xdata *)0xfe64)
#define     ALAMIN                  (*(unsigned char volatile xdata *)0xfe65)
#define     ALASEC                  (*(unsigned char volatile xdata *)0xfe66)
#define     ALASSEC                 (*(unsigned char volatile xdata *)0xfe67)
#define     INIYEAR                 (*(unsigned char volatile xdata *)0xfe68)
#define     INIMONTH                (*(unsigned char volatile xdata *)0xfe69)
#define     INIDAY                  (*(unsigned char volatile xdata *)0xfe6a)
#define     INIHOUR                 (*(unsigned char volatile xdata *)0xfe6b)
#define     INIMIN                  (*(unsigned char volatile xdata *)0xfe6c)
#define     INISEC                  (*(unsigned char volatile xdata *)0xfe6d)
#define     INISSEC                 (*(unsigned char volatile xdata *)0xfe6e)
#define     INIWEEK                 (*(unsigned char volatile xdata *)0xfe6f)
#define     WEEK                    (*(unsigned char volatile xdata *)0xfe6f)
#define     YEAR                    (*(unsigned char volatile xdata *)0xfe70)
#define     MONTH                   (*(unsigned char volatile xdata *)0xfe71)
#define     DAY                     (*(unsigned char volatile xdata *)0xfe72)
#define     HOUR                    (*(unsigned char volatile xdata *)0xfe73)
#define     MIN                     (*(unsigned char volatile xdata *)0xfe74)
#define     SEC                     (*(unsigned char volatile xdata *)0xfe75)
#define     SSEC                    (*(unsigned char volatile xdata *)0xfe76)

#define     T11CR                   (*(unsigned char volatile xdata *)0xfe78)
#define     T11PS                   (*(unsigned char volatile xdata *)0xfe79)
#define     T11H                    (*(unsigned char volatile xdata *)0xfe7a)
#define     T11L                    (*(unsigned char volatile xdata *)0xfe7b)

#define     I2CCFG                  (*(unsigned char volatile xdata *)0xfe80)
#define     I2CMSCR                 (*(unsigned char volatile xdata *)0xfe81)
#define     I2CMSST                 (*(unsigned char volatile xdata *)0xfe82)
#define     I2CSLCR                 (*(unsigned char volatile xdata *)0xfe83)
#define     I2CSLST                 (*(unsigned char volatile xdata *)0xfe84)
#define     I2CSLADR                (*(unsigned char volatile xdata *)0xfe85)
#define     I2CTXD                  (*(unsigned char volatile xdata *)0xfe86)
#define     I2CRXD                  (*(unsigned char volatile xdata *)0xfe87)
#define     I2CMSAUX                (*(unsigned char volatile xdata *)0xfe88)
#define     I2CPSCR                 (*(unsigned char volatile xdata *)0xfe89)

#define     SPI_CLKDIV              (*(unsigned char volatile xdata *)0xfe90)
#define     PWMA_CLKDIV             (*(unsigned char volatile xdata *)0xfe91)
#define     PWMB_CLKDIV             (*(unsigned char volatile xdata *)0xfe92)
#define     TFPU_CLKDIV             (*(unsigned char volatile xdata *)0xfe93)
#define     I2S_CLKDIV              (*(unsigned char volatile xdata *)0xfe94)

#define     RSTFLAG                 (*(unsigned char volatile xdata *)0xfe99)
#define     RSTCR0                  (*(unsigned char volatile xdata *)0xfe9a)
#define     RSTCR1                  (*(unsigned char volatile xdata *)0xfe9b)
#define     RSTCR2                  (*(unsigned char volatile xdata *)0xfe9c)
#define     RSTCR3                  (*(unsigned char volatile xdata *)0xfe9d)
#define     RSTCR4                  (*(unsigned char volatile xdata *)0xfe9e)
#define     RSTCR5                  (*(unsigned char volatile xdata *)0xfe9f)

#define     TM0PS                   (*(unsigned char volatile xdata *)0xfea0)
#define     TM1PS                   (*(unsigned char volatile xdata *)0xfea1)
#define     TM2PS                   (*(unsigned char volatile xdata *)0xfea2)
#define     TM3PS                   (*(unsigned char volatile xdata *)0xfea3)
#define     TM4PS                   (*(unsigned char volatile xdata *)0xfea4)
#define     ADCTIM                  (*(unsigned char volatile xdata *)0xfea8)
#define     ADCEXCFG                (*(unsigned char volatile xdata *)0xfead)
#define     CMPEXCFG                (*(unsigned char volatile xdata *)0xfeae)

#define     PWMA_ETRPS              (*(unsigned char volatile xdata *)0xfeb0)
#define     PWMA_ENO                (*(unsigned char volatile xdata *)0xfeb1)
#define     PWMA_PS                 (*(unsigned char volatile xdata *)0xfeb2)
#define     PWMA_IOAUX              (*(unsigned char volatile xdata *)0xfeb3)
#define     PWMB_ETRPS              (*(unsigned char volatile xdata *)0xfeb4)
#define     PWMB_ENO                (*(unsigned char volatile xdata *)0xfeb5)
#define     PWMB_PS                 (*(unsigned char volatile xdata *)0xfeb6)
#define     PWMB_IOAUX              (*(unsigned char volatile xdata *)0xfeb7)
#define     PWMA_PS2                (*(unsigned char volatile xdata *)0xfeb8)
#define     PWMA_RCRH               (*(unsigned char volatile xdata *)0xfeb9)
#define     PWMB_RCRH               (*(unsigned char volatile xdata *)0xfeba)

#define     PWMA_CR1                (*(unsigned char volatile xdata *)0xfec0)
#define     PWMA_CR2                (*(unsigned char volatile xdata *)0xfec1)
#define     PWMA_SMCR               (*(unsigned char volatile xdata *)0xfec2)
#define     PWMA_ETR                (*(unsigned char volatile xdata *)0xfec3)
#define     PWMA_IER                (*(unsigned char volatile xdata *)0xfec4)
#define     PWMA_SR1                (*(unsigned char volatile xdata *)0xfec5)
#define     PWMA_SR2                (*(unsigned char volatile xdata *)0xfec6)
#define     PWMA_EGR                (*(unsigned char volatile xdata *)0xfec7)
#define     PWMA_CCMR1              (*(unsigned char volatile xdata *)0xfec8)
#define     PWMA_CCMR2              (*(unsigned char volatile xdata *)0xfec9)
#define     PWMA_CCMR3              (*(unsigned char volatile xdata *)0xfeca)
#define     PWMA_CCMR4              (*(unsigned char volatile xdata *)0xfecb)
#define     PWMA_CCER1              (*(unsigned char volatile xdata *)0xfecc)
#define     PWMA_CCER2              (*(unsigned char volatile xdata *)0xfecd)
#define     PWMA_CNTRH              (*(unsigned char volatile xdata *)0xfece)
#define     PWMA_CNTRL              (*(unsigned char volatile xdata *)0xfecf)
#define     PWMA_PSCRH              (*(unsigned char volatile xdata *)0xfed0)
#define     PWMA_PSCRL              (*(unsigned char volatile xdata *)0xfed1)
#define     PWMA_ARRH               (*(unsigned char volatile xdata *)0xfed2)
#define     PWMA_ARRL               (*(unsigned char volatile xdata *)0xfed3)
#define     PWMA_RCR                (*(unsigned char volatile xdata *)0xfed4)
#define     PWMA_CCR1H              (*(unsigned char volatile xdata *)0xfed5)
#define     PWMA_CCR1L              (*(unsigned char volatile xdata *)0xfed6)
#define     PWMA_CCR2H              (*(unsigned char volatile xdata *)0xfed7)
#define     PWMA_CCR2L              (*(unsigned char volatile xdata *)0xfed8)
#define     PWMA_CCR3H              (*(unsigned char volatile xdata *)0xfed9)
#define     PWMA_CCR3L              (*(unsigned char volatile xdata *)0xfeda)
#define     PWMA_CCR4H              (*(unsigned char volatile xdata *)0xfedb)
#define     PWMA_CCR4L              (*(unsigned char volatile xdata *)0xfedc)
#define     PWMA_BKR                (*(unsigned char volatile xdata *)0xfedd)
#define     PWMA_DTR                (*(unsigned char volatile xdata *)0xfede)
#define     PWMA_OISR               (*(unsigned char volatile xdata *)0xfedf)

#define     PWMB_CR1                (*(unsigned char volatile xdata *)0xfee0)
#define     PWMB_CR2                (*(unsigned char volatile xdata *)0xfee1)
#define     PWMB_SMCR               (*(unsigned char volatile xdata *)0xfee2)
#define     PWMB_ETR                (*(unsigned char volatile xdata *)0xfee3)
#define     PWMB_IER                (*(unsigned char volatile xdata *)0xfee4)
#define     PWMB_SR1                (*(unsigned char volatile xdata *)0xfee5)
#define     PWMB_SR2                (*(unsigned char volatile xdata *)0xfee6)
#define     PWMB_EGR                (*(unsigned char volatile xdata *)0xfee7)
#define     PWMB_CCMR1              (*(unsigned char volatile xdata *)0xfee8)
#define     PWMB_CCMR2              (*(unsigned char volatile xdata *)0xfee9)
#define     PWMB_CCMR3              (*(unsigned char volatile xdata *)0xfeea)
#define     PWMB_CCMR4              (*(unsigned char volatile xdata *)0xfeeb)
#define     PWMB_CCER1              (*(unsigned char volatile xdata *)0xfeec)
#define     PWMB_CCER2              (*(unsigned char volatile xdata *)0xfeed)
#define     PWMB_CNTRH              (*(unsigned char volatile xdata *)0xfeee)
#define     PWMB_CNTRL              (*(unsigned char volatile xdata *)0xfeef)
#define     PWMB_PSCRH              (*(unsigned char volatile xdata *)0xfef0)
#define     PWMB_PSCRL              (*(unsigned char volatile xdata *)0xfef1)
#define     PWMB_ARRH               (*(unsigned char volatile xdata *)0xfef2)
#define     PWMB_ARRL               (*(unsigned char volatile xdata *)0xfef3)
#define     PWMB_RCR                (*(unsigned char volatile xdata *)0xfef4)
#define     PWMB_CCR5H              (*(unsigned char volatile xdata *)0xfef5)
#define     PWMB_CCR5L              (*(unsigned char volatile xdata *)0xfef6)
#define     PWMB_CCR6H              (*(unsigned char volatile xdata *)0xfef7)
#define     PWMB_CCR6L              (*(unsigned char volatile xdata *)0xfef8)
#define     PWMB_CCR7H              (*(unsigned char volatile xdata *)0xfef9)
#define     PWMB_CCR7L              (*(unsigned char volatile xdata *)0xfefa)
#define     PWMB_CCR8H              (*(unsigned char volatile xdata *)0xfefb)
#define     PWMB_CCR8L              (*(unsigned char volatile xdata *)0xfefc)
#define     PWMB_BKR                (*(unsigned char volatile xdata *)0xfefd)
#define     PWMB_DTR                (*(unsigned char volatile xdata *)0xfefe)
#define     PWMB_OISR               (*(unsigned char volatile xdata *)0xfeff)

/////////////////////////////////////////////////
//7E:FD00H-7E:FDFFH
/////////////////////////////////////////////////

#define     P0INTE                  (*(unsigned char volatile xdata *)0xfd00)
#define     P1INTE                  (*(unsigned char volatile xdata *)0xfd01)
#define     P2INTE                  (*(unsigned char volatile xdata *)0xfd02)
#define     P3INTE                  (*(unsigned char volatile xdata *)0xfd03)
#define     P4INTE                  (*(unsigned char volatile xdata *)0xfd04)
#define     P5INTE                  (*(unsigned char volatile xdata *)0xfd05)
#define     P6INTE                  (*(unsigned char volatile xdata *)0xfd06)
#define     P7INTE                  (*(unsigned char volatile xdata *)0xfd07)
#define     P0INTF                  (*(unsigned char volatile xdata *)0xfd10)
#define     P1INTF                  (*(unsigned char volatile xdata *)0xfd11)
#define     P2INTF                  (*(unsigned char volatile xdata *)0xfd12)
#define     P3INTF                  (*(unsigned char volatile xdata *)0xfd13)
#define     P4INTF                  (*(unsigned char volatile xdata *)0xfd14)
#define     P5INTF                  (*(unsigned char volatile xdata *)0xfd15)
#define     P6INTF                  (*(unsigned char volatile xdata *)0xfd16)
#define     P7INTF                  (*(unsigned char volatile xdata *)0xfd17)
#define     P0IM0                   (*(unsigned char volatile xdata *)0xfd20)
#define     P1IM0                   (*(unsigned char volatile xdata *)0xfd21)
#define     P2IM0                   (*(unsigned char volatile xdata *)0xfd22)
#define     P3IM0                   (*(unsigned char volatile xdata *)0xfd23)
#define     P4IM0                   (*(unsigned char volatile xdata *)0xfd24)
#define     P5IM0                   (*(unsigned char volatile xdata *)0xfd25)
#define     P6IM0                   (*(unsigned char volatile xdata *)0xfd26)
#define     P7IM0                   (*(unsigned char volatile xdata *)0xfd27)
#define     P0IM1                   (*(unsigned char volatile xdata *)0xfd30)
#define     P1IM1                   (*(unsigned char volatile xdata *)0xfd31)
#define     P2IM1                   (*(unsigned char volatile xdata *)0xfd32)
#define     P3IM1                   (*(unsigned char volatile xdata *)0xfd33)
#define     P4IM1                   (*(unsigned char volatile xdata *)0xfd34)
#define     P5IM1                   (*(unsigned char volatile xdata *)0xfd35)
#define     P6IM1                   (*(unsigned char volatile xdata *)0xfd36)
#define     P7IM1                   (*(unsigned char volatile xdata *)0xfd37)
#define     P0WKUE                  (*(unsigned char volatile xdata *)0xfd40)
#define     P1WKUE                  (*(unsigned char volatile xdata *)0xfd41)
#define     P2WKUE                  (*(unsigned char volatile xdata *)0xfd42)
#define     P3WKUE                  (*(unsigned char volatile xdata *)0xfd43)
#define     P4WKUE                  (*(unsigned char volatile xdata *)0xfd44)
#define     P5WKUE                  (*(unsigned char volatile xdata *)0xfd45)
#define     P6WKUE                  (*(unsigned char volatile xdata *)0xfd46)
#define     P7WKUE                  (*(unsigned char volatile xdata *)0xfd47)

#define     CCAPM2                  (*(unsigned char volatile xdata *)0xfd50)
#define     CCAP2L                  (*(unsigned char volatile xdata *)0xfd51)
#define     CCAP2H                  (*(unsigned char volatile xdata *)0xfd52)
#define     PCA_PWM2                (*(unsigned char volatile xdata *)0xfd53)
#define     CCAPM3                  (*(unsigned char volatile xdata *)0xfd54)
#define     CCAP3L                  (*(unsigned char volatile xdata *)0xfd55)
#define     CCAP3H                  (*(unsigned char volatile xdata *)0xfd56)
#define     PCA_PWM3                (*(unsigned char volatile xdata *)0xfd57)
#define     CCAPM0                  (*(unsigned char volatile xdata *)0xfd58)
#define     CCAP0L                  (*(unsigned char volatile xdata *)0xfd59)
#define     CCAP0H                  (*(unsigned char volatile xdata *)0xfd5a)
#define     PCA_PWM0                (*(unsigned char volatile xdata *)0xfd5b)
#define     CCAPM1                  (*(unsigned char volatile xdata *)0xfd5c)
#define     CCAP1L                  (*(unsigned char volatile xdata *)0xfd5d)
#define     CCAP1H                  (*(unsigned char volatile xdata *)0xfd5e)
#define     PCA_PWM1                (*(unsigned char volatile xdata *)0xfd5f)

#define     PINIPL                  (*(unsigned char volatile xdata *)0xfd60)
#define     PINIPH                  (*(unsigned char volatile xdata *)0xfd61)

#define     CCON                    (*(unsigned char volatile xdata *)0xfd64)
    #define     CF                  0x80
    #define     CR                  0x40
    #define     CCF2                0x04
    #define     CCF1                0x02
    #define     CCF0                0x01

#define     CL                      (*(unsigned char volatile xdata *)0xfd65)
#define     CH                      (*(unsigned char volatile xdata *)0xfd66)
#define     CMOD                    (*(unsigned char volatile xdata *)0xfd67)
    #define     CIDL                0x80
    #define     ECF                 0x01

#define     UR1TOCR                 (*(unsigned char volatile xdata *)0xfd70)
#define     UR1TOSR                 (*(unsigned char volatile xdata *)0xfd71)
#define     UR1TOTH                 (*(unsigned char volatile xdata *)0xfd72)
#define     UR1TOTL                 (*(unsigned char volatile xdata *)0xfd73)
#define     UR2TOCR                 (*(unsigned char volatile xdata *)0xfd74)
#define     UR2TOSR                 (*(unsigned char volatile xdata *)0xfd75)
#define     UR2TOTH                 (*(unsigned char volatile xdata *)0xfd76)
#define     UR2TOTL                 (*(unsigned char volatile xdata *)0xfd77)
#define     UR3TOCR                 (*(unsigned char volatile xdata *)0xfd78)
#define     UR3TOSR                 (*(unsigned char volatile xdata *)0xfd79)
#define     UR3TOTH                 (*(unsigned char volatile xdata *)0xfd7a)
#define     UR3TOTL                 (*(unsigned char volatile xdata *)0xfd7b)
#define     UR4TOCR                 (*(unsigned char volatile xdata *)0xfd7c)
#define     UR4TOSR                 (*(unsigned char volatile xdata *)0xfd7d)
#define     UR4TOTH                 (*(unsigned char volatile xdata *)0xfd7e)
#define     UR4TOTL                 (*(unsigned char volatile xdata *)0xfd7f)

#define     SPITOCR                 (*(unsigned char volatile xdata *)0xfd80)
#define     SPITOSR                 (*(unsigned char volatile xdata *)0xfd81)
#define     SPITOTH                 (*(unsigned char volatile xdata *)0xfd82)
#define     SPITOTL                 (*(unsigned char volatile xdata *)0xfd83)
#define     I2CTOCR                 (*(unsigned char volatile xdata *)0xfd84)
#define     I2CTOSR                 (*(unsigned char volatile xdata *)0xfd85)
#define     I2CTOTH                 (*(unsigned char volatile xdata *)0xfd86)
#define     I2CTOTL                 (*(unsigned char volatile xdata *)0xfd87)

#define     UR1TOTE                 (*(unsigned char volatile xdata *)0xfd88)
#define     UR2TOTE                 (*(unsigned char volatile xdata *)0xfd89)
#define     UR3TOTE                 (*(unsigned char volatile xdata *)0xfd8a)
#define     UR4TOTE                 (*(unsigned char volatile xdata *)0xfd8b)
#define     SPITOTE                 (*(unsigned char volatile xdata *)0xfd8c)
#define     I2CTOTE                 (*(unsigned char volatile xdata *)0xfd8d)

#define     I2SCR                   (*(unsigned char volatile xdata *)0xfd98)
#define     I2SSR                   (*(unsigned char volatile xdata *)0xfd99)
#define     I2SDRH                  (*(unsigned char volatile xdata *)0xfd9a)
#define     I2SDRL                  (*(unsigned char volatile xdata *)0xfd9b)
#define     I2SPRH                  (*(unsigned char volatile xdata *)0xfd9c)
#define     I2SPRL                  (*(unsigned char volatile xdata *)0xfd9d)
#define     I2SCFGH                 (*(unsigned char volatile xdata *)0xfd9e)
#define     I2SCFGL                 (*(unsigned char volatile xdata *)0xfd9f)
#define     I2SMD                   (*(unsigned char volatile xdata *)0xfda0)
#define     I2SMCKDIV               (*(unsigned char volatile xdata *)0xfda1)

#define     CRECR                   (*(unsigned char volatile xdata *)0xfda8)
#define     CRECNTH                 (*(unsigned char volatile xdata *)0xfda9)
#define     CRECNTL                 (*(unsigned char volatile xdata *)0xfdaa)
#define     CRERES                  (*(unsigned char volatile xdata *)0xfdab)

#define     S2CFG                   (*(unsigned char volatile xdata *)0xfdb4)
#define     S2ADDR                  (*(unsigned char volatile xdata *)0xfdb5)
#define     S2ADEN                  (*(unsigned char volatile xdata *)0xfdb6)
#define     USARTCR1                (*(unsigned char volatile xdata *)0xfdc0)
#define     USARTCR2                (*(unsigned char volatile xdata *)0xfdc1)
#define     USARTCR3                (*(unsigned char volatile xdata *)0xfdc2)
#define     USARTCR4                (*(unsigned char volatile xdata *)0xfdc3)
#define     USARTCR5                (*(unsigned char volatile xdata *)0xfdc4)
#define     USARTGTR                (*(unsigned char volatile xdata *)0xfdc5)
#define     USARTBRH                (*(unsigned char volatile xdata *)0xfdc6)
#define     USARTBRL                (*(unsigned char volatile xdata *)0xfdc7)
#define     USART2CR1               (*(unsigned char volatile xdata *)0xfdc8)
#define     USART2CR2               (*(unsigned char volatile xdata *)0xfdc9)
#define     USART2CR3               (*(unsigned char volatile xdata *)0xfdca)
#define     USART2CR4               (*(unsigned char volatile xdata *)0xfdcb)
#define     USART2CR5               (*(unsigned char volatile xdata *)0xfdcc)
#define     USART2GTR               (*(unsigned char volatile xdata *)0xfdcd)
#define     USART2BRH               (*(unsigned char volatile xdata *)0xfdce)
#define     USART2BRL               (*(unsigned char volatile xdata *)0xfdcf)

#define     CHIPID                  ( (unsigned char volatile xdata *)0xfde0)

#define     CHIPID0                 (*(unsigned char volatile xdata *)0xfde0)
#define     CHIPID1                 (*(unsigned char volatile xdata *)0xfde1)
#define     CHIPID2                 (*(unsigned char volatile xdata *)0xfde2)
#define     CHIPID3                 (*(unsigned char volatile xdata *)0xfde3)
#define     CHIPID4                 (*(unsigned char volatile xdata *)0xfde4)
#define     CHIPID5                 (*(unsigned char volatile xdata *)0xfde5)
#define     CHIPID6                 (*(unsigned char volatile xdata *)0xfde6)
#define     CHIPID7                 (*(unsigned char volatile xdata *)0xfde7)
#define     CHIPID8                 (*(unsigned char volatile xdata *)0xfde8)
#define     CHIPID9                 (*(unsigned char volatile xdata *)0xfde9)
#define     CHIPID10                (*(unsigned char volatile xdata *)0xfdea)
#define     CHIPID11                (*(unsigned char volatile xdata *)0xfdeb)
#define     CHIPID12                (*(unsigned char volatile xdata *)0xfdec)
#define     CHIPID13                (*(unsigned char volatile xdata *)0xfded)
#define     CHIPID14                (*(unsigned char volatile xdata *)0xfdee)
#define     CHIPID15                (*(unsigned char volatile xdata *)0xfdef)
#define     CHIPID16                (*(unsigned char volatile xdata *)0xfdf0)
#define     CHIPID17                (*(unsigned char volatile xdata *)0xfdf1)
#define     CHIPID18                (*(unsigned char volatile xdata *)0xfdf2)
#define     CHIPID19                (*(unsigned char volatile xdata *)0xfdf3)
#define     CHIPID20                (*(unsigned char volatile xdata *)0xfdf4)
#define     CHIPID21                (*(unsigned char volatile xdata *)0xfdf5)
#define     CHIPID22                (*(unsigned char volatile xdata *)0xfdf6)
#define     CHIPID23                (*(unsigned char volatile xdata *)0xfdf7)
#define     CHIPID24                (*(unsigned char volatile xdata *)0xfdf8)
#define     CHIPID25                (*(unsigned char volatile xdata *)0xfdf9)
#define     CHIPID26                (*(unsigned char volatile xdata *)0xfdfa)
#define     CHIPID27                (*(unsigned char volatile xdata *)0xfdfb)
#define     CHIPID28                (*(unsigned char volatile xdata *)0xfdfc)
#define     CHIPID29                (*(unsigned char volatile xdata *)0xfdfd)
#define     CHIPID30                (*(unsigned char volatile xdata *)0xfdfe)
#define     CHIPID31                (*(unsigned char volatile xdata *)0xfdff)

/////////////////////////////////////////////////
//7E:FC00H-7E:FCFFH
/////////////////////////////////////////////////



/////////////////////////////////////////////////
//7E:FB00H-7E:FBFFH
/////////////////////////////////////////////////

#define     CHIPIDX                 ( (unsigned char volatile xdata *)0xfbd0)

#define     CHIPIDX0                (*(unsigned char volatile xdata *)0xfbd0)
#define     CHIPIDX1                (*(unsigned char volatile xdata *)0xfbd1)
#define     CHIPIDX2                (*(unsigned char volatile xdata *)0xfbd2)
#define     CHIPIDX3                (*(unsigned char volatile xdata *)0xfbd3)
#define     CHIPIDX4                (*(unsigned char volatile xdata *)0xfbd4)
#define     CHIPIDX5                (*(unsigned char volatile xdata *)0xfbd5)
#define     CHIPIDX6                (*(unsigned char volatile xdata *)0xfbd6)
#define     CHIPIDX7                (*(unsigned char volatile xdata *)0xfbd7)
#define     CHIPIDX8                (*(unsigned char volatile xdata *)0xfbd8)
#define     CHIPIDX9                (*(unsigned char volatile xdata *)0xfbd9)
#define     CHIPIDX10               (*(unsigned char volatile xdata *)0xfbda)
#define     CHIPIDX11               (*(unsigned char volatile xdata *)0xfbdb)
#define     CHIPIDX12               (*(unsigned char volatile xdata *)0xfbdc)
#define     CHIPIDX13               (*(unsigned char volatile xdata *)0xfbdd)
#define     CHIPIDX14               (*(unsigned char volatile xdata *)0xfbde)
#define     CHIPIDX15               (*(unsigned char volatile xdata *)0xfbdf)
#define     CHIPIDX16               (*(unsigned char volatile xdata *)0xfbe0)
#define     CHIPIDX17               (*(unsigned char volatile xdata *)0xfbe1)
#define     CHIPIDX18               (*(unsigned char volatile xdata *)0xfbe2)
#define     CHIPIDX19               (*(unsigned char volatile xdata *)0xfbe3)
#define     CHIPIDX20               (*(unsigned char volatile xdata *)0xfbe4)
#define     CHIPIDX21               (*(unsigned char volatile xdata *)0xfbe5)
#define     CHIPIDX22               (*(unsigned char volatile xdata *)0xfbe6)
#define     CHIPIDX23               (*(unsigned char volatile xdata *)0xfbe7)
#define     CHIPIDX24               (*(unsigned char volatile xdata *)0xfbe8)
#define     CHIPIDX25               (*(unsigned char volatile xdata *)0xfbe9)
#define     CHIPIDX26               (*(unsigned char volatile xdata *)0xfbea)
#define     CHIPIDX27               (*(unsigned char volatile xdata *)0xfbeb)
#define     CHIPIDX28               (*(unsigned char volatile xdata *)0xfbec)
#define     CHIPIDX29               (*(unsigned char volatile xdata *)0xfbed)
#define     CHIPIDX30               (*(unsigned char volatile xdata *)0xfbee)
#define     CHIPIDX31               (*(unsigned char volatile xdata *)0xfbef)

#define     HSPWMA_CFG              (*(unsigned char volatile xdata *)0xfbf0)
#define     HSPWMA_ADR              (*(unsigned char volatile xdata *)0xfbf1)
#define     HSPWMA_DAT              (*(unsigned char volatile xdata *)0xfbf2)
#define     HSPWMA_ADRH             (*(unsigned char volatile xdata *)0xfbf3)

#define     HSPWMB_CFG              (*(unsigned char volatile xdata *)0xfbf4)
#define     HSPWMB_ADR              (*(unsigned char volatile xdata *)0xfbf5)
#define     HSPWMB_DAT              (*(unsigned char volatile xdata *)0xfbf6)
#define     HSPWMB_ADRH             (*(unsigned char volatile xdata *)0xfbf7)

#define     HSSPI_CFG               (*(unsigned char volatile xdata *)0xfbf8)
#define     HSSPI_CFG2              (*(unsigned char volatile xdata *)0xfbf9)
#define     HSSPI_STA               (*(unsigned char volatile xdata *)0xfbfa)
#define     HSSPI_PSCR              (*(unsigned char volatile xdata *)0xfbfb)

/////////////////////////////////////////////////
//7E:FA00H-7E:FAFFH
/////////////////////////////////////////////////

#define     DMA_M2M_CFG             (*(unsigned char volatile xdata *)0xfa00)
#define     DMA_M2M_CR              (*(unsigned char volatile xdata *)0xfa01)
#define     DMA_M2M_STA             (*(unsigned char volatile xdata *)0xfa02)
#define     DMA_M2M_AMT             (*(unsigned char volatile xdata *)0xfa03)
#define     DMA_M2M_DONE            (*(unsigned char volatile xdata *)0xfa04)
#define     DMA_M2M_TXAH            (*(unsigned char volatile xdata *)0xfa05)
#define     DMA_M2M_TXAL            (*(unsigned char volatile xdata *)0xfa06)
#define     DMA_M2M_RXAH            (*(unsigned char volatile xdata *)0xfa07)
#define     DMA_M2M_RXAL            (*(unsigned char volatile xdata *)0xfa08)

#define     DMA_ADC_CFG             (*(unsigned char volatile xdata *)0xfa10)
#define     DMA_ADC_CR              (*(unsigned char volatile xdata *)0xfa11)
#define     DMA_ADC_STA             (*(unsigned char volatile xdata *)0xfa12)
#define     DMA_ADC_AMT             (*(unsigned char volatile xdata *)0xfa13)
#define     DMA_ADC_DONE            (*(unsigned char volatile xdata *)0xfa14)
#define     DMA_ADC_RXAH            (*(unsigned char volatile xdata *)0xfa17)
#define     DMA_ADC_RXAL            (*(unsigned char volatile xdata *)0xfa18)
#define     DMA_ADC_CFG2            (*(unsigned char volatile xdata *)0xfa19)
#define     DMA_ADC_CHSW0           (*(unsigned char volatile xdata *)0xfa1a)
#define     DMA_ADC_CHSW1           (*(unsigned char volatile xdata *)0xfa1b)
#define     DMA_ADC_ITVH            (*(unsigned char volatile xdata *)0xfa1e)
#define     DMA_ADC_ITVL            (*(unsigned char volatile xdata *)0xfa1f)

#define     DMA_SPI_CFG             (*(unsigned char volatile xdata *)0xfa20)
#define     DMA_SPI_CR              (*(unsigned char volatile xdata *)0xfa21)
#define     DMA_SPI_STA             (*(unsigned char volatile xdata *)0xfa22)
#define     DMA_SPI_AMT             (*(unsigned char volatile xdata *)0xfa23)
#define     DMA_SPI_DONE            (*(unsigned char volatile xdata *)0xfa24)
#define     DMA_SPI_TXAH            (*(unsigned char volatile xdata *)0xfa25)
#define     DMA_SPI_TXAL            (*(unsigned char volatile xdata *)0xfa26)
#define     DMA_SPI_RXAH            (*(unsigned char volatile xdata *)0xfa27)
#define     DMA_SPI_RXAL            (*(unsigned char volatile xdata *)0xfa28)
#define     DMA_SPI_CFG2            (*(unsigned char volatile xdata *)0xfa29)
#define     DMA_SPI_ITVH            (*(unsigned char volatile xdata *)0xfa2e)
#define     DMA_SPI_ITVL            (*(unsigned char volatile xdata *)0xfa2f)

#define     DMA_UR1T_CFG            (*(unsigned char volatile xdata *)0xfa30)
#define     DMA_UR1T_CR             (*(unsigned char volatile xdata *)0xfa31)
#define     DMA_UR1T_STA            (*(unsigned char volatile xdata *)0xfa32)
#define     DMA_UR1T_AMT            (*(unsigned char volatile xdata *)0xfa33)
#define     DMA_UR1T_DONE           (*(unsigned char volatile xdata *)0xfa34)
#define     DMA_UR1T_TXAH           (*(unsigned char volatile xdata *)0xfa35)
#define     DMA_UR1T_TXAL           (*(unsigned char volatile xdata *)0xfa36)
#define     DMA_UR1R_CFG            (*(unsigned char volatile xdata *)0xfa38)
#define     DMA_UR1R_CR             (*(unsigned char volatile xdata *)0xfa39)
#define     DMA_UR1R_STA            (*(unsigned char volatile xdata *)0xfa3a)
#define     DMA_UR1R_AMT            (*(unsigned char volatile xdata *)0xfa3b)
#define     DMA_UR1R_DONE           (*(unsigned char volatile xdata *)0xfa3c)
#define     DMA_UR1R_RXAH           (*(unsigned char volatile xdata *)0xfa3d)
#define     DMA_UR1R_RXAL           (*(unsigned char volatile xdata *)0xfa3e)

#define     DMA_UR2T_CFG            (*(unsigned char volatile xdata *)0xfa40)
#define     DMA_UR2T_CR             (*(unsigned char volatile xdata *)0xfa41)
#define     DMA_UR2T_STA            (*(unsigned char volatile xdata *)0xfa42)
#define     DMA_UR2T_AMT            (*(unsigned char volatile xdata *)0xfa43)
#define     DMA_UR2T_DONE           (*(unsigned char volatile xdata *)0xfa44)
#define     DMA_UR2T_TXAH           (*(unsigned char volatile xdata *)0xfa45)
#define     DMA_UR2T_TXAL           (*(unsigned char volatile xdata *)0xfa46)
#define     DMA_UR2R_CFG            (*(unsigned char volatile xdata *)0xfa48)
#define     DMA_UR2R_CR             (*(unsigned char volatile xdata *)0xfa49)
#define     DMA_UR2R_STA            (*(unsigned char volatile xdata *)0xfa4a)
#define     DMA_UR2R_AMT            (*(unsigned char volatile xdata *)0xfa4b)
#define     DMA_UR2R_DONE           (*(unsigned char volatile xdata *)0xfa4c)
#define     DMA_UR2R_RXAH           (*(unsigned char volatile xdata *)0xfa4d)
#define     DMA_UR2R_RXAL           (*(unsigned char volatile xdata *)0xfa4e)

#define     DMA_UR3T_CFG            (*(unsigned char volatile xdata *)0xfa50)
#define     DMA_UR3T_CR             (*(unsigned char volatile xdata *)0xfa51)
#define     DMA_UR3T_STA            (*(unsigned char volatile xdata *)0xfa52)
#define     DMA_UR3T_AMT            (*(unsigned char volatile xdata *)0xfa53)
#define     DMA_UR3T_DONE           (*(unsigned char volatile xdata *)0xfa54)
#define     DMA_UR3T_TXAH           (*(unsigned char volatile xdata *)0xfa55)
#define     DMA_UR3T_TXAL           (*(unsigned char volatile xdata *)0xfa56)
#define     DMA_UR3R_CFG            (*(unsigned char volatile xdata *)0xfa58)
#define     DMA_UR3R_CR             (*(unsigned char volatile xdata *)0xfa59)
#define     DMA_UR3R_STA            (*(unsigned char volatile xdata *)0xfa5a)
#define     DMA_UR3R_AMT            (*(unsigned char volatile xdata *)0xfa5b)
#define     DMA_UR3R_DONE           (*(unsigned char volatile xdata *)0xfa5c)
#define     DMA_UR3R_RXAH           (*(unsigned char volatile xdata *)0xfa5d)
#define     DMA_UR3R_RXAL           (*(unsigned char volatile xdata *)0xfa5e)

#define     DMA_UR4T_CFG            (*(unsigned char volatile xdata *)0xfa60)
#define     DMA_UR4T_CR             (*(unsigned char volatile xdata *)0xfa61)
#define     DMA_UR4T_STA            (*(unsigned char volatile xdata *)0xfa62)
#define     DMA_UR4T_AMT            (*(unsigned char volatile xdata *)0xfa63)
#define     DMA_UR4T_DONE           (*(unsigned char volatile xdata *)0xfa64)
#define     DMA_UR4T_TXAH           (*(unsigned char volatile xdata *)0xfa65)
#define     DMA_UR4T_TXAL           (*(unsigned char volatile xdata *)0xfa66)
#define     DMA_UR4R_CFG            (*(unsigned char volatile xdata *)0xfa68)
#define     DMA_UR4R_CR             (*(unsigned char volatile xdata *)0xfa69)
#define     DMA_UR4R_STA            (*(unsigned char volatile xdata *)0xfa6a)
#define     DMA_UR4R_AMT            (*(unsigned char volatile xdata *)0xfa6b)
#define     DMA_UR4R_DONE           (*(unsigned char volatile xdata *)0xfa6c)
#define     DMA_UR4R_RXAH           (*(unsigned char volatile xdata *)0xfa6d)
#define     DMA_UR4R_RXAL           (*(unsigned char volatile xdata *)0xfa6e)

#define     DMA_LCM_CFG             (*(unsigned char volatile xdata *)0xfa70)
#define     DMA_LCM_CR              (*(unsigned char volatile xdata *)0xfa71)
#define     DMA_LCM_STA             (*(unsigned char volatile xdata *)0xfa72)
#define     DMA_LCM_AMT             (*(unsigned char volatile xdata *)0xfa73)
#define     DMA_LCM_DONE            (*(unsigned char volatile xdata *)0xfa74)
#define     DMA_LCM_TXAH            (*(unsigned char volatile xdata *)0xfa75)
#define     DMA_LCM_TXAL            (*(unsigned char volatile xdata *)0xfa76)
#define     DMA_LCM_RXAH            (*(unsigned char volatile xdata *)0xfa77)
#define     DMA_LCM_RXAL            (*(unsigned char volatile xdata *)0xfa78)
#define     DMA_LCM_ITVH            (*(unsigned char volatile xdata *)0xfa7e)
#define     DMA_LCM_ITVL            (*(unsigned char volatile xdata *)0xfa7f)

#define     DMA_M2M_AMTH            (*(unsigned char volatile xdata *)0xfa80)
#define     DMA_M2M_DONEH           (*(unsigned char volatile xdata *)0xfa81)
#define     DMA_ADC_AMTH            (*(unsigned char volatile xdata *)0xfa82)
#define     DMA_ADC_DONEH           (*(unsigned char volatile xdata *)0xfa83)
#define     DMA_SPI_AMTH            (*(unsigned char volatile xdata *)0xfa84)
#define     DMA_SPI_DONEH           (*(unsigned char volatile xdata *)0xfa85)
#define     DMA_LCM_AMTH            (*(unsigned char volatile xdata *)0xfa86)
#define     DMA_LCM_DONEH           (*(unsigned char volatile xdata *)0xfa87)
#define     DMA_UR1T_AMTH           (*(unsigned char volatile xdata *)0xfa88)
#define     DMA_UR1T_DONEH          (*(unsigned char volatile xdata *)0xfa89)
#define     DMA_UR1R_AMTH           (*(unsigned char volatile xdata *)0xfa8a)
#define     DMA_UR1R_DONEH          (*(unsigned char volatile xdata *)0xfa8b)
#define     DMA_UR2T_AMTH           (*(unsigned char volatile xdata *)0xfa8c)
#define     DMA_UR2T_DONEH          (*(unsigned char volatile xdata *)0xfa8d)
#define     DMA_UR2R_AMTH           (*(unsigned char volatile xdata *)0xfa8e)
#define     DMA_UR2R_DONEH          (*(unsigned char volatile xdata *)0xfa8f)
#define     DMA_UR3T_AMTH           (*(unsigned char volatile xdata *)0xfa90)
#define     DMA_UR3T_DONEH          (*(unsigned char volatile xdata *)0xfa91)
#define     DMA_UR3R_AMTH           (*(unsigned char volatile xdata *)0xfa92)
#define     DMA_UR3R_DONEH          (*(unsigned char volatile xdata *)0xfa93)
#define     DMA_UR4T_AMTH           (*(unsigned char volatile xdata *)0xfa94)
#define     DMA_UR4T_DONEH          (*(unsigned char volatile xdata *)0xfa95)
#define     DMA_UR4R_AMTH           (*(unsigned char volatile xdata *)0xfa96)
#define     DMA_UR4R_DONEH          (*(unsigned char volatile xdata *)0xfa97)

#define     DMA_I2CT_CFG            (*(unsigned char volatile xdata *)0xfa98)
#define     DMA_I2CT_CR             (*(unsigned char volatile xdata *)0xfa99)
#define     DMA_I2CT_STA            (*(unsigned char volatile xdata *)0xfa9a)
#define     DMA_I2CT_AMT            (*(unsigned char volatile xdata *)0xfa9b)
#define     DMA_I2CT_DONE           (*(unsigned char volatile xdata *)0xfa9c)
#define     DMA_I2CT_TXAH           (*(unsigned char volatile xdata *)0xfa9d)
#define     DMA_I2CT_TXAL           (*(unsigned char volatile xdata *)0xfa9e)
#define     DMA_I2CR_CFG            (*(unsigned char volatile xdata *)0xfaa0)
#define     DMA_I2CR_CR             (*(unsigned char volatile xdata *)0xfaa1)
#define     DMA_I2CR_STA            (*(unsigned char volatile xdata *)0xfaa2)
#define     DMA_I2CR_AMT            (*(unsigned char volatile xdata *)0xfaa3)
#define     DMA_I2CR_DONE           (*(unsigned char volatile xdata *)0xfaa4)
#define     DMA_I2CR_RXAH           (*(unsigned char volatile xdata *)0xfaa5)
#define     DMA_I2CR_RXAL           (*(unsigned char volatile xdata *)0xfaa6)

#define     DMA_I2CT_AMTH           (*(unsigned char volatile xdata *)0xfaa8)
#define     DMA_I2CT_DONEH          (*(unsigned char volatile xdata *)0xfaa9)
#define     DMA_I2CR_AMTH           (*(unsigned char volatile xdata *)0xfaaa)
#define     DMA_I2CR_DONEH          (*(unsigned char volatile xdata *)0xfaab)
#define     DMA_I2C_CR              (*(unsigned char volatile xdata *)0xfaad)
#define     DMA_I2C_ST1             (*(unsigned char volatile xdata *)0xfaae)
#define     DMA_I2C_ST2             (*(unsigned char volatile xdata *)0xfaaf)

#define     DMA_I2ST_CFG            (*(unsigned char volatile xdata *)0xfab0)
#define     DMA_I2ST_CR             (*(unsigned char volatile xdata *)0xfab1)
#define     DMA_I2ST_STA            (*(unsigned char volatile xdata *)0xfab2)
#define     DMA_I2ST_AMT            (*(unsigned char volatile xdata *)0xfab3)
#define     DMA_I2ST_DONE           (*(unsigned char volatile xdata *)0xfab4)
#define     DMA_I2ST_TXAH           (*(unsigned char volatile xdata *)0xfab5)
#define     DMA_I2ST_TXAL           (*(unsigned char volatile xdata *)0xfab6)
#define     DMA_I2SR_CFG            (*(unsigned char volatile xdata *)0xfab8)
#define     DMA_I2SR_CR             (*(unsigned char volatile xdata *)0xfab9)
#define     DMA_I2SR_STA            (*(unsigned char volatile xdata *)0xfaba)
#define     DMA_I2SR_AMT            (*(unsigned char volatile xdata *)0xfabb)
#define     DMA_I2SR_DONE           (*(unsigned char volatile xdata *)0xfabc)
#define     DMA_I2SR_RXAH           (*(unsigned char volatile xdata *)0xfabd)
#define     DMA_I2SR_RXAL           (*(unsigned char volatile xdata *)0xfabe)

#define     DMA_I2ST_AMTH           (*(unsigned char volatile xdata *)0xfac0)
#define     DMA_I2ST_DONEH          (*(unsigned char volatile xdata *)0xfac1)
#define     DMA_I2SR_AMTH           (*(unsigned char volatile xdata *)0xfac2)
#define     DMA_I2SR_DONEH          (*(unsigned char volatile xdata *)0xfac3)
#define     DMA_I2C_ITVH            (*(unsigned char volatile xdata *)0xfac4)
#define     DMA_I2C_ITVL            (*(unsigned char volatile xdata *)0xfac5)
#define     DMA_I2S_ITVH            (*(unsigned char volatile xdata *)0xfac6)
#define     DMA_I2S_ITVL            (*(unsigned char volatile xdata *)0xfac7)
#define     DMA_UR1_ITVH            (*(unsigned char volatile xdata *)0xfac8)
#define     DMA_UR1_ITVL            (*(unsigned char volatile xdata *)0xfac9)
#define     DMA_UR2_ITVH            (*(unsigned char volatile xdata *)0xfaca)
#define     DMA_UR2_ITVL            (*(unsigned char volatile xdata *)0xfacb)
#define     DMA_UR3_ITVH            (*(unsigned char volatile xdata *)0xfacc)
#define     DMA_UR3_ITVL            (*(unsigned char volatile xdata *)0xfacd)
#define     DMA_UR4_ITVH            (*(unsigned char volatile xdata *)0xface)
#define     DMA_UR4_ITVL            (*(unsigned char volatile xdata *)0xfacf)

#define     DMA_QSPI_CFG            (*(unsigned char volatile xdata *)0xfad0)
#define     DMA_QSPI_CR             (*(unsigned char volatile xdata *)0xfad1)
#define     DMA_QSPI_STA            (*(unsigned char volatile xdata *)0xfad2)
#define     DMA_QSPI_AMT            (*(unsigned char volatile xdata *)0xfad3)
#define     DMA_QSPI_DONE           (*(unsigned char volatile xdata *)0xfad4)
#define     DMA_QSPI_TXAH           (*(unsigned char volatile xdata *)0xfad5)
#define     DMA_QSPI_TXAL           (*(unsigned char volatile xdata *)0xfad6)
#define     DMA_QSPI_RXAH           (*(unsigned char volatile xdata *)0xfad7)
#define     DMA_QSPI_RXAL           (*(unsigned char volatile xdata *)0xfad8)
#define     DMA_QSPI_AMTH           (*(unsigned char volatile xdata *)0xfadb)
#define     DMA_QSPI_DONEH          (*(unsigned char volatile xdata *)0xfadc)
#define     DMA_QSPI_ITVH           (*(unsigned char volatile xdata *)0xfade)
#define     DMA_QSPI_ITVL           (*(unsigned char volatile xdata *)0xfadf)

#define     DMA_P2P_CR1             (*(unsigned char volatile xdata *)0xfaf0)
#define     DMA_P2P_CR2             (*(unsigned char volatile xdata *)0xfaf1)
#define     DMA_ARB_CFG             (*(unsigned char volatile xdata *)0xfaf8)
#define     DMA_ARB_STA             (*(unsigned char volatile xdata *)0xfaf9)

/////////////////////////////////////////////////
//7E:F900H-7E:F9FFH
/////////////////////////////////////////////////

#define     QSPI_CR1                (*(unsigned char volatile xdata *)0xf900)
#define     QSPI_CR2                (*(unsigned char volatile xdata *)0xf901)
#define     QSPI_CR3                (*(unsigned char volatile xdata *)0xf902)
#define     QSPI_CR4                (*(unsigned char volatile xdata *)0xf903)
#define     QSPI_DCR1               (*(unsigned char volatile xdata *)0xf904)
#define     QSPI_DCR2               (*(unsigned char volatile xdata *)0xf905)
#define     QSPI_SR1                (*(unsigned char volatile xdata *)0xf906)
#define     QSPI_SR2                (*(unsigned char volatile xdata *)0xf907)
#define     QSPI_FCR                (*(unsigned char volatile xdata *)0xf908)
#define     QSPI_HCR1               (*(unsigned char volatile xdata *)0xf909)
#define     QSPI_HCR2               (*(unsigned char volatile xdata *)0xf90a)
#define     QSPI_DLR1               (*(unsigned char volatile xdata *)0xf910)
#define     QSPI_DLR2               (*(unsigned char volatile xdata *)0xf911)
#define     QSPI_CCR1               (*(unsigned char volatile xdata *)0xf914)
#define     QSPI_CCR2               (*(unsigned char volatile xdata *)0xf915)
#define     QSPI_CCR3               (*(unsigned char volatile xdata *)0xf916)
#define     QSPI_CCR4               (*(unsigned char volatile xdata *)0xf917)
#define     QSPI_AR1                (*(unsigned char volatile xdata *)0xf918)
#define     QSPI_AR2                (*(unsigned char volatile xdata *)0xf919)
#define     QSPI_AR3                (*(unsigned char volatile xdata *)0xf91a)
#define     QSPI_AR4                (*(unsigned char volatile xdata *)0xf91b)
#define     QSPI_ABR                (*(unsigned char volatile xdata *)0xf91c)
#define     QSPI_DR                 (*(unsigned char volatile xdata *)0xf920)
#define     QSPI_PSMKR1             (*(unsigned char volatile xdata *)0xf924)
#define     QSPI_PSMAR1             (*(unsigned char volatile xdata *)0xf928)
#define     QSPI_PIR1               (*(unsigned char volatile xdata *)0xf92c)
#define     QSPI_PIR2               (*(unsigned char volatile xdata *)0xf92d)

#define     PWMA_ENO2               (*(unsigned char volatile xdata *)0xf930)
#define     PWMA_IOAUX2             (*(unsigned char volatile xdata *)0xf931)
#define     PWMA_CR3                (*(unsigned char volatile xdata *)0xf932)
#define     PWMA_SR3                (*(unsigned char volatile xdata *)0xf933)
#define     PWMA_CCER3              (*(unsigned char volatile xdata *)0xf934)
#define     PWMA_CCMR1X             (*(unsigned char volatile xdata *)0xf938)
#define     PWMA_CCMR2X             (*(unsigned char volatile xdata *)0xf939)
#define     PWMA_CCMR3X             (*(unsigned char volatile xdata *)0xf93a)
#define     PWMA_CCMR4X             (*(unsigned char volatile xdata *)0xf93b)
#define     PWMA_CCMR5              (*(unsigned char volatile xdata *)0xf93c)
#define     PWMA_CCMR5X             (*(unsigned char volatile xdata *)0xf93d)
#define     PWMA_CCMR6              (*(unsigned char volatile xdata *)0xf93e)
#define     PWMA_CCMR6X             (*(unsigned char volatile xdata *)0xf93f)
#define     PWMA_CCR5H              (*(unsigned char volatile xdata *)0xf940)
#define     PWMA_CCR5L              (*(unsigned char volatile xdata *)0xf941)
#define     PWMA_CCR5X              (*(unsigned char volatile xdata *)0xf942)
#define     PWMA_CCR6H              (*(unsigned char volatile xdata *)0xf943)
#define     PWMA_CCR6L              (*(unsigned char volatile xdata *)0xf944)
#define     PWMA_DER                (*(unsigned char volatile xdata *)0xf948)
#define     PWMA_DBA                (*(unsigned char volatile xdata *)0xf949)
#define     PWMA_DBL                (*(unsigned char volatile xdata *)0xf94a)
#define     PWMA_DMACR              (*(unsigned char volatile xdata *)0xf94b)

#define     DMA_PWMAT_CFG           (*(unsigned char volatile xdata *)0xf980)
#define     DMA_PWMAT_CR            (*(unsigned char volatile xdata *)0xf981)
#define     DMA_PWMAT_STA           (*(unsigned char volatile xdata *)0xf982)
#define     DMA_PWMAT_AMTH          (*(unsigned char volatile xdata *)0xf984)
#define     DMA_PWMAT_AMT           (*(unsigned char volatile xdata *)0xf985)
#define     DMA_PWMAT_DONEH         (*(unsigned char volatile xdata *)0xf986)
#define     DMA_PWMAT_DONE          (*(unsigned char volatile xdata *)0xf987)
#define     DMA_PWMAT_TXAH          (*(unsigned char volatile xdata *)0xf988)
#define     DMA_PWMAT_TXAL          (*(unsigned char volatile xdata *)0xf989)
#define     DMA_PWMA_ITVH           (*(unsigned char volatile xdata *)0xf98e)
#define     DMA_PWMA_ITVL           (*(unsigned char volatile xdata *)0xf98f)

#define     DMA_PWMAR_CFG           (*(unsigned char volatile xdata *)0xf990)
#define     DMA_PWMAR_CR            (*(unsigned char volatile xdata *)0xf991)
#define     DMA_PWMAR_STA           (*(unsigned char volatile xdata *)0xf992)
#define     DMA_PWMAR_AMTH          (*(unsigned char volatile xdata *)0xf994)
#define     DMA_PWMAR_AMT           (*(unsigned char volatile xdata *)0xf995)
#define     DMA_PWMAR_DONEH         (*(unsigned char volatile xdata *)0xf996)
#define     DMA_PWMAR_DONE          (*(unsigned char volatile xdata *)0xf997)
#define     DMA_PWMAR_RXAH          (*(unsigned char volatile xdata *)0xf998)
#define     DMA_PWMAR_RXAL          (*(unsigned char volatile xdata *)0xf999)

/////////////////////////////////////////////////
//USB Control Regiter
/////////////////////////////////////////////////

#define     USBBASE                 0
#define     FADDR                   (USBBASE + 0)
#define     UPDATE                  0x80
#define     POWER                   (USBBASE + 1)
#define     ISOUD                   0x80
#define     USBRST                  0x08
#define     USBRSU                  0x04
#define     USBSUS                  0x02
#define     ENSUS                   0x01
#define     INTRIN1                 (USBBASE + 2)
#define     EP5INIF                 0x20
#define     EP4INIF                 0x10
#define     EP3INIF                 0x08
#define     EP2INIF                 0x04
#define     EP1INIF                 0x02
#define     EP0IF                   0x01
#define     INTROUT1                (USBBASE + 4)
#define     EP5OUTIF                0x20
#define     EP4OUTIF                0x10
#define     EP3OUTIF                0x08
#define     EP2OUTIF                0x04
#define     EP1OUTIF                0x02
#define     INTRUSB                 (USBBASE + 6)
#define     SOFIF                   0x08
#define     RSTIF                   0x04
#define     RSUIF                   0x02
#define     SUSIF                   0x01
#define     INTRIN1E                (USBBASE + 7)
#define     EP5INIE                 0x20
#define     EP4INIE                 0x10
#define     EP3INIE                 0x08
#define     EP2INIE                 0x04
#define     EP1INIE                 0x02
#define     EP0IE                   0x01
#define     INTROUT1E               (USBBASE + 9)
#define     EP5OUTIE                0x20
#define     EP4OUTIE                0x10
#define     EP3OUTIE                0x08
#define     EP2OUTIE                0x04
#define     EP1OUTIE                0x02
#define     INTRUSBE                (USBBASE + 11)
#define     SOFIE                   0x08
#define     RSTIE                   0x04
#define     RSUIE                   0x02
#define     SUSIE                   0x01
#define     FRAME1                  (USBBASE + 12)
#define     FRAME2                  (USBBASE + 13)
#define     INDEX                   (USBBASE + 14)
#define     INMAXP                  (USBBASE + 16)
#define     CSR0                    (USBBASE + 17)
#define     SSUEND                  0x80
#define     SOPRDY                  0x40
#define     SDSTL                   0x20
#define     SUEND                   0x10
#define     DATEND                  0x08
#define     STSTL                   0x04
#define     IPRDY                   0x02
#define     OPRDY                   0x01
#define     INCSR1                  (USBBASE + 17)
#define     INCLRDT                 0x40
#define     INSTSTL                 0x20
#define     INSDSTL                 0x10
#define     INFLUSH                 0x08
#define     INUNDRUN                0x04
#define     INFIFONE                0x02
#define     INIPRDY                 0x01
#define     INCSR2                  (USBBASE + 18)
#define     INAUTOSET               0x80
#define     INISO                   0x40
#define     INMODEIN                0x20
#define     INMODEOUT               0x00
#define     INENDMA                 0x10
#define     INFCDT                  0x08
#define     OUTMAXP                 (USBBASE + 19)
#define     OUTCSR1                 (USBBASE + 20)
#define     OUTCLRDT                0x80
#define     OUTSTSTL                0x40
#define     OUTSDSTL                0x20
#define     OUTFLUSH                0x10
#define     OUTDATERR               0x08
#define     OUTOVRRUN               0x04
#define     OUTFIFOFUL              0x02
#define     OUTOPRDY                0x01
#define     OUTCSR2                 (USBBASE + 21)
#define     OUTAUTOCLR              0x80
#define     OUTISO                  0x40
#define     OUTENDMA                0x20
#define     OUTDMAMD                0x10
#define     COUNT0                  (USBBASE + 22)
#define     OUTCOUNT1               (USBBASE + 22)
#define     OUTCOUNT2               (USBBASE + 23)
#define     FIFO0                   (USBBASE + 32)
#define     FIFO1                   (USBBASE + 33)
#define     FIFO2                   (USBBASE + 34)
#define     FIFO3                   (USBBASE + 35)
#define     FIFO4                   (USBBASE + 36)
#define     FIFO5                   (USBBASE + 37)
#define     UTRKCTL                 (USBBASE + 48)
#define     UTRKSTS                 (USBBASE + 49)

/////////////////////////////////////////////////
//Interrupt Vector
/////////////////////////////////////////////////

#define     INT0_VECTOR             0       //0003H
#define     TMR0_VECTOR             1       //000BH
#define     INT1_VECTOR             2       //0013H
#define     TMR1_VECTOR             3       //001BH
#define     UART1_VECTOR            4       //0023H
#define     ADC_VECTOR              5       //002BH
#define     LVD_VECTOR              6       //0033H
#define     PCA_VECTOR              7       //003BH
#define     UART2_VECTOR            8       //0043H
#define     SPI_VECTOR              9       //004BH
#define     INT2_VECTOR             10      //0053H
#define     INT3_VECTOR             11      //005BH
#define     TMR2_VECTOR             12      //0063H
#define     USER_VECTOR             13      //006BH
#define     INT4_VECTOR             16      //0083H
#define     UART3_VECTOR            17      //008BH
#define     UART4_VECTOR            18      //0093H
#define     TMR3_VECTOR             19      //009BH
#define     TMR4_VECTOR             20      //00A3H
#define     CMP_VECTOR              21      //00ABH
#define     I2C_VECTOR              24      //00C3H
#define     USB_VECTOR              25      //00CBH
#define     PWMA_VECTOR             26      //00D3H
#define     PWMB_VECTOR             27      //00DBH

#define     RTC_VECTOR              36      //0123H
#define     P0INT_VECTOR            37      //012BH
#define     P1INT_VECTOR            38      //0133H
#define     P2INT_VECTOR            39      //013BH
#define     P3INT_VECTOR            40      //0143H
#define     P4INT_VECTOR            41      //014BH
#define     P5INT_VECTOR            42      //0153H
#define     P6INT_VECTOR            43      //015BH
#define     P7INT_VECTOR            44      //0163H
#define     DMA_M2M_VECTOR          47      //017BH
#define     DMA_ADC_VECTOR          48      //0183H
#define     DMA_SPI_VECTOR          49      //018BH
#define     DMA_UR1T_VECTOR         50      //0193H
#define     DMA_UR1R_VECTOR         51      //019BH
#define     DMA_UR2T_VECTOR         52      //01A3H
#define     DMA_UR2R_VECTOR         53      //01ABH
#define     DMA_UR3T_VECTOR         54      //01B3H
#define     DMA_UR3R_VECTOR         55      //01BBH
#define     DMA_UR4T_VECTOR         56      //01C3H
#define     DMA_UR4R_VECTOR         57      //01CBH
#define     DMA_LCM_VECTOR          58      //01D3H
#define     LCM_VECTOR              59      //01DBH
#define     DMA_I2CT_VECTOR         60      //01E3H
#define     DMA_I2CR_VECTOR         61      //01EBH
#define     I2S_VECTOR              62      //01F3H
#define     DMA_I2ST_VECTOR         63      //01FBH
#define     DMA_I2SR_VECTOR         64      //0203H
#define     DMA_QSPI_VECTOR         65      //020BH
#define     QSPI_VECTOR             66      //0213H
#define     TMR11_VECTOR            67      //021BH
#define     DMA_PWMAT_VECTOR        72      //0243H
#define     DMA_PWMAR_VECTOR        73      //024BH

/////////////////////////////////////////////////

#define	EAXSFR()		P_SW2 |= 0x80		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
#define	EAXRAM()		P_SW2 &= ~0x80		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */

/////////////////////////////////////////////////
#define NOP1()  _nop_()
#define NOP2()  NOP1(),NOP1()
#define NOP3()  NOP2(),NOP1()
#define NOP4()  NOP3(),NOP1()
#define NOP5()  NOP4(),NOP1()
#define NOP6()  NOP5(),NOP1()
#define NOP7()  NOP6(),NOP1()
#define NOP8()  NOP7(),NOP1()
#define NOP9()  NOP8(),NOP1()
#define NOP10() NOP9(),NOP1()
#define NOP11() NOP10(),NOP1()
#define NOP12() NOP11(),NOP1()
#define NOP13() NOP12(),NOP1()
#define NOP14() NOP13(),NOP1()
#define NOP15() NOP14(),NOP1()
#define NOP16() NOP15(),NOP1()
#define NOP17() NOP16(),NOP1()
#define NOP18() NOP17(),NOP1()
#define NOP19() NOP18(),NOP1()
#define NOP20() NOP19(),NOP1()
#define NOP21() NOP20(),NOP1()
#define NOP22() NOP21(),NOP1()
#define NOP23() NOP22(),NOP1()
#define NOP24() NOP23(),NOP1()
#define NOP25() NOP24(),NOP1()
#define NOP26() NOP25(),NOP1()
#define NOP27() NOP26(),NOP1()
#define NOP28() NOP27(),NOP1()
#define NOP29() NOP28(),NOP1()
#define NOP30() NOP29(),NOP1()
#define NOP31() NOP30(),NOP1()
#define NOP32() NOP31(),NOP1()
#define NOP33() NOP32(),NOP1()
#define NOP34() NOP33(),NOP1()
#define NOP35() NOP34(),NOP1()
#define NOP36() NOP35(),NOP1()
#define NOP37() NOP36(),NOP1()
#define NOP38() NOP37(),NOP1()
#define NOP39() NOP38(),NOP1()
#define NOP40() NOP39(),NOP1()
#define NOP(N)  NOP##N()

/////////////////////////////////////////////////


#endif

