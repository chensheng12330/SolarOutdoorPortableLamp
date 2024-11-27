
/**
 * @file main.c
 * @author sherwin.chen (chensheng12330@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-04-01
 *
 * @copyright Copyright (c) 2024
 *
 */

/** 接线图
 * 芯片: Ai8051


实现功能
- 通过按键1控制灯光的开与关
  - 短按-显示当前电量
	- 1. 白灯
	- 2. 黄灯
	- 3. 白黄灯
	- 4. 警示灯
  - 长按
	- 1. 关机，关闭所有功能
	- 2. 开机并显示电量
- 通过按键2控制灯光的亮度
  - 短按循环调节
	- 1. 100%
	- 2. 75%
	- 3. 50%
	- 4. 25%
  - 长按恢复默认值 100%
*/

#define DEBUG_MODE 1 // 开发模式

#include "config.h"
#include "STC8G_H_ADC.h"
// #include	"STC8G_H_GPIO.h"
#include "STC8H_PWM.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_UART.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Switch.h"
#include "STC8G_H_Timer.h"
#include "STC8G_H_Exti.h"

void KeyScan(void);
void displayBatterPower(float inVol);
void SysOpen();
void SysClose();

/*************	功能说明	**************

本例程基于STC8H8K64U为主控芯片的实验箱8进行编写测试，STC8G、STC8H系列芯片可通用参考.
本程序演示多路ADC查询采样，通过串口2发送给上位机，波特率115200,N,8,1。
下载时, 选择时钟 22.1184MHz (可以在配置文件"config.h"中修改).

- 硬件资源
1. pwm
2. timer
3. adc
4. uart
5. key1,key2,key3

- 状态机
1. 按键Key2输出PWM占空比: PWM100,PWM75,PWM50,PWM25 [3.6:KEY-brightness]
2. 按键Key1输出LED模式: LED_Power_Show,LED_White,LED_YELLO, LED_RED_BLUE
3. 按钮key3调节RGB显示模式


- 中断
1. timer0按键检测中断
2. timer1


- 开发计划
1. 按键监控
2. 输出IO口控制
3. pwm亮度调节
4. 8个RGB灯(RGB-WS2812B)驱动
5. RGB-KEY控制
6. 太能阳充电开启检测
7. 外部USB充电开启
8. 

RTX51-Tiny
https://blog.csdn.net/weixin_51026398/article/details/123776288?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-5-123776288-blog-92062159.235^v43^control&spm=1001.2101.3001.4242.4&utm_relevant_index=6
******

******************************************/

/*************	本地常量声明	**************/
#define ADC_CHANNEL 0	 // ADC通道选择
#define VOLTAGE_HIGH 125 // 高电压阈值，对应12.5V
#define VOLTAGE_LOW 85	 // 低电压阈值，对应8.5V

/*************	本地变量声明	**************/

sbit IO_LED_White = P1 ^ 3;	   // OUT-白光LED驱动控制开关，默认关
sbit IO_LED_WarnRed = P1 ^ 4;  // OUT-红警示LEDLED驱动控制开关，默认关
sbit IO_LED_YELLO = P1 ^ 5;	   // OUT-自然光LED驱动控制开关，默认关
sbit IO_LED_WarnBlue = P1 ^ 6; // OUT-蓝光LED驱动控制开关，默认关
sbit IO_LED_RGB      = P1 ^ 1; // OUT-RGB信号控制开关，默认关

#define POW_LED_OPEN 0		  // 电量LED灯开启
#define POW_LED_CLOSE 1		  // 电量LED灯关闭
sbit IO_LED_WORKLED = P1 ^ 7; // 工作指示灯
sbit IO_LED_ERR = P1 ^ 2;	  // 程序出错LED灯、低电量灯

// 按键
sbit KEY1 = P3 ^ 6; // 主菜单按键
sbit KEY2 = P3 ^ 7; // 亮度调节按键
sbit KEY3 = P5 ^ 2; // RGB模式选择按键
sbi RestartKey = P4 ^ 7; //重启

// 3.0/3.1 烧写

// 电量显示LED
sbit BAT_POW_LED4 = P1 ^ 5;
sbit BAT_POW_LED3 = P3 ^ 4;
sbit BAT_POW_LED2 = P3 ^ 3;
sbit BAT_POW_LED1 = P3 ^ 2;

