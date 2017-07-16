#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

void LED_GPIO_Config(void);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);

#endif
