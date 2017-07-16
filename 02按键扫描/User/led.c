#include "led.h"

/**************************LED IO端口配置**********************/
void LED_GPIO_Config(){
	//定义GPIO_InitTypeDef结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//开启外设时钟，stm32使用IO口时需要开启外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	//初始化GPIO端口
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//默认给端口为0
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}

/******************************LED开启******************************/
void LED_On(void){
	GPIO_SetBits(GPIOC,GPIO_Pin_3);
}

/*********************************LED关闭**************************/
void LED_Off(void){
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}

/*******************************LED反转**************************/
void LED_Toggle(){
	GPIO_WriteBit(GPIOC,GPIO_Pin_3,!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3));
}
