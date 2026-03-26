/**
 * @file main.c
 * @author sherwin.chen (chensheng12330@gmail.com)
 * @brief 消防应急灯控制系统 - 基于STC8H1K17
 * @version 2.0
 * @date 2026-03-16
 *
 * @copyright Copyright (c) 2024-2026
 *
 * 功能说明:
 * 检测到外部断电信号(P3.2/INT0下降沿)后自动开启照明LED，持续照明10分钟后休眠，
 * 等待通电信号(P3.2/INT0上升沿)唤醒恢复开机状态。
 *
 * 硬件资源:
 * - PWM2N (P1.3): 照明LED亮度控制(NMos驱动)
 * - ADC1  (P1.1): 电池电压检测
 * - Timer1:       1ms系统节拍(按键扫描/定时)
 * - UART1 (P3.0/P3.1): 调试串口输出, 115200bps
 * - INT0  (P3.2): 断电/通电信号检测(双边沿)
 * - INT2  (P3.6): 关机状态按键唤醒(下降沿)
 */

#define DEBUG_MODE 1

#include "config.h"
#include "STC8G_H_ADC.h"
#include "STC8H_PWM.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_UART.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Switch.h"
#include "STC8G_H_Timer.h"
#include "STC8G_H_Exti.h"

/*============================================================================*/
/*                             常量定义                                        */
/*============================================================================*/

#define LED_ON              0       /* LED低电平点亮(共阳/NMos低有效) */
#define LED_OFF             1       /* LED高电平熄灭 */

#define PWM_PERIOD          1000    /* PWM周期值 */
#define LED_PWM_DUTY        800     /* 照明LED默认占空比(80%) */

#define EMERGENCY_TIME_MS   600000UL /* 应急照明持续时间: 10分钟 */
#define ADC_INTERVAL_MS     10000    /* 电池电压采样间隔: 10秒 */

#define KEY_SHORT_MS        50      /* 短按防抖阈值: 50ms */
#define KEY_LONG_MS         1500    /* 长按判定阈值: 1.5s */

#define BAT_VOLTAGE_FULL    4.0f    /* 满电阈值 */
#define BAT_VOLTAGE_HIGH    3.8f    /* 高电量阈值 */
#define BAT_VOLTAGE_MID     3.6f    /* 中电量阈值 */
#define BAT_VOLTAGE_LOW     3.4f    /* 低电量阈值, 低于此值强制关灯 */

/*============================================================================*/
/*                             引脚定义                                        */
/*============================================================================*/

sbit IO_LED_Light  = P1 ^ 3;   /* 照明LED (PWM2N, NMos驱动) */
sbit IO_LED_Status = P1 ^ 7;   /* 状态指示LED */

sbit POWER_SIGNAL  = P3 ^ 2;   /* 断电/通电信号输入 (INT0) */
sbit KEY1          = P3 ^ 6;   /* 按键1 */

sbit BAT_LED1      = P3 ^ 7;   /* 电量LED1 (最低1格) */
sbit BAT_LED2      = P3 ^ 3;   /* 电量LED2 */
sbit BAT_LED3      = P3 ^ 4;   /* 电量LED3 */
sbit BAT_LED4      = P3 ^ 5;   /* 电量LED4 (最高4格) */

/*============================================================================*/
/*                             系统状态定义                                    */
/*============================================================================*/

enum SysState {
    SYS_ON        = 0,  /* 开机状态: 监控断电信号, 显示电量 */
    SYS_OFF       = 1,  /* 关机状态: 低功耗休眠, 等待长按开机 */
    SYS_EMERGENCY = 2,  /* 应急照明: LED亮灯10分钟 */
    SYS_SLEEP     = 3   /* 休眠状态: 等待通电信号唤醒 */
};

/*============================================================================*/
/*                             全局变量                                        */
/*============================================================================*/

enum SysState sysState;

bit monitorEnabled;         /* 断电监控开关: 1=开启, 0=关闭 */
bit powerFailFlag;          /* 断电标志 (INT0下降沿置位) */
bit powerRestoreFlag;       /* 通电标志 (INT0上升沿置位) */

bit B_1ms;                  /* 1ms定时节拍标志 */

