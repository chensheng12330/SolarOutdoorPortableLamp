#include <STC8.H>

#define ADC_CHANNEL 0    // ADC通道选择
#define VOLTAGE_HIGH 125  // 高电压阈值，对应12.5V
#define VOLTAGE_LOW 85    // 低电压阈值，对应8.5V

sbit IO_HIGH = P1^0;  // 控制IO引脚为高电平
sbit IO_LOW = P1^1;   // 控制IO引脚为低电平
sbit LED = P0^0;      // LED引脚
sbit UART1_BUSY = P3^1;  // 串口1忙碌标志位

unsigned int high_count = 0;  // 统计IO_HIGH为1的次数

void InitIO() {
    IO_HIGH = 0;  // 初始化IO引脚为低电平
    IO_LOW = 0;   // 初始化IO引脚为低电平
    LED = 0;      // 初始化LED引脚为低电平
}

void InitADC() {
    ADC_CONTR = 0x80;   // ADC基本配置
    ADC_RES = 0;        // 清除上次结果
    ADC_CONTR = ADC_CONTR & 0xf8 | ADC_CHANNEL;  // 选择ADC通道
}

unsigned int GetADCResult() {
    ADC_CONTR |= 0x08;  // 开始转换
    while (!(ADC_CONTR & 0x10));  // 等待转换完成
    return ((ADC_RES << 2) | (ADC_RESL & 0x03));  // 返回ADC结果
}

void WriteToEEPROM(unsigned char addr, unsigned char dat) {
    IAP_CONTR = 0x82;  // 开启EEPROM写操作
    IAP_ADDRH = 0x00;  // EEPROM地址高位为0
    IAP_ADDRL = addr;  // 设置EEPROM地址
    IAP_DATA = dat;    // 设置要写入的数据
    IAP_TRIG = 0x5a;   // 触发EEPROM写操作
    IAP_TRIG = 0xa5;
    _nop_();
    _nop_();
    IAP_CONTR = 0x00;  // 关闭EEPROM写操作
}

void UART1_SendByte(unsigned char dat) {
    while (UART1_BUSY);  // 等待UART1空闲
    SBUF_1 = dat;  // 发送数据
}

void UART1_SendString(unsigned char *str) {
    while (*str != '\0') {
        UART1_SendByte(*str);
        str++;
    }
}

void delay(unsigned int t) {
    unsigned int i, j;
    for (i = 0; i < t; i++)
        for (j = 0; j < 120; j++);
}

void main() {
    unsigned int adc_value;
    unsigned char high_count_str[5];  // 用于存储high_count的字符串表示形式

    InitIO();   // 初始化IO引脚
    InitADC();  // 初始化ADC

    while (1) {
        adc_value = GetADCResult();  // 读取ADC值

        if (adc_value < VOLTAGE_LOW) {
            IO_HIGH = 1;  // 控制IO引脚为高电平
            high_count++; // 统计IO_HIGH为1的次数
        } else if (adc_value > VOLTAGE_HIGH) {
            IO_LOW = 0;  // 控制IO引脚为低电平
        }

        // LED每5秒亮一次，持续1秒
        LED = 1;  // LED亮
        delay(200);  // 等待200ms
        LED = 0;  // LED灭
        delay(4300);  // 等待4300ms

        // 每隔一段时间将高电平次数写入EEPROM
        if (high_count >= 10) {  // 每10次写入一次EEPROM
            WriteToEEPROM(0, high_count);  // 写入高电平次数到EEPROM地址0
            high_count = 0;  // 清零统计
        }

        // 检测串口1通信信号，发送当前的high_count数据
        if (!UART1_BUSY) {  // 如果串口1空闲
            sprintf(high_count_str, "%d", high_count);  // 将high_count转换为字符串
            UART1_SendString(high_count_str);  // 发送high_count字符串
            UART1_SendByte('\r');  // 发送回车符
            UART1_SendByte('\n');  // 发送换行符
        }
    }
}


