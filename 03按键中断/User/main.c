#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "led.h"
#include "delay.h"
#include "stdio.h"


/**********************�����жϿ�����***********************/
void NVIC_Config(void){
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//ȷ�����ȼ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
}

/********************�����ⲿ�ж�**************************/
void EXTI_PE13_Config(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//��������ʱ�ӣ���Ϊ�˿ڸ���Ϊ�ⲿ�жϣ��ʻ��迪��AFIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	
	//����NVIC�жϿ�����
	NVIC_Config();
	
	//����GPIO�˿�����
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	//����Ϊ��������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
	//�����ж�ģʽ
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

