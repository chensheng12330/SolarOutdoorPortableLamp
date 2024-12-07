/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#ifndef	__STC8G_H_NVIC_H
#define	__STC8G_H_NVIC_H

#include	"config.h"

//========================================================================
//                              ��������
//========================================================================

#define	FALLING_EDGE		1		//�����½����ж�
#define	RISING_EDGE			2		//�����������ж�

//========================================================================
//                              ��ʱ���ж�����
//========================================================================

#define 	Timer0_Interrupt(n)		(n==0?(ET0 = 0):(ET0 = 1))				/* Timer0�ж�ʹ�� */
#define 	Timer1_Interrupt(n)		(n==0?(ET1 = 0):(ET1 = 1))				/* Timer1�ж�ʹ�� */
#define 	Timer2_Interrupt(n)		IE2 = (IE2 & ~0x04) | (n << 2)			/* Timer2�ж�ʹ�� */
#define 	Timer3_Interrupt(n)		IE2 = (IE2 & ~0x20) | (n << 5)			/* Timer3�ж�ʹ�� */
#define 	Timer4_Interrupt(n)		IE2 = (IE2 & ~0x40) | (n << 6)			/* Timer4�ж�ʹ�� */

//========================================================================
//                             �ⲿ�ж�����
//========================================================================

#define 	INT0_Interrupt(n)		(n==0?(EX0 = 0):(EX0 = 1))			/* INT0�ж�ʹ�� */
#define 	INT1_Interrupt(n)		(n==0?(EX1 = 0):(EX1 = 1))			/* INT1�ж�ʹ�� */
#define 	INT2_Interrupt(n)		INTCLKO = (INTCLKO & ~0x10) | (n << 4)	/* INT2�ж�ʹ�� */
#define 	INT3_Interrupt(n)		INTCLKO = (INTCLKO & ~0x20) | (n << 5)	/* INT3�ж�ʹ�� */
#define 	INT4_Interrupt(n)		INTCLKO = (INTCLKO & ~0x40) | (n << 6)	/* INT4�ж�ʹ�� */

//========================================================================
//                              ADC�ж�����
//========================================================================

#define 	ADC_Interrupt(n)		(n==0?(EADC = 0):(EADC = 1))	/* ADC�жϿ��� */

//========================================================================
//                              SPI�ж�����
//========================================================================

#define 	SPI_Interrupt(n)		IE2 = (IE2 & ~0x02) | (n << 1)	/* SPI�ж�ʹ�� */

//========================================================================
//                              I2C�ж�����
//========================================================================

#define		I2C_Master_Inturrupt(n)	(n==0?(I2CMSCR &= ~0x80):(I2CMSCR |= 0x80))	//0����ֹ I2C ���ܣ�1��ʹ�� I2C ����

//========================================================================
//                              UART�ж�����
//========================================================================

#define		UART1_Interrupt(n)	(n==0?(ES = 0):(ES = 1))			/* UART1�ж�ʹ�� */
#define		UART2_Interrupt(n)	IE2 = (IE2 & ~0x01) | (n)			/* UART2�ж�ʹ�� */
#define		UART3_Interrupt(n)	IE2 = (IE2 & ~0x08) | (n << 3)		/* UART3�ж�ʹ�� */
#define		UART4_Interrupt(n)	IE2 = (IE2 & ~0x10) | (n << 4)		/* UART4�ж�ʹ�� */

//========================================================================
//                              RTC�ж�����
//========================================================================

#define 	RTC_Interrupt(n)		RTCIEN = (n)		/* RTC�ж�ʹ�� */

//========================================================================
//                            �ж����ȼ�����
//========================================================================

