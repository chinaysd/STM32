#include "system.h"



void Delay_Time(unsigned int Time)
{
	static unsigned int i,j;
	for(i = Time;i > 0 ; i --)
	{
		for(j = 200; j > 0 ; j --);
	}
}

void System_Init(void)
{
	// 程序来到main函数之前，启动文件：statup_stm32f10x_hd.s已经调用
	// SystemInit()函数把系统时钟初始化成72MHZ
	// SystemInit()在system_stm32f10x.c中定义
	// 如果用户想修改系统时钟，可自行编写程序修改
	
	// 重新设置系统时钟，这时候可以选择使用HSE还是HSI
	
	// 使用HSI时，SYSCLK = 4M * RCC_PLLMul_x, x:[2,3,...16],最高是64MH
	//Hsi_Init(RCC_PLLMul_16);

       // 使用HSE时，SYSCLK = 8M * RCC_PLLMul_x, x:[2,3,...16],最高是128M
	Hse_Init(RCC_PLLMul_2);
	Led_Init();
}

void System_Handle(void)
{
      LED_SET(1);	
      Delay_Time(1000);
      LED_SET(0);	
      Delay_Time(1000);
}




