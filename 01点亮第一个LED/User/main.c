#include "stm32f10x.h" 
#include "led.h"

void Delay(void);

int main(void){
	
	LED_GPIO_Config();
	
	while(1){
		LED_ON();
		Delay();
		LED_OFF();
		Delay();
		
	}
}

void Delay(void){
	uint16_t t,s;
	for(t=0;t<5000;t++){
		for(s=0;s<500;s++);
	}
}
