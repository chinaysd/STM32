#ifndef _BSP_LED_H_
#define _BSP_LED_H_


#include "stm32f10x.h"


#define LED_NUM     2
#define LED_ERROR   1
#define LED_SUCCESS 0

#define LED1_PORT   GPIOC
#define LED1_PIN    GPIO_Pin_2

#define LED2_PORT   GPIOC
#define LED2_PIN    GPIO_Pin_3

typedef struct
{
	unsigned char ID;
	
}
LED_PARA_T;




unsigned char Led_App_Handle(unsigned char sum);
unsigned char BackCall_LED(unsigned char n,unsigned char (*ptr)(unsigned char));


#endif


