
#define 	MAIN_Fosc		25600000UL	//������ʱ��

#include	"AI8051U.h"


/*************	����˵��	**************

���ȱ��޸ĳ���, ֱ������"SPI.hex"����, ����ʱѡ����Ƶ24MHz������25.6MHz. ʵ��20~30MHz��������������

ʹ��SPI-MOSI���ֱ������WS2812����ɫ�ʵ�, DMA���䣬��ռ��CPUʱ�䡣��������24���ƣ��ӳɻ�״��
����ʹ��USART1-SPIģʽ��P1.5-MOSI��������ź�ֱ������WS2812��
����ʹ��SPI����ģʽ����P1.6��P1.7��SPIռ�ã����������ã������Խ�P1.7-SCLK����Ϊ������Ϊ����ʹ�á�
 DMA, 2��Ƶ, һ���ֽ���Ҫʱ��28T��
      4��Ƶ, һ���ֽ���Ҫʱ��44T��
      8��Ƶ, һ���ֽ���Ҫʱ��72T��
     16��Ƶ, һ���ֽ���Ҫʱ��144T��
DMA����ʱ�䣺@25.6MHz, DMA����һ���ֽ�2.8125us��һ����Ҫ����12���ֽ�33.75us��8192�ֽ�xdata���һ������682����.

ÿ����3���ֽڣ��ֱ��Ӧ�̡��졢����MSB�ȷ�.
800KHz����, ����0(1/4ռ�ձ�): H=0.3125us  L=0.9375us, ����1(3/4ռ�ձ�): H=0.9375us  L=0.3125us, RESET>=50us.
�ߵ�ƽʱ��Ҫ��ȷ������Ҫ��ķ�Χ��, �͵�ƽʱ�䲻��Ҫ��ȷ����, ����Ҫ�����Сֵ��С��RES��50us����.

WS2812S�ı�׼ʱ������:
TH+TL = 1.25us��150ns, RES>50us
T0H = 0.25us��150ns = 0.10us - 0.40us
T0L = 1.00us��150ns = 0.85us - 1.15us
T1H = 1.00us��150ns = 0.85us - 1.15us
T1L = 0.25us��150ns = 0.10us - 0.40us
����λ����֮��ļ��ҪС��RES��50us.

SPI����:
����ʹ��USART1-SPIģʽ��P1.5-MOSI��������ź�ֱ������WS2812��
����ʹ��SPI����ģʽ����P1.6��P1.7��SPIռ�ã����������ã������Խ�P1.7-SCLK����Ϊ������Ϊ����ʹ�á�

��SPI����, �ٶ�3.0~3.5MHz����3.2MHzΪ���, MSB�ȷ�, ÿ���ֽڸ�4λ�͵�4λ�ֱ��Ӧһ��λ����, 1000Ϊ����0, 1110Ϊ����1.
SPI����λ       D7 D6 D5 D4    D3 D2 D1 D0
SPI����         1  0  0  0     1  1  1  0
               WS2812����0    WS2812����1
SPI���ݸ߰��ֽڶ�Ӧ��WS2812����0-->0x80, ����1-->0xe0,
SPI���ݵͰ��ֽڶ�Ӧ��WS2812����0-->0x08, ����1-->0x0e,
��Ƶ25.6MHz, SPI��Ƶ8 = 3.2MHz. ���.

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/


/*************	���غ�������	**************/

#define	COLOR	50				//���ȣ����255

#define	LED_NUM	24				//LED�Ƹ���
#define	SPI_NUM	(LED_NUM*12)	//LED�ƶ�ӦSPI�ֽ���

u8	xdata  led_RGB[LED_NUM][3];	//LED��Ӧ��RGB��led_buff[i][0]-->�̣�led_buff[i][1]-->�죬led_buff[i][0]-->��.
u8	xdata  led_SPI[SPI_NUM];	//LED�ƶ�ӦSPI�ֽ���

bit	B_UR1T_DMA_busy;	//UR1T-DMAæ��־


/*************  �ⲿ�����ͱ������� *****************/
void	LoadSPI(void);
void	UART1_SPI_Config(u8 SPI_io, u8 SPI_speed);	//(SPI_io, SPI_speed), ����:  SPI_io: �л�IO(SS MOSI MISO SCLK), 0: �л���P1.4 P1.5 P1.6 P1.7,  1: �л���P2.4 P2.5 P2.6 P2.7, 2: �л���P4.0 P4.1 P4.2 P4.3,  3: �л���P3.5 P3.4 P3.3 P3.2,
													//                            SPI_speed: SPI���ٶ�, 0: fosc/4,  1: fosc/8,  2: fosc/16,  3: fosc/2
