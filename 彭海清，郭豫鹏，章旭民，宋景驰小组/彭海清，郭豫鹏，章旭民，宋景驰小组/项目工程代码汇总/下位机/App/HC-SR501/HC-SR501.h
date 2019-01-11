#ifndef _HC_SR501_H
#define _HC_SR501_H

#include "system.h"


#define HC_PORT 			GPIOA   
#define  HC_PIN 			GPIO_Pin_2
#define HC_PORT_RCC		RCC_APB2Periph_GPIOA






void HC_Init();


#endif