//                                           7      6      5      4      3      2      1      0      Reset Value
//sfr IP2   = 0xB5; //                    PPWM2FD PI2C   PCMP    PX4  PPWM0FD  PPWM0  PSPI   PS2     0000,0000
#define		PUSB	0x80
#define		PPWM2FD	0x80
#define		PTKSU	0x80
#define		PI2C	0x40
#define		PCMP	0x20
#define		PX4		0x10
#define		PPWM0FD	0x08
#define		PPWMB	0x08
#define		PPWM0	0x04
#define		PPWMA	0x04
#define		PSPI	0x02
#define		PS2		0x01
//                                           7      6      5      4      3      2      1      0      Reset Value
//sfr IP2H  = 0xB6; //                    PPWM2FDH PI2CH PCMPH   PX4H PPWM0FDH PPWM0H PSPIH  PS2H    0000,0000
#define		PUSBH		0x80
#define		PPWM2FDH	0x80
#define		PTKSUH		0x80
#define		PI2CH		0x40
#define		PCMPH		0x20
#define		PX4H		0x10
#define		PPWM0FDH	0x08
#define		PPWMBH		0x08
#define		PPWM0H		0x04
#define		PPWMAH		0x04
#define		PSPIH		0x02
#define		PS2H		0x01

//����2�ж����ȼ�����
#define 	UART2_Priority(n)			do{if(n == 0) IP2H &= ~PS2H, IP2 &= ~PS2; \
																if(n == 1) IP2H &= ~PS2H, IP2 |= PS2; \
																if(n == 2) IP2H |= PS2H, IP2 &= ~PS2; \
																if(n == 3) IP2H |= PS2H, IP2 |= PS2; \
															}while(0)
//SPI�ж����ȼ�����
#define 	SPI_Priority(n)				do{if(n == 0) IP2H &= ~PSPIH, IP2 &= ~PSPI; \
																if(n == 1) IP2H &= ~PSPIH, IP2 |= PSPI; \
																if(n == 2) IP2H |= PSPIH, IP2 &= ~PSPI; \
																if(n == 3) IP2H |= PSPIH, IP2 |= PSPI; \
															}while(0)
//�ⲿ�ж�4�ж����ȼ�����
#define 	INT4_Priority(n)			do{if(n == 0) IP2H &= ~PX4H, IP2 &= ~PX4; \
																if(n == 1) IP2H &= ~PX4H, IP2 |= PX4; \
																if(n == 2) IP2H |= PX4H, IP2 &= ~PX4; \
																if(n == 3) IP2H |= PX4H, IP2 |= PX4; \
															}while(0)
//�Ƚ����ж����ȼ�����
#define 	CMP_Priority(n)				do{if(n == 0) IP2H &= ~PCMPH, IP2 &= ~PCMP; \
																if(n == 1) IP2H &= ~PCMPH, IP2 |= PCMP; \
																if(n == 2) IP2H |= PCMPH, IP2 &= ~PCMP; \
																if(n == 3) IP2H |= PCMPH, IP2 |= PCMP; \
															}while(0)
//I2C�ж����ȼ�����
#define 	I2C_Priority(n)				do{if(n == 0) IP2H &= ~PI2CH, IP2 &= ~PI2C; \
																if(n == 1) IP2H &= ~PI2CH, IP2 |= PI2C; \
																if(n == 2) IP2H |= PI2CH, IP2 &= ~PI2C; \
																if(n == 3) IP2H |= PI2CH, IP2 |= PI2C; \
															}while(0)
//��ǿ��PWM0�ж����ȼ�����
#define 	PWM0_Priority(n)			do{if(n == 0) IP2H &= ~PPWM0H, IP2 &= ~PPWM0; \
																if(n == 1) IP2H &= ~PPWM0H, IP2 |= PPWM0; \
																if(n == 2) IP2H |= PPWM0H, IP2 &= ~PPWM0; \
																if(n == 3) IP2H |= PPWM0H, IP2 |= PPWM0; \
															}while(0)
//��ǿ��PWM0�쳣����ж����ȼ�����
#define 	PWM0FD_Priority(n)			do{if(n == 0) IP2H &= ~PPWM0FDH, IP2 &= ~PPWM0FD; \
																if(n == 1) IP2H &= ~PPWM0FDH, IP2 |= PPWM0FD; \
																if(n == 2) IP2H |= PPWM0FDH, IP2 &= ~PPWM0FD; \
																if(n == 3) IP2H |= PPWM0FDH, IP2 |= PPWM0FD; \
															}while(0)
//��ǿ��PWM2�쳣����ж����ȼ�����
#define 	PWM2FD_Priority(n)			do{if(n == 0) IP2H &= ~PPWM2FDH, IP2 &= ~PPWM2FD; \
																if(n == 1) IP2H &= ~PPWM2FDH, IP2 |= PPWM2FD; \
																if(n == 2) IP2H |= PPWM2FDH, IP2 &= ~PPWM2FD; \
																if(n == 3) IP2H |= PPWM2FDH, IP2 |= PPWM2FD; \
															}while(0)
