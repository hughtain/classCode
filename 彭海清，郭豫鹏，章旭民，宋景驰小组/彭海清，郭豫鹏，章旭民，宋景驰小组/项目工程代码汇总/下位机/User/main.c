//#define fan_GLOBALS

#include "system.h"
#include "usart.h"
#include "led.h"
#include "machine.h"
#include "key.h"
#include "low.h"
#include "pwm.h"
#include "time.h"
#include "mq2.h"
#include "lsen.h"
#include "dht11.h"
#include "tftlcd.h"
#include "UnItdelay.h"
#include "HC-SR501.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "includes.h"
#include "adc_temp.h"
#include "SysTick.h"
#include "esp8266_drive.h"
#include "sta_tcpclent_test.h"






float temh,teml,humh,huml,brih,bril;//阀值全局变量
//float model;//系统运作模式全局变量

//extern  u16 ADC_ConvertedValue1;

//任务优先级
#define START_TASK_PRIO		3
//任务堆栈大小	
#define START_STK_SIZE 		1024
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);


//led任务优先级
#define LED1_TASK_PRIO		4
//任务堆栈大小	
#define LED1_STK_SIZE 		1024
//任务控制块
OS_TCB Led1TaskTCB;
//任务堆栈	
CPU_STK LED1_TASK_STK[LED1_STK_SIZE];
void led1_task(void *p_arg);


//stm32内部温度任务优先级
#define QUEUEWR_TASK_PRIO		6
//任务堆栈大小	
#define QUEUEWR_STK_SIZE 		128
//任务控制块
OS_TCB QUEUEWRTaskTCB;
//任务堆栈	
CPU_STK QUEUEWR_TASK_STK[QUEUEWR_STK_SIZE];
void QueueWr_task(void *p_arg);


//wifi任务优先级
#define QUEUERD_TASK_PRIO		7
//任务堆栈大小	
#define QUEUERD_STK_SIZE 		128
//任务控制块
OS_TCB QUEUERDTaskTCB;
//任务堆栈	
CPU_STK QUEUERD_TASK_STK[QUEUERD_STK_SIZE];
void QueueRd_task(void *p_arg);


//继电器任务优先级
#define LOW_TASK_PRIO		8
//任务堆栈大小	
#define LOW_STK_SIZE 		128
//任务控制块
OS_TCB LOWTaskTCB;
//任务堆栈	
CPU_STK LOW_TASK_STK[LOW_STK_SIZE];
void LOW_task(void *p_arg);


//温湿度任务
#define DHT_TASK_PRIO		9
//任务堆栈大小	
#define DHT_STK_SIZE 		128
//任务控制块
OS_TCB DHTTaskTCB;
//任务堆栈	
CPU_STK DHT_TASK_STK[DHT_STK_SIZE];
void DHT_task(void *p_arg);

//人体感应任务
#define HC_TASK_PRIO		10
//任务堆栈大小	
#define HC_STK_SIZE 		128
//任务控制块
OS_TCB HCTaskTCB;
//任务堆栈	
CPU_STK HC_TASK_STK[HC_STK_SIZE];
void HC_task(void *p_arg);


//pwm任务
#define PWM_TASK_PRIO		11
//任务堆栈大小	
#define PWM_STK_SIZE 		128
//任务控制块
OS_TCB PWMTaskTCB;
//任务堆栈	
CPU_STK PWM_TASK_STK[PWM_STK_SIZE];
void PWM_task(void *p_arg);


//亮度任务
#define LSEN_TASK_PRIO		12
//任务堆栈大小	
#define LSEN_STK_SIZE 		128
//任务控制块
OS_TCB LSENTaskTCB;
//任务堆栈	
CPU_STK LSEN_TASK_STK[LSEN_STK_SIZE];
void LSEN_task(void *p_arg);

//MQ135任务
#define MQ_TASK_PRIO		13
//任务堆栈大小	
#define MQ_STK_SIZE 		128
//任务控制块
OS_TCB MQTaskTCB;
//任务堆栈	
CPU_STK MQ_TASK_STK[MQ_STK_SIZE];
void MQ_task(void *p_arg);


