#include "water.h"


void Water_Gpio_config()
{
	GPIO_InitTypeDef Water_Gpio;
	Water_Gpio.GPIO_Mode=GPIO_Mode_Out_OD;
	Water_Gpio.GPIO_Pin=water_pin;
	Water_Gpio.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(water_port,&Water_Gpio);
	Water_Off
}