//���������ж����ȼ�����
#define 	PTKSU_Priority(n)			do{if(n == 0) IP2H &= ~PTKSUH, IP2 &= ~PTKSU; \
																if(n == 1) IP2H &= ~PTKSUH, IP2 |= PTKSU; \
																if(n == 2) IP2H |= PTKSUH, IP2 &= ~PTKSU; \
																if(n == 3) IP2H |= PTKSUH, IP2 |= PTKSU; \
															}while(0)

//USB�ж����ȼ�����
#define 	USB_Priority(n)				do{if(n == 0) IP2H &= ~PUSBH, IP2 &= ~PUSB; \
																if(n == 1) IP2H &= ~PUSBH, IP2 |= PUSB; \
																if(n == 2) IP2H |= PUSBH, IP2 &= ~PUSB; \
																if(n == 3) IP2H |= PUSBH, IP2 |= PUSB; \
															}while(0)

//�߼�PWMA�ж����ȼ�����
#define 	PWMA_Priority(n)			do{if(n == 0) IP2H &= ~PPWMAH, IP2 &= ~PPWMA; \
																if(n == 1) IP2H &= ~PPWMAH, IP2 |= PPWMA; \
																if(n == 2) IP2H |= PPWMAH, IP2 &= ~PPWMA; \
																if(n == 3) IP2H |= PPWMAH, IP2 |= PPWMA; \
															}while(0)

//�߼�PWMB�ж����ȼ�����
#define 	PWMB_Priority(n)			do{if(n == 0) IP2H &= ~PPWMBH, IP2 &= ~PPWMB; \
																if(n == 1) IP2H &= ~PPWMBH, IP2 |= PPWMB; \
																if(n == 2) IP2H |= PPWMBH, IP2 &= ~PPWMB; \
																if(n == 3) IP2H |= PPWMBH, IP2 |= PPWMB; \
															}while(0)


//                                           7      6      5     4      3      2      1     0      Reset Value
//sfr IP3   = 0xDF; //                    PPWM4FD PPWM5  PPWM4  PPWM3  PPWM2  PPWM1  PS4   PS3     0000,0000
#define		PPWM4FD		0x80
#define		PPWM5		0x40
#define		PPWM4		0x20
#define		PPWM3		0x10
#define		PPWM2		0x08
#define		PPWM1		0x04
#define		PRTC		0x04
#define		PS4			0x02
#define		PS3			0x01
//                                           7        6       5      4       3       2     1     0      Reset Value
//sfr IP3H  = 0xEE; //                    PPWM4FDH PPWM5H  PPWM4H  PPWM3H  PPWM2H  PPWM1H PS4H  PS3H    0000,0000
#define		PPWM4FDH	0x80
#define		PPWM5H		0x40
#define		PPWM4H		0x20
#define		PPWM3H		0x10
#define		PPWM2H		0x08
#define		PPWM1H		0x04
#define		PRTCH		0x04
#define		PS4H		0x02
#define		PS3H		0x01

//RTC�ж����ȼ�����
#define 	RTC_Priority(n)				do{if(n == 0) IP3H &= ~PRTCH, IP3 &= ~PRTC; \
																if(n == 1) IP3H &= ~PRTCH, IP3 |= PRTC; \
																if(n == 2) IP3H |= PRTCH, IP3 &= ~PRTC; \
																if(n == 3) IP3H |= PRTCH, IP3 |= PRTC; \
															}while(0)

//��ǿ��PWM1�ж����ȼ�����
#define 	PWM1_Priority(n)			do{if(n == 0) IP3H &= ~PPWM1H, IP3 &= ~PPWM1; \
																if(n == 1) IP3H &= ~PPWM1H, IP3 |= PPWM1; \
																if(n == 2) IP3H |= PPWM1H, IP3 &= ~PPWM1; \
																if(n == 3) IP3H |= PPWM1H, IP3 |= PPWM1; \
															}while(0)
