
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
串口调试输出: UART2_SW_P10_P11
 * 芯片: STC8H17K
   1.2:xxxxx    1.1:  LED-2
   1.3:IO-White	1.0:  LED-1
   1.4:LED-3    3.7:xxxxxx
   1.5:LED-4	3.6:KEY-MAIN
   1.6:UART2_Rx 3.5:ADC_BAT
   1.7:UART2_Tx 3.4:LED_ERR
   5.4			3.3: WORKLED
   vcc			3.2: IN_Charging
   adc-ref	    3.1: TxD1
   gnd			3.0: RxD1

实现功能
1. 电量显示LED [低电平亮]
2. 工作指示灯 [0:工作, 1:不工作] 低电平亮
3. 运行异常LED灯 [1:正常, 0:异常] 低电平亮
4. 充电输入口 [1:充电, 0:不充电]
5. 日志UART2接收
6. 日志UART2发送
7. 主菜单按键
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
5. key1,key2

- 状态机
1. 按键Key2输出PWM占空比: PWM100,PWM75,PWM50,PWM25 [3.6:KEY-brightness]
2. 按键Key1输出LED模式: LED_Power_Show,LED_White,LED_YELLO, LED_RED_BLUE

- 中断
1. timer0按键检测中断
2. timer1


- 开发计划
1. 按键监控
2. 输出IO口控制
3. pwm亮度调节

RTX51-Tiny
https://blog.csdn.net/weixin_51026398/article/details/123776288?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-5-123776288-blog-92062159.235^v43^control&spm=1001.2101.3001.4242.4&utm_relevant_index=6
******

******************************************/

/*************	本地常量声明	**************/
#define POW_LED_OPEN  1  // 电量LED灯开启
#define POW_LED_CLOSE 0  // 电量LED灯关闭

/*************	本地变量声明	**************/

//P1排口 推 0-5 推挽输出, 6-7: 双向口
sbit IO_LED_White = P1 ^ 3;    // OUT-白光LED驱动控制开关，默认关
// 电量显示LED [低电平亮]
sbit BAT_POW_LED4 = P1 ^ 5; 
sbit BAT_POW_LED3 = P1 ^ 4;
sbit BAT_POW_LED2 = P1 ^ 1;
sbit BAT_POW_LED1 = P1 ^ 0;

sbit LogUART2_Rx = P1 ^ 6; // 日志UART2接收
sbit LogUART2_Tx = P1 ^ 7; // 日志UART2发送

// P3排口
sbit IO_IN_Charging = P3 ^ 2; // [高阻输入] 充电输入口 [高阻输入][1:充电, 0:不充电]
sbit IO_LED_WORKLED = P3 ^ 3; // [推挽输出] 工作指示灯 [0:工作, 1:不工作] 低电平亮
sbit IO_LED_ERR     = P3 ^ 4; // [推挽输出] 运行异常LED灯 [1:正常, 0:异常] 低电平亮

sbit ADC_BAT 		= P3 ^ 5; // [高阻输入] IN-电池电压
sbit KEY1 			= P3 ^ 6; // [高阻输入]主菜单按键

//其它功能标识
u16 Key1_cnt;
bit Key1_Flag;
bit B_1ms; // 1ms标志
bit Key1_Function;
bit Key1_Long_Function;


// PWM模块
PWMx_Duty PWMA_Duty;
u16 PWMPeriod = 1000; // PWM周期设置 HZ: 1/1000  = 1ms

u16 LED_WORKLED_Flag = 0; // 默认值为0
u16 LED_WORKLED_50ms = 0;

u16 s_ChargingStopFlag = 0;
u16 S_OpenLedFlag = 0;
u16 LED_White_Timer_Open_S = 0;
u16 LED_White_Timer_1s = 0;
u16 LED_White_Timer_ms = 0;

u32 WorkLED2S_Count;
bit show1_off0;

u32 ADC10S_Count;
u16 ADC_Timer_ms;

u32 B_1ms_Count; // 1ms累加计数器,可用于事件循环执行时间间隔

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
	CMD_None_Led  = 0,	// 关闭所有灯
	CMD_White_Led = 1,	// 开启一次白灯
	CMD_Sys_Close = 2,	// 系统关机
	CMD_Sys_Open  = 3,	// 系统开机
};

