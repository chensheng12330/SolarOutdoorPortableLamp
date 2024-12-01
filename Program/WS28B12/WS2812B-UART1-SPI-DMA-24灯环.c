
#define 	MAIN_Fosc		25600000UL	//定义主时钟

#include	"AI8051U.h"


/*************	功能说明	**************

请先别修改程序, 直接下载"SPI.hex"测试, 下载时选择主频24MHz或输入25.6MHz. 实测20~30MHz都能正常驱动。

使用SPI-MOSI输出直接驱动WS2812三基色彩灯, DMA传输，不占用CPU时间。本例驱动24个灯，接成环状。
本例使用USART1-SPI模式的P1.5-MOSI输出驱动信号直接驱动WS2812。
由于使用SPI主机模式，则P1.6、P1.7被SPI占用，不能做他用，但可以将P1.7-SCLK设置为高阻作为输入使用。
 DMA, 2分频, 一个字节需要时钟28T，
      4分频, 一个字节需要时钟44T。
      8分频, 一个字节需要时钟72T。
     16分频, 一个字节需要时钟144T。
DMA发送时间：@25.6MHz, DMA发送一个字节2.8125us，一个灯要发送12个字节33.75us，8192字节xdata最多一次驱动682个灯.

每个灯3个字节，分别对应绿、红、蓝则，MSB先发.
800KHz码率, 数据0(1/4占空比): H=0.3125us  L=0.9375us, 数据1(3/4占空比): H=0.9375us  L=0.3125us, RESET>=50us.
高电平时间要精确控制在要求的范围内, 低电平时间不需要精确控制, 大于要求的最小值并小于RES的50us即可.

WS2812S的标准时序如下:
TH+TL = 1.25us±150ns, RES>50us
T0H = 0.25us±150ns = 0.10us - 0.40us
T0L = 1.00us±150ns = 0.85us - 1.15us
T1H = 1.00us±150ns = 0.85us - 1.15us
T1L = 0.25us±150ns = 0.10us - 0.40us
两个位数据之间的间隔要小于RES的50us.

SPI方案:
本例使用USART1-SPI模式的P1.5-MOSI输出驱动信号直接驱动WS2812。
由于使用SPI主机模式，则P1.6、P1.7被SPI占用，不能做他用，但可以将P1.7-SCLK设置为高阻作为输入使用。

用SPI传输, 速度3.0~3.5MHz，以3.2MHz为最佳, MSB先发, 每个字节高4位和低4位分别对应一个位数据, 1000为数据0, 1110为数据1.
SPI数据位       D7 D6 D5 D4    D3 D2 D1 D0
SPI数据         1  0  0  0     1  1  1  0
               WS2812数据0    WS2812数据1
SPI数据高半字节对应的WS2812数据0-->0x80, 数据1-->0xe0,
SPI数据低半字节对应的WS2812数据0-->0x08, 数据1-->0x0e,
主频25.6MHz, SPI分频8 = 3.2MHz. 最佳.

******************************************/

/*************	本地常量声明	**************/


/*************	本地变量声明	**************/


/*************	本地函数声明	**************/

#define	COLOR	50				//亮度，最大255

#define	LED_NUM	24				//LED灯个数
#define	SPI_NUM	(LED_NUM*12)	//LED灯对应SPI字节数

u8	xdata  led_RGB[LED_NUM][3];	//LED对应的RGB，led_buff[i][0]-->绿，led_buff[i][1]-->红，led_buff[i][0]-->蓝.
u8	xdata  led_SPI[SPI_NUM];	//LED灯对应SPI字节数

bit	B_UR1T_DMA_busy;	//UR1T-DMA忙标志


/*************  外部函数和变量声明 *****************/
void	LoadSPI(void);
void	UART1_SPI_Config(u8 SPI_io, u8 SPI_speed);	//(SPI_io, SPI_speed), 参数:  SPI_io: 切换IO(SS MOSI MISO SCLK), 0: 切换到P1.4 P1.5 P1.6 P1.7,  1: 切换到P2.4 P2.5 P2.6 P2.7, 2: 切换到P4.0 P4.1 P4.2 P4.3,  3: 切换到P3.5 P3.4 P3.3 P3.2,
													//                            SPI_speed: SPI的速度, 0: fosc/4,  1: fosc/8,  2: fosc/16,  3: fosc/2
