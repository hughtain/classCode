#include "time.h"
#include "led.h"
#include "includes.h"

/*******************************************************************************
* 函 数 名         : TIM4_Init
* 函数功能		   : TIM4初始化函数
* 输    入         : per:重装载值
					 psc:分频系数
* 输    出         : 无
*******************************************************************************/
u32 DelayCnt;


void TIM3_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM4时钟
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //分频系数
	//TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_Cmd(TIM3,DISABLE); //使能定时器	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	
	
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //开启定时器中断	
}

/*******************************************************************************
* 函 数 名         : TIM4_IRQHandler
* 函数功能		   : TIM4中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void TIM3_IRQHandler(void)
{
	OSIntEnter();
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update))
	{
	   if(DelayCnt>0)
		 {
			 
			 DelayCnt--;
			 
		 }
		 else
		 {
			 DelayCnt=0;
		 }
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);	
	
	OSIntExit();
}
void Delay_10us(u32 us)
{
	OS_ERR err;
	
	OSSchedLock(&err);
	DelayCnt=us;
	TIM_Cmd(TIM3,ENABLE); 
	
	while(DelayCnt);
	TIM_Cmd(TIM3,DISABLE); 
	OSSchedUnlock(&err);
	
	
}