///////按键示例/////
/*******按键检测扫描程序*********/
void Key_scan()
{ 
/**********按键1检测**************/        
        if(key1==1)//按键1未被按下检测
        { //按键1短按，吸合电磁阀
                key_lock1=0;  //按键1自锁标志清零
                delay_cnt1=0; //按键1去抖动延时计数器清零        
          if(key_lock1_Short==1) //短按的触发标志等于1，检测短按已经松开
                {
                  key_lock1_Short=0;//短按的触发标志清零
                  key_sec=1;//触发1号键，按键1吸合电磁阀        
                }
        }//按键1花
        else //key1==0 按键按下
        { 
                if(key_lock1==0)//有按键按下，且已经解锁
                {
                        ++delay_cnt1;//去抖自增
                        if(delay_cnt1>cnt_delay_cnt1)//滤波检测
                        {        
                                key_lock1_Short=1;//短按锁紧
                                if(delay_cnt1>cnt_delay_cnt3)//长按检测
                                {
                                        key_lock1_Short=0;
                                        delay_cnt1=0;//按键去抖动延时计数器清零
                                        key_lock1=1;//自锁按键置1,避免一直触发
                                        key_sec=6;//触发是6按键选择值
                                }//长按去抖判断
                        }//短按去抖判断
                }//进入按下判断
        }//按键1 else花
        
/**********按键2检测**************/
        if(key2==1)        //按键2是P3.7
        {
                key_lock2=0;//按键自锁标志清零
                delay_cnt2=0;//按键去抖动延时计数器清零        
        }
        else
        {
                if(key_lock2==0)//key_lock2是按键自锁标志2 有按键按下，且是第一次被按下
                {
                        ++delay_cnt2;//去抖动延时计数2自增
                        if(delay_cnt2>cnt_delay_cnt1) //cnt_delay_cnt1是按键去抖动延时阀值
                        {        
                                delay_cnt2=0;//去抖动延时计数清零
                                key_lock2=1;//自锁按键置1,避免一直触发
                          key_sec=2;//触发2号键                          
                        }
                }
        }
        
/**********位置传感器1检测是按照按键3判断（C1=P3^3; 位置1 查原理图）*********/
        if(C1==1)// 位置1未到位
        {
                ++delay_cnt6;//位置1检测未到位去抖动延时计数6自增
                if(delay_cnt6>cnt_delay_cnt1)//按键去抖动延时阀值240 稳定检测未到位则清零位；
                {
                        key_lock3=0;//位置1按键锁3解锁清零
                        delay_cnt6=0;//位置1按键去抖动计数清零   
                }//位置1未到位清零花
                delay_cnt3=0;//位置1到位延时去抖计数3清零   
        }//未到位判断花
        else if(C1==0)//检测位置1到位
        {
                delay_cnt6=0;//位置1检测未到位去抖动延时计数6
                ++delay_cnt3;//位置1检测到位延时计数自增
                if(delay_cnt3>cnt_delay_cnt1)//按键延时去抖阀值  240
                {        
                        delay_cnt3=0;//延时计数清零
                        key_lock3=1;//位置1按键锁3置位锁紧,避免一直触发
                }//位置1检测到位处理花
        }//位置1检测到位判断花

/***位置传感器2检测按照按键4判断*****/

        if(C2==1)//位置2未检测到位
        {
                ++delay_cnt7;//位置2检测未到位延去抖
                if(delay_cnt7>cnt_delay_cnt1)//cnt_delay_cnt1是按键延时去抖阀值
                {        
                        delay_cnt7=0;//位置2延时计数清零
                        key_lock4=0;//位置2按键锁4清零解锁, 
                }
                delay_cnt4=0;//位置2检测到位按键去抖动延时计数器清零        
        }
        else if(C2==0)//位置2检测到位
        {
                ++delay_cnt4;//位置2到位延时去抖计数自增
                if(delay_cnt4>cnt_delay_cnt1)//延时计数大于去动阈值，去抖完成
                {        
                        delay_cnt4=0;//位置2到位延时去抖计数清零
                        key_lock4=1;//位置2按键锁4置位,避免一直触发
                }
                delay_cnt7=0;//位置2未到位延时计数清零
        }
        
        
/****无线信号检测按照按键5检测（WX=P3^2对应的按键5;）******/
        if(WX==1)        //未检测无线信号，标志清零
        {
                key_lock5=0;  //按键自锁标志5清零
                delay_cnt5=0; //按键去抖动延时计数器5清零        
        }
        else //WX==0 检测到标志的去抖，判断
        {
                if(key_lock5==0)  //判定自锁标志5状态为0，开始去抖动
                {
                        ++delay_cnt5;  //延时去抖计数自增
                        if(delay_cnt5>cnt_delay_cnt2)//延时去抖完毕
                        {        
                                delay_cnt5=0;//延时去抖计数清零
                                key_lock5=1;//自锁按键置位,避免一直触发
                          key_sec=5;//无线信号                  
                        }//触发按键及标志清零花
                }//检测到无线信号花
        }//检测无线信号花
        
}//按键扫描检测花