void	UR1T_DMA_TRIG(u8 xdata *TxBuf, u16 num);
void	delay_ms(u16 ms);



/*************** ������ *******************************/

void main(void)
{
	u16	i,k;
	u8	xdata *px;

	EAXFR = 1;	//���������չ�Ĵ���
	WTST  = 0;
	CKCON = 0;

	P1M1 = 0;	P1M0 = 0;

	UART1_SPI_Config(0, 1);	//(SPI_io, SPI_speed), ����: SPI_io: �л�IO(SS MOSI MISO SCLK), 0: �л���P1.4 P1.5 P1.6 P1.7,  1: �л���P2.4 P2.5 P2.6 P2.7, 2: �л���P4.0 P4.1 P4.2 P4.3,  3: �л���P3.5 P3.4 P3.3 P3.2,
							//                           SPI_speed: SPI���ٶ�, 0: fosc/4,  1: fosc/8,  2: fosc/16,  3: fosc/2
	EA = 1;
//	MCLKO47_DIV(100);	//��Ƶ��Ƶ��������ڲ�����Ƶ

	k = 0;		//

	while (1)
	{
		while(B_UR1T_DMA_busy)	;	//�ȴ�DMA���

		px = &led_RGB[0][0];	//����(��ɫ)�׵�ַ
		for(i=0; i<(LED_NUM*3); i++, px++)	*px = 0;	//������е���ɫ

		i = k;
		led_RGB[i][1] = COLOR;		//��ɫ
		if(++i >= LED_NUM)	i = 0;	//��һ����
		led_RGB[i][0] = COLOR;		//��ɫ
		if(++i >= LED_NUM)	i = 0;	//��һ����
		led_RGB[i][2] = COLOR;		//��ɫ

		LoadSPI();			//����ɫװ�ص�SPI����
		UR1T_DMA_TRIG(led_SPI, SPI_NUM);	//(u8 xdata *TxBuf, u16 num);

		if(++k >= LED_NUM)	k = 0;			//˳ʱ��
	//	if(--k >= LED_NUM)	k = LED_NUM-1;	//��ʱ��
		delay_ms(50);
	}
}


//================ ��ʱ���� ==============
void  delay_ms(u16 ms)
{
	u16 i;
	do
	{
		i = MAIN_Fosc / 6000;
		while(--i)	;
	}while(--ms);
}



//================ ����ɫװ�ص�SPI���� ==============
void	LoadSPI(void)
{
	u8	xdata *px;
	u16	i,j;
	u8	k;
	u8	dat;

	for(i=0; i<SPI_NUM; i++)	led_SPI[i] = 0;
	px = &led_RGB[0][0];	//�׵�ַ
	for(i=0, j=0; i<(LED_NUM*3); i++)
	{
		dat = *px;
		px++;
		for(k=0; k<4; k++)
		{
			if(dat & 0x80)	led_SPI[j]  = 0xE0;	//����1
			else			led_SPI[j]  = 0x80;	//����0
			if(dat & 0x40)	led_SPI[j] |= 0x0E;	//����1
			else			led_SPI[j] |= 0x08;	//����0
			dat <<= 2;
			j++;
		}
	}
}


//========================================================================
// ����: void  UART1_SPI_Config(u8 SPI_io, u8 SPI_speed)
// ����: SPI��ʼ��������
// ����: io: �л�����IO,            SS  MOSI MISO SCLK
//                       0: �л��� P1.4 P1.5 P1.6 P1.7
//                       1: �л��� P2.4 P2.5 P2.6 P2.7
//                       2: �л��� P4.0 P4.1 P4.2 P4.3
//                       3: �л��� P3.5 P3.4 P3.3 P3.2
//       SPI_speed: SPI���ٶ�, 0: fosc/4,  1: fosc/8,  2: fosc/16,  3: fosc/2
// ����: none.
// �汾: VER1.0
// ����: 2024-8-13
// ��ע:
//========================================================================
//USARTCR1   ����1ͬ��ģʽ(SPI)���ƼĴ���1
//   7       6       5       4       3       2       1       0    	Reset Value
// LINEN    DORD   CLKEN   SPMOD   SPIEN   SPSLV    CPOL   CPHA     0x00
#define	DORD	(0<<6)	// SPI�����շ�˳��,	1��LSB�ȷ��� 0��MSB�ȷ�
#define	SPMOD	(1<<4)	// SPIģʽʹ��λ��	1: ����SPI�� 0����ֹSPI
#define	SPIEN	(1<<3)	// SPIʹ��λ��		1: ����SPI�� 0����ֹSPI1: ����SPI��								0����ֹSPI������SPI�ܽž�Ϊ��ͨIO
#define	SPSLV	(0<<2)	// SPI�ӻ�ģʽʹ��, 1����Ϊ�ӻ�, 0����Ϊ����
#define	CPOL	(1<<1)	// SPIʱ�Ӽ���ѡ��, 1: ����ʱSCLKΪ�ߵ�ƽ��	0������ʱSCLKΪ�͵�ƽ
#define	CPHA	1		// SPIʱ����λѡ��, 1: ������SCLKǰ������,���ز���.	0: ������SCLKǰ�ز���,��������.

