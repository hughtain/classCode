#ifndef _HC-SR501_H
#define _HC-SR501_H

#include "system.h"

void Lsen_Init(void);
u8 Lsens_Get_Val(void);
u16 Get_Adc3(u8 ch); 
void  Adc3_Init(void);



#endif