/* 按键状态 */
u16 keyCnt;                 /* 按键按下持续计数(ms) */
bit keyFlag;                /* 按键已锁定标志(防重复触发) */
bit keyShortFlag;           /* 短按中间标志 */
bit keyShortPress;          /* 短按事件(释放后触发) */
bit keyLongPress;           /* 长按事件 */

/* 定时计数器 */
u16 adcIntervalCnt;         /* ADC采样间隔计数(ms) */
u32 emergencyTimerCnt;      /* 应急照明倒计时(ms) */

/* 电池电压 */
float lastBatVoltage;       /* 最近一次电池电压值 */

/* PWM */
PWMx_Duty PWMA_Duty;

/*============================================================================*/
/*                             函数声明                                        */
/*============================================================================*/

void GPIO_config(void);
void ADC_config(void);
void UART_config(void);
void Timer_config(void);
void PWM_config(void);
void Exti_config(void);

void KeyScan(void);
void readAndDisplayBattery(void);
void displayBatteryPower(float inVol);
void allLedsOff(void);

void enterOnState(void);
void enterOffState(void);
void enterEmergencyState(void);
void enterSleepState(void);

/*============================================================================*/
/*                         硬件初始化函数                                      */
/*============================================================================*/

/**
 * @brief GPIO端口配置
 *
 * P1.1:  高阻输入(ADC电池电压)
 * P1.3:  推挽输出(照明LED/PWM2N)
 * P1.7:  推挽输出(状态LED)
 * P1.0/P1.2/P1.4~P1.6: 推挽输出(未用, 拉低)
 *
 * P3.0/P3.1: 准双向口(UART1)
 * P3.2:  高阻输入+上拉(电源信号/INT0)
 * P3.6:  高阻输入+上拉(按键/INT2)
 * P3.3/P3.4/P3.5/P3.7: 推挽输出(电量LED)
 */
void GPIO_config(void) {
    /* P1端口: P1.1高阻(ADC), 其余推挽输出 */
    P1M0 = 0xFD;   /* 11111101: 除P1.1外全部推挽 */
    P1M1 = 0x02;   /* 00000010: P1.1高阻输入 */

    /* P3端口: P3.2/P3.6高阻输入, P3.3/P3.4/P3.5/P3.7推挽, P3.0/P3.1准双向 */
    P3M0 = 0xB8;   /* 10111000: P3.3/P3.4/P3.5/P3.7推挽 */
    P3M1 = 0x44;   /* 01000100: P3.2/P3.6高阻输入 */

    /* P3.2和P3.6上拉使能 */
    P3PU = 0x44;    /* 01000100 */

    /* 初始化所有输出为安全状态 */
    IO_LED_Light  = 0;
    IO_LED_Status = LED_OFF;
    BAT_LED1 = BAT_LED2 = BAT_LED3 = BAT_LED4 = LED_OFF;

    /* 未使用引脚拉低 */
    P10 = 0; P12 = 0; P14 = 0; P15 = 0; P16 = 0;
}

/**
 * @brief 外部中断配置
 *
 * INT0 (P3.2): 双边沿, 检测断电(下降沿)/通电(上升沿)
 */
void Exti_config(void) {
    EXTI_InitTypeDef Exti_InitStructure;

    /* INT0: 上升沿+下降沿中断 */
    Exti_InitStructure.EXTI_Mode = EXT_MODE_RiseFall;
    Ext_Inilize(EXT_INT0, &Exti_InitStructure);
    NVIC_INT0_Init(ENABLE, Priority_3);
}

/**
 * @brief INT0中断服务函数 - 断电/通电信号检测
 *
 * 读取P3.2电平判断事件类型:
 * - LOW  = 断电信号(下降沿触发)
 * - HIGH = 通电信号(上升沿触发)
 */
void INT0_ISR_Handler(void) interrupt INT0_VECTOR {
    if (POWER_SIGNAL == 0) {
        powerFailFlag = 1;
    } else {
        powerRestoreFlag = 1;
    }
}

/**
 * @brief INT2中断服务函数 - 关机状态按键唤醒
 *
 * INT2仅支持下降沿, 用于SYS_OFF状态唤醒MCU
 */
void INT2_ISR_Handler(void) interrupt INT2_VECTOR {
    /* 唤醒MCU即可, 后续逻辑在主循环处理 */
}

