/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#ifndef		__CONFIG_H
#define		__CONFIG_H

/** 接线图
 * 芯片: STC8H17K, 3.3v
   1.2:LowLED	 	 1.1:BAT-SUN --TxD2
   1.3:IO-White	 1.0:LED-4   --RxD2
   1.4:IO-RED	 	 3.7: KEY-brightness
   1.5:IO-YELLO	 3.6: KEY-MAIN
   1.6:IO-BLUE	 3.5: BAT-ADC
   1.7:WORKLED	 3.4: LED-3
   5.4			 		 3.3: LED-2
   vcc			 		 3.2: LED-1
   adc-ref	     3.1: TxD1
   gnd			 		 3.0: RxD1

   IO口配置:
   P1:
   --P1.2 ~ P1.7: 推挽输出
   --P1.0 ~ P1.1: 高阻输出，ADC输入测量

   P3:
   --P3.0~P3.1, P3.6~P3.7: 双向口
   --P3.2~P3.5: 推挽输出


 左引脚：
    T2/SS/PWM2P/P1.2
    T2CLKO/MOSI/PWM2N/P1.3   -IO-White
    I2CSDA/MISO/PWM3P/P1.4   -IO-RED
    I2CSCL/SCLK/PWM3N/P1.5   -IO-YELLO
    XTALO/MCLKO_2/RxD_3/PWM4P/P1.6  IO-BLUE
    XTALI/TxD_3/PWM5_2/PWM4N/P1.7
    MCLKO/nRST/PWM6_2/P5.4
右引脚：
    P1.1/ADC1/TxD2/PWM1N
    P1.0/ADC0/RxD2/PWM1P
    P3.7/INT3/TxD_2/CMP+
    P3.6/ADC14/INT2/RxD_2/CMP-
    P3.5/ADC13/T1/T0CLKO/SS_4/PWMFLT/PWMFLT2
    P3.4/ADC12/T0/T1CLKO/MOSI_4/PWM4P_2/PWM8_2/CMPO
    P3.3/ADC11/INT1/MISO_4/I2CSDA_4/PWM4N_2/PWM7_2
    P3.2/ADC10/INT0/SCLK_4/I2CSCL_4/PWMETI/PWMETI2
    P3.1/ADC9/TxD
    P3.0/ADC8/RxD/INT4
*/

//========================================================================
//                               主时钟定义
//========================================================================

#define MAIN_Fosc		22118400L	//定义主时钟
//#define MAIN_Fosc		12000000L	//定义主时钟
//#define MAIN_Fosc		11059200L	//定义主时钟
//#define MAIN_Fosc		 5529600L	//定义主时钟
//#define MAIN_Fosc		24000000L	//定义主时钟
#define Baudrate 115200L
#define TM (65536 - (MAIN_Fosc / Baudrate / 4))

//========================================================================
//                                头文件
//========================================================================

#include "type_def.h"
#include "STC8H.H"
#include <intrins.h>
#include <stdlib.h>
#include <stdio.h>

//========================================================================
//                             外部函数和变量声明
//========================================================================


#endif