//USARTCR4   ����1ͬ��ģʽ(SPI)���ƼĴ���4
//   7    6   5   4     3     2     1  0     Reset Value
//   -    -   -   -   SCCKS[1:0]   SPICKS       0x00
#define	SPICKS		0	// 0: SYSclk/4,  1: SYSclk/8,  2: SYSclk/16, 3: SYSclk/2

void  UART1_SPI_Config(u8 SPI_io, u8 SPI_speed)
{
	SCON = 0x10;	//�������, ģʽ0
	SPI_io &= 3;
	USARTCR1 = DORD | SPMOD | SPSLV | CPOL | CPHA;	//������SPMOD
	USARTCR4 = SPI_speed & 3;	//����SPI �ٶ�
	P_SW3 = (P_SW3 & ~0x0c) | (SPI_io<<2);		//�л�IO
	RI = 0;			//��0 SPIF��־
	TI = 0;			//��0 SPIF��־

	if(SPI_io == 0)
	{
		P1n_standard(0xf0);			//�л��� P1.4(SS) P1.5(MOSI) P1.6(MISO) P1.7(SCLK), ����Ϊ׼˫���
		PullUpEnable(P1PU, 0xf0);	//������������    ����˿��ڲ���������   PxPU, Ҫ���õĶ˿ڶ�ӦλΪ1
		P1n_push_pull(Pin7+Pin5);	//MOSI SCLK����Ϊ�������
		SlewRateHigh(P1SR, Pin7+Pin5);	//MOSI SCLK�˿��������Ϊ����ģʽ   PxSR, Ҫ���õĶ˿ڶ�ӦλΪ1.    ����ģʽ��3.3V����ʱ�ٶȿ��Ե�13.5MHz(27MHz��Ƶ��SPI�ٶ�2��Ƶ)
	}
	else if(SPI_io == 1)
	{
		P2n_standard(0xf0);			//�л���P2.4(SS) P2.5(MOSI) P2.6(MISO) P2.7(SCLK), ����Ϊ׼˫���
		PullUpEnable(P2PU, 0xf0);	//������������    ����˿��ڲ���������   PxPU, Ҫ���õĶ˿ڶ�ӦλΪ1
		P2n_push_pull(Pin7+Pin5);	//MOSI SCLK����Ϊ�������
		SlewRateHigh(P2SR, Pin7+Pin5);	//MOSI SCLK�˿��������Ϊ����ģʽ   PxSR, Ҫ���õĶ˿ڶ�ӦλΪ1.    ����ģʽ��3.3V����ʱ�ٶȿ��Ե�13.5MHz(27MHz��Ƶ��SPI�ٶ�2��Ƶ)
	}
	else if(SPI_io == 2)
	{
		P4n_standard(0x0f);			//�л���P4.0(SS) P4.1(MOSI) P4.2(MISO) P4.3(SCLK), ����Ϊ׼˫���
		PullUpEnable(P4PU, 0x0f);	//������������    ����˿��ڲ���������   PxPU, Ҫ���õĶ˿ڶ�ӦλΪ1
		P4n_push_pull(Pin3+Pin1);	//MOSI SCLK����Ϊ�������
		SlewRateHigh(P4SR, Pin3+Pin1);	//MOSI SCLK�˿��������Ϊ����ģʽ   PxSR, Ҫ���õĶ˿ڶ�ӦλΪ1.    ����ģʽ��3.3V����ʱ�ٶȿ��Ե�13.5MHz(27MHz��Ƶ��SPI�ٶ�2��Ƶ)
	}
	else if(SPI_io == 3)
	{
		P3n_standard(0x3C);		//�л���P3.5(SS) P3.4(MOSI) P3.3(MISO) P3.2(SCLK), ����Ϊ׼˫���
		PullUpEnable(P3PU, 0x3c);	//������������    ����˿��ڲ���������   PxPU, Ҫ���õĶ˿ڶ�ӦλΪ1
		P3n_push_pull(Pin4+Pin2);	//MOSI SCLK����Ϊ�������
		SlewRateHigh(P3SR, Pin4+Pin2);	//MOSI SCLK�˿��������Ϊ����ģʽ   PxSR, Ҫ���õĶ˿ڶ�ӦλΪ1.    ����ģʽ��3.3V����ʱ�ٶȿ��Ե�13.5MHz(27MHz��Ƶ��SPI�ٶ�2��Ƶ)
	}

	USARTCR1 = DORD | SPMOD | SPIEN | SPSLV | CPOL | CPHA;	//�������SPIEN
}


