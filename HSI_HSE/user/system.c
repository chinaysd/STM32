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
	// ��������main����֮ǰ�������ļ���statup_stm32f10x_hd.s�Ѿ�����
	// SystemInit()������ϵͳʱ�ӳ�ʼ����72MHZ
	// SystemInit()��system_stm32f10x.c�ж���
	// ����û����޸�ϵͳʱ�ӣ������б�д�����޸�
	
	// ��������ϵͳʱ�ӣ���ʱ�����ѡ��ʹ��HSE����HSI
	
	// ʹ��HSIʱ��SYSCLK = 4M * RCC_PLLMul_x, x:[2,3,...16],�����64MH
	//Hsi_Init(RCC_PLLMul_16);

       // ʹ��HSEʱ��SYSCLK = 8M * RCC_PLLMul_x, x:[2,3,...16],�����128M
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




