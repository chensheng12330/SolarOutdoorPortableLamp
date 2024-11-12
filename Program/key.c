/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序        */
/*---------------------------------------------------------------------*/

/*************  功能说明    **************

按键(P3.2)每1毫秒扫描一次，连续50ms为低电平则判定按键有效

按键(P3.3)每1毫秒扫描一次，连续1s为低电平则判定按键长按有效，连续低电平时间大于50ms小于1s则判定为按键短按有效

每次有效按键从串口1(P3.0,P3.1)打印一串字符串，串口默认设置：115200,N,8,1

下载时, 选择时钟 11.0592MHZ (用户可自行修改频率).

******************************************/

#include    "reg51.h"   //包含芯片头文件后(如"stc8h.h")，不用再包含"reg51.h"
#include    "stdio.h"

#define     MAIN_Fosc       11059200L   //定义主时钟
#define     BAUD            115200
#define     TM              (65536 -(MAIN_Fosc/BAUD/4))
#define     Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 中断频率, 1000次/秒

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

//包含芯片头文件后，下列寄存器可以不用手动定义
sfr P_SW1 = 0xa2;
sfr P_SW2 = 0xba;
sfr AUXR = 0x8E;
sfr T2H  = 0xD6;
sfr T2L  = 0xD7;

sfr P4   = 0xC0;
sfr P5   = 0xC8;
sfr P6   = 0xE8;
sfr P7   = 0xF8;
sfr P1M1 = 0x91;    //PxM1.n,PxM0.n     =00--->Standard,    01--->push-pull
sfr P1M0 = 0x92;    //                  =10--->pure input,  11--->open drain
sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P3M1 = 0xB1;
sfr P3M0 = 0xB2;
sfr P4M1 = 0xB3;
sfr P4M0 = 0xB4;
sfr P5M1 = 0xC9;
sfr P5M0 = 0xCA;
sfr P6M1 = 0xCB;
sfr P6M0 = 0xCC;
sfr P7M1 = 0xE1;
sfr P7M0 = 0xE2;

sbit P00 = P0^0;
sbit P01 = P0^1;
sbit P02 = P0^2;
sbit P03 = P0^3;
sbit P04 = P0^4;
sbit P05 = P0^5;
sbit P06 = P0^6;
sbit P07 = P0^7;
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;
sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P22 = P2^2;
sbit P23 = P2^3;
sbit P24 = P2^4;
sbit P25 = P2^5;
sbit P26 = P2^6;
sbit P27 = P2^7;
sbit P30 = P3^0;
sbit P31 = P3^1;
sbit P32 = P3^2;
sbit P33 = P3^3;
sbit P34 = P3^4;
sbit P35 = P3^5;
sbit P36 = P3^6;
sbit P37 = P3^7;
sbit P40 = P4^0;
sbit P41 = P4^1;
sbit P42 = P4^2;
sbit P43 = P4^3;
sbit P44 = P4^4;
sbit P45 = P4^5;
sbit P46 = P4^6;
sbit P47 = P4^7;
sbit P50 = P5^0;
sbit P51 = P5^1;
sbit P52 = P5^2;
sbit P53 = P5^3;
sbit P54 = P5^4;
sbit P55 = P5^5;
sbit P56 = P5^6;
sbit P57 = P5^7;

#define P0PU     (*(unsigned char  volatile xdata *)  0xFE10)
#define P1PU     (*(unsigned char  volatile xdata *)  0xFE11)
#define P2PU     (*(unsigned char  volatile xdata *)  0xFE12)
#define P3PU     (*(unsigned char  volatile xdata *)  0xFE13)
//以上为手动定义用到的寄存器

sbit KEY1 = P3^2;
sbit KEY2 = P3^3;

u16 Key1_cnt;
u16 Key2_cnt;
bit Key1_Flag;
bit Key2_Flag;
bit B_1ms;          //1ms标志
bit Key2_Short_Flag;
bit Key2_Long_Flag;

bit Key1_Function;
bit Key2_Short_Function;
bit Key2_Long_Function;

void delay_ms(u8 ms);
void Timer0_config(void);
void KeyScan(void);

