#include "stm32f10x.h"
#include "led.h"

uint32_t Current_Time;

/****************SysTick系统定时器初始化******************/
void SysTick_Init(void){
	//如果配置错误，则停在此处
	if(SysTick_Config(SystemCoreClock/10000)){
		while(1);
	}
	//关闭SysTick
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

/********************SysTick延时*************************/
void Delay_us(uint32_t time){
	Current_Time = time;
	//开启SysTick
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	while(Current_Time);
}

/************************Main****************************/
int main(void){
	LED_GPIO_Config();
	
	SysTick_Init();
	
	while(1){
		LED_Toggle();
		Delay_us(5000);
	}
}