//MQ135任务
#define TFT_TASK_PRIO		14
//任务堆栈大小	
#define TFT_STK_SIZE 		128
//任务控制块
OS_TCB TFTTaskTCB;
//任务堆栈	
CPU_STK TFT_TASK_STK[TFT_STK_SIZE];
void TFT_task(void *p_arg);

//窗口任务
#define WIN_TASK_PRIO		15
//任务堆栈大小	
#define WIN_STK_SIZE 		128
//任务控制块
OS_TCB WINTaskTCB;
//任务堆栈	
CPU_STK WIN_TASK_STK[WIN_STK_SIZE];
void WIN_task(void *p_arg);



//湿度控制任务
#define HUM_TASK_PRIO		16
//任务堆栈大小	
#define HUM_STK_SIZE 		128
//任务控制块
OS_TCB HUMTaskTCB;
//任务堆栈	
CPU_STK HUM_TASK_STK[HUM_STK_SIZE];
void HUM_task(void *p_arg);

OS_Q HUM_queue;//温度消息队列
OS_Q WIN_queue;//窗口消息对列
OS_Q My_queue;//温度消息队列
OS_Q Hum_queue;//湿度消息队列
OS_Q Lsen_queue;//亮度消息队列
OS_Q Low_queue;//继电器消息队列
OS_Q Flag_queue;//控制变量消息队列
OS_Q Lsencontrol_queue;//亮度消息队列

int main()
{  	
	OS_ERR err;
	Systick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	

	
	//adc_init();
	

	HC_Init();	
	Lsen_Init();
  TIM3_CH1_PWM_Init(500,72-1);
	
	//LED_Init();
	MAC_Init();
	KEY_Init();
		//LCD初始化
	relay_init();


  ADC_Temp_Init();
	
	USART1_Init(9600);
	
		//TFTLCD_Init();	
	
		
		
	
  ESP8266_STA_TCPClient_Test_Init();
		
	
	//TIM3_Init(10-1,72-1);
	
	OSInit(&err);		//初始化UCOSIII
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值 
	OSStart(&err);  //开启UCOSIII
	while(1);
}

