#include "soil_H.h"
#include <stm32f10x_adc.h>
#include "stm32f10x_dma.h"
#include "stm32f10x_rcc.h"
#include "stdio.h"
#include "delay.h"

__IO uint16_t ADC_ConvertedValue=0;


///ADC����
static void ADC1_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 
    /* ʹ�� DMA clock */ 
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    /* ʹ�� ADC1 and GPIOC clock */ 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |RCC_ADC_port, ENABLE);
    /* Configure PC.01 as analog input */  
    GPIO_InitStructure.GPIO_Pin = Gpio_ADC_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����
    GPIO_Init(Gpio_ADC_port, &GPIO_InitStructure); 
	
}

////////////����DMA
void  DMA1_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;//ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue; //�ɼ�����ģ������
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 1;  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;// 
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1, ENABLE);
}



//����adc
static void ADC1_Mode_Config(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    DMA1_Config();
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//����adc
    ADC_InitStructure.ADC_ScanConvMode = DISABLE ;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    RCC_ADCCLKConfig(RCC_PCLK2_Div4);
    //���ò�������
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
    ADC_DMACmd(ADC1, ENABLE);       
    ADC_Cmd(ADC1, ENABLE);
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


///��ʼ��ADC
void ADC1_Init(void)
{
    ADC1_GPIO_Config();
    ADC1_Mode_Config();
}


uint8_t Read_Soil( )
{
	uint8_t num;
	float temp=0,hum;

	
	for(num=0;num<3;num++)
	{
		temp+=ADC_ConvertedValue;
			mDelay(500);

	}
	temp=temp/3;	
	hum=1-((temp-1250)/2750);  //ʵ��õ� ������ģ��ֵΪ1700 ����ˮ�����4000
		printf("%f",temp);
	hum=hum*100;
	
	return (u8)hum;
}





