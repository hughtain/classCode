#include "beep.h"

BEEP_INFO beepInfo = {0};


/*
************************************************************
*	
*	函数功能：	蜂鸣器初始化

************************************************************
*/
void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);				

	//初始化完成后，关闭蜂鸣器
	Beep_Set(BEEP_OFF);
}


/*
************************************************************
*	函数名称：	Beep_Set
*	函数功能：	蜂鸣器控制
************************************************************
*/
void Beep_Set(_Bool status)
{
	//如果status等于BEEP_ON，则返回Bit_SET，否则返回Bit_RESET
	GPIO_WriteBit(GPIOA, GPIO_Pin_8, status == BEEP_ON ? Bit_SET : Bit_RESET);
	
	beepInfo.beep_status = status;
}
