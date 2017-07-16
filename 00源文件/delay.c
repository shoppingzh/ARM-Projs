#include "delay.h"

/*****************°´¼üÏû¶¶ÑÓÊ±**********************/
void Key_Delay(void){
	uint16_t i;
	for(i=0;i<0x0FFF;i++);
}

void Delay(uint32_t time){
	uint32_t i;
	for(i=0;i<time;i++);
}
