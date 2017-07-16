#include "usartdma.h"

uint8_t Buf[BUFFER_SIZE];

/************************DMA初始化*************************/
void DMA_Config(void){
	DMA_InitTypeDef DMA_InitStruct;
	
	//开启DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStruct.DMA_BufferSize = BUFFER_SIZE;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST; //外设作为目的地
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;  //禁止内存到内存转移数据
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)Buf;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  //内存转移以字节为单位
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存转移时地址自增
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_PeripheralBaseAddr = USART1_DR_BASE;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //外设存放以字节为单位
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址存放的数据始终被覆盖
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;  //设置DMA操作优先级，在这里没有意义
	
	//初始化DMA，选择DMA通道
	DMA_Init(DMA1_Channel4,&DMA_InitStruct);
	
	//使能DMA
	DMA_Cmd(DMA1_Channel4,ENABLE);
	
	//开启DMA中断，当数据转移完成后触发中断
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
}
