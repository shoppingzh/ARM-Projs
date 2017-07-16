#include "stm32f10x.h"
#include "led.h"
#include "usart1.h"
#include "usartdma.h"
#include "nvic.h"

extern uint8_t Buf[BUFFER_SIZE];

int main(void){
	
	LED_GPIO_Config();
	USART_Config();
	//因为要使用到DMA中断，所以应初始化NVIC中断控制器
	NVIC_Config();
	DMA_Config();
	
	//初始化要发送的缓冲区内容
	uint16_t i;
	for(i=0;i<BUFFER_SIZE;i++){
		Buf[i] = 0xff;
	}

	//发出DMA请求
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);

	LED_On();
	
	while(1);
	
}
