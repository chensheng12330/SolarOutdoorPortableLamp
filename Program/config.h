/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#ifndef		__CONFIG_H
#define		__CONFIG_H

/** 接线图
 * 芯片: Ai8051, 3.3v
  1.1 :RGB-LED | pwm52/PWM1N/CCP2/T2CLKO/ADC1/P1.1
  1.2:LowLED   | QSPIIO3/PWMETI2_4/PWMETI1_4/PWM2P/ECI/RxD2/ADC2/P1.2
  1.3:IO-White | QSPIIO2/PWM6_2/PWM2N/CP0/TxD2/ADC3/P1.3
  1.4:IO-RED   | i2sws2/QSPINCS/PWM3P/CCP1/sda2/SS/ADC4/P1.4
  1.5:IO-YELLO | 2ssd2/QSPIIO0/pwm72/PWM3N/scl2/MOSI/ADC5/P1.5
  1.6:IO-BLUE  | I2SMCLK_4/I2SMCLK_2/QSPIIO1/PWM4P/MISO/RxD_3/ADC6/P1.6
  1.7:WORKLED  | I2SCK_2/QSPICLK/PWM8_2/PWM4N/SCLK/TxD_3/ADC7/P1.7
  3.0: RxD1
  3.1: TxD1
  3.2: LED-1   | I2SCK/PWM_ETI2/PWM_ETI1/SCL_4/SCLK_4/INT0/P3.2
  3.3: LED-2   | PWMAPS5/I2SMCLK/SDA_4/MISO_4/INT1/P3.3
  3.4: LED-3   | PWMAPS6/I2SSD/MOSI_4/T1CLKO/T0/P3.4
  3.5: LED-4   | I2SWS/PWMFLT/SS_4/T0CLKO/T1/P3.5
  3.6: KEY-brightness(亮度)  |P3.6/INT2/WR_2/RxD_2
  3.7: KEY-MAIN(菜单)        |P3.7/INT3/RD_2/TxD_2
  0.0 : ADC_BAT       |PWM1P_2/RxD3/AD0/ADC8/P0.
  0.1 : ADC_SUN       |PWM5/PWM1N_2/TxD3/AD1/ADC9/P0.1
  0.2 : ADC_ExtPower  |PWM2P_2/RxD4/AD2/ADC10/P0.2
  0.3 : ADC_LightSen  |PWM6/PWM2N_2/TxD4/AD3/ADC11/P0.3
  0.4 : ADC_Temp      |P0.4/ADC12/AD4/T3/PWM3P_2
  5.2 : RGB-KEY       |QSPIIO2_2/PWM7_4/RxD4_2/P5.2
  4.2 : RxD2 (UART2)  |QSPIIO1_2/CCP0_2/MISO_3/RxD2_2/WR/P4.2
  4.3 : TxD2 (UART2)  |I2SCK_4/QSPICLK_2/CCP1_2/SCLK_3/TxD2_2/RxD_4/P4.3
  4.7 : Restart-Key   |PWMAPS6_2/QSPINCS_3/ADC_ETR/MCLKO/nRST/P4.7

  IO口配置:
  P1:
  --P1.2 ~ P1.7: 推挽输出
  --P1.0 ~ P1.1: 高阻输出，ADC输入测量

  P3:
  --P3.0~P3.1, P3.6~P3.7: 双向口
  --P3.2~P3.5: 推挽输出
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