/**
 * @brief ADC配置 - 电池电压检测通道ADC1(P1.1)
 */
void ADC_config(void) {
    ADC_InitTypeDef ADC_InitStructure;

    ADC_InitStructure.ADC_SMPduty   = 31;
    ADC_InitStructure.ADC_CsSetup   = 0;
    ADC_InitStructure.ADC_CsHold    = 1;
    ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X16T;
    ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;
    ADC_Inilize(&ADC_InitStructure);
    ADC_PowerControl(ENABLE);
    NVIC_ADC_Init(DISABLE, Priority_0);
}

/**
 * @brief UART1配置 - 调试串口 P3.0(RxD)/P3.1(TxD), 115200bps
 *
 * 使用Timer2作为波特率发生器, Timer1保留给系统节拍
 */
void UART_config(void) {
    COMx_InitDefine COMx_InitStructure;

    COMx_InitStructure.UART_Mode     = UART_8bit_BRTx;
    COMx_InitStructure.UART_BRT_Use  = BRT_Timer2;
    COMx_InitStructure.UART_BaudRate = 115200ul;
    COMx_InitStructure.UART_RxEnable = DISABLE;
    UART_Configuration(UART1, &COMx_InitStructure);
    NVIC_UART1_Init(ENABLE, Priority_1);
    UART1_SW(UART1_SW_P30_P31);
}

/**
 * @brief Timer1配置 - 1ms系统节拍
 *
 * 16位自动重装, 1T模式, 中断频率1000Hz
 */
void Timer_config(void) {
    TIM_InitTypeDef TIM_InitStructure;

    TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;
    TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;
    TIM_InitStructure.TIM_ClkOut    = DISABLE;
    TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000);
    TIM_InitStructure.TIM_Run       = ENABLE;
    Timer_Inilize(Timer1, &TIM_InitStructure);
    NVIC_Timer1_Init(ENABLE, Priority_0);
}

/**
 * @brief Timer1中断服务函数 - 1ms节拍
 */
void Timer1_ISR_Handler(void) interrupt TMR1_VECTOR {
    B_1ms = 1;
}

/**
 * @brief PWM配置 - 仅PWM2N通道(P1.3照明LED)
 *
 * PWM2映射到P1.2(PWM2P, 未用)/P1.3(PWM2N, 照明LED)
 * 初始化后PWM输出关闭, 由状态机控制开启
 */
void PWM_config(void) {
    PWMx_InitDefine PWMx_InitStructure;

    PWMA_Duty.PWM2_Duty = LED_PWM_DUTY;

    /* PWM2通道配置 */
    PWMx_InitStructure.PWM_Mode      = CCMRn_PWM_MODE1;
    PWMx_InitStructure.PWM_Duty      = PWMA_Duty.PWM2_Duty;
    PWMx_InitStructure.PWM_EnoSelect = ENO2N;
    PWM_Configuration(PWM2, &PWMx_InitStructure);

    /* PWMA通用配置 */
    PWMx_InitStructure.PWM_Period        = PWM_PERIOD;
    PWMx_InitStructure.PWM_DeadTime      = 0;
    PWMx_InitStructure.PWM_MainOutEnable = ENABLE;
    PWMx_InitStructure.PWM_CEN_Enable    = ENABLE;
    PWM_Configuration(PWMA, &PWMx_InitStructure);

    PWM2_SW(PWM2_SW_P12_P13);

    NVIC_PWM_Init(PWMA, DISABLE, Priority_0);

    /* 初始化时关闭PWM输出 */
    PWMA_ENO = 0x0;
    IO_LED_Light = 0;
}

/*============================================================================*/
/*                             功能函数                                        */
/*============================================================================*/

/**
 * @brief 关闭所有LED指示灯
 */
void allLedsOff(void) {
    IO_LED_Status = LED_OFF;
    BAT_LED1 = BAT_LED2 = BAT_LED3 = BAT_LED4 = LED_OFF;
}

/**
 * @brief 关闭照明LED (PWM输出禁止)
 */
void lightOff(void) {
    PWMA_ENO = 0x0;
    IO_LED_Light = 0;
}

/**
 * @brief 开启照明LED (PWM2N输出使能)
 */