enum CMDMenu cmd_Menu;

/*************	本地函数声明	**************/
void handleCmdMenu(enum CMDMenu cmdMenu);
void setPWMWithLEDBrightness(enum PWMDutyLevel pwmLevel);
void scanerChargingDetection(void);
void scanerWhiteLEDControl(void);
/*************  外部函数和变量声明 *****************/
/******************* IO配置函数 *******************/

void ______Hal__CONFIG() {}
void GPIO_config(void)
{
	// 指令版FV
	// P3-[0,1],[2,3,4]

	// 设置P3.6，P3.7, P3.5为高阻输入
//	P3M0 = 0x00;
//	P3M1 = 0xe0;

//	// 使能P3.6，P3.7口上拉
//	P3PU = 0xc0;

//	//[P1]
//	// p1-[1] uart2，双向口
//	// p1-[0,2~7] 推挽输出，控制MOS管
	P1M0 = 0x78;
	P1M1 = 0x00;
		// P1M0 = 0x3f; P1M1 = 0x00; //
    	// P3M0 = 0x18; P3M1 = 0x64;
		// P3PU = 0x60;

	P3M0 = 0x18;
	P3M1 = 0xe0;
	P3PU = 0xe0;

	IO_LED_WORKLED = POW_LED_CLOSE;
	IO_LED_White   = POW_LED_CLOSE;
}

void Exti_config(void) {

  EXTI_InitTypeDef Exti_InitStructure; // 结构定义
  // P3.2: [高阻输入] 充电输入口 [高阻输入]  P3.2/INTO/
  // P3.6: [高阻输入] 主菜单按键            P3.6/INT2/

  Exti_InitStructure.EXTI_Mode = EXT_MODE_Fall; // 中断模式,   EXT_MODE_RiseFall,EXT_MODE_Fall
  Ext_Inilize(EXT_INT2, &Exti_InitStructure); // 初始化
  Ext_Inilize(EXT_INT3, &Exti_InitStructure); // 初始化
  NVIC_INT2_Init(ENABLE, Priority_2);
  NVIC_INT3_Init(ENABLE, Priority_1);
  // 中断使能, ENABLE/DISABLE; 优先级(低到高)
  // Priority_0,Priority_1,Priority_2,Priority_3
}

/******************* AD配置函数 *******************/
// void ADC_config(void)
// {
// 	ADC_InitTypeDef ADC_InitStructure; // 结构定义

// 	ADC_InitStructure.ADC_SMPduty = 31;					   // ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
// 	ADC_InitStructure.ADC_CsSetup = 0;					   // ADC 通道选择时间控制 0(默认),1
// 	ADC_InitStructure.ADC_CsHold = 1;					   // ADC 通道选择保持时间控制 0,1(默认),2,3
// 	ADC_InitStructure.ADC_Speed = ADC_SPEED_2X16T;		   // 设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
// 	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED; // ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
// 	ADC_Inilize(&ADC_InitStructure);					   // 初始化
// 	ADC_PowerControl(ENABLE);							   // ADC电源开关, ENABLE或DISABLE
// 	NVIC_ADC_Init(DISABLE, Priority_0);					   // 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
// }

/***************  串口2初始化函数,调试输出 *****************/
void UART_config(void) 
{
	COMx_InitDefine COMx_InitStructure;			   // 结构定义
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; // 模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//选择波特率发生器, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2, 所以不用选择),注意不能再使用Timer2作为中断
	COMx_InitStructure.UART_BaudRate = 115200ul;	// 波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE;		// 接收允许,   ENABLE或DISABLE
	UART_Configuration(UART1, &COMx_InitStructure); // 初始化串口2 USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE, Priority_3);			// 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	UART1_SW(UART1_SW_P30_P31);
}