//��ǿ��PWM2�ж����ȼ�����
#define 	PWM2_Priority(n)			do{if(n == 0) IP3H &= ~PPWM2H, IP3 &= ~PPWM2; \
																if(n == 1) IP3H &= ~PPWM2H, IP3 |= PPWM2; \
																if(n == 2) IP3H |= PPWM2H, IP3 &= ~PPWM2; \
																if(n == 3) IP3H |= PPWM2H, IP3 |= PPWM2; \
															}while(0)

//��ǿ��PWM3�ж����ȼ�����
#define 	PWM3_Priority(n)			do{if(n == 0) IP3H &= ~PPWM3H, IP3 &= ~PPWM3; \
																if(n == 1) IP3H &= ~PPWM3H, IP3 |= PPWM3; \
																if(n == 2) IP3H |= PPWM3H, IP3 &= ~PPWM3; \
																if(n == 3) IP3H |= PPWM3H, IP3 |= PPWM3; \
															}while(0)
//��ǿ��PWM4�ж����ȼ�����
#define 	PWM4_Priority(n)			do{if(n == 0) IP3H &= ~PPWM4H, IP3 &= ~PPWM4; \
																if(n == 1) IP3H &= ~PPWM4H, IP3 |= PPWM4; \
																if(n == 2) IP3H |= PPWM4H, IP3 &= ~PPWM4; \
																if(n == 3) IP3H |= PPWM4H, IP3 |= PPWM4; \
															}while(0)
//��ǿ��PWM5�ж����ȼ�����
#define 	PWM5_Priority(n)			do{if(n == 0) IP3H &= ~PPWM5H, IP3 &= ~PPWM5; \
																if(n == 1) IP3H &= ~PPWM5H, IP3 |= PPWM5; \
																if(n == 2) IP3H |= PPWM5H, IP3 &= ~PPWM5; \
																if(n == 3) IP3H |= PPWM5H, IP3 |= PPWM5; \
															}while(0)
//��ǿ��PWM4�쳣����ж����ȼ�����
#define 	PWM4FD_Priority(n)			do{if(n == 0) IP3H &= ~PPWM4FDH, IP3 &= ~PPWM4FD; \
																if(n == 1) IP3H &= ~PPWM4FDH, IP3 |= PPWM4FD; \
																if(n == 2) IP3H |= PPWM4FDH, IP3 &= ~PPWM4FD; \
																if(n == 3) IP3H |= PPWM4FDH, IP3 |= PPWM4FD; \
															}while(0)
//����3�ж����ȼ�����
#define 	UART3_Priority(n)			do{if(n == 0) IP3H &= ~PS3H, IP3 &= ~PS3; \
																if(n == 1) IP3H &= ~PS3H, IP3 |= PS3; \
																if(n == 2) IP3H |= PS3H, IP3 &= ~PS3; \
																if(n == 3) IP3H |= PS3H, IP3 |= PS3; \
															}while(0)
//����4�ж����ȼ�����
#define 	UART4_Priority(n)			do{if(n == 0) IP3H &= ~PS4H, IP3 &= ~PS4; \
																if(n == 1) IP3H &= ~PS4H, IP3 |= PS4; \
																if(n == 2) IP3H |= PS4H, IP3 &= ~PS4; \
																if(n == 3) IP3H |= PS4H, IP3 |= PS4; \
															}while(0)


//                                           7      6      5      4      3      2      1      0      Reset Value
//sfr IPH   = 0xB7; //�ж����ȼ���λ       PPCAH  PLVDH   PADCH   PSH   PT1H    PX1H   PT0H   PX0H    0000,0000
//#define		PPCAH	0x80
#define		PLVDH	0x40
#define		PADCH	0x20
#define		PSH		0x10
#define		PT1H	0x08
#define		PX1H	0x04
#define		PT0H	0x02
#define		PX0H	0x01

//�ⲿ�ж�0�ж����ȼ�����
#define 	INT0_Priority(n)			do{if(n == 0) IPH &= ~PX0H, PX0 = 0; \
																if(n == 1) IPH &= ~PX0H, PX0 = 1; \
																if(n == 2) IPH |= PX0H, PX0 = 0; \
																if(n == 3) IPH |= PX0H, PX0 = 1; \
															}while(0)
