#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "stm32f10x.h"

#define KEY_NUM       3

#define KEY_ERROR      1
#define KEY_SUCCESS    0

#define KEY1_PORT     GPIOC
#define KEY1_PIN      GPIO_Pin_13

#define KEY2_PORT     GPIOA
#define KEY2_PIN      GPIO_Pin_0

typedef struct
{
	unsigned char ID;
}
KEY_PARA_T;


unsigned char Key_App_Handle(unsigned char sum);
unsigned char BackCall_Key(unsigned char n,unsigned char (*ptr)(unsigned char));

#endif



