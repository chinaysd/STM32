#include "system.h"





void System_Init(void)
{
       Led_Init();
	 #if 1
	 Exti_Config();
	 #else
        Exti_Init();
	 #endif
}

void System_Handle(void)
{
    	
}









