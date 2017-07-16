#include "led.h"

/***********************LED�Ƶ�GPIO�˿�����********************/
void LED_GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GPIO_InitStruct);	
}

/**********************��/�ر�LED*****************************/
void LED(uint8_t status){
	if(status == ON){
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
	}
	if(status == OFF){
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	}
}

/*********************��תLED***************************/
void LED_Toggle(void){
	if(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_3) == SET){
		LED(OFF);
	}else{
		LED(ON);
	}
}