//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	
	CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
	
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
	
	cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
    cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        /* Determine nbr SysTick increments                     */
    OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */

    Mem_Init();       
	
	
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//进入临界区
	
	//创建温度消息队列 My_queue
    OSQCreate((OS_Q *)&My_queue,    
               (CPU_CHAR    *)"My_queue",    
			   (OS_MSG_QTY ) 10,    //最多存放消息的数目
               (OS_ERR      *)&err);         //错误类型
		//创建湿度消息队列 Hum_queue
    OSQCreate((OS_Q *)&Hum_queue,    
               (CPU_CHAR    *)"Hum_queue",    
			   (OS_MSG_QTY ) 10,    //最多存放消息的数目
               (OS_ERR      *)&err);         //错误类型
			//创建亮度消息队列
    OSQCreate((OS_Q *)&Lsen_queue,    
               (CPU_CHAR    *)"Lsen_queue",    
			   (OS_MSG_QTY ) 10,    //最多存放消息的数目
               (OS_ERR      *)&err);         //错误类型
		//创建继电器消息队列 My_queue
    OSQCreate((OS_Q *)&Low_queue,    
               (CPU_CHAR    *)"Low_queue",    
			   (OS_MSG_QTY ) 10,    //最多存放消息的数目
               (OS_ERR      *)&err); 
		
			//创建控制变量消息队列 My_queue
    OSQCreate((OS_Q *)&Flag_queue,    
               (CPU_CHAR    *)"Flag_queue",    
			   (OS_MSG_QTY ) 10,    //最多存放消息的数目
               (OS_ERR      *)&err); 
		OSQCreate((OS_Q *)&Lsencontrol_queue,    
               (CPU_CHAR    *)"Lsencontrol_queue",    
			   (OS_MSG_QTY ) 10,    //最多存放消息的数目
               (OS_ERR      *)&err); 
		
			OSQCreate((OS_Q *)&WIN_queue,    
               (CPU_CHAR    *)"WIN_queue",    
			   (OS_MSG_QTY ) 10,    //最多存放消息的数目
               (OS_ERR      *)&err); 
			
			OSQCreate((OS_Q *)&HUM_queue,    
               (CPU_CHAR    *)"HUM_queue",    
			   (OS_MSG_QTY ) 10,    //最多存放消息的数目
               (OS_ERR      *)&err); 
		
		
	
	//创建LED1任务
	OSTaskCreate((OS_TCB 	* )&Led1TaskTCB,		
				 (CPU_CHAR	* )"led1 task", 		
                 (OS_TASK_PTR )led1_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LED1_TASK_PRIO,     
                 (CPU_STK   * )&LED1_TASK_STK[0],	
                 (CPU_STK_SIZE)LED1_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED1_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);
				 
	//创建stm32内部温度任务
	OSTaskCreate((OS_TCB 	* )&QUEUEWRTaskTCB,		
				 (CPU_CHAR	* )"QueueWr_task", 		
                 (OS_TASK_PTR )QueueWr_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )QUEUEWR_TASK_PRIO,     
                 (CPU_STK   * )&QUEUEWR_TASK_STK[0],	
                 (CPU_STK_SIZE)QUEUEWR_STK_SIZE/10,	
                 (CPU_STK_SIZE)QUEUEWR_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);
		
	//创建wifi任务
	OSTaskCreate((OS_TCB 	* )&QUEUERDTaskTCB,		
				 (CPU_CHAR	* )"QueueRd_task", 		
                 (OS_TASK_PTR )QueueRd_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )QUEUERD_TASK_PRIO,     
                 (CPU_STK   * )&QUEUERD_TASK_STK[0],	
                 (CPU_STK_SIZE)QUEUERD_STK_SIZE/10,	
                 (CPU_STK_SIZE)QUEUERD_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);
								 
						 
				 
		//创建继电器任务
	OSTaskCreate((OS_TCB 	* )&LOWTaskTCB,		
				 (CPU_CHAR	* )"LOW_task", 		
                 (OS_TASK_PTR )LOW_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LOW_TASK_PRIO,     
                 (CPU_STK   * )&LOW_TASK_STK[0],	
                 (CPU_STK_SIZE)LOW_STK_SIZE/10,	
                 (CPU_STK_SIZE)LOW_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);
								 
	
								 
			//创建温湿度任务
	OSTaskCreate((OS_TCB 	* )&DHTTaskTCB,		
				 (CPU_CHAR	* )"DHT_task", 		
                 (OS_TASK_PTR )DHT_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )DHT_TASK_PRIO,     
                 (CPU_STK   * )&DHT_TASK_STK[0],	
                 (CPU_STK_SIZE)DHT_STK_SIZE/10,	
                 (CPU_STK_SIZE)DHT_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);
								 
								 
	//人体感应
  OSTaskCreate((OS_TCB 	* )&PWMTaskTCB,		
				 (CPU_CHAR	* )"PWM_task", 		
                 (OS_TASK_PTR )PWM_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )PWM_TASK_PRIO,     
                 (CPU_STK   * )&PWM_TASK_STK[0],	
                 (CPU_STK_SIZE)PWM_STK_SIZE/10,	
                 (CPU_STK_SIZE)PWM_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
								 
//PWM控制任务
    OSTaskCreate((OS_TCB 	* )&HCTaskTCB,		
				 (CPU_CHAR	* )"HC_task", 		
                 (OS_TASK_PTR )HC_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )HC_TASK_PRIO,     
                 (CPU_STK   * )&HC_TASK_STK[0],	
                 (CPU_STK_SIZE)HC_STK_SIZE/10,	
                 (CPU_STK_SIZE)HC_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
