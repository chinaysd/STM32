# STM32
STM32可以在此源码上修改

1、使用外部中断时注意IO口复用的时钟定义，例如：RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);

2、使用串口打印 printf函数时，需要注意以下几点：
A、包含头文件stdio.h
B、还有以下这个函数：
int fputc(int ch, FILE *f)//重定向，让printf输出到串口
{
    USART_SendData(USART1,ch);

    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    return ch;
}



