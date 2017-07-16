#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "led.h"
#include "delay.h"
#include "stdio.h"


/**********************配置中断控制器***********************/
void NVIC_Config(void){
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//确定优先级组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
}

/********************配置外部中断**************************/
void EXTI_PE13_Config(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//开启外设时钟，因为端口复用为外部中断，故还需开启AFIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	
	//配置NVIC中断控制器
	NVIC_Config();
	
	//开启GPIO端口输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	//设置为上拉输入
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
	//设置中断模式
	EXTI_InitStruct.EXTI_Line = EXTI_Line13;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);	
}


int main(void){
	
	LED_GPIO_Config();
	//LED_On();
	
	EXTI_PE13_Config();
	
	while(1);
	
}