//光敏控制任务
    OSTaskCreate((OS_TCB 	* )&LSENTaskTCB,		
				 (CPU_CHAR	* )"LSEN_task", 		
                 (OS_TASK_PTR )LSEN_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LSEN_TASK_PRIO,     
                 (CPU_STK   * )&LSEN_TASK_STK[0],	
                 (CPU_STK_SIZE)LSEN_STK_SIZE/10,	
                 (CPU_STK_SIZE)LSEN_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	

 //MQ控制任务
    OSTaskCreate((OS_TCB 	* )&MQTaskTCB,		
				         (CPU_CHAR	* )"MQ_task", 		
                 (OS_TASK_PTR )MQ_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )MQ_TASK_PRIO,     
                 (CPU_STK   * )&MQ_TASK_STK[0],	
                 (CPU_STK_SIZE)MQ_STK_SIZE/10,	
                 (CPU_STK_SIZE)MQ_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
			
//LCD控制任务
    OSTaskCreate((OS_TCB 	* )&TFTTaskTCB,		
				         (CPU_CHAR	* )"TFT_task", 		
                 (OS_TASK_PTR )TFT_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )TFT_TASK_PRIO,     
                 (CPU_STK   * )&TFT_TASK_STK[0],	
                 (CPU_STK_SIZE)TFT_STK_SIZE/10,	
                 (CPU_STK_SIZE)TFT_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
//窗口控制任务
    OSTaskCreate((OS_TCB 	* )&WINTaskTCB,		
				         (CPU_CHAR	* )"WIN_task", 		
                 (OS_TASK_PTR )WIN_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )WIN_TASK_PRIO,     
                 (CPU_STK   * )&WIN_TASK_STK[0],	
                 (CPU_STK_SIZE)WIN_STK_SIZE/10,	
                 (CPU_STK_SIZE)WIN_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
		
//湿度控制任务
    OSTaskCreate((OS_TCB 	* )&HUMTaskTCB,		
				         (CPU_CHAR	* )"HUM_task", 		
                 (OS_TASK_PTR )HUM_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )HUM_TASK_PRIO,     
                 (CPU_STK   * )&HUM_TASK_STK[0],	
                 (CPU_STK_SIZE)HUM_STK_SIZE/10,	
                 (CPU_STK_SIZE)HUM_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
								 

	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务			 
	OS_CRITICAL_EXIT();	//退出临界区
}
//12湿度
void HUM_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	char *pmsg;
	int flag=0,flag1=0;
	OS_MSG_SIZE msg_size;
	p_arg = p_arg;
	
	while(1)
	{
			  
   pmsg=OSQPend(&HUM_queue,0,OS_OPT_PEND_NON_BLOCKING,&msg_size,0,&err);
      
		if(pmsg=="ON")
		 {
			 
			 
			 machine1_goto();
			 
			
			 
		 }
		 if(pmsg=="OFF")
 		 {
			 
				 
			 machine1_back();
			
			 }
		 if(pmsg=="STOP")
 		 {
			 
				 
			 machine1_fast_stop();
			
			 }
		 			 
		
		 
		OSTimeDlyHMSM(0,0,0,1,OS_OPT_TIME_DLY,&err); //延时200ms

	}
	
	
}



//11窗口任务
void WIN_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	char *pmsg;
	int flag=0,flag1=0;
	OS_MSG_SIZE msg_size;
	p_arg = p_arg;
	
	while(1)
	{
			  
   pmsg=OSQPend(&WIN_queue,0,OS_OPT_PEND_NON_BLOCKING,&msg_size,0,&err);
       OSSchedLock(&err);
		if(pmsg=="ON")
		 {
			 if(flag==0)
			 {
				 flag=1;
				 flag1=0;
			 
			 machine_goto();
			 unitdelay_ms(500);
			 machine_fast_stop();
			 }
			 
		 }
		 if(pmsg=="OFF")
 		 {
			 if(flag1==0)
			 {
				 flag1=1;
				 flag=0;
				 
			 machine_back();
			 unitdelay_ms(500);
			 machine_fast_stop();
			 }
		 }			 
		OSSchedUnlock(&err);
		 pmsg=NULL;
		OSTimeDlyHMSM(0,0,0,1,OS_OPT_TIME_DLY,&err); //延时200ms

	}
	
	
}

//1tftlcd任务
void TFT_task(void *p_arg)
{
	
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;
	
//	
//	    FRONT_COLOR=BLACK;
//			LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,12,"Hello World!");
//			LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"Hello World!");
//			LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,24,"Hello World!");
//			LCD_ShowFontHZ(10, 80,"普中科技");
//			LCD_ShowString(10,120,tftlcd_data.width,tftlcd_data.height,24,"www.prechin.cn");
	
	while(1)
	{
			
		     
				OSTimeDlyHMSM(0,0,0,1,OS_OPT_TIME_DLY,&err); //延时200ms

	}
	
	
}