sbit ADC_BAT = P0 ^ 0; // IN-电池电压 P1 ^ 1
sbit ADC_SUN = P0 ^ 1; // IN-太阳能电板电压
sbit ADC_ExtPower = P0 ^ 2; // IN-外部USB充电
sbit ADC_LightSen = P0 ^ 3; // IN-光感
sbit ADC_Temp = P0 ^ 4;		// IN-温度监控

// 4.2/4.3 日志-UART2

u16 Key1_cnt;
u16 Key2_cnt;
bit Key1_Flag;
bit Key2_Flag;
bit B_1ms; // 1ms标志
bit Key2_Short_Flag;
bit Key2_Long_Flag;

bit Key1_Function;
bit Key1_Long_Function;
bit Key2_Short_Function;
bit Key2_Long_Function;

// PWM模块
PWMx_Duty PWMA_Duty;
u16 PWMPeriod = 1000; // PWM周期设置 HZ: 1/1000  = 1ms

// 红蓝警示灯
bit CMD_Warn_Led_Flag = 0; // 默认为0
u16 B_50ms = 0;			   // time2, 中断标志

u16 LED_WORKLED_Flag = 0; // 默认值为0
u16 LED_WORKLED_50ms = 0;

u16 WLED2S_Count;
bit Red0_blue1;

u32 WorkLED2S_Count;
bit show1_off0;

u32 ADC10S_Count;
u16 ADC_Timer_ms;

enum PWMDutyLevel
{
	PWM_Duty_Level_100 = 0, // 100亮度
	PWM_Duty_Level_75 = 1,	// 75亮度
	PWM_Duty_Level_50 = 2,
	PWM_Duty_Level_25 = 3,
	PWM_Duty_Level_0 = 4
};

enum PWMDutyLevel pwm_DutyLevel;

enum CMDMenu
{
	CMD_None_Led = 0,	// 关闭所有灯
	CMD_White_Led = 1,	// 开启白灯
	CMD_Yello_Led = 2,	// 开启黄灯
	CMD_WH_YE_Led = 3,	// 黄白灯一起开
	CMD_Warn_Led = 4,	// 开启警示灯
	CMD_Sys_Close = 5,	// 系统关机
	CMD_Sys_Open = 6,	// 系统开机
	CMD_ADJ_BRI_LED = 7 // 亮度调节
};

enum CMDMenu cmd_Menu;

/*************	本地函数声明	**************/
void turnOnLEDWithCMDType(enum CMDMenu cmdMenu);
void setPWMWithLEDBrightness(enum PWMDutyLevel pwmLevel);

/*************  外部函数和变量声明 *****************/
/******************* IO配置函数 *******************/

void ______Hal__CONFIG() {}
void GPIO_config(void)
{
	// 指令版FV
	// P3-[0,1],[2,3,4]

	// 设置P3.6，P3.7, P3.5为高阻输入
	P3M0 = 0x00;
	P3M1 = 0xe0;

	// 使能P3.6，P3.7口上拉
	P3PU = 0xc0;

	//[P1]
	// p1-[1] uart2，双向口
	// p1-[0,2~7] 推挽输出，控制MOS管
	P1M0 = 0x78;
	P1M1 = 0x00;

	IO_LED_WORKLED = IO_LED_ERR = POW_LED_CLOSE;

	// P1 = 0;
	// PWM 双向IO
	IO_LED_White = IO_LED_WarnRed = IO_LED_YELLO = IO_LED_WarnBlue = 0;

	/*
		GPIO_InitTypeDef GPIO_InitStructureADC;		//结构定义
		GPIO_InitTypeDef GPIO_InitStructureDebug;
		GPIO_InitTypeDef GPIO_InitStructureControl;

		//P3-[0,1],[2,3,4]
		// AD口设置为输入口 ADC-VoluteIO: [3.2 /3.3 /3.4]
		// 3.2 ADC10
		// 3.3 ADC11
		// 3.4 ADC12
		// ---3.5 ADC13
		GPIO_InitStructureADC.Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4; // 指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
		GPIO_InitStructureADC.Mode = GPIO_HighZ;						  // 指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
		GPIO_Inilize(GPIO_P3, &GPIO_InitStructureADC);					  // 初始化


		// UART - IO : [3.6-rxd / 3.7-txd]
		// GPIO_InitStructureDebug.Pin = GPIO_Pin_6 | GPIO_Pin_7; // 指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7

		// ROM-IO: [3.1,3.0]
		GPIO_InitStructureDebug.Mode = GPIO_PullUp;			// 指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
		GPIO_Inilize(GPIO_P3, &GPIO_InitStructureDebug);	// 初始化

		// P1-[2,3]
		// 4. relay - IO : 继电器IO > P1 .2 / T2 / SS / PWM2P
		// 5. 工作指示灯 P1 .3 / T2CLKO / MOSI / PWM2N

		GPIO_InitStructureControl.Pin = GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_InitStructureControl.Mode = GPIO_OUT_PP;
		GPIO_Inilize(GPIO_P1, &GPIO_InitStructureControl);
	*/

	// iORelay = 0;
	// iOWorkLED = 1;
}

