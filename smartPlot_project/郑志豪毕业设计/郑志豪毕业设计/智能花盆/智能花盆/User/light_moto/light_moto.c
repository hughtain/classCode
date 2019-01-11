#include "light_moto.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "delay.h"


unsigned char  S_Rotation[4]={0x01,0x02,0x04,0x08};//正转表格
unsigned char  N_Rotation[4]={0x01,0x08,0x04,0x02};//正转表格
void  Shelter_GpioConfig()
{
	 GPIO_InitTypeDef GPIO_InitStructure; 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; //电机驱动ioP0.1.2.3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //输入
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
}  
//////////通过输出电平控制步进电机

void Shadding()
{
	unsigned  char i=128;//90度
	 while(i--)
	 {
     GPIO_SetBits(GPIOC,GPIO_Pin_0);//依次高电平输出	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_1);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_3);	
		 mDelay(50);		
		 
		 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
		 GPIO_SetBits(GPIOC,GPIO_Pin_1);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_3);	
		 
		
		 mDelay(50);		
		 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_1);	
		 GPIO_SetBits(GPIOC,GPIO_Pin_2);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_3);	
		 mDelay(50);		
		 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_1);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
		 GPIO_SetBits(GPIOC,GPIO_Pin_3);		
		 mDelay(50);
		 
 }

	
}



void  UnShadding()
{
	unsigned  char i=128;//90度
	 while(i--)
	 {
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0);//依次高电平输出	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_1);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_3);	
		 mDelay(50);		
		  GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_1);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
		 GPIO_SetBits(GPIOC,GPIO_Pin_3);	
		 
			
		 mDelay(50);		
		 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_1);	
		 GPIO_SetBits(GPIOC,GPIO_Pin_2);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_3);	
		 mDelay(50);		
		 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
		 GPIO_SetBits(GPIOC,GPIO_Pin_1);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
		 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
		 mDelay(50);
	 }
	
}