void lightOn(void) {
    PWMA_ENO = 0x0;
    PWM2N_OUT_EN();
}

/**
 * @brief 按键扫描 - KEY1 (P3.6)
 *
 * 短按(>50ms, 释放触发): 置位keyShortPress
 * 长按(>1.5s): 置位keyLongPress
 * 每1ms调用一次
 */
void KeyScan(void) {
    if (!KEY1) {
        if (!keyFlag) {
            keyCnt++;
            if (keyCnt >= KEY_LONG_MS) {
                keyShortFlag = 0;
                keyFlag = 1;
                keyLongPress = 1;
            } else if (keyCnt >= KEY_SHORT_MS) {
                keyShortFlag = 1;
            }
        }
    } else {
        if (keyShortFlag) {
            keyShortFlag = 0;
            keyShortPress = 1;
        }
        keyCnt = 0;
        keyFlag = 0;
    }
}

/**
 * @brief 读取电池电压并更新电量LED显示
 *
 * ADC通道: ADC_CH1 (P1.1)
 * 电压计算: Vbat = ADC值 * 4.2 / 1024
 */
void readAndDisplayBattery(void) {
    u32 adcResVal;
    float fCalVol;

    adcResVal = Get_ADCResult(ADC_CH1);

    if (adcResVal == 4096 || adcResVal < 1) {
#ifdef DEBUG_MODE
        PrintfString1("ADC error. val: %ld\r\n", adcResVal);
#endif
        return;
    }

    fCalVol = (adcResVal * 4.2f) / 1024.0f;
    lastBatVoltage = fCalVol;

#ifdef DEBUG_MODE
    PrintfString1("BAT: %f V, ADC: %ld\r\n", fCalVol, adcResVal);
#endif

    displayBatteryPower(fCalVol);
}

/**
 * @brief 电量LED显示
 *
 * 根据电压值点亮对应数量的LED(级联显示):
 *   >= 4.0V: 4格 (LED1~LED4全亮)
 *   >= 3.8V: 3格 (LED1~LED3)
 *   >= 3.6V: 2格 (LED1~LED2)
 *   >= 3.4V: 1格 (LED1)
 *   <  3.4V: 0格 (全灭)
 *
 * @param inVol 电池电压值(V)
 */
void displayBatteryPower(float inVol) {
    u8 level = 0;

    if (inVol >= BAT_VOLTAGE_FULL) {
        level = 4;
    } else if (inVol >= BAT_VOLTAGE_HIGH) {
        level = 3;
    } else if (inVol >= BAT_VOLTAGE_MID) {
        level = 2;
    } else if (inVol >= BAT_VOLTAGE_LOW) {
        level = 1;
    }

    BAT_LED1 = BAT_LED2 = BAT_LED3 = BAT_LED4 = LED_OFF;

    switch (level) {
    case 4: BAT_LED4 = LED_ON;
    case 3: BAT_LED3 = LED_ON;
    case 2: BAT_LED2 = LED_ON;
    case 1: BAT_LED1 = LED_ON;
    default: break;
    }

#ifdef DEBUG_MODE
    PrintfString1("BAT level: %bd\r\n", level);
#endif
}

/*============================================================================*/
/*                           状态切换函数                                      */
/*============================================================================*/

/**
 * @brief 进入开机状态(SYS_ON)
 *
 * 初始化所有外设, 开启断电监控, 状态LED亮起,
 * 立即读取一次电池电压并显示电量
 */
void enterOnState(void) {
    sysState = SYS_ON;

    /* 初始化外设 */
    UART_config();
    Timer_config();
    ADC_config();
    PWM_config();

    /* 配置INT0(电源信号), 禁用INT2(关机唤醒) */
    Exti_config();
    NVIC_INT2_Init(DISABLE, Priority_2);

    /* 默认开启断电监控 */
    monitorEnabled = 1;
    IO_LED_Status = LED_ON;

    /* 清除标志位 */
    powerFailFlag = 0;
    powerRestoreFlag = 0;
    keyShortPress = 0;
    keyLongPress = 0;
    keyCnt = 0;
    keyFlag = 0;
    keyShortFlag = 0;
    adcIntervalCnt = 0;

#ifdef DEBUG_MODE
    PrintString1("=> SYS_ON\r\n");
#endif

    /* 读取并显示当前电量 */
    readAndDisplayBattery();
}

