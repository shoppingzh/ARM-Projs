#include "adc.h"

__IO uint16_t Value;

/******************ADC��GPIO�˿ڳ�ʼ��******************/
void ADC_GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}

/********************ADC DMA��ʼ��*************************/
void ADC_DMA_Config(){
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStruct.DMA_BufferSize = 1;  //һ������
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;  //���� -> �ڴ�
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;  //�����ڴ� -> �ڴ�
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&Value;  //�ڴ��ַ
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  //�ڴ�����ݴ�СΪ16λ������
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;  //ÿ�ηŵ�ָ�����ڴ浥Ԫ��������
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;  //ѭ��ת�ƣ�����ת��
	DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DATA_ADDR;  //��ADC1���ڴ��ַȡ����
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //ÿ��ȡ�����ݴ�СΪ����
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //ÿ�δ�ָ��λ��ȡ���ݣ�������
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;  //���ø����ȼ���������������
	
	//��ʼ��DMA
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	//����DMAת��
	DMA_Cmd(DMA1_Channel1,ENABLE);
}	


/********************ADC����********************/
void ADC_Config(void){
	ADC_InitTypeDef ADC_InitStruct;
	
	//����ADC1������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	//��ʼ������
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;   //��������ת��
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;  //�Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //�������ⲿ����ת��
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;  //����ADC
	ADC_InitStruct.ADC_NbrOfChannel = 1;  //ת��ͨ����Ϊ1
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;  //�ر�ɨ��ת��ģʽ
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//����ADC��ת��ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //72MHz��6��Ƶ��Ϊ12MHz
	//���ò�������
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,1,ADC_SampleTime_55Cycles5);
	
	//ʹ��ADC1��DMAͨ��
	ADC_DMACmd(ADC1,ENABLE);
	//ʹ��ADC
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	//ADת��
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
