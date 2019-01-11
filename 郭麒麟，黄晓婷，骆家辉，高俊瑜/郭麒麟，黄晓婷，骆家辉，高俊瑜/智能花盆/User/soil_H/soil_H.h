#ifndef _SOIL_H_
#define  _SOIL_H_
#include "stm32f10x.h"

#define ADC1_DR_Address ((u32)0x40012400+0x4c)
#define  RCC_ADC_port RCC_APB2Periph_GPIOA
#define  Gpio_ADC_pin  GPIO_Pin_1
#define  Gpio_ADC_port GPIOA



void  DMA1_Config(void);
void ADC1_Init(void);
uint8_t Read_Soil(void);


#endif

