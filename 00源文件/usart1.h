#ifndef _USART1_H
#define _USART1_H

#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stdio.h"

void USART_Config(void);
int fputc(int ch, FILE * f);

#endif