//2MQ任务
void MQ_task(void *p_arg)
{
		OS_ERR err;
	  float ADC_ConvertedValueLocal;  
   float airquailty,airquailty1;
	  u16 ADC_ConvertedValue1=99;
	  CPU_SR_ALLOC();
	   p_arg = p_arg;
	
	   	
	   while(1)
		 {
			     
		
//            ADC_ConvertedValueLocal =(float) ADC_ConvertedValue1/4096*3.3;  
//		        airquailty=((float)((float)ADC_ConvertedValue1*3300)/4095);
//		        airquailty1=airquailty/1000;
//			      OS_CRITICAL_ENTER();	//进入临界区
//            printf("The current AD value =0x%04X\n",ADC_ConvertedValue1);  
//            printf("The current AD value =%f V\n",ADC_ConvertedValueLocal);
//            printf("The  airquailty=%f \n",airquailty1);
//            OS_CRITICAL_EXIT();     //退出临界区			 
			 
			 			 OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_DLY,&err); //延时200ms

			 
		 }
	
	
}
//3LSEN任务函数
void LSEN_task(void *p_arg)
{
	OS_ERR err;
	OS_MSG_SIZE msg_size;
	char *pmsg;
	int model1;
	u8 adcx;
	 char str[30]={0};
    	CPU_SR_ALLOC();	
	 p_arg = p_arg;
	  
	  
	
	 while(1)
	 {
		   adcx=Lsens_Get_Val();
		  OS_CRITICAL_ENTER();	//进入临界区
		    //printf("%d\n",adcx);
		    sprintf(str,"guadu 11:00 %d\r\n",adcx);
	      OSQPost(&Lsen_queue,
				str,
				sizeof(str),
				OS_OPT_POST_LIFO| OS_OPT_POST_ALL,
				&err);
		
		   OS_CRITICAL_EXIT();     //退出临界区		
				
		 pmsg=OSQPend(&Flag_queue,0,OS_OPT_PEND_NON_BLOCKING,&msg_size,0,&err);
    
				 if(err==OS_ERR_NONE)  //消息接收成功
	 {
		 if(strncmp(pmsg,"autom",5)==0)
			{
			
				model1=1;
	
		  }else
			{
				
					model1=0;
			}
	 }
	
				if(model1==1)
	 {
			 if(adcx<bril||adcx>brih)
			 { 
				   
				 	OSQPost (&Lsencontrol_queue,           //目标任务的控制块
					(void        *)"openLsen",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "openLsen" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err);  
				 
			 }else
			 { 
				  
				 	OSQPost (&Lsencontrol_queue,           //目标任务的控制块
					(void        *)"closeLsen",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "closeLsen" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err);  
				 
			 }
			 
		 }
     				
			 OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_DLY,&err); //延时200ms

		 
		 
		 
		 
	 }
	
	
}	


//4PWM任务函数
void PWM_task(void *p_arg)
{
	OS_ERR err;
	int model1;
	OS_MSG_SIZE msg_size;
	char *pmsg;
	u16 i=0;  
	u8 fx=0;
	 p_arg = p_arg;
	while(1)
	{
		
		pmsg=OSQPend(&Lsencontrol_queue,0,OS_OPT_PEND_NON_BLOCKING,&msg_size,0,&err);
    if(err==OS_ERR_NONE)  //消息接收成功
	 {
		 if(strncmp(pmsg,"openLsen",8)==0)
			{
			
				model1=1;
	
		  }else
			{
				
					model1=0;
			}
	 }
			
		if(model1==1)
	 {		
		 
		 if(fx==0)
		{
			i++;
			if(i==500)
			{
				fx=1;
			}
		}
		else
		{
			i--;
			if(i==0)
			{
				fx=0;
			}
		}
				TIM_SetCompare1(TIM3,i);  //i值最大可以取499，因为ARR最大值是499.
	}
		else
		
	{
			  
			TIM_SetCompare1(TIM3,i);  //i值最大可以取499，因为ARR最大值是499.
		
			
	}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_DLY,&err); //延时200ms
   }
	
	
	
}

//5人体感应任务函数
void HC_task(void *p_arg)
{
	OS_ERR err;
	int i;
	 p_arg = p_arg;
	
	while(1)
	{
		

		 OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_DLY,&err); //延时200ms
					
		}
    
	}
	
	