void	UR1T_DMA_TRIG(u8 xdata *TxBuf, u16 num);
void	delay_ms(u16 ms);



/*************** 主函数 *******************************/

void main(void)
{
	u16	i,k;
	u8	xdata *px;

	EAXFR = 1;	//允许访问扩展寄存器
	WTST  = 0;
	CKCON = 0;

	P1M1 = 0;	P1M0 = 0;

	UART1_SPI_Config(0, 1);	//(SPI_io, SPI_speed), 参数: SPI_io: 切换IO(SS MOSI MISO SCLK), 0: 切换到P1.4 P1.5 P1.6 P1.7,  1: 切换到P2.4 P2.5 P2.6 P2.7, 2: 切换到P4.0 P4.1 P4.2 P4.3,  3: 切换到P3.5 P3.4 P3.3 P3.2,
							//                           SPI_speed: SPI的速度, 0: fosc/4,  1: fosc/8,  2: fosc/16,  3: fosc/2
	EA = 1;
//	MCLKO47_DIV(100);	//主频分频输出，用于测量主频

	k = 0;		//

	while (1)
	{
		while(B_UR1T_DMA_busy)	;	//等待DMA完成

		px = &led_RGB[0][0];	//亮度(颜色)首地址
		for(i=0; i<(LED_NUM*3); i++, px++)	*px = 0;	//清除所有的颜色

		i = k;
		led_RGB[i][1] = COLOR;		//红色
		if(++i >= LED_NUM)	i = 0;	//下一个灯
		led_RGB[i][0] = COLOR;		//绿色
		if(++i >= LED_NUM)	i = 0;	//下一个灯
		led_RGB[i][2] = COLOR;		//蓝色

		LoadSPI();			//将颜色装载到SPI数据
		UR1T_DMA_TRIG(led_SPI, SPI_NUM);	//(u8 xdata *TxBuf, u16 num);

		if(++k >= LED_NUM)	k = 0;			//顺时针
	//	if(--k >= LED_NUM)	k = LED_NUM-1;	//逆时针
		delay_ms(50);
	}
}


//================ 延时函数 ==============
void  delay_ms(u16 ms)
{
	u16 i;
	do
	{
		i = MAIN_Fosc / 6000;
		while(--i)	;
	}while(--ms);
}



//================ 将颜色装载到SPI数据 ==============
void	LoadSPI(void)
{
	u8	xdata *px;
	u16	i,j;
	u8	k;
	u8	dat;

	for(i=0; i<SPI_NUM; i++)	led_SPI[i] = 0;
	px = &led_RGB[0][0];	//首地址
	for(i=0, j=0; i<(LED_NUM*3); i++)
	{
		dat = *px;
		px++;
		for(k=0; k<4; k++)
		{
			if(dat & 0x80)	led_SPI[j]  = 0xE0;	//数据1
			else			led_SPI[j]  = 0x80;	//数据0
			if(dat & 0x40)	led_SPI[j] |= 0x0E;	//数据1
			else			led_SPI[j] |= 0x08;	//数据0
			dat <<= 2;
			j++;
		}
	}
}


