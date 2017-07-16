#include "stm32f10x.h"
#include "led.h"
#include "usart1.h"
#include "usartdma.h"
#include "nvic.h"

extern uint8_t Buf[BUFFER_SIZE];

int main(void){
	
	LED_GPIO_Config();
	USART_Config();
	//��ΪҪʹ�õ�DMA�жϣ�����Ӧ��ʼ��NVIC�жϿ�����
	NVIC_Config();
	DMA_Config();
	
	//��ʼ��Ҫ���͵Ļ���������
	uint16_t i;
	for(i=0;i<BUFFER_SIZE;i++){
		Buf[i] = 0xff;
	}

	//����DMA����
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);

	LED_On();
	
	while(1);
	
}
