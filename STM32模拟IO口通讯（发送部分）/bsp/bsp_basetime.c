#include "bsp_basetime.h"

BASETIME_PARA_T BaseTime_Para[BASETIME_NUM];

NVIC_InitTypeDef BaseTime_InitStruct;
TIM_TimeBaseInitTypeDef TIM6_TimeBaseStruct;

unsigned char BaseTime_Init(unsigned char id)
{
	if(id > BASETIME_NUM)
		return BASETIME_ERROR;
	if(id == 0)
	{
		 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		 BaseTime_InitStruct.NVIC_IRQChannel = TIM6_IRQn;
		 BaseTime_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
		 BaseTime_InitStruct.NVIC_IRQChannelSubPriority = 1;
		 BaseTime_InitStruct.NVIC_IRQChannelCmd  = ENABLE;
		 NVIC_Init(&BaseTime_InitStruct);
     return BASETIME_SUCCESS;    		
	}
	else if(id == 1)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
		TIM6_TimeBaseStruct.TIM_Period = 200;
		TIM6_TimeBaseStruct.TIM_Prescaler = 88;
		TIM_TimeBaseInit(TIM6,&TIM6_TimeBaseStruct);
		TIM_ClearFlag(TIM6,TIM_FLAG_Update);
		TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
		TIM_Cmd(TIM6,ENABLE);
		return BASETIME_SUCCESS;
	}
	return BASETIME_ERROR;
}

unsigned char BaseTime_App_Init(BASETIME_PARA_T *p)
{
	unsigned char BaseTime_Init(unsigned char ID);
	return BaseTime_Init(p->ID);
}

unsigned char BaseTime_App_Handle(unsigned char sum)
{
   static unsigned char i;
	 if(sum > BASETIME_NUM)
		 return BASETIME_ERROR;
	 for(i = 0; i < sum; i ++)
	 {
		 BaseTime_Para[i].ID = i;
		 BaseTime_App_Init(&BaseTime_Para[i]);
	 }
	 if(i != sum)
	 {
		 return BASETIME_ERROR;
	 }
	 else 
	 {
		 return BASETIME_SUCCESS;
	 }
}















