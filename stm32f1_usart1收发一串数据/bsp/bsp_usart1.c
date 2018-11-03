#include "bsp_usart1.h"
#include "string.h"



unsigned char Rev_Data;
unsigned char Rev_Num;
unsigned char Rev_String[REV_BUF_SIZE];


GPIO_InitTypeDef GPIO_InitStruct;
USART_InitTypeDef USART_InitStruct;

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
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

void Usart1_Init(unsigned int Baud_Value)
{
	//设置IO口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//设置串口1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//IO口设置PA9
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//IO口设置PA10
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//串口1设置
	USART_InitStruct.USART_BaudRate = Baud_Value;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStruct);	
	
		// 串口中断优先级配置
	NVIC_Configuration();
	
	// 使能串口接收中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
	
	// 使能串口
	USART_Cmd(USART1, ENABLE);
}

static void Send_Byte(unsigned char data)
{
	USART_SendData(USART1,data);
	//while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) != RESET);
	//USART_GetFlagStatus(USART1,USART_FLAG_TXE) = RESET;
	while((USART1->SR&0X40)==0);//等待发送结束 
}

static unsigned char Send_Data(PROTOCOL_TX *p)
{
	static unsigned char i;
	for(i = 0; i < BUF_SIZE; i ++)
	{
		Send_Byte(p->Buf[i]);
	}
	return 0;
}

unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned int Data)
{
	PROTOCOL_TX buf;
	memset(&buf,0,sizeof(buf));
	buf.Usart1_Para.ADDR = addr;
	buf.Usart1_Para.ID = id;
	buf.Usart1_Para.DATA1 = Hight(Data);
	buf.Usart1_Para.DATA2 = Low(Data);
	buf.Usart1_Para.CHECKSUM = (unsigned char)(buf.Usart1_Para.ADDR + buf.Usart1_Para.ID + buf.Usart1_Para.DATA1 + buf.Usart1_Para.DATA2);
	buf.Usart1_Para.STOP1 = 0x0d;
	buf.Usart1_Para.STOP2 = 0x0a;
	return Send_Data(&buf);
}

/*****************************************************************************************************************************************
*
*
*                             接收处理
*
***************************************************************************************************************************************/


unsigned char Serial_IF_OR_NO(void)
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
  if((Rev_Num & 0x80) == 0)
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
				Rev_String[Rev_Num] = Rev_Data;
				Rev_Num ++;
				if(Rev_String[0] != 0x01)
				{
					Rev_Num &= 0x00;
				}
				if(Rev_Num > REV_BUF_SIZE)
				{
					Rev_Num &= 0x00;
				}
			}
		}			
	}
	
}