/************************ 定时器配置 ****************************/
void Timer_config(void)
{
	TIM_InitTypeDef TIM_InitStructure; // 结构定义

	//[Timer1 按键检测信号源1ms] 定时器1做16位自动重装, 中断频率为1000HZ
	TIM_InitStructure.TIM_Mode = TIM_16BitAutoReload;			 // 指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_T1Stop
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;				 // 指定时钟源, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut = DISABLE;						 // 是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value = 65536UL - (MAIN_Fosc / 1000); // 初值,
	TIM_InitStructure.TIM_Run = ENABLE;							 // 是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer1, &TIM_InitStructure);					 // 初始化Timer1	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer1_Init(ENABLE, Priority_0);						 // 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

void PWM_config(void)
{
	PWMx_InitDefine PWMx_InitStructure;
	PWMA_Duty.PWM_COM_Duty = PWMPeriod * 2 / 3;

	// 调试代码
	PWMA_Duty.PWM2_Duty = PWMA_Duty.PWM_COM_Duty;

	// PWM2 1.2:LowLED 1.3:IO-White
	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	   // 模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM2_Duty; // PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO2N;		   // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM2, &PWMx_InitStructure);	   // 初始化PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Period = PWMPeriod;	   // 周期时间,   0~65535
	PWMx_InitStructure.PWM_DeadTime = 0;		   // 死区发生器设置, 0~255
	PWMx_InitStructure.PWM_MainOutEnable = ENABLE; // 主输出使能, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable = ENABLE;	   // 使能计数器, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);  // 初始化PWM通用寄存器,  PWMA,PWMB

	PWM2_SW(PWM2_SW_P12_P13); // PWM2_SW_P12_P13,PWM2_SW_P22_P23,PWM2_SW_P62_P63
	NVIC_PWM_Init(PWMA, DISABLE, Priority_0);

	PWMA_ENO = 0x0; // 初使化时，关闭所有PWM输出
}

void ______Hal__WhileTast() {}

// 工作LED闪显
void scanerWorkLEDChange(void)
{
	if (LED_WORKLED_Flag == 1 && LED_WORKLED_50ms == 1)
	{
		LED_WORKLED_50ms = 0;
		WorkLED2S_Count++;
		if (WorkLED2S_Count >= 1500)
		{
			// 交换显示
			if (show1_off0 == 0)
			{
				IO_LED_WORKLED = POW_LED_OPEN;
				show1_off0 = 1;
				// PrintfString("work led show.");
			}
			else
			{
				IO_LED_WORKLED = POW_LED_CLOSE;
				show1_off0 = 0;
				// PrintfString("work led off.");
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
				PrintfString("ADC error. val: %ld \r\n", adcResVal);
				return;
			}
			// 计算电压值
			// inVol = Res*RefVol / 1024
			// 外部电池电压4.2v  (获取内部参考电压)
			// 外部参考电压为2.5v， IO口电压的计算公式应为:  2500 * adc_result / 4096, 待调试.
			fCalVol = (adcResVal * 4.2f) / 1024.0f; // 单位mv（1196） 

#ifdef DEBUG_MODE
			PrintfString("batter voltage: %f v. adcResVal: %ld\r\n", fCalVol, adcResVal);
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
		if (Key1_Function) {
			Key1_Function = 0;

			PrintfString("Key1 pressed.\r\n");
			if (cmd_Menu >= CMD_None_Led || cmd_Menu <= CMD_Sys_Open)
			{
				if ((cmd_Menu + 1) > CMD_Sys_Open)
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
				cmd_Menu = CMD_None_Led;
			}

			PrintfString("cmd menu: %hd. \r\n", cmd_Menu);
			handleCmdMenu(cmd_Menu);
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
	//ADC_config();
	// 初始化PWM
	//PWM_config();
	// 启用全局中断
	EA = 1;

	#ifdef DEBUG_MODE
	PrintfString("STC8 Fire Lamp Programme!\r\n"); // UART2发送一个字符串
	#endif

	// 初始化命令菜单状态
	cmd_Menu = CMD_None_Led;
	while (1)
	{
		//PrintfString("STC8");
		// 按键检查
		menuCheck();
		if (cmd_Menu == CMD_Sys_Close) {
			continue;
		}

		// 工作LED灯显示
		scanerWorkLEDChange();

		// 关灯状态，不进行后续操作
		if (cmd_Menu == CMD_None_Led) {
			continue;
		}
		// 电量显示
		//scanerBatterVoltage();

		// 1秒一次检测
		if (B_1ms_Count % 1000 == 0) { 
			
			// 充电状态检测
			scanerChargingDetection();

			// LED灯开关控制
			scanerWhiteLEDControl();
        }
		
	}
}

// 充电状态检测
void scanerChargingDetection(void)
{
  if (s_ChargingStopFlag) {
    s_ChargingStopFlag = 0;
    PrintfString("charging stop\r\n");
    S_OpenLedFlag = 1;
  }
}

// 白灯控制
void scanerWhiteLEDControl() {
  // LED灯开关控制
  if (S_OpenLedFlag) {
    S_OpenLedFlag = 0;           // 防止重复触发
    LED_White_Timer_Open_S = 1000; // 10s
    IO_LED_White = POW_LED_OPEN;

		PrintfString("white led open.\r\n");
    //   PWMA_ENO = 0x0;
    //   PWM2N_OUT_EN();
  }

  // 判断LED灯是否计时停止
  if (LED_White_Timer_Open_S > 0) {
    LED_White_Timer_Open_S--;
    if (LED_White_Timer_Open_S == 0) {
      IO_LED_White = POW_LED_CLOSE;

	  PrintfString("white led close.\r\n");
      // PWMA_ENO = 0x0;
      // PWM2N_OUT_DIS();
    }
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
		// 保存已设置值
		PWMA_Duty.PWM_COM_Duty = curPWMDuty;
		PWMA_Duty2(curPWMDuty);
		PrintfString("Update PWM Duty: %d \r\n", curPWMDuty);
	}
}

void handleCmdMenu(enum CMDMenu cmdMenu)
{
	LED_WORKLED_Flag = 1;
	switch (cmdMenu)
	{
	case CMD_None_Led: // 关闭所有灯
		/* code */
		PrintfString("close all led");
		PWMA_ENO = 0x0; // Close All;
		LED_WORKLED_Flag = 0;
		LED_White_Timer_Open_S = 0;
		IO_LED_White   = POW_LED_CLOSE;
		IO_LED_WORKLED = POW_LED_CLOSE;
		break;
	case CMD_White_Led: // 开启白灯
		/* code */
		PrintfString("open white led");
		S_OpenLedFlag = 1;
		break;
	case CMD_Sys_Close: // 系统关机
		/* code */
		PrintfString("sys close");
		SysClose();
		break;
	case CMD_Sys_Open: // 系统开机
		/* code */
		PrintfString("sys open");
		SysOpen();
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

	PrintfString("Battery level: %d", level);
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
			if (Key1_cnt >= 500) // 50ms防抖
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
}

/**
 * @brief 系统开启
 *
 */
void SysOpen()
{
	cmd_Menu = CMD_Sys_Open;
	PrintfString("Sys Open.");
	pwm_DutyLevel = PWM_Duty_Level_75;

	UART1_RxEnable(1);
	Timer1_Run(1);
	Timer2_Run(1);
	//ADC_PowerOn(1);

	return;
}

/**
 * @brief 系统关闭
 *
 */
void SysClose()
{
	cmd_Menu = CMD_Sys_Close;
	PrintfString("Sys Close.");
	PWMA_ENO = 0x0; // Close All;

	IO_LED_White = POW_LED_CLOSE;
	IO_LED_WORKLED = POW_LED_CLOSE;
	// IO口强制为高阻模式
	// UART接收 关闭
	//UART1_RxEnable(0);
	// Time 关闭
	//Timer1_Stop();
	//Timer2_Stop();
	//  ADC 关闭
	//ADC_PowerOn(0);
	// PWM 关闭
	//PWMA_DIS();
	// 省电模式

	PCON |= 0x02; ;	//Sleep
	return;
}

// 充电状态检测中断(下降沿触发) 存在问题，需要改为轮询
void INT3_ISR_Handler(void) interrupt INT3_VECTOR {
  s_ChargingStopFlag = 1;
  PrintString1("INT3 \r\n");
}

// 主菜单按键中断(下降沿触发)
void INT2_ISR_Handler(void) interrupt INT2_VECTOR {
  if (cmd_Menu == CMD_Sys_Close) {
    // 系统关闭状态
    //cmd_Menu = CMD_Sys_Open;
    //SysOpen();
  }
  PrintString1("INT2 \r\n");
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
  B_1ms_Count++;
  LED_WORKLED_50ms = 1;
  ADC_Timer_ms = 1;

  if (B_1ms_Count > 60000)
  {
	  B_1ms_Count = 0;
  }
}