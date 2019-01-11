#ifndef _machine_H
#define _machine_H

#include "system.h"

/*  LED时钟端口、引脚定义 */
#define MAC_PORT 			GPIOC   
#define MAC_PIN 			(GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_7)
#define MAC_PORT_RCC		RCC_APB2Periph_GPIOC


#define MAC1 PCout(2)  	//D1指示灯连接的是PC0管脚
#define MAC2 PCout(3)  	//D2指示灯连接的是PC1管脚
#define MAC3 PCout(4)	//D3指示灯连接的是PC2管脚


#define MAC0 PCout(0)  	//D1指示灯连接的是PC0管脚
#define MAC5 PCout(5)  	//D2指示灯连接的是PC1管脚
#define MAC7 PCout(7)	//D3指示灯连接的是PC2管脚





void machine_stop(void);//停止
void machine_fast_stop(void);//快速停止
void machine_back(void);//逆时针转
void machine_goto(void);//顺时针转



void machine1_stop(void);//停止
void machine1_fast_stop(void);//快速停止
void machine1_back(void);//逆时针转
void machine1_goto(void);//顺时针转

void MAC_Init(void);


#endif
