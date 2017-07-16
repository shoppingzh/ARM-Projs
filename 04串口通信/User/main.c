#include "stm32f10x.h"
#include "usart1.h"
#include "stdio.h"
#include "delay.h"
#include "key.h"

int fputc(int ch, FILE * f){
	USART_SendData(USART1,(unsigned char)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
	return ch;
}

int main(void){

	USART_Config();
	
	uint8_t i = 0;
	
	while(1){
		printf(" Hello,world!");
		Delay(0x00ffffff);
	}
	
	
	while(1){
		//USART_SendData(USART1,i++);
		//while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
		Delay(0x0000ff00);
	}
	
}
