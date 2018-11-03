#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_basetime.h"

#define uchar unsigned char
#define uint  unsigned int


void System_Init(void);
void System_Handle(void);

#endif