/**************按键服务子程序*****************/
void key_server()//按键服务子程序
{        
        if(key_sec==1)//直行键
        {        
                
                key_sec=0;//触发键值清0
                Flag_work=1;//工作标志置1
                if(Flag_position==1)//1直行
                {
                
                d1=1;//关闭电磁阀1
                d2=1; //关闭电磁阀2

                }
                else //Flag_position==0  拐弯变直行动作
                {
                
    led_L=1;//关闭左箭头指示灯
                led_U=1;//关闭上箭头指示灯
                led_O=1;//关闭红色圆形指示灯        
                d1=1;//关闭电磁阀1 d1 =P1^0;
                d2=0;//开启电磁阀2 d2 =P1^1;
                Flag_position=1;//道岔位置直行
                Time_error=0;//定时器报错清零        

                }  
                
        }//按键1判断花
        
        if(key_sec==2)//拐弯按键
        {        
                key_sec=0;        //触发键值清0
                Flag_work=1;//工作标志置1
                if(Flag_position==0)
                {
                        
                d1=1;//关闭电磁阀1
                d2=1; //关闭电磁阀2
                        
                }
                else //Flag_position==1  直行变拐弯动作
                {
                led_L=1;//关闭左箭头指示灯灭(P1^4)
                led_U=1;//关闭上箭头指示灯灭（P1^5）
                led_O=1;//关闭红色圆形指示灯
                d1=0;//开启右电磁阀1 （0开1关）伸展拐弯
                d2=1;//关闭左电磁阀2 （0开1关）回缩
                Flag_position=0;//道岔位置左拐
                Time_error=0;//报错次数清零
                
          }                
        }        
/*******无线信号键值的判断处理*********/
        if(key_sec==5)//按键选择值是5无线信号触发
        {        
                  key_sec=0;//触发键值清0
                  Flag_work=1;//工作标志
                        
                if(Flag_position==0) //由拐弯到直行动作
                {        
                                        
                        //拐弯变成直行
                        Flag_position=1;//道岔位置直行
                        d1=1;//关闭电磁阀1伸展
                        d2=0;//开启电磁阀2回缩动作
                        led_L=1;//关闭左箭头指示灯
                        led_U=1;//关闭上箭头指示灯
                        

                }//拐弯位置判断子花        
                
                else //Flag_position==1  直行变拐弯动作
                {
                        
                        //直行变成拐弯
                        Flag_position=0;//道岔位置在拐弯
                        d1=0;//开启电磁阀1 （0开1关）
                        d2=1;//关闭电磁阀2
                        led_L=1;//关闭灯led_L
                        led_U=1;//关闭灯led_U=1


                }//直行位置判断子花
                
        }//判断无线触发编码判断花
        
/**********对码学习键值判断处理****************/
        if(key_sec==6)//按键选择值是6        //调节数字  对码学习 查找：key_sec=6   P103行按键检测
        {        
                key_sec=0;//按键选择变量清零 //触发键值清0
                YY_OUT=0;//开启语音输出（低开高关）判断显示主控的语音输入口长按
                Delay1000ms();//延时1秒
                YY_OUT=1;//关闭语音输出
        }
        
}//按键服务程序结束花 
//********************各个功能子程序*******************************//

