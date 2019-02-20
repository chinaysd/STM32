#include "bsp_hse.h"

/* ���� ϵͳʱ��:SYSCLK, AHB����ʱ��:HCLK, APB2����ʱ��:PCLK2, APB1����ʱ��:PCLK1
 * PCLK2 = HCLK = SYSCLK
 * PCLK1 = HCLK/2,���ֻ����36M
 * ����˵����pllmul��PLL�ı�Ƶ���ӣ��ڵ��õ�ʱ������ǣ�RCC_PLLMul_x , x:[2,3,...16]
 * ������HSE_SetSysClock(RCC_PLLMul_9);  ������ϵͳʱ��Ϊ��8MHZ * 9 = 72MHZ
 *       HSE_SetSysClock(RCC_PLLMul_16); ������ϵͳʱ��Ϊ��8MHZ * 16 = 128MHZ����Ƶ����
 *
 * HSE��Ϊʱ����Դ������PLL��Ƶ��Ϊϵͳʱ�ӣ�����ͨ��������
 */


void Hse_Init(uint32_t pllmul)
{
	__IO uint32_t StartUpCounter = 0, HSEStartUpStatus = 0;

	// ��RCC�����ʼ���ɸ�λ״̬������Ǳ����
	  RCC_DeInit();

	  //ʹ��HSE�������ⲿ���񣬱��𿪷����õ���8M
	  RCC_HSEConfig(RCC_HSE_ON);

	  // �ȴ� HSE �����ȶ�
	  HSEStartUpStatus = RCC_WaitForHSEStartUp();
		
		// ֻ�� HSE �ȶ�֮�����������ִ��
	  if (HSEStartUpStatus == SUCCESS)
	  {
	//----------------------------------------------------------------------//
	    // ʹ��FLASH Ԥ��ȡ������
	    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

	    // SYSCLK�������������ʱ��ı������ã�����ͳһ���ó�2
			// ���ó�2��ʱ��SYSCLK����48MҲ���Թ�����������ó�0����1��ʱ��
			// ������õ�SYSCLK�����˷�Χ�Ļ���������Ӳ�����󣬳��������
			// 0��0 < SYSCLK <= 24M
			// 1��24< SYSCLK <= 48M
			// 2��48< SYSCLK <= 72M
	    FLASH_SetLatency(FLASH_Latency_2);
	//----------------------------------------------------------------------//
	 
	    // AHBԤ��Ƶ��������Ϊ1��Ƶ��HCLK = SYSCLK 
	    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
	  
	    // APB2Ԥ��Ƶ��������Ϊ1��Ƶ��PCLK2 = HCLK
	    RCC_PCLK2Config(RCC_HCLK_Div1); 

	    // APB1Ԥ��Ƶ��������Ϊ1��Ƶ��PCLK1 = HCLK/2 
	    RCC_PCLK1Config(RCC_HCLK_Div2);
			
	   //-----------------���ø���Ƶ����Ҫ��������������-------------------//
	    // ����PLLʱ����ԴΪHSE������PLL��Ƶ����
			// PLLCLK = 8MHz * pllmul
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllmul);
	   //------------------------------------------------------------------//

	    // ����PLL 
	    RCC_PLLCmd(ENABLE);

	    // �ȴ� PLL�ȶ�
	    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	    {
	    }

	    // ��PLL�ȶ�֮�󣬰�PLLʱ���л�Ϊϵͳʱ��SYSCLK
	    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	    // ��ȡʱ���л�״̬λ��ȷ��PLLCLK��ѡΪϵͳʱ��
	    while (RCC_GetSYSCLKSource() != 0x08)
	    {
	    }
	  }
	  else
	  { // ���HSE����ʧ�ܣ���ô����ͻ���������û�����������ӳ���Ĵ��봦��
			// ��HSE����ʧ�ܻ��߹��ϵ�ʱ�򣬵�Ƭ�����Զ���HSI����Ϊϵͳʱ�ӣ�
			// HSI���ڲ��ĸ���ʱ�ӣ�8MHZ
	    while (1)
	    {
	    }
	  }
}




