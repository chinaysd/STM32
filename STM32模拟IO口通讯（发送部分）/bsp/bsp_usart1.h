#ifndef _BSP_USART1_H_
#define _BSP_USART1_H_

#include "stm32f10x.h"

#define    USART1_CONFIG_PROCESS     3      //3个步骤

#define    USART1_ERROR              1
#define    USART1_SUCCESS            0


/***********************发送**********************************/
#define    BUF_SIZE     7
#define    STOP_DATA    0X0D0A
#define    Hight(x)     (((x)>> 8)&0xff)
#define    Low(x)       ((x)&0xff)

/**********************接收**************************************/
#define    Get_32Bit(x,y)      (((((x)<<8)&0xff)|y)&0xffff)


typedef struct
{
	unsigned char ID;
}
USART1_PARA_T;

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
DATA_FORMAT_TX;



typedef union
{
	unsigned char Buf[BUF_SIZE];
	DATA_FORMAT_TX Data_Format_tx;
}
PROTOCOL_SEND;



unsigned char Usart1_App_Handle(unsigned char sum);
void Usart1_Send(unsigned char Data);
unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned char TX_Data);


void Rev_Serial_IQH(void);
unsigned char Rev_Serial_If(void);
//void Rev_Serial_Handle(void);


#endif


