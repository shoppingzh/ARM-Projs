#include "stm32f10x.h"
#include "led.h"

uint32_t Current_Time;

/****************SysTickϵͳ��ʱ����ʼ��******************/
void SysTick_Init(void){
	//������ô�����ͣ�ڴ˴�
	if(SysTick_Config(SystemCoreClock/10000)){
		while(1);
	}
	//�ر�SysTick
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

/********************SysTick��ʱ*************************/
void Delay_us(uint32_t time){
	Current_Time = time;
	//����SysTick
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