//6数据接收处理任务函数
void led1_task(void *p_arg)
{
	OS_ERR err;
	char Data_RX_BUF1[5];
	char Data_RX_BUF2[5];
	char Data_RX_BUF3[5];
	char Data_RX_BUF4[5];
	char Data_RX_BUF5[5];
	char Data_RX_BUF6[5];
	char Data_RX_BUF7[5];
	char *p;
	float tem;
	
	int t=0,h=0,g=0;
	char* pEnd;
        CPU_SR_ALLOC();
  p_arg = p_arg;
	
	
	
	
	
	while(1)
	{
	  //清空数组   
		 memset(Data_RX_BUF1,0,5);
		  memset(Data_RX_BUF2,0,5);
			 memset(Data_RX_BUF3,0,5);
			  memset(Data_RX_BUF4,0,5);
				 memset(Data_RX_BUF5,0,5);
				  memset(Data_RX_BUF6,0,5);
					 memset(Data_RX_BUF7,0,5);
		//截取字符串数组
		 reqorder(ESP8266_Fram_Record_Struct .Data_RX_BUF,Data_RX_BUF1,0);
	/******上位机自动和手动按钮信息处理*******/	
		 OS_CRITICAL_ENTER();
      if(strncmp(Data_RX_BUF1,"manmm",5)==0)
			{
				 
				OSQPost(&Flag_queue,
				"manmm",
				sizeof("manmm"),
				OS_OPT_POST_FIFO | OS_OPT_POST_ALL,
				&err);
		}
		
		 if(strncmp(Data_RX_BUF1,"autom",5)==0)
		 {   
  		    
        OSQPost(&Flag_queue,
				"autom",
				sizeof("autom"),
				OS_OPT_POST_FIFO | OS_OPT_POST_ALL,
				&err);
				//temperature
        reqorder(ESP8266_Fram_Record_Struct .Data_RX_BUF,Data_RX_BUF2,1);//按分隔符取温度值
			  temh = strtof (Data_RX_BUF2, &pEnd);//字符串转为浮点型

			  reqorder(ESP8266_Fram_Record_Struct .Data_RX_BUF,Data_RX_BUF3,2);
			   teml = strtof (Data_RX_BUF3, &pEnd);
//  			 printf("%f\n",teml);
//			   printf("%s\n", Data_RX_BUF3);
			 
			 //huminuss
			  reqorder(ESP8266_Fram_Record_Struct .Data_RX_BUF,Data_RX_BUF4,3);
			  humh = strtof (Data_RX_BUF4, &pEnd);
//  			printf("%f\n",humh);
//			 
//			  printf("%s\n", Data_RX_BUF4);
			  reqorder(ESP8266_Fram_Record_Struct .Data_RX_BUF,Data_RX_BUF5,4);
    			  huml = strtof (Data_RX_BUF5, &pEnd);
//  			printf("%f\n",huml);
//			  printf("%s\n", Data_RX_BUF5);
			 
			 //brightness
			  reqorder(ESP8266_Fram_Record_Struct .Data_RX_BUF,Data_RX_BUF6,5);
			  brih = strtof (Data_RX_BUF6, &pEnd);
//  			printf("%f\n",brih);
//				
//				printf("%s\n", Data_RX_BUF6);
			  reqorder(ESP8266_Fram_Record_Struct .Data_RX_BUF,Data_RX_BUF7,6);
			  bril = strtof (Data_RX_BUF7, &pEnd);
//  			printf("%f\n",bril);
//				printf("%s\n", Data_RX_BUF7);
			 
		 }
		 /******上位机自动和手动按钮信息处理*******/
		 
		 
		 /*****************上位机按键处理************/
		 if(strncmp(Data_RX_BUF1,"openf",5)==0)
		{ OSQPost(&Low_queue,
				"ON",
				sizeof("ON"),
				OS_OPT_POST_FIFO | OS_OPT_POST_ALL,
				&err);
		}else
		 if(strncmp(Data_RX_BUF1,"closf",5)==0)
		{
			OSQPost(&Low_queue,
				"OFF",
				sizeof("OFF"),
				OS_OPT_POST_FIFO | OS_OPT_POST_ALL,
				&err);
		}else
		 if(strncmp(Data_RX_BUF1,"openLsen",8)==0)
		{   
			
			
			OSQPost (&Lsencontrol_queue,           //目标任务的控制块
					(void        *)"openLsen",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "openLsen" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err);  
		}else
		if(strncmp(Data_RX_BUF1,"closeLsen",9)==0)
		{
			
			OSQPost (&Lsencontrol_queue,           //目标任务的控制块
					(void        *)"closeLsen",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "closeLsen" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err); 
           					
		}
		else
		 if(strncmp(Data_RX_BUF1,"openwin",7)==0)
		{   
			
			
			OSQPost (&WIN_queue,           //目标任务的控制块
					(void        *)"ON",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "ON" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err);  
		}else
		if(strncmp(Data_RX_BUF1,"closewin",8)==0)
		{
			
			OSQPost (&WIN_queue,           //目标任务的控制块
					(void        *)"OFF",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "OFF" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err); 
           		
		}
		else
		
		 if(strncmp(Data_RX_BUF1,"openhum",7)==0)
		{   
			printf("%s\n",Data_RX_BUF1);
			
			OSQPost (&HUM_queue,           //目标任务的控制块
					(void        *)"ON",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "ON" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err);  
		}else
		if(strncmp(Data_RX_BUF1,"closehum",8)==0)
		{
				printf("%s\n",Data_RX_BUF1);
			OSQPost (&HUM_queue,           //目标任务的控制块
					(void        *)"OFF",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "OFF" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err); 
           		
		}
		else
		if(strncmp(Data_RX_BUF1,"humstop",7)==0)
		{
				printf("%s\n",Data_RX_BUF1);
			OSQPost (&HUM_queue,           //目标任务的控制块
					(void        *)"STOP",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "STOP" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err); 
           		
		}
		
		 OS_CRITICAL_EXIT();
	   /*****************上位机按键处理************/
		   
		  
       ESP8266_Fram_Record_Struct .InfBit .FramLength = 0;	
	     ESP8266_Fram_Record_Struct.Data_RX_BUF[ESP8266_Fram_Record_Struct.InfBit.FramLength ] = '\0';
   
			 OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_DLY,&err); //延时200ms
	}
}
//7温湿度任务函数
void DHT_task(void *p_arg)
{
	  OS_ERR err;
	char *pmsg;
	int model1;
	OS_MSG_SIZE msg_size;
	p_arg = p_arg;
	
	while(1)
	{
		
		    u8 buffer[5];
        double temp;
		     double hum;
        char str1[30]={0};
		    char str[30]={0};
		    OSSchedLock(&err);
        if (dht11_read_data(buffer) == 0)
					
        {
            temp = buffer[2] + buffer[3] / 10.0;
					   hum = buffer[0] + buffer[1] / 10.0;
        }
				OSSchedUnlock(&err);
				/*******发送WIFI************/
					sprintf(str1,"shidu 11:00 %.2f\r\n",hum);
				sprintf(str,"wendu 11:00 %.2f\r\n",temp);
	      OSQPost(&My_queue,
				str,
				sizeof(str),
				OS_OPT_POST_LIFO| OS_OPT_POST_ALL,
				&err);
				 OSQPost(&Hum_queue,
				str1,
				sizeof(str1),
				OS_OPT_POST_LIFO| OS_OPT_POST_ALL,
				&err);
					/*******发送WIFI************/
				
				 	/*******数据处理************/
				
   pmsg=OSQPend(&Flag_queue,0,OS_OPT_PEND_NON_BLOCKING,&msg_size,0,&err);
    
			 if(err==OS_ERR_NONE)  //消息接收成功
	 {
		 if(strncmp(pmsg,"autom",5)==0)
			{
			
				model1=1;
	
		  }else
			{
				
					model1=0;
			}
	 }	
				
				
				
		if(model1==1)
		
		 {
			 
			 
			 if(hum>humh)
			 {
				 OSQPost (&HUM_queue,           //目标任务的控制块
					(void        *)"ON",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "ON" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err);  
				 
				}
			   else
					 if(hum<huml)
					 {
						 
						 	OSQPost (&HUM_queue,           //目标任务的控制块
					(void        *)"OFF",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "OFF" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err); 
						 
						 
					 }else
					 {
						 	 
						 	OSQPost (&HUM_queue,           //目标任务的控制块
					(void        *)"STOP",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "STOP" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err); 
						 
						 
						 
					 }
			 if(temp>temh)
			 { 
				   
				 	OSQPost (&Low_queue,           //目标任务的控制块
					(void        *)"ON",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "ON" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err);  
					
						OSQPost (&WIN_queue,           //目标任务的控制块
					(void        *)"ON",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "ON" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err);  
				 
			 }else
			 if(temp<=temh)
			 { 
				  
				 	OSQPost (&Low_queue,           //目标任务的控制块
					(void        *)"OFF",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "OFF" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err); 
   

          OSQPost (&WIN_queue,           //目标任务的控制块
					(void        *)"OFF",             //消息内容
					(OS_MSG_SIZE  )sizeof ( "OFF" ),  //消息长度
					(OS_OPT       )OS_OPT_POST_FIFO,        //发布到任务消息队列的入口端
					(OS_ERR      *)&err);  					
				 
			 }
			 
		 }
				  /*******数据处理************/
				
			

		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY,&err); //延时200ms
		
		
	}
	
	
}
//8继电器任务函数
void LOW_task(void *p_arg)
{
	OS_ERR err;
	char *pmsg;
	OS_MSG_SIZE msg_size;
	p_arg = p_arg;
	while(1)
	{
		pmsg=OSQPend(&Low_queue,0,OS_OPT_PEND_NON_BLOCKING,&msg_size,0,&err);
    
		
		if(pmsg=="ON")
		{
			relay_off();
			
		}else if(pmsg=="OFF")
		{
			relay_on();
			
		}
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_DLY,&err);
		
	}
	
	
	
}

