#ifndef _ADC_H
#define _ADC_H

#include "stm32f10x.h"

#define ADC1_DATA_ADDR ADC1_BASE+0x4C

//Functions
void ADC_GPIO_Config(void);
void ADC_DMA_Config(void);
void ADC_Config(void);


#endif
