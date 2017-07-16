#include "key.h"

/**************按键GPIO端口配置****************/
void KEY_GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//开启外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//初始化GPIO端口参数：输入模式，无需配置输出速度
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	
	//初始化GPIO端口
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}

/**********************按键扫描***********************/
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
