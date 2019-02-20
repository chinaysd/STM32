#include "bsp_hse.h"

/* 设置 系统时钟:SYSCLK, AHB总线时钟:HCLK, APB2总线时钟:PCLK2, APB1总线时钟:PCLK1
 * PCLK2 = HCLK = SYSCLK
 * PCLK1 = HCLK/2,最高只能是36M
 * 参数说明：pllmul是PLL的倍频因子，在调用的时候可以是：RCC_PLLMul_x , x:[2,3,...16]
 * 举例：HSE_SetSysClock(RCC_PLLMul_9);  则设置系统时钟为：8MHZ * 9 = 72MHZ
 *       HSE_SetSysClock(RCC_PLLMul_16); 则设置系统时钟为：8MHZ * 16 = 128MHZ，超频慎用
 *
 * HSE作为时钟来源，经过PLL倍频作为系统时钟，这是通常的做法
 */


void Hse_Init(uint32_t pllmul)
{
	__IO uint32_t StartUpCounter = 0, HSEStartUpStatus = 0;

	// 把RCC外设初始化成复位状态，这句是必须的
	  RCC_DeInit();

	  //使能HSE，开启外部晶振，秉火开发板用的是8M
	  RCC_HSEConfig(RCC_HSE_ON);

	  // 等待 HSE 启动稳定
	  HSEStartUpStatus = RCC_WaitForHSEStartUp();
		
		// 只有 HSE 稳定之后则继续往下执行
	  if (HSEStartUpStatus == SUCCESS)
	  {
	//----------------------------------------------------------------------//
	    // 使能FLASH 预存取缓冲区
	    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

	    // SYSCLK周期与闪存访问时间的比例设置，这里统一设置成2
			// 设置成2的时候，SYSCLK低于48M也可以工作，如果设置成0或者1的时候，
			// 如果配置的SYSCLK超出了范围的话，则会进入硬件错误，程序就死了
			// 0：0 < SYSCLK <= 24M
			// 1：24< SYSCLK <= 48M
			// 2：48< SYSCLK <= 72M
	    FLASH_SetLatency(FLASH_Latency_2);
	//----------------------------------------------------------------------//
	 
	    // AHB预分频因子设置为1分频，HCLK = SYSCLK 
	    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
	  
	    // APB2预分频因子设置为1分频，PCLK2 = HCLK
	    RCC_PCLK2Config(RCC_HCLK_Div1); 

	    // APB1预分频因子设置为1分频，PCLK1 = HCLK/2 
	    RCC_PCLK1Config(RCC_HCLK_Div2);
			
	   //-----------------设置各种频率主要就是在这里设置-------------------//
	    // 设置PLL时钟来源为HSE，设置PLL倍频因子
			// PLLCLK = 8MHz * pllmul
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllmul);
	   //------------------------------------------------------------------//

	    // 开启PLL 
	    RCC_PLLCmd(ENABLE);

	    // 等待 PLL稳定
	    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	    {
	    }

	    // 当PLL稳定之后，把PLL时钟切换为系统时钟SYSCLK
	    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	    // 读取时钟切换状态位，确保PLLCLK被选为系统时钟
	    while (RCC_GetSYSCLKSource() != 0x08)
	    {
	    }
	  }
	  else
	  { // 如果HSE开启失败，那么程序就会来到这里，用户可在这里添加出错的代码处理
			// 当HSE开启失败或者故障的时候，单片机会自动把HSI设置为系统时钟，
			// HSI是内部的高速时钟，8MHZ
	    while (1)
	    {
	    }
	  }
}




