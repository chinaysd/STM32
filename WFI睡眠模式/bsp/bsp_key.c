#include "bsp_key.h"

KEY_PARA_T Key_Para[ KEY_NUM];


NVIC_InitTypeDef NVIC_InitStruct;
GPIO_InitTypeDef KEY_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;


void Nvic_Config(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority  = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void Exit_Key_Init(void)
{
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}

unsigned char Key_Init(unsigned char id)
{
	if(id > KEY_NUM)
		return KEY_ERROR;
	if(id == 0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		Nvic_Config();
		KEY_InitStruct.GPIO_Pin = KEY1_PIN;
		KEY_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(KEY1_PORT,&KEY_InitStruct);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
		Exit_Key_Init();
		return KEY_SUCCESS;
	}
	else if(id == 1)
	{
		
		return KEY_SUCCESS;
	}
	return KEY_ERROR;
}


unsigned char Key_App_Init(KEY_PARA_T *P)
{
	unsigned char Key_Init(unsigned char ID);
	return Key_Init(P->ID);
}

unsigned char Key_App_Handle(unsigned char sum)
{
	static unsigned char i;
	if(sum > KEY_NUM)
		return KEY_ERROR;
	for(i = 0; i < sum; i ++)
	{
		Key_Para[i].ID = i;
		Key_App_Init(&Key_Para[i]);
	}
	if(i != sum)
	{
		return KEY_ERROR;
	}
	else 
	{
		return KEY_SUCCESS;
	}
}



