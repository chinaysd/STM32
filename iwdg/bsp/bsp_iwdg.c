#include "bsp_iwdg.h"


void Iwdg_Init(void)
{
	 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	 IWDG_SetPrescaler(IWDG_Prescaler_64);
	 IWDG_SetReload(625);
	 IWDG_ReloadCounter();
	 IWDG_Enable();
}

void Iwdg_Feed(void)
{
	IWDG_ReloadCounter();
}











