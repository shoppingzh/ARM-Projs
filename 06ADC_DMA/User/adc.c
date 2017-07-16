#include "adc.h"

__IO uint16_t Value;

/******************ADC的GPIO端口初始化******************/
void ADC_GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}

/********************ADC DMA初始化*************************/
void ADC_DMA_Config(){
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStruct.DMA_BufferSize = 1;  //一个数据
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;  //外设 -> 内存
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;  //进制内存 -> 内存
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&Value;  //内存地址
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  //内存的数据大小为16位，半字
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;  //每次放到指定的内存单元，不自增
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;  //循环转移，不断转移
	DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DATA_ADDR;  //从ADC1的内存地址取数据
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //每次取的数据大小为半字
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //每次从指定位置取数据，不自增
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;  //设置高优先级，该设置无意义
	
	//初始化DMA
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	//开启DMA转移
	DMA_Cmd(DMA1_Channel1,ENABLE);
}	


/********************ADC配置********************/
void ADC_Config(void){
	ADC_InitTypeDef ADC_InitStruct;
	
	//开启ADC1的外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	//初始化配置
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;   //开启连续转换
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;  //右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //不采用外部触发转换
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;  //独立ADC
	ADC_InitStruct.ADC_NbrOfChannel = 1;  //转换通道数为1
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;  //关闭扫描转换模式
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//配置ADC的转换时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //72MHz的6分频，为12MHz
	//配置采样周期
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,1,ADC_SampleTime_55Cycles5);
	
	//使能ADC1的DMA通道
	ADC_DMACmd(ADC1,ENABLE);
	//使能ADC
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	//AD转换
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