/**********************主程序***************************************/
void main()
{        
//Buzzer_dr=0;//蜂鸣器初始化
        Init_IO();//IO初始化
//  Init_Timer0(); 
        Timer1Init();////1毫秒@11.0592MHz 定时器初始化
//  Init_Uart1();
        d1=1;//关闭电磁阀1
        d2=1;//关闭电磁阀2
        YY_OUT=1;//关闭语音输出
        YY_OUT_2=1;//关闭语音输出2


  while(1)
        {        
//          key_server();//按键触发值任务处理
                if(Flag_Second==1)//Flag_Second是秒计数标志  Flag_Second=1 定时器1中断
                {
                        U8 j;        
                        U8 i;        
                        Flag_Second=0;//秒计时标志清零        
                        if(Flag_work==1) //工作标志置1
                        {
                                led_O=~led_O;//灯led_O取反
                                Time_S++;//秒计数自增
                                if(Time_S>=5)//秒计数大于等于5，则
                                {
                                        Flag_work=0;//工作标志清零，不工作状态/工作异常状态  Flag_work==0
                                  Time_S=0;//秒计数清零  
                                }
                        }//工作标志为1花
                        else//Flag_work==0
                        { 
/***************检测到位有关*******************************/
                                if(key_lock3==0 && key_lock4==0 )//按键自锁标志3和4都为0，就是应该检测到的没有检测到，所以两个都是0
                                { 
                                        led_O=~led_O;//灯O取反
                                        led_L=1;//关闭led_L
                                        led_U=1;//关闭led_L
                                        Time_error++;//报错次数自增
                                }
                                
                                //key_lock3位置1和key_lock4位置2都是1锁紧状态，故障状态
                                if(key_lock3==1 && key_lock4==1 )//按键自锁标志3和4都为1，正常是不出现的；
                                { 
                                        led_O=~led_O;//O型灯翻转
                                        led_L=1;//关闭左箭头指示灯
                                        led_U=1;//关闭上箭头指示灯
                                        Time_error++;//报错次数
                                }        
                                
                                
                        }//else判断Flag_Second==0时花
                        
      //控制语音播报
                        if(Time_error>=10) //报错次数大于等于10；
                        {                                
                                Time_error=0;//报错计数清零
                                YY_OUT=0;//开启语音播报
                                led_L=1;//关闭左箭头指示灯
                                led_U=1;//关闭上箭头指示灯
                                led_O=1;//关闭红色圆形指示灯
                                delayms(100);//延时100ms
                                YY_OUT=1;//关闭语音播报
                                delayms(200);//延时时间

                        }         
                                             
      //按键自锁标志3等于0,且4为1,且工作标志0  key_lock4=C2=拐弯；key_lock3=C1=直行；
                        if(key_lock3==0 && key_lock4==1 && Flag_work==0)//拐弯检测
                        { 
                                
                                j=0;
                                led_L=0;//开启拐弯指示灯
                                led_U=1;//关闭直行指示灯
                                led_O=1;//关闭圈型指示灯
                                d1=1;//关闭电磁阀1
                                d2=1;//关闭电磁阀2
                                Time_error=0;//报错计数清零
                                Flag_position=0;//道岔位置直
                                
                                if(i<3)
                                {
                          YY_OUT_2=0;//开启语音播报
              delayms(1000);//延时1000ms
                    YY_OUT_2=1;//关闭语音播报
                                delayms(1000);//延时1000ms,
                                i++;
                                }

                        } 
                        
                        if(key_lock3==1 && key_lock4==0  && Flag_work==0)//直行检测
                        {  
                                
                
                                i=0;
                                led_L=1;//关闭左拐箭头指示灯
                                led_U=0;//开启直行指示灯
                                led_O=1;//关闭圆形红色指示灯
                                d1=1;//关闭电磁阀1
                                d2=1;//关闭电磁阀2                                
                                Time_error=0;//报错计数清零
                                Flag_position=1;//道岔位置为直行；
                                
                                if(j<3)
                                {
                          YY_OUT_2=0;//开启语音播报
              delayms(100);//延时100ms
                    YY_OUT_2=1;//关闭语音播报
                                delayms(1900);//延时1900ms,
        j++;                                        
                                }
                                
                           }
                         
                }//秒标志等于1花 
        }//while花        
}//主函数花
/*********定时器T1中断函数********/

void Time1_isr() interrupt 3 using 1 //1ms进入一次中断，扫描按键，定时器1中断
{        
        Key_scan();//先判断按键扫描函数，是否有按键按下；
        key_server();//按键触发值任务处理        
        ++interrupt_cnt; //1秒钟需要的中断次数累加
        if(interrupt_cnt>=400) //cnt_1s一秒钟需要多少次定时中断。时间的精度校正就是靠修改cnt_1s这个数据。
        {        
                interrupt_cnt=0;//中断计数清零
                Flag_Second=1;//定时1到时间，秒标志置1
        }
}

定时器部分
/*************************
系统频率：11.0592MHz   定时器T1
定时长度：100us  定时模式：16位自动重装
误差率：0.00%    定时时钟：1T（FOSC）
************************/
void Timer1Init(void)//1毫秒@11.0592MHz
{
        //定时器配置；
        AUXR |= 0x40;//定时器时钟1T模式（即CPU时钟不分频分频（FOSC/1））
        TMOD &= 0x0F;//设置定时器1模式:只有TR1=1才允许计时，定时模式，16位自动重装
        TL1 = 0xAE;                                //设置定时初始值
        TH1 = 0xFB;                                //设置定时初始值
        TF1 = 0;//定时器1溢出标志位TF1清除
        TR1 = 1;//定时器1开始计时
        //开中断
        ET1 = 1;//开定时器中断
        EA=1;//开总中断/CPU开中断
}