//9湿度任务函数
void QueueWr_task(void *p_arg)
{
	OS_ERR err;
	
	
	p_arg = p_arg;
				
	while(1)
	{
//		    u8 buffer[5];
//        double hum;
//        char str1[30]={0};
//		    OSSchedLock(&err);
//        if (dht11_read_data(buffer) == 0)
//					
//        {
//            hum = buffer[0] + buffer[1] / 10.0;
//         
//        }
//				OSSchedUnlock(&err);
//				sprintf(str1,"shidu 11:00 %.2f\r\n",hum);
//	  OSTaskQPost(&QUEUERDTaskTCB,
//				str1,
//				sizeof(str1),
//				OS_OPT_POST_FIFO,
//				&err);
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY,&err); //延时200ms
		
//		t=(float)temp/100;
//		if(t>33.41)
//		{
//			OSQPost(&Low_queue,
//				"ON",
//				sizeof("ON"),
//				OS_OPT_POST_FIFO | OS_OPT_POST_ALL,
//				&err);
//		}else
//		{
//			OSQPost(&Low_queue,
//				"OFF",
//				sizeof("OFF"),
//				OS_OPT_POST_FIFO | OS_OPT_POST_ALL,
//				&err);
//		
//		}
//	  sprintf(str,"wendu 11:00 %.2f\r\n",(float)temp/100);
//		OSQPost(&My_queue,
//				str,
//				sizeof(str),
//				OS_OPT_POST_FIFO | OS_OPT_POST_ALL,
//				&err);
		
		}
}


//10WIFI发送任务函数
void QueueRd_task(void *p_arg)
{
	OS_ERR err;
	OS_MSG_SIZE msg_size;
	char *pmsg;
		char *pmsg1;
	char *pmsg2="guadu 11:00 89.00";
	CPU_SR_ALLOC();
	p_arg = p_arg;
				
	while(1)
	{

		pmsg=OSQPend(&My_queue,0,OS_OPT_PEND_NON_BLOCKING,&msg_size,0,&err);
		pmsg1=OSQPend(&Hum_queue,0,OS_OPT_PEND_NON_BLOCKING,&msg_size,0,&err);
    pmsg2=OSQPend(&Lsen_queue,0,OS_OPT_PEND_NON_BLOCKING,&msg_size,0,&err);

		
		
		if(err==OS_ERR_NONE)  //消息接收成功
		{
           OSSchedLock(&err);
			  ESP8266_STA_TCPClient_Test_Send(pmsg);
			  unitdelay_ms(100);
				ESP8266_STA_TCPClient_Test_Send(pmsg1);
			  unitdelay_ms(100);
				ESP8266_STA_TCPClient_Test_Send(pmsg2);
			     OSSchedUnlock(&err);
		}
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY,&err); 
	}
}




