#include "bsp_key.h"

KEY_PARA_T Key_Para[KEY_NUM];

GPIO_InitTypeDef Key_InitStruct;
NVIC_InitTypeDef Key_NVIC_InitStruct;
EXTI_InitTypeDef Key_EXTI_InitStruct;
unsigned char Key_Init(unsigned char id)
{
	if(id > KEY_NUM)
	   return KEY_ERROR;
	if(id == 0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		Key_InitStruct.GPIO_Pin = KEY2_PIN;
		Key_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		Key_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(KEY2_PORT,&Key_InitStruct);
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		Key_InitStruct.GPIO_Pin = KEY1_PIN;
		GPIO_Init(KEY1_PORT,&Key_InitStruct);
		return KEY_SUCCESS;
	}
	else if(id == 1)
	{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		Key_NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
		Key_NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
		Key_NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
		Key_NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&Key_NVIC_InitStruct);
		
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		Key_NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
		Key_NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&Key_NVIC_InitStruct);
		return KEY_SUCCESS;
	}
	else if(id == 2)
	{
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
		Key_EXTI_InitStruct.EXTI_Line = EXTI_Line0;
		Key_EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		Key_EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
		Key_EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_Init(&Key_EXTI_InitStruct);
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
		Key_EXTI_InitStruct.EXTI_Line = EXTI_Line13;
	  Key_EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		Key_EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
		Key_EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_Init(&Key_EXTI_InitStruct);
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
	for(i = 0;i < sum; i ++)
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

unsigned char BackCall_Key(unsigned char n,unsigned char (*ptr)(unsigned char))
{
	(*ptr)(n);
	return KEY_SUCCESS;
}