/**
 * @brief 进入关机状态(SYS_OFF)
 *
 * 关闭所有LED和外设, 启用INT2(P3.6)用于按键唤醒,
 * 进入STOP低功耗模式
 */
void enterOffState(void) {
    sysState = SYS_OFF;

#ifdef DEBUG_MODE
    PrintString1("=> SYS_OFF\r\n");
    delay_ms(50);
#endif

    /* 关闭照明和所有LED */
    lightOff();
    allLedsOff();

    /* 禁用INT0(电源信号) */
    NVIC_INT0_Init(DISABLE, Priority_3);

    /* 关闭外设 */
    Timer1_Stop();
    ADC_PowerOn(0);
    PWMA_DIS();

    /* 启用INT2(P3.6按键下降沿)用于唤醒 */
    NVIC_INT2_Init(ENABLE, Priority_2);
}

/**
 * @brief 进入应急照明状态(SYS_EMERGENCY)
 *
 * 开启照明LED(PWM), 启动10分钟倒计时,
 * 持续监测电池电压
 */
void enterEmergencyState(void) {
    sysState = SYS_EMERGENCY;
    emergencyTimerCnt = 0;
    adcIntervalCnt = 0;

    /* 开启照明LED */
    lightOn();

#ifdef DEBUG_MODE
    PrintString1("=> SYS_EMERGENCY\r\n");
#endif

    /* 立即读取一次电池电压 */
    readAndDisplayBattery();
}

/**
 * @brief 进入休眠状态(SYS_SLEEP)
 *
 * 关闭照明和LED, 关闭外设,
 * INT0保持使能等待通电信号(上升沿)唤醒
 */
void enterSleepState(void) {
    sysState = SYS_SLEEP;

#ifdef DEBUG_MODE
    PrintString1("=> SYS_SLEEP\r\n");
    delay_ms(50);
#endif

    /* 关闭照明和所有LED */
    lightOff();
    allLedsOff();

    /* 关闭外设, INT0保持使能 */
    Timer1_Stop();
    ADC_PowerOn(0);
    PWMA_DIS();

    /* 清除标志 */
    powerRestoreFlag = 0;
    powerFailFlag = 0;
}

/*============================================================================*/
/*                             主函数                                          */
/*============================================================================*/

