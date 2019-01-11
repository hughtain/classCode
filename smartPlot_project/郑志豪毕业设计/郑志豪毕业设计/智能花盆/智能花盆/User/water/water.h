#include <stm32f10x.h>

#define water_pin GPIO_Pin_0 //////////////PB0Ë®±Ã
#define water_port GPIOB

#define Water_ON   GPIO_ResetBits(water_port,water_pin);
#define Water_Off  	GPIO_SetBits(water_port,water_pin);

void Water_Gpio_config(void);



