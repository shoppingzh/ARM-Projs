#include "usartdma.h"

uint8_t Buf[BUFFER_SIZE];

/************************DMA��ʼ��*************************/
void DMA_Config(void){
	DMA_InitTypeDef DMA_InitStruct;
	
	//����DMAʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStruct.DMA_BufferSize = BUFFER_SIZE;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST; //������ΪĿ�ĵ�
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;  //��ֹ�ڴ浽�ڴ�ת������
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)Buf;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  //�ڴ�ת�����ֽ�Ϊ��λ
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ�ת��ʱ��ַ����
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_PeripheralBaseAddr = USART1_DR_BASE;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���������ֽ�Ϊ��λ
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ��ŵ�����ʼ�ձ�����
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;  //����DMA�������ȼ���������û������
	
	//��ʼ��DMA��ѡ��DMAͨ��
	DMA_Init(DMA1_Channel4,&DMA_InitStruct);
	
	//ʹ��DMA
	DMA_Cmd(DMA1_Channel4,ENABLE);
	
	//����DMA�жϣ�������ת����ɺ󴥷��ж�
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
}
