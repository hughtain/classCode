#include "HC-SR501.h"


void HC_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	
	RCC_APB2PeriphClockCmd(HC_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=HC_PIN;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;	 //设置褪淙胂吕Ｊ侥Ｊ�
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(HC_PORT,&GPIO_InitStructure); 	   /* 初始化GPIO */
	
	
}