//========================================================================
// 函数: void  UART1_SPI_Config(u8 SPI_io, u8 SPI_speed)
// 描述: SPI初始化函数。
// 参数: io: 切换到的IO,            SS  MOSI MISO SCLK
//                       0: 切换到 P1.4 P1.5 P1.6 P1.7
//                       1: 切换到 P2.4 P2.5 P2.6 P2.7
//                       2: 切换到 P4.0 P4.1 P4.2 P4.3
//                       3: 切换到 P3.5 P3.4 P3.3 P3.2
//       SPI_speed: SPI的速度, 0: fosc/4,  1: fosc/8,  2: fosc/16,  3: fosc/2
// 返回: none.
// 版本: VER1.0
// 日期: 2024-8-13
// 备注:
//========================================================================
//USARTCR1   串口1同步模式(SPI)控制寄存器1
//   7       6       5       4       3       2       1       0    	Reset Value
// LINEN    DORD   CLKEN   SPMOD   SPIEN   SPSLV    CPOL   CPHA     0x00
#define	DORD	(0<<6)	// SPI数据收发顺序,	1：LSB先发， 0：MSB先发
#define	SPMOD	(1<<4)	// SPI模式使能位，	1: 允许SPI， 0：禁止SPI
#define	SPIEN	(1<<3)	// SPI使能位，		1: 允许SPI， 0：禁止SPI1: 允许SPI，								0：禁止SPI，所有SPI管脚均为普通IO
#define	SPSLV	(0<<2)	// SPI从机模式使能, 1：设为从机, 0：设为主机
#define	CPOL	(1<<1)	// SPI时钟极性选择, 1: 空闲时SCLK为高电平，	0：空闲时SCLK为低电平
#define	CPHA	1		// SPI时钟相位选择, 1: 数据在SCLK前沿驱动,后沿采样.	0: 数据在SCLK前沿采样,后沿驱动.

//USARTCR4   串口1同步模式(SPI)控制寄存器4
//   7    6   5   4     3     2     1  0     Reset Value
//   -    -   -   -   SCCKS[1:0]   SPICKS       0x00
#define	SPICKS		0	// 0: SYSclk/4,  1: SYSclk/8,  2: SYSclk/16, 3: SYSclk/2

void  UART1_SPI_Config(u8 SPI_io, u8 SPI_speed)
{
	SCON = 0x10;	//允许接收, 模式0
	SPI_io &= 3;
	USARTCR1 = DORD | SPMOD | SPSLV | CPOL | CPHA;	//先设置SPMOD
	USARTCR4 = SPI_speed & 3;	//配置SPI 速度
	P_SW3 = (P_SW3 & ~0x0c) | (SPI_io<<2);		//切换IO
	RI = 0;			//清0 SPIF标志
	TI = 0;			//清0 SPIF标志

	if(SPI_io == 0)
	{
		P1n_standard(0xf0);			//切换到 P1.4(SS) P1.5(MOSI) P1.6(MISO) P1.7(SCLK), 设置为准双向口
		PullUpEnable(P1PU, 0xf0);	//设置上拉电阻    允许端口内部上拉电阻   PxPU, 要设置的端口对应位为1
		P1n_push_pull(Pin7+Pin5);	//MOSI SCLK设置为推挽输出
		SlewRateHigh(P1SR, Pin7+Pin5);	//MOSI SCLK端口输出设置为高速模式   PxSR, 要设置的端口对应位为1.    高速模式在3.3V供电时速度可以到13.5MHz(27MHz主频，SPI速度2分频)
	}
	else if(SPI_io == 1)
	{
		P2n_standard(0xf0);			//切换到P2.4(SS) P2.5(MOSI) P2.6(MISO) P2.7(SCLK), 设置为准双向口
		PullUpEnable(P2PU, 0xf0);	//设置上拉电阻    允许端口内部上拉电阻   PxPU, 要设置的端口对应位为1
		P2n_push_pull(Pin7+Pin5);	//MOSI SCLK设置为推挽输出
		SlewRateHigh(P2SR, Pin7+Pin5);	//MOSI SCLK端口输出设置为高速模式   PxSR, 要设置的端口对应位为1.    高速模式在3.3V供电时速度可以到13.5MHz(27MHz主频，SPI速度2分频)
	}
	else if(SPI_io == 2)
	{
		P4n_standard(0x0f);			//切换到P4.0(SS) P4.1(MOSI) P4.2(MISO) P4.3(SCLK), 设置为准双向口
		PullUpEnable(P4PU, 0x0f);	//设置上拉电阻    允许端口内部上拉电阻   PxPU, 要设置的端口对应位为1
		P4n_push_pull(Pin3+Pin1);	//MOSI SCLK设置为推挽输出
		SlewRateHigh(P4SR, Pin3+Pin1);	//MOSI SCLK端口输出设置为高速模式   PxSR, 要设置的端口对应位为1.    高速模式在3.3V供电时速度可以到13.5MHz(27MHz主频，SPI速度2分频)
	}
	else if(SPI_io == 3)
	{
		P3n_standard(0x3C);		//切换到P3.5(SS) P3.4(MOSI) P3.3(MISO) P3.2(SCLK), 设置为准双向口
		PullUpEnable(P3PU, 0x3c);	//设置上拉电阻    允许端口内部上拉电阻   PxPU, 要设置的端口对应位为1
		P3n_push_pull(Pin4+Pin2);	//MOSI SCLK设置为推挽输出
		SlewRateHigh(P3SR, Pin4+Pin2);	//MOSI SCLK端口输出设置为高速模式   PxSR, 要设置的端口对应位为1.    高速模式在3.3V供电时速度可以到13.5MHz(27MHz主频，SPI速度2分频)
	}

	USARTCR1 = DORD | SPMOD | SPIEN | SPSLV | CPOL | CPHA;	//最后设置SPIEN
}


