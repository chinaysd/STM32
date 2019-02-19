#include "bsp_exti.h"

NVIC_InitTypeDef NVIC_InitStruct;
GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;

#if 1
static void Nvic_Init(void)
{
	#if 1
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	 NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	 NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	 NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	 NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStruct);
	 NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	 NVIC_Init(&NVIC_InitStruct);
	 #else
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	 NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	 NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	 NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	 NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStruct);
	 #endif
}

static void Gpio_Init(void)
{
	#if 1
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	 GPIO_InitStruct.GPIO_Pin = EXTI0_PIN;
	 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_Init(EXTI0_PORT, &GPIO_InitStruct);
	 //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	 //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	 GPIO_InitStruct.GPIO_Pin = EXTI1_PIN;
	 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_Init(EXTI1_PORT, &GPIO_InitStruct);
	 #else
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	 Nvic_Init();
	 GPIO_InitStruct.GPIO_Pin = EXTI1_PIN;
	 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_Init(EXTI1_PORT, &GPIO_InitStruct);

	 #endif
}

static void Exti_Init(void)
{
	#if 1
	 Gpio_Init();
	 Nvic_Init();
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	 EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	 EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;//EXTI_Trigger_Rising;
	 EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStruct);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);
	 EXTI_InitStruct.EXTI_Line = EXTI_Line13;
	 EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;//EXTI_Trigger_Falling;
	 EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStruct);
	 #else
	 Gpio_Init();
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);
	 EXTI_InitStruct.EXTI_Line = EXTI_Line13;
	 EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;//EXTI_Trigger_Falling;
	 EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStruct);
	 #endif
}

void Exti_Config(void)
{
	Exti_Init();
}
#else

static void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
      NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
      NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
      NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
      NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStruct);
      NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;  
      NVIC_Init(&NVIC_InitStruct);
}


void Exti_Init(void)
{
   
   GPIO_InitTypeDef GPIO_InitStruct;
   EXTI_InitTypeDef EXTI_InitStruct; 
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOC,ENABLE);
   Nvic_Init();
   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOA,&GPIO_InitStruct);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
   
   EXTI_InitStruct.EXTI_Line = EXTI_Line0;
   EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
   EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
   EXTI_InitStruct.EXTI_LineCmd = ENABLE;
   EXTI_Init(&EXTI_InitStruct);
   
   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOC,&GPIO_InitStruct);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);

   EXTI_InitStruct.EXTI_Line = EXTI_Line13;
   EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
   EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
   EXTI_InitStruct.EXTI_LineCmd = ENABLE;
   EXTI_Init(&EXTI_InitStruct);
}




#endif


