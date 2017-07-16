#include "led.h"

/*--------------------LED IO�˿�����--------------------*/
void LED_GPIO_Config(){
	//����GPIO_InitTypeDef�ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//��������ʱ�ӣ�stm32ʹ��IO��ʱ��Ҫ��������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	//��ʼ��GPIO�˿�
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

/*--------------------LED����--------------------*/
void LED_ON(void){
	GPIO_SetBits(GPIOC,GPIO_Pin_3);
}

/*--------------------LED�ر�--------------------*/
void LED_OFF(void){
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}
