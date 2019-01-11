#include "machine.h"

/*******************************************************************************
* 函 数 名         : LED_Init
* 函数功能		   : LED初始化函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void MAC_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	
	RCC_APB2PeriphClockCmd(MAC_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=MAC_PIN;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(MAC_PORT,&GPIO_InitStructure); 	   /* 初始化GPIO */
	
	//GPIO_SetBits(LED_PORT,LED_PIN);   //将LED端口拉高，熄灭所有LED
}

void machine_goto(void)//顺时针转
{
	  MAC1=1;
	  MAC2=0;
	  MAC3=1;
}	



void machine_back(void)//逆时针转
{
	  MAC1=0;
	  MAC2=1;
	  MAC3=1;
}	

void machine_fast_stop(void)//快速停止
{
	  MAC1=1;
	  MAC2=1;
	  MAC3=1;
}	

void machine_stop(void)//停止
{
	  MAC1=0;
	  MAC2=0;
	  MAC3=0;
}	


void machine1_goto(void)//顺时针转
{
	  MAC0=1;
	  MAC5=0;
	  MAC7=1;
}	


void machine1_back(void)//逆时针转
{
	  MAC0=0;
	  MAC5=1;
	  MAC7=1;
}	

void machine1_fast_stop(void)//快速停止
{
	  MAC0=1;
	  MAC5=1;
	  MAC7=1;
}	

void machine1_stop(void)//停止
{
	  MAC0=0;
	  MAC5=0;
	  MAC7=0;
}	