STCMCU按键功能 - 未测试
#ifndef __YUYY_KEY_H_
#define __YUYY_KEY_H_
#include "config.h"

#define KEYNUMS 4          // 按键总数
#define KEYSCANINTERVAL 10 // 按键扫描间隔
#define DEBOUNCETIME 30    // 去抖时间
#define LONGPRESSTIME 2000 // 长按识别时间
#define KEYPORT P3         // 按键io端口号
#define KEYIOSTART 2       // 按键io起始值 屠龙刀的按键从P3.2开始

    enum YUYY_KEYSTATE {
            KEY_UP = 0,      // 按键未按下
            KEY_DOWN,        // 按键按下
            KEY_SINGLECLICK, // 单击按键 按下按键后在LONGPRESSTIME之前松开
            KEY_LONGPRESS,   // 长按按键 按下按键的时间超过LONGPRESSTIME
            KEY_LONGPRESSUP  // 长按后松开
    };
// 定义回调
typedef void (*yuyy_key_cb)(uint8_t keynum, enum YUYY_KEYSTATE state);

/**
 * 10ms一次检查按键状态
 */
void yuyy_keyloop(void);
/**
 * 设置回调函数
 * 外部文件通过回调函数监控按键状态
 */
void yuyy_setkeycb(yuyy_key_cb cb);
#endif

#include "yuyy_key.h"

uint16_t keydowncount[KEYNUMS] = {0};
yuyy_key_cb keycb;

void sendkeystate(uint8_t keynum, enum YUYY_KEYSTATE state)
{
        if (keycb)
        {
                keycb(keynum, state);
        }
}

void yuyy_keyloop(void)
{
        uint8_t i = 0;
        while (i < KEYNUMS)
        {
                if ((~KEYPORT) & (1 << (i + KEYIOSTART)))
                {
                        if (keydowncount[i] < 0xFFFF)
                        {
                                keydowncount[i]++;
                        }
                        if (keydowncount[i] * KEYSCANINTERVAL == DEBOUNCETIME)
                        {
                                sendkeystate(i, KEY_DOWN);
                        }
                        if (keydowncount[i] * KEYSCANINTERVAL == LONGPRESSTIME)
                        {
                                sendkeystate(i, KEY_LONGPRESS);
                        }
                }
                else
                {
                        if (keydowncount[i] * KEYSCANINTERVAL > DEBOUNCETIME)
                        {
                                if (keydowncount[i] * KEYSCANINTERVAL < LONGPRESSTIME)
                                {
                                        sendkeystate(i, KEY_SINGLECLICK);
                                }
                                else
                                {
                                        sendkeystate(i, KEY_LONGPRESSUP);
                                }
                        }
                        keydowncount[i] = 0;
                }
                i++;
        }
}

void yuyy_setkeycb(yuyy_key_cb cb)
{
        keycb = cb;
}

#include "yuyy_key.h"
uint16_t time0counter = 0;
// 使用USB-HID打印按键状态变化
void test_keystate_changed(uint8_t keynum, enum YUYY_KEYSTATE state)
{
        switch (state)
        {
        case KEY_DOWN:
                printf_hid("按键%d 按下\r\n", keynum);
                break;
        case KEY_SINGLECLICK:
                printf_hid("按键%d 单击\r\n", keynum);
                break;

        case KEY_LONGPRESS:
                printf_hid("按键%d 长按\r\n", keynum);
                break;
        case KEY_LONGPRESSUP:
                printf_hid("按键%d 长按松开\r\n", keynum);
                break;

        default:
                break;
        }
}

void Timer0_Init(void) // 1毫秒@24.000MHz
{
        TMOD &= 0xF0; // 设置定时器模式
        TL0 = 0x30;   // 设置定时初始值
        TH0 = 0xF8;   // 设置定时初始值
        TF0 = 0;      // 清除TF0标志
        ET0 = 1;      // 开启中断
        TR0 = 1;      // 定时器0开始计时
}

void timer0_int(void) interrupt 1 // 1ms 中断函数
{
        if (time0counter < 10)
        {
                time0counter++;
        }
        else
        {
                time0counter = 0;
                yuyy_keyloop();
        }
}

// main函数中（省略了其它初始化代码）
Timer0_Init();
yuyy_setkeycb(test_keystate_changed);
while (1)
{
}