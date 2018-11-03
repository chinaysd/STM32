#ifndef _BSP_USART1_H_
#define _BSP_USART1_H_

#include "stm32f10x.h"


#define     Baud       115200

#define BUF_SIZE     7
#define Hight(x)     (((x) >> 8)&&0xff)
#define Low(x)       (x)

#define REV_BUF_SIZE       7
#define Get_32bit(z,w)     ((((z)<<8)|w)&0xffff)



typedef struct
{
	unsigned char ADDR;
	unsigned char ID;
	unsigned char DATA1;
	unsigned char DATA2;
	unsigned char CHECKSUM;
	unsigned char STOP1;
	unsigned char STOP2;
}
USART1_PARA_T;

typedef union
{
	USART1_PARA_T Usart1_Para;
	unsigned char Buf[BUF_SIZE];
}
PROTOCOL_TX;




void Usart1_Init(unsigned int Baud_Value);
unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned int Data);


/***********************************************以下为接受函数**************************************/
void Rev_Serial_IQH(void);
unsigned char Serial_IF_OR_NO(void);

#endif



