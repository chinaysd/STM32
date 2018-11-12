#include "bsp_usart1.h"
#include "string.h"

#include "bsp_led.h"
#include "hal_led.h"




/**********************************************************************************
 接收到数据的变量定义
***********************************************************************************/
unsigned char Rev_Data;
unsigned char Rev_Num;
unsigned char Rev_String_Data[BUF_SIZE];
unsigned int  Temp;

USART1_PARA_T Usart1_Para[USART1_CONFIG_PROCESS];

static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}


unsigned char Usart1_Init(unsigned char id)
{
	
	if(id > USART1_CONFIG_PROCESS)
		return USART1_ERROR;
	#if 1
	if(id == 0)
	{
		NVIC_InitTypeDef Usart1_NVIC_InitStruct;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		Usart1_NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
		Usart1_NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
		Usart1_NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
		Usart1_NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&Usart1_NVIC_InitStruct);
		return USART1_SUCCESS;
	}
	else if(id == 1)
	{
		GPIO_InitTypeDef Usart1_GPIO_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		Usart1_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
		Usart1_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		Usart1_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&Usart1_GPIO_InitStruct);
		
		Usart1_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
		Usart1_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA,&Usart1_GPIO_InitStruct);
		return USART1_SUCCESS;
	}
	else if(id == 2)
	{
		USART_InitTypeDef Usart1_InitStruct;
		Usart1_InitStruct.USART_BaudRate = 115200;
		Usart1_InitStruct.USART_WordLength = USART_WordLength_8b;
		Usart1_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		Usart1_InitStruct.USART_Parity = USART_Parity_No;
		Usart1_InitStruct.USART_StopBits = USART_StopBits_1;
		Usart1_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART1,&Usart1_InitStruct);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		USART_Cmd(USART1,ENABLE);
		return USART1_SUCCESS;
	}
	#endif
	return USART1_ERROR;
}

unsigned char Usart1_App_Init(USART1_PARA_T *p)
{
	unsigned char Usart1_Init(unsigned char ID);
	return Usart1_Init(p->ID);
}

unsigned char Usart1_App_Handle(unsigned char sum)
{
	static unsigned char i;
	if(i > sum)
		return USART1_ERROR;
	for(i = 0; i < sum; i ++)
	{
		Usart1_Para[i].ID = i;
		Usart1_App_Init(&Usart1_Para[i]);
	}
	if(i != sum)
	{
		return USART1_ERROR;
	}
	else 
	{
		return USART1_SUCCESS;
	}
}


void Usart1_Send(unsigned char Data)
{
	USART_SendData(USART1,Data);
	//while(USART_GetITStatus(USART1,USART_IT_TXE) != RESET);
	while((USART1->SR&0X40)==0);//等待发送结束 
}

unsigned char Send_Data(PROTOCOL_SEND *p)
{
	static unsigned char i;
	for(i = 0;i < BUF_SIZE;i ++)
	{
		Usart1_Send(p->Buf[i]);
	}
	return 0;
}

unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned char TX_Data)
{
	PROTOCOL_SEND buf;
	memset(&buf,0,sizeof(buf));
	buf.Data_Format_tx.ADDR      = addr;
	buf.Data_Format_tx.ID        = id;
	buf.Data_Format_tx.DATA1     = Hight(TX_Data);
	buf.Data_Format_tx.DATA2     = Low(TX_Data);
	buf.Data_Format_tx.CHECKSUM  = (unsigned char)(buf.Data_Format_tx.ADDR + buf.Data_Format_tx.ID + buf.Data_Format_tx.DATA1 + buf.Data_Format_tx.DATA2);
	buf.Data_Format_tx.STOP1     = Hight(STOP_DATA);
	buf.Data_Format_tx.STOP2     = Low(STOP_DATA);
	return Send_Data(&buf);
}


/***********************************************************************************************************************************************/

unsigned char Rev_Serial_If(void)
{
	if(Rev_Num & 0x80)
	{
		Rev_Num &= 0x00;
		return 1;
	}
	else
	{
		return 0;
	}
}

void Rev_Serial_IQH(void)
{
	Rev_Data = USART_ReceiveData(USART1);
	if((Rev_Num & 0x80) == 0x00)
	{
		if(Rev_Num & 0x40)
		{
		  if(Rev_Data == 0x0a)
			{
				Rev_Num |= 0x80;
			}	
      else
			{
				Rev_Num &= 0x00;
			}				
		}
		else
		{
			if(Rev_Data == 0x0d)
			{
				Rev_Num |= 0x40;
			}
			else
			{
				Rev_String_Data[Rev_Num] = Rev_Data;
				Rev_Num ++;
				if(Rev_String_Data[0] != 0x55)
				{
					Rev_Num &= 0x00;
				}
				if(Rev_Num > BUF_SIZE)
				{
					Rev_Num &= 0x00;
				}
			}
		}
	}
}










