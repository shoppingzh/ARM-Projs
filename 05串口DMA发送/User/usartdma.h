#ifndef _USART_DMA_H
#define _USART_DMA_H

#include "stm32f10x.h"
#include "stm32f10x_dma.h"

#define BUFFER_SIZE (uint32_t)50000
#define USART1_DR_BASE USART1_BASE+0x04

void DMA_Config(void);

#endif