void Exti_config(void)
{
	EXTI_InitTypeDef Exti_InitStructure; // 结构定义

	Exti_InitStructure.EXTI_Mode = EXT_MODE_Fall; // 中断模式,   EXT_MODE_RiseFall,EXT_MODE_Fall
	Ext_Inilize(EXT_INT3, &Exti_InitStructure);	  // 初始化
	NVIC_INT3_Init(ENABLE, Priority_3);			  // 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3									
}

void INT3_ISR_Handler(void) interrupt INT3_VECTOR
{

	if (cmd_Menu == CMD_Sys_Close)
	{
		// 系统关闭状态
		cmd_Menu = CMD_Sys_Open;
		SysOpen();
	}
	PrintString2("INT3 event");
}

/******************* AD配置函数 *******************/
void ADC_config(void)
{
	ADC_InitTypeDef ADC_InitStructure; // 结构定义

	ADC_InitStructure.ADC_SMPduty = 31;					   // ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
	ADC_InitStructure.ADC_CsSetup = 0;					   // ADC 通道选择时间控制 0(默认),1
	ADC_InitStructure.ADC_CsHold = 1;					   // ADC 通道选择保持时间控制 0,1(默认),2,3
	ADC_InitStructure.ADC_Speed = ADC_SPEED_2X16T;		   // 设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED; // ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);					   // 初始化
	ADC_PowerControl(ENABLE);							   // ADC电源开关, ENABLE或DISABLE
	NVIC_ADC_Init(DISABLE, Priority_0);					   // 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

/***************  串口2初始化函数,调试输出 *****************/
void UART_config(void) 
{
	COMx_InitDefine COMx_InitStructure;			   // 结构定义
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; // 模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	//	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//选择波特率发生器, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2, 所以不用选择)
	COMx_InitStructure.UART_BaudRate = 115200ul;	// 波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE;		// 接收允许,   ENABLE或DISABLE
	UART_Configuration(UART2, &COMx_InitStructure); // 初始化串口2 USART1,USART2,USART3,USART4
	NVIC_UART2_Init(ENABLE, Priority_1);			// 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	UART2_SW(UART2_SW_P10_P11);						// UART2_SW_P10_P11,UART2_SW_P46_P47
}

/************************ 定时器配置 ****************************/
void Timer_config(void)
{
	TIM_InitTypeDef TIM_InitStructure; // 结构定义

	// // 定时器0做16位自动重装, 中断频率为100000HZ，中断函数从P6.7取反输出50KHZ方波信号.
	// TIM_InitStructure.TIM_Mode = TIM_16BitAutoReload;				// 指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	// TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;					// 指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	// TIM_InitStructure.TIM_ClkOut = DISABLE;							// 是否输出高速脉冲, ENABLE或DISABLE
	// TIM_InitStructure.TIM_Value = 65536UL - (MAIN_Fosc / 100000UL); // 初值,
	// TIM_InitStructure.TIM_Run = ENABLE;								// 是否初始化后启动定时器, ENABLE或DISABLE
	// Timer_Inilize(Timer0, &TIM_InitStructure);						// 初始化Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	// NVIC_Timer0_Init(ENABLE, Priority_0);							// 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

	//[按键检测信号源1ms] 定时器1做16位自动重装, 中断频率为1000HZ，中断函数从P6.6取反输出5KHZ方波信号.
	TIM_InitStructure.TIM_Mode = TIM_16BitAutoReload;			 // 指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_T1Stop
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;				 // 指定时钟源, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut = DISABLE;						 // 是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value = 65536UL - (MAIN_Fosc / 50000); // 初值,
	TIM_InitStructure.TIM_Run = ENABLE;							 // 是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer1, &TIM_InitStructure);					 // 初始化Timer1	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer1_Init(ENABLE, Priority_0);						 // 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

	//[红蓝警灯信号] [50ms]
	// // 定时器2做16位自动重装, 中断频率为100HZ，中断函数从P6.5取反输出500HZ方波信号.
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;				// 指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut = DISABLE;						// 是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value = 65536UL - (MAIN_Fosc / 1000); // 初值
	TIM_InitStructure.TIM_PS = 0;								// 8位预分频器(n+1), 0~255, (注意:并非所有系列都有此寄存器,详情请查看数据手册)
	TIM_InitStructure.TIM_Run = DISABLE;						// 是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer2, &TIM_InitStructure);					// 初始化Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer2_Init(DISABLE, NULL);							// 中断使能, ENABLE/DISABLE; 无优先级

	// // 定时器3做16位自动重装, 中断频率为100HZ，中断函数从P6.4取反输出50HZ方 波信号.
	// TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;				  // 指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	// TIM_InitStructure.TIM_ClkOut = DISABLE;							  // 是否输出高速脉冲, ENABLE或DISABLE
	// TIM_InitStructure.TIM_Value = 65536UL - (MAIN_Fosc / (100 * 12)); // 初值
	// TIM_InitStructure.TIM_PS = 0;									  // 8位预分频器(n+1), 0~255, (注意:并非所有系列都有此寄存器,详情请查看数据手册)
	// TIM_InitStructure.TIM_Run = ENABLE;								  // 是否初始化后启动定时器, ENABLE或DISABLE
	// Timer_Inilize(Timer3, &TIM_InitStructure);						  // 初始化Timer3	  Timer0,Timer1,Timer2,Timer3,Timer4
	// NVIC_Timer3_Init(ENABLE, NULL);									  // 中断使能, ENABLE/DISABLE; 无优先级

	// // 定时器4做16位自动重装, 中断频率为50HZ，中断函数从P6.3取反输出25HZ方波信号.
	// TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;				 // 指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	// TIM_InitStructure.TIM_ClkOut = DISABLE;							 // 是否输出高速脉冲, ENABLE或DISABLE
	// TIM_InitStructure.TIM_Value = 65536UL - (MAIN_Fosc / (50 * 12)); // 初值
	// TIM_InitStructure.TIM_PS = 0;									 // 8位预分频器(n+1), 0~255, (注意:并非所有系列都有此寄存器,详情请查看数据手册)
	// TIM_InitStructure.TIM_Run = ENABLE;								 // 是否初始化后启动定时器, ENABLE或DISABLE
	// Timer_Inilize(Timer4, &TIM_InitStructure);						 // 初始化Timer4	  Timer0,Timer1,Timer2,Timer3,Timer4
	// NVIC_Timer4_Init(ENABLE, NULL);									 // 中断使能, ENABLE/DISABLE; 无优先级
}

//========================================================================
// 函数: Timer0_ISR_Handler
// 描述: Timer0中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
void Timer1_ISR_Handler(void) interrupt TMR1_VECTOR // 进中断时已经清除标志
{
	// TODO: 在此处添加用户代码
	B_1ms = 1;
	B_50ms = 1;
	LED_WORKLED_50ms = 1;
	ADC_Timer_ms = 1;
}

void PWM_config(void)
{

	PWMx_InitDefine PWMx_InitStructure;

	PWMA_Duty.PWM_COM_Duty = PWMPeriod * 2 / 3;

	// 调试代码
	PWMA_Duty.PWM2_Duty = PWMA_Duty.PWM_COM_Duty;
	PWMA_Duty.PWM3_Duty = PWMA_Duty.PWM_COM_Duty;
	PWMA_Duty.PWM4_Duty = PWMA_Duty.PWM_COM_Duty;

	// PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	// PWMx_InitStructure.PWM_Duty    = PWMA_Duty.PWM1_Duty;	//PWM占空比时间, 0~Period
	// PWMx_InitStructure.PWM_EnoSelect   = ENO1P | ENO1N;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	// PWM_Configuration(PWM1, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

	// PWM2 1.2:LowLED 1.3:IO-White
	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	   // 模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM2_Duty; // PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO2N;		   // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM2, &PWMx_InitStructure);	   // 初始化PWM,  PWMA,PWMB

	// PWM3  1.4:IO-RED  1.5:IO-YELLO
	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	   // 模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM3_Duty; // PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO3P | ENO3N;  // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM3, &PWMx_InitStructure);	   // 初始化PWM,  PWMA,PWMB

	// PWM4  1.6:IO-BLUE 1.7:WORKLED
	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	   // 模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM4_Duty; // PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO4P;		   // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM4, &PWMx_InitStructure);	   // 初始化PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Period = PWMPeriod;	   // 周期时间,   0~65535
	PWMx_InitStructure.PWM_DeadTime = 0;		   // 死区发生器设置, 0~255
	PWMx_InitStructure.PWM_MainOutEnable = ENABLE; // 主输出使能, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable = ENABLE;	   // 使能计数器, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);  // 初始化PWM通用寄存器,  PWMA,PWMB

	PWM2_SW(PWM2_SW_P12_P13); // PWM2_SW_P12_P13,PWM2_SW_P22_P23,PWM2_SW_P62_P63
	PWM3_SW(PWM3_SW_P14_P15); // PWM3_SW_P14_P15,PWM3_SW_P24_P25,PWM3_SW_P64_P65
	PWM4_SW(PWM4_SW_P16_P17); // PWM4_SW_P16_P17,PWM4_SW_P26_P27,PWM4_SW_P66_P67,PWM4_SW_P34_P33

	//
	NVIC_PWM_Init(PWMA, DISABLE, Priority_0);

	PWMA_ENO = 0x0; // 初使化时，关闭所有PWM输出
	IO_LED_WarnRed = 0;
	IO_LED_WarnBlue = 0;
}

void ______Hal__WhileTast() {}

// 扫描并处理警示灯交互显示逻辑, 2秒交替显示 2*1000/50
void scanerWarinLEDChange(void)
{
	if (CMD_Warn_Led_Flag == 1 && B_50ms == 1)
	{
		B_50ms = 0;
		WLED2S_Count++;
		if (WLED2S_Count >= 40000)
		{
			// 交换显示
			if (Red0_blue1 == 0)
			{
				PWMA_ENO = 0x0;
				// PWM3P_OUT_EN();
				// PWM3N_OUT_DIS();
				Red0_blue1 = 1;
				IO_LED_WarnRed = 0;
				IO_LED_WarnBlue = 1;
				PrintfString2("red led show.");
			}
			else
			{
				PWMA_ENO = 0x0;
				// PWM3N_OUT_EN();
				// PWM3P_OUT_DIS();
				Red0_blue1 = 0;
				IO_LED_WarnRed = 1;
				IO_LED_WarnBlue = 0;
				PrintfString2("blue led show.");
			}

			// 重置计算器
			WLED2S_Count = 0;
		}
	}
}

// 工作LED闪显
void scanerWorkLEDChange(void)
{
	if (LED_WORKLED_Flag == 1 && LED_WORKLED_50ms == 1)
	{
		LED_WORKLED_50ms = 0;
		WorkLED2S_Count++;
		if (WorkLED2S_Count >= 100000)
		{
			// 交换显示
			if (show1_off0 == 0)
			{
				IO_LED_WORKLED = POW_LED_OPEN;
				show1_off0 = 1;
				// PrintfString2("work led show.");
			}
			else
			{
				IO_LED_WORKLED = POW_LED_CLOSE;
				show1_off0 = 0;
				// PrintfString2("work led off.");
			}

			// 重置计算器
			WorkLED2S_Count = 0;
		}
	}
}

//  电池电压扫描，10s一次.
void scanerBatterVoltage()
{
	u32 adcResVal = 0;
	float fCalVol = 0;

	if (LED_WORKLED_Flag == 1 && ADC_Timer_ms == 1)
	{
		ADC_Timer_ms = 0;
		ADC10S_Count++;
		if (ADC10S_Count >= 60000)
		{
			// 重置计算器
			ADC10S_Count = 0;

			// 获取电压值  P3.5/ADC13
			adcResVal = Get_ADCResult(ADC_CH13); // 参数0~15,查询方式做一次ADC, 返回值就是结果, == 4096 为错误

			if (adcResVal == 4096 || adcResVal < 1) // 数据异常时
			{
				PrintfString2("ADC error. val: %ld \r\n", adcResVal);
				return;
			}
			// 计算电压值
			// inVol = Res*RefVol / 1024
			// 外部电池电压4.2v  (获取内部参考电压)
			// 外部参考电压为2.5v， IO口电压的计算公式应为:  2500 * adc_result / 4096, 待调试.
			fCalVol = (adcResVal * 4.2f) / 1024.0f; // 单位mv（1196） 

#ifdef DEBUG_MODE
			PrintfString2("batter voltage: %f v. adcResVal: %ld\r\n", fCalVol, adcResVal);
#endif
			// 电压值转换LED灯显示
			displayBatterPower(fCalVol);
		}
	}
	return;
}

void menuCheck()
{
	// 按键功能菜单
	if (B_1ms == 1) // 1ms检测一次
	{
		B_1ms = 0;
		KeyScan();

		// Key1, 灯控制循环
		if (Key1_Function)
		{
			Key1_Function = 0;
			PrintString2("Key1 pressed.\r\n");
			if (cmd_Menu >= CMD_None_Led || cmd_Menu <= CMD_Warn_Led)
			{
				if ((cmd_Menu + 1) > CMD_Warn_Led)
				{
					cmd_Menu = CMD_None_Led;
				}
				else
				{
					cmd_Menu++;
				}
			}
			else
			{
				cmd_Menu = CMD_White_Led;
			}

			PrintfString2("cmd menu: %hd. \r\n", cmd_Menu);
			turnOnLEDWithCMDType(cmd_Menu);
		}
		// else if(Key1_Long_Function){
		// 	//长按关灯
		// 	cmd_Menu = CMD_None_Led;
		// 	PrintString2("Key1_Long pressed.\r\n");
		// 	turnOnLEDWithCMDType(cmd_Menu);
		// 	PrintfString2("cmd menu: %d",cmd_Menu);
		// }

		// Key2, 亮度调节
		else if (Key2_Short_Function)
		{
			// cmd_Menu = CMD_Warn_Led;
			Key2_Short_Function = 0;
			PrintString2("Key2 short pressed.\r\n");
			if ((pwm_DutyLevel + 1) > 4)
			{
				pwm_DutyLevel = PWM_Duty_Level_100;
			}
			else
			{
				pwm_DutyLevel++;
			}

			// 设置
			setPWMWithLEDBrightness(pwm_DutyLevel);
		}

		// Key2, 关机-开机
		else if (Key2_Long_Function)
		{
			Key2_Long_Function = 0;
			PrintString2("Key2 long pressed.\r\n");
			if (cmd_Menu == CMD_Sys_Close)
			{
				cmd_Menu = CMD_Sys_Open;
				SysOpen();
			}
			else
			{
				cmd_Menu = CMD_Sys_Close;
				SysClose();
			}
			PrintfString2("cmd menu: %hd", cmd_Menu);
		}
	}
}

/**********************************************/
void main(void)
{

	EAXSFR(); /* 扩展寄存器访问使能 */

	// 初始化GPIO
	GPIO_config();
	// 初始化外部中断
	Exti_config();
	// 初始化UART
	UART_config();
	// 初始化定时器
	Timer_config();
	// 初始化ADC
	ADC_config();
	// 初始化PWM
	PWM_config();
	// 启用全局中断
	EA = 1;

	#ifdef DEBUG_MODE
	PrintString2("STC8 Solar Charging Lamp Programme!\r\n"); // UART2发送一个字符串
	#endif

	// 初始化命令菜单状态
	cmd_Menu = CMD_None_Led;
	while (1)
	{
		// 按键检查
		menuCheck();

		// 红蓝警示灯检查
		scanerWarinLEDChange();

		// 工作LED灯显示
		scanerWorkLEDChange();

		// 电量显示
		scanerBatterVoltage();
	}
}

void ______Hal__FunctionSet() {}
// 设置LED的亮度级别
void setPWMWithLEDBrightness(enum PWMDutyLevel pwmLevel)
{
	// PWMA_Duty.PWM2_Duty

	u16 curPWMDuty = 0; // 0-100 单位百分比
	switch (pwmLevel)
	{
	case PWM_Duty_Level_100:
		/* code */
		curPWMDuty = PWMPeriod * 0.8;
		break;

	case PWM_Duty_Level_75:
		/* code */
		curPWMDuty = PWMPeriod * 0.55;
		break;
	case PWM_Duty_Level_50:
		/* code */
		curPWMDuty = PWMPeriod * 0.35;
		break;
	case PWM_Duty_Level_25:
		/* code */
		curPWMDuty = PWMPeriod * 0.25;
		break;
	case PWM_Duty_Level_0:
		/* code */
		curPWMDuty = 0;
		break;
	default:
		curPWMDuty = 0;
		break;
	}

	if (curPWMDuty != PWMA_Duty.PWM_COM_Duty)
	{
		// PWMA_Duty.PWM2_Duty = PWMA_Duty.PWM3_Duty = PWMA_Duty.PWM4_Duty = curPWMDuty;
		// UpdatePwm(PWMA, &PWMA_Duty);

		// 保存已设置值
		PWMA_Duty.PWM_COM_Duty = curPWMDuty;

		// 更新 2/3/4 PWM数据
		PWMA_Duty2(curPWMDuty);
		PWMA_Duty3(curPWMDuty);
		PWMA_Duty4(curPWMDuty);
		// PrintString2("Update PWM Duty...");
		PrintfString2("Update PWM Duty: %d \r\n", curPWMDuty);
	}
}

void turnOnLEDWithCMDType(enum CMDMenu cmdMenu)
{
	if (CMD_Warn_Led_Flag == 1)
	{
		// 停止使用警示灯资源.
		CMD_Warn_Led_Flag = 0;
		// Timer2_Stop();
		PWM3N_OUT_DIS();
		PWM3P_OUT_DIS();
		IO_LED_WarnRed = 0;
		IO_LED_WarnBlue = 0;
	}

	LED_WORKLED_Flag = 1;
	switch (cmdMenu)
	{
	case CMD_None_Led: // 关闭所有灯
		/* code */
		PrintString2("close all led");
		PWMA_ENO = 0x0; // Close All;
		LED_WORKLED_Flag = 0;
		IO_LED_WORKLED = IO_LED_ERR = BAT_POW_LED1 = BAT_POW_LED2 = BAT_POW_LED3 = BAT_POW_LED4 = POW_LED_CLOSE;
		// PWM2P_OUT_DIS();
		// PWM2N_OUT_DIS();
		// PWM3N_OUT_DIS();
		// PWM3N_OUT_DIS();
		// PWM4N_OUT_DIS();
		// PWM4N_OUT_DIS();
		break;
	case CMD_White_Led: // 开启白灯
		/* code */
		PrintString2("open white led");
		PWMA_ENO = 0x0;
		PWM2N_OUT_EN();
		break;
	case CMD_Yello_Led: // 开启黄灯
		/* code */
		PrintString2("open yeelor led");
		PWMA_ENO = 0x0;
		PWM3N_OUT_EN();
		break;
	case CMD_WH_YE_Led: // 黄白灯一起开
		/* code */
		PrintString2("open white+yeelor led");
		PWMA_ENO = 0x0;
		PWM2N_OUT_EN();
		PWM3N_OUT_EN();
		break;
	case CMD_Warn_Led: // 开启警示灯
		/* code */

		PrintString2("open Warn led");
		// 启动Time
		PWMA_ENO = 0x0; // STOP ALL PWM Enable Switch

		CMD_Warn_Led_Flag = 1;
		break;
	default:
		break;
	}

	return;
}

/**
 * @brief 电量显示， 开机后，20秒显示一次电量.
 *
满电状态：
电压范围：4.2V ~ 4.0V
描述：电池接近满电状态，提供最长的使用时间。
高电量状态：

电压范围：4.0V ~ 3.8V
描述：此电量范围仍然较高，足够支持大部分应用。
中电量状态：

电压范围：3.8V ~ 3.6V
描述：电量中等，使用时间明显减少，需开始考虑充电。
低电量状态：

电压范围：3.6V ~ 3.4V
描述：电量接近最低范围，建议尽快充电，以免电池电压继续下降。

 */
void displayBatterPower(float inVol)
{
	u16 level = 0;
	// 4个等级电压值
	// 控制IO： 3.5/3.4/3.3/3.2

	if (inVol >= 4.0)
	{
		// 4
		level = 4;
	}
	else if (inVol > 3.8 && inVol < 4.0)
	{

		level = 3;
	}
	else if (inVol > 3.6 && inVol < 3.8)
	{

		level = 2;
	}
	else if (inVol > 3.4 && inVol < 3.6)
	{
		level = 1;
	}
	else
	{
		level = 0;
	}

	// 关闭所有
	BAT_POW_LED4 = BAT_POW_LED3 = BAT_POW_LED2 = BAT_POW_LED1 = POW_LED_CLOSE;

	switch (level)
	{
	case 4 /* constant-expression */:
		/* code */
		BAT_POW_LED4 = POW_LED_OPEN; // 开启
	case 3 /* constant-expression */:
		/* code */
		BAT_POW_LED3 = POW_LED_OPEN;
	case 2 /* constant-expression */:
		/* code */
		BAT_POW_LED2 = POW_LED_OPEN;
	case 1 /* constant-expression */:
		/* code */
		BAT_POW_LED1 = POW_LED_OPEN;
	case 0 /* constant-expression */:
		/* code */
		// BAT_POW_LED0 = 1;

	default:
		break;
	}

	PrintfString2("Battery level: %d", level);
}

//========================================================================
// 函数: void KeyScan(void)
// 描述: 按键扫描函数。
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注:
//========================================================================
void KeyScan(void)
{
	// 单纯短按按键
	if (!KEY1)
	{
		if (!Key1_Flag)
		{
			Key1_cnt++;
			if (Key1_cnt >= 3000) // 50ms防抖
			{
				Key1_Flag = 1; // 设置按键状态，防止重复触发
				Key1_Function = 1;
			}
		}
	}
	else
	{
		Key1_cnt = 0;
		Key1_Flag = 0;
	}

	// 长按短按按键
	if (!KEY2)
	{
		if (!Key2_Flag)
		{
			Key2_cnt++;
			if (Key2_cnt >= 15000) // 长按1s
			{
				Key2_Short_Flag = 0; // 清除短按标志
				Key2_Long_Flag = 1;	 // 设置长按标志
				Key2_Flag = 1;		 // 设置按键状态，防止重复触发
				Key2_Long_Function = 1;
			}
			else if (Key2_cnt >= 50) // 50ms防抖
			{
				Key2_Short_Flag = 1; // 设置短按标志
			}
		}
	}
	else
	{
		if (Key2_Short_Flag) // 判断是否短按
		{
			Key2_Short_Flag = 0; // 清除短按标志
			Key2_Short_Function = 1;
		}
		Key2_cnt = 0;
		Key2_Flag = 0; // 按键释放
	}
}

/**
 * @brief 系统开启
 *
 */
void SysOpen()
{
	cmd_Menu = CMD_White_Led;
	PrintString2("Sys Open.");
	pwm_DutyLevel = PWM_Duty_Level_75;

	UART2_RxEnable(1);
	Timer1_Run(1);
	// Timer2_Run();
	ADC_PowerOn(1);

	turnOnLEDWithCMDType(cmd_Menu);
	return;
}

/**
 * @brief 系统关闭
 *
 */
void SysClose()
{
	cmd_Menu = CMD_Sys_Close;
	PrintString2("Sys Close.");
	PWMA_ENO = 0x0; // Close All;
	LED_WORKLED_Flag = IO_LED_WORKLED = BAT_POW_LED1 = BAT_POW_LED2 = BAT_POW_LED3 = BAT_POW_LED4 = POW_LED_CLOSE;
	// PWM2P_OUT_DIS();
	// IO口强制为高阻模式
	// UART接收 关闭
	UART2_RxEnable(0);
	// Time 关闭
	Timer1_Stop();
	// Timer2_Stop();
	//  ADC 关闭
	ADC_PowerOn(0);
	// PWM 关闭
	PWMA_DIS();
	// 省电模式

	PCON |= 0x02; ;	//Sleep
	return;
}