//�ⲿ�ж�1�ж����ȼ�����
#define 	INT1_Priority(n)			do{if(n == 0) IPH &= ~PX1H, PX1 = 0; \
																if(n == 1) IPH &= ~PX1H, PX1 = 1; \
																if(n == 2) IPH |= PX1H, PX1 = 0; \
																if(n == 3) IPH |= PX1H, PX1 = 1; \
															}while(0)
//��ʱ��0�ж����ȼ�����
#define 	Timer0_Priority(n)			do{if(n == 0) IPH &= ~PT0H, PT0 = 0; \
																if(n == 1) IPH &= ~PT0H, PT0 = 1; \
																if(n == 2) IPH |= PT0H, PT0 = 0; \
																if(n == 3) IPH |= PT0H, PT0 = 1; \
															}while(0)
//��ʱ��1�ж����ȼ�����
#define 	Timer1_Priority(n)			do{if(n == 0) IPH &= ~PT1H, PT1 = 0; \
																if(n == 1) IPH &= ~PT1H, PT1 = 1; \
																if(n == 2) IPH |= PT1H, PT1 = 0; \
																if(n == 3) IPH |= PT1H, PT1 = 1; \
															}while(0)
//����1�ж����ȼ�����
#define 	UART1_Priority(n)			do{if(n == 0) IPH &= ~PSH, PS = 0; \
																if(n == 1) IPH &= ~PSH, PS = 1; \
																if(n == 2) IPH |= PSH, PS = 0; \
																if(n == 3) IPH |= PSH, PS = 1; \
															}while(0)
//ADC�ж����ȼ�����
#define 	ADC_Priority(n)				do{if(n == 0) IPH &= ~PADCH, PADC = 0; \
																if(n == 1) IPH &= ~PADCH, PADC = 1; \
																if(n == 2) IPH |= PADCH, PADC = 0; \
																if(n == 3) IPH |= PADCH, PADC = 1; \
															}while(0)
//��ѹ����ж����ȼ�����
#define 	LVD_Priority(n)				do{if(n == 0) IPH &= ~PLVDH, PADC = 0; \
																if(n == 1) IPH &= ~PLVDH, PADC = 1; \
																if(n == 2) IPH |= PLVDH, PADC = 0; \
																if(n == 3) IPH |= PLVDH, PADC = 1; \
															}while(0)
/*
//CCP/PCA/PWM�ж����ȼ����� - �ŵ�"STC8G_PCA"�ļ�
#define 	PCA_Priority(n)				do{if(n == 0) IPH &= ~PPCAH, PPCA = 0; \
																if(n == 1) IPH &= ~PPCAH, PPCA = 1; \
																if(n == 2) IPH |= PPCAH, PPCA = 0; \
																if(n == 3) IPH |= PPCAH, PPCA = 1; \
															}while(0)
*/

//========================================================================
//                           �ⲿ�����ͱ�������
//========================================================================

u8 NVIC_Timer0_Init(u8 State, u8 Priority);
u8 NVIC_Timer1_Init(u8 State, u8 Priority);
u8 NVIC_Timer2_Init(u8 State, u8 Priority);
u8 NVIC_Timer3_Init(u8 State, u8 Priority);
u8 NVIC_Timer4_Init(u8 State, u8 Priority);
u8 NVIC_INT0_Init(u8 State, u8 Priority);
u8 NVIC_INT1_Init(u8 State, u8 Priority);
u8 NVIC_INT2_Init(u8 State, u8 Priority);
u8 NVIC_INT3_Init(u8 State, u8 Priority);
u8 NVIC_INT4_Init(u8 State, u8 Priority);
u8 NVIC_ADC_Init(u8 State, u8 Priority);
u8 NVIC_SPI_Init(u8 State, u8 Priority);
u8 NVIC_CMP_Init(u8 State, u8 Priority);
u8 NVIC_I2C_Init(u8 Mode, u8 State, u8 Priority);
u8 NVIC_UART1_Init(u8 State, u8 Priority);
u8 NVIC_UART2_Init(u8 State, u8 Priority);
u8 NVIC_UART3_Init(u8 State, u8 Priority);
u8 NVIC_UART4_Init(u8 State, u8 Priority);
u8 NVIC_PWM_Init(u8 Channel, u8 State, u8 Priority);
u8 NVIC_RTC_Init(u8 State, u8 Priority);

#endif

