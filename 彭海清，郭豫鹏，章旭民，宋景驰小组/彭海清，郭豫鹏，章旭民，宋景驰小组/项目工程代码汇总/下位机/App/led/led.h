#ifndef _led_H
#define _led_H

#include "system.h"

/*  LEDʱ�Ӷ˿ڡ����Ŷ��� */
#define LED_PORT 			GPIOC   
#define LED_PIN 			(GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_7)
#define LED_PORT_RCC		RCC_APB2Periph_GPIOC


#define led1 PCout(0)
#define led6 PCout(5)
#define led8 PCout(7)
//#define led4 PCout(3)


void LED_Init(void);


#endif
