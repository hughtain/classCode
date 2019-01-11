#ifndef _machine_H
#define _machine_H

#include "system.h"

/*  LEDʱ�Ӷ˿ڡ����Ŷ��� */
#define MAC_PORT 			GPIOC   
#define MAC_PIN 			(GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_7)
#define MAC_PORT_RCC		RCC_APB2Periph_GPIOC


#define MAC1 PCout(2)  	//D1ָʾ�����ӵ���PC0�ܽ�
#define MAC2 PCout(3)  	//D2ָʾ�����ӵ���PC1�ܽ�
#define MAC3 PCout(4)	//D3ָʾ�����ӵ���PC2�ܽ�


#define MAC0 PCout(0)  	//D1ָʾ�����ӵ���PC0�ܽ�
#define MAC5 PCout(5)  	//D2ָʾ�����ӵ���PC1�ܽ�
#define MAC7 PCout(7)	//D3ָʾ�����ӵ���PC2�ܽ�





void machine_stop(void);//ֹͣ
void machine_fast_stop(void);//����ֹͣ
void machine_back(void);//��ʱ��ת
void machine_goto(void);//˳ʱ��ת



void machine1_stop(void);//ֹͣ
void machine1_fast_stop(void);//����ֹͣ
void machine1_back(void);//��ʱ��ת
void machine1_goto(void);//˳ʱ��ת

void MAC_Init(void);


#endif
