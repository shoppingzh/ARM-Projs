#include "stm32f10x.h"
#include "adc.h"
#include "stdio.h"
#include "usart1.h"
#include "delay.h"

extern __IO uint16_t Value;

int main(void){
	
	USART_Config();
	//
	ADC_GPIO_Config();
	ADC_DMA_Config();
	ADC_Config();
	
	while(1){
		printf("当前转换后的值为：%04x\n",Value);
		Delay(0x00ffffee);
	}
	
	
	
	
}