void main(void) {
    u8 i;

    EAXSFR();

    /* 硬件初始化 */
    GPIO_config();
    Exti_config();
    UART_config();
    Timer_config();
    ADC_config();
    PWM_config();

    EA = 1;

#ifdef DEBUG_MODE
    PrintString1("STC8H Fire Emergency Lamp v2.0\r\n");
#endif

    /* 开机动画: 电量LED依次点亮 */
    delay_ms(200);
    BAT_LED1 = LED_ON;
    delay_ms(200);
    BAT_LED2 = LED_ON;
    delay_ms(200);
    BAT_LED3 = LED_ON;
    delay_ms(200);
    BAT_LED4 = LED_ON;
    delay_ms(200);
    IO_LED_Status = LED_ON;
    delay_ms(250); delay_ms(250);
    delay_ms(250); delay_ms(250);

    /* 进入开机状态 */
    enterOnState();

    /*========================================================================*/
    /*                         状态机主循环                                     */
    /*========================================================================*/
    while (1) {
        switch (sysState) {

        /*--------------------------------------------------------------------*/
        /* SYS_ON: 开机状态                                                    */
        /*   - 1ms节拍驱动按键扫描和ADC采样                                      */
        /*   - 短按切换监控, 长按关机                                            */
        /*   - 断电信号触发应急照明                                              */
        /*--------------------------------------------------------------------*/
        case SYS_ON:
            if (B_1ms) {
                B_1ms = 0;
                KeyScan();
                adcIntervalCnt++;
            }

            /* 短按: 切换断电监控开关 */
            if (keyShortPress) {
                keyShortPress = 0;
                monitorEnabled = !monitorEnabled;
                IO_LED_Status = monitorEnabled ? LED_ON : LED_OFF;
                if (!monitorEnabled) {
                    powerFailFlag = 0;
                }
#ifdef DEBUG_MODE
                PrintfString1("Monitor: %s\r\n", monitorEnabled ? "ON" : "OFF");
#endif
            }

            /* 长按: 关机 */
            if (keyLongPress) {
                keyLongPress = 0;
                enterOffState();
                break;
            }

            /* 断电信号检测 */
            if (powerFailFlag && monitorEnabled) {
                powerFailFlag = 0;
                enterEmergencyState();
                break;
            }

            /* 每10秒读取电池电压 */
            if (adcIntervalCnt >= ADC_INTERVAL_MS) {
                adcIntervalCnt = 0;
                readAndDisplayBattery();
            }
            break;

        /*--------------------------------------------------------------------*/
        /* SYS_EMERGENCY: 应急照明状态                                          */
        /*   - 照明LED持续亮灯, 10分钟倒计时                                     */
        /*   - 电池电压过低时提前关灯                                            */
        /*   - 倒计时结束或电压过低 → 进入休眠                                    */
        /*--------------------------------------------------------------------*/
        case SYS_EMERGENCY:
            if (B_1ms) {
                B_1ms = 0;
                emergencyTimerCnt++;
                adcIntervalCnt++;
            }

            /* 每10秒检测电池电压 */
            if (adcIntervalCnt >= ADC_INTERVAL_MS) {
                adcIntervalCnt = 0;
                readAndDisplayBattery();
            }

            /* 10分钟到期 或 电池电压过低 → 结束应急 */
            if (emergencyTimerCnt >= EMERGENCY_TIME_MS ||
                lastBatVoltage < BAT_VOLTAGE_LOW) {
#ifdef DEBUG_MODE
                if (lastBatVoltage < BAT_VOLTAGE_LOW) {
                    PrintString1("BAT LOW, stop early\r\n");
                } else {
                    PrintString1("10min timeout\r\n");
                }
#endif
                /* 若应急期间电源已恢复, 直接回到开机状态 */
                if (powerRestoreFlag) {
                    powerRestoreFlag = 0;
                    powerFailFlag = 0;
                    lightOff();
                    allLedsOff();
                    enterOnState();
                } else {
                    enterSleepState();
                }
                break;
            }
            break;

        /*--------------------------------------------------------------------*/
        /* SYS_SLEEP: 休眠状态                                                 */
        /*   - 所有外设已关闭, INT0保持使能                                      */
        /*   - 进入STOP模式, 等待通电信号(P3.2上升沿)唤醒                         */
        /*--------------------------------------------------------------------*/
        case SYS_SLEEP:
            /* 若电源已恢复(P3.2=HIGH), 跳过休眠直接开机 */
            if (POWER_SIGNAL || powerRestoreFlag) {
                powerRestoreFlag = 0;
                powerFailFlag = 0;
                enterOnState();
                break;
            }

            /* 进入STOP低功耗模式 */
            PCON |= 0x02;
            _nop_();
            _nop_();

            /* --- MCU被INT0唤醒后从此处继续执行 --- */

            if (powerRestoreFlag) {
                powerRestoreFlag = 0;
                powerFailFlag = 0;
                enterOnState();
            }
            /* 非通电唤醒(如噪声), 继续循环回到STOP */
            break;

        /*--------------------------------------------------------------------*/
        /* SYS_OFF: 关机状态                                                    */
        /*   - 所有外设已关闭, INT2(P3.6)使能                                    */
        /*   - 进入STOP模式, 等待按键唤醒                                        */
        /*   - 唤醒后检测长按才开机, 短按继续休眠                                  */
        /*--------------------------------------------------------------------*/
        case SYS_OFF:
            /* 进入STOP低功耗模式 */
            PCON |= 0x02;
            _nop_();
            _nop_();

            /* --- MCU被INT2唤醒后从此处继续执行 --- */

            /* 禁用INT2, 避免重复触发 */
            NVIC_INT2_Init(DISABLE, Priority_2);

            /* 检测是否为长按(1.5秒) */
            for (i = 0; i < 15; i++) {
                delay_ms(100);
                if (KEY1) {
                    break;
                }
            }

            if (i >= 15) {
                /* 长按确认: 开机 */
                enterOnState();
            } else {
                /* 短按: 重新启用INT2, 继续休眠 */
                NVIC_INT2_Init(ENABLE, Priority_2);
            }
            break;
        }
    }
}
