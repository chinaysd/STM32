# STM32
STM32可以在此源码上修改

1、使用外部中断时注意IO口复用的时钟定义，例如：RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
