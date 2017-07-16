#include "key.h"

/**************����GPIO�˿�����****************/
void KEY_GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//��������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//��ʼ��GPIO�˿ڲ���������ģʽ��������������ٶ�
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	
	//��ʼ��GPIO�˿�
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}

/**********************����ɨ��***********************/
uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	if(!GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)){
		Key_Delay();
		if(!GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)){
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin));
			return KEY_DOWN;
		}
		return KEY_UP;
	}
	return KEY_UP;
}