//DMA_UR1T_CFG 	UR1T_DMA配置寄存器
#define		DMA_UR1TIE	(1<<7)	// UR1T DMA中断使能控制位，bit7, 0:禁止UR1T DMA中断，     1：允许中断。
#define		DMA_UR1TIP	(0<<2)	// UR1T DMA中断优先级控制位，bit3~bit2, (最低)0~3(最高).
#define		DMA_UR1TPTY		0	// UR1T DMA数据总线访问优先级控制位，bit1~bit0, (最低)0~3(最高).

//DMA_UR1T_CR 	UR1T_DMA控制寄存器
#define		DMA_ENUR1T		(1<<7)	// UR1T DMA功能使能控制位，    bit7, 0:禁止UR1T DMA功能，  1：允许UR1T DMA功能。
#define		UR1T_TRIG		(1<<6)	// UR1T DMA发送触发控制位，    bit6, 0:写0无效，           1：写1开始UR1T DMA主机模式操作。

//DMA_UR1T_STA 	UR1T_DMA状态寄存器
#define		UR1T_TXOVW	(1<<2)	// UR1T DMA数据覆盖标志位，bit2, 软件清0.
#define		DMA_UR1TIF	1		// UR1T DMA中断请求标志位，bit0, 软件清0.

void	UR1T_DMA_TRIG(u8 xdata *TxBuf, u16 num)
{
	u16	i;		//@40MHz, Fosc/4, 200字节272us，100字节137us，50字节69.5us，N个字节耗时 N*1.35+2 us, 54T一个字节，其中状态机耗时0.35us(14T), 传输耗时1.0us(40T, 即10个SPI位时间).

	i   = (u16)TxBuf;		//要发送数据的首地址
	DMA_UR1T_TXAH = (u8)(i >> 8);	//发送地址寄存器高字节
	DMA_UR1T_TXAL = (u8)i;			//发送地址寄存器低字节
	DMA_UR1T_AMTH = (u8)((num-1)>>8);				//设置传输总字节数(高8位),	设置传输总字节数 = N+1
	DMA_UR1T_AMT  = (u8)(num-1);			//设置传输总字节数(低8位).
	DMA_UR1T_STA  = 0x00;
	DMA_UR1T_CFG  = DMA_UR1TIE | DMA_UR1TIP | DMA_UR1TPTY;
	DMA_UR1T_CR   = DMA_ENUR1T | UR1T_TRIG;
P10 = 1;	//高电平时间用于指示DMA传输总耗时
	B_UR1T_DMA_busy = 1;	//标志UR1T-DMA忙，UR1T DMA中断中清除此标志，使用SPI DMA前要确认此标志为0
}

//========================================================================
// 函数: void UR1T_DMA_ISR (void) interrupt DMA_UR1T_VECTOR
// 描述: UR1T_DMA中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2024-1-5
//========================================================================
void UR1T_DMA_ISR (void) interrupt DMA_UR1T_VECTOR
{
P10= 0;	//高电平时间用于指示DMA传输总耗时
	DMA_UR1T_STA = 0;		//清除中断标志
	DMA_UR1T_CR  = 0;
	B_UR1T_DMA_busy = 0;		//清除SPI-DMA忙标志，SPI DMA中断中清除此标志，使用SPI DMA前要确认此标志为0
}
