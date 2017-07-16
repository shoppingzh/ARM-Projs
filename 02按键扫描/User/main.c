#include "stm32f10x.h"
#include "led.h"
#include "key.h"

int main(void){
	LED_GPIO_Config();
	KEY_GPIO_Config();
	while(1){
		if( Key_Scan(GPIOC,GPIO_Pin_13) == KEY_DOWN ){
			LED_Toggle();
		}
	}
}