//DMA_UR1T_CFG 	UR1T_DMA���üĴ���
#define		DMA_UR1TIE	(1<<7)	// UR1T DMA�ж�ʹ�ܿ���λ��bit7, 0:��ֹUR1T DMA�жϣ�     1�������жϡ�
#define		DMA_UR1TIP	(0<<2)	// UR1T DMA�ж����ȼ�����λ��bit3~bit2, (���)0~3(���).
#define		DMA_UR1TPTY		0	// UR1T DMA�������߷������ȼ�����λ��bit1~bit0, (���)0~3(���).

//DMA_UR1T_CR 	UR1T_DMA���ƼĴ���
#define		DMA_ENUR1T		(1<<7)	// UR1T DMA����ʹ�ܿ���λ��    bit7, 0:��ֹUR1T DMA���ܣ�  1������UR1T DMA���ܡ�
#define		UR1T_TRIG		(1<<6)	// UR1T DMA���ʹ�������λ��    bit6, 0:д0��Ч��           1��д1��ʼUR1T DMA����ģʽ������

//DMA_UR1T_STA 	UR1T_DMA״̬�Ĵ���
#define		UR1T_TXOVW	(1<<2)	// UR1T DMA���ݸ��Ǳ�־λ��bit2, �����0.
#define		DMA_UR1TIF	1		// UR1T DMA�ж������־λ��bit0, �����0.

void	UR1T_DMA_TRIG(u8 xdata *TxBuf, u16 num)
{
	u16	i;		//@40MHz, Fosc/4, 200�ֽ�272us��100�ֽ�137us��50�ֽ�69.5us��N���ֽں�ʱ N*1.35+2 us, 54Tһ���ֽڣ�����״̬����ʱ0.35us(14T), �����ʱ1.0us(40T, ��10��SPIλʱ��).

	i   = (u16)TxBuf;		//Ҫ�������ݵ��׵�ַ
	DMA_UR1T_TXAH = (u8)(i >> 8);	//���͵�ַ�Ĵ������ֽ�
	DMA_UR1T_TXAL = (u8)i;			//���͵�ַ�Ĵ������ֽ�
	DMA_UR1T_AMTH = (u8)((num-1)>>8);				//���ô������ֽ���(��8λ),	���ô������ֽ��� = N+1
	DMA_UR1T_AMT  = (u8)(num-1);			//���ô������ֽ���(��8λ).
	DMA_UR1T_STA  = 0x00;
	DMA_UR1T_CFG  = DMA_UR1TIE | DMA_UR1TIP | DMA_UR1TPTY;
	DMA_UR1T_CR   = DMA_ENUR1T | UR1T_TRIG;
P10 = 1;	//�ߵ�ƽʱ������ָʾDMA�����ܺ�ʱ
	B_UR1T_DMA_busy = 1;	//��־UR1T-DMAæ��UR1T DMA�ж�������˱�־��ʹ��SPI DMAǰҪȷ�ϴ˱�־Ϊ0
}

//========================================================================
// ����: void UR1T_DMA_ISR (void) interrupt DMA_UR1T_VECTOR
// ����: UR1T_DMA�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2024-1-5
//========================================================================
void UR1T_DMA_ISR (void) interrupt DMA_UR1T_VECTOR
{
P10= 0;	//�ߵ�ƽʱ������ָʾDMA�����ܺ�ʱ
	DMA_UR1T_STA = 0;		//����жϱ�־
	DMA_UR1T_CR  = 0;
	B_UR1T_DMA_busy = 0;		//���SPI-DMAæ��־��SPI DMA�ж�������˱�־��ʹ��SPI DMAǰҪȷ�ϴ˱�־Ϊ0
}
