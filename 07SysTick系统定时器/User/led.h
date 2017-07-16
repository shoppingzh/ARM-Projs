#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

#define ON 1
#define OFF 0

void LED_GPIO_Config(void);
void LED(uint8_t status);
void LED_Toggle(void);

#endif