void PrintfInit(void)
{
    P_SW1 = (P_SW1 & 0x3f) | 0x00;    //USART1 switch to, 0x00: P3.0 P3.1, 0x40: P3.6 P3.7, 0x80: P1.6 P1.7, 0xC0: P4.3 P4.4
    SCON = (SCON & 0x3f) | 0x40; 
    AUXR |= 0x40;		//定时器时钟1T模式
    AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
    TL1  = TM;
    TH1  = TM>>8;
    TR1 = 1;				//定时器1开始计时

//    SCON = (SCON & 0x3f) | 0x40; 
//    T2L  = TM;
//    T2H  = TM>>8;
//    AUXR |= 0x15;		//串口1选择定时器2为波特率发生器
}
 
void UartPutc(unsigned char dat)
{
    SBUF = dat; 
    while(TI == 0); 
    TI = 0;
}
 
char putchar(char c)
{
    UartPutc(c);
    return c;
}

/******************** 主函数 **************************/
void main(void)
{
    P_SW2 |= 0x80;		//使能XFR访问

    P0M1 = 0x00;   P0M0 = 0x00;   //设置为准双向口
    P1M1 = 0x00;   P1M0 = 0x00;   //设置为准双向口
    P2M1 = 0x00;   P2M0 = 0x00;   //设置为准双向口
    P3M1 = 0x0c;   P3M0 = 0x00;   //设置P3.2，P3.3为高阻输入
    P4M1 = 0x00;   P4M0 = 0x00;   //设置为准双向口
    P5M1 = 0x00;   P5M0 = 0x00;   //设置为准双向口
    P6M1 = 0x00;   P6M0 = 0x00;   //设置为准双向口
    P7M1 = 0x00;   P7M0 = 0x00;   //设置为准双向口

    P3PU |= 0x0c;		//使能P3.2，P3.3口上拉

    Timer0_config();
    PrintfInit();
    EA = 1;     //打开总中断

    printf("Key pressed test.\r\n");

    while (1)
    {
        //delay_ms(1);
        if(B_1ms == 1)	//1ms检测一次
        {
            B_1ms = 0;
            KeyScan();
            if(Key1_Function)
            {
                Key1_Function = 0;
                printf("Key1 pressed.\r\n");
                P20 = !P20;
            }
            if(Key2_Short_Function)
            {
                Key2_Short_Function = 0;
                printf("Key2 short pressed.\r\n");
                P21 = !P21;
            }
            if(Key2_Long_Function)
            {
                Key2_Long_Function = 0;
                printf("Key2 long pressed.\r\n");
                P22 = !P22;
            }
        }
    }
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
    //单纯短按按键
    if(!KEY1)
    {
        if(!Key1_Flag)
        {
            Key1_cnt++;
            if(Key1_cnt >= 50)		//50ms防抖
            {
                Key1_Flag = 1;			//设置按键状态，防止重复触发
                Key1_Function = 1;
            }
        }
    }
    else
    {
        Key1_cnt = 0;
        Key1_Flag = 0;
    }

    //长按短按按键
    if(!KEY2)
    {
        if(!Key2_Flag)
        {
            Key2_cnt++;
            if(Key2_cnt >= 1000)		//长按1s
            {
                Key2_Short_Flag = 0;	//清除短按标志
                Key2_Long_Flag = 1;		//设置长按标志
                Key2_Flag = 1;				//设置按键状态，防止重复触发
                Key2_Long_Function = 1;
            }
            else if(Key2_cnt >= 50)		//50ms防抖
            {
                Key2_Short_Flag = 1;		//设置短按标志
            }
        }
    }
    else
    {
        if(Key2_Short_Flag)			//判断是否短按
        {
            Key2_Short_Flag = 0;	//清除短按标志
            Key2_Short_Function = 1;
        }
        Key2_cnt = 0;
        Key2_Flag = 0;	//按键释放
    }
}

//========================================================================
// 函数: void delay_ms(u8 ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~255ms. 自动适应主时钟.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
//void delay_ms(u8 ms)
//{
//    u16 i;
//    do{
//        i = MAIN_Fosc / 10000;
//        while(--i);   //10T per loop
//    }while(--ms);
//}

//========================================================================
// 函数: void Timer0_config(void)
// 描述: Timer0初始化函数。
// 参数: 无.
// 返回: 无.
// 版本: V1.0, 2020-6-10
//========================================================================
void Timer0_config(void)
{
    AUXR |= 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
    TH0 = (u8)(Timer0_Reload / 256);
    TL0 = (u8)(Timer0_Reload % 256);
    ET0 = 1;    //Timer0 interrupt enable
    TR0 = 1;    //Tiner0 run
}

/********************** Timer0 1ms中断函数 ************************/
void timer0(void) interrupt 1
{
    B_1ms = 1;
}
