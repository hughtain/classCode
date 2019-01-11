
  
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./systick/bsp_SysTick.h"

//网络协议层
#include "onenet.h"
#include "EdpKit.h"
//网络设备
#include "esp8266.h"
//硬件驱动
#include "hwtimer.h"
#include "warning.h"
#include "dht11.h"
#include "beep.h"
#include "iic.h"
#include "soil_H.h"
#include "water.h"
#include "light_moto.h"
#include "BH1750.h"



//rtos
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "delay.h"






//C库
#include <string.h>
#include <stdio.h>

enum net_status{Conneted=0,Closed,Lost,Error};
enum net_status Net_status;
extern _Bool water_flag;
unsigned int Task_Delay[NumOfTask]; 
float frame_count = 0;
data_Stream data_value;



///////////////////
TaskHandle_t CheckSensorTask_Handler;
TaskHandle_t NetTask_Handler;
TaskHandle_t ReceiveCmdTask_Handler;
TaskHandle_t IWDG_Task_Handler;


//////////////////任务栈分配
#define CheckSensor_Stack 384
#define Net_Task_Stack 1024//500+
#define ReceiveCmd_Stack 256//54
#define IWDG_TASK_Stack		64

/////////////////优先级分配
#define CheckSensor_Priority 2
#define Net_Task_Prioruty 4
#define ReceiveCMd_Priority 5



void NET_Event_CallBack(NET_EVENT net_event);


///个钟硬件初始化
void Hardware_Init()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//中断控制器分组设置
  USART_Config();
	DHT11_Init();									//温湿度传感器初始化
  Usart2_Init(115200);          //wifi串口初始化
  ESP8266_Init();
	ADC1_Init();
	Water_Gpio_config();              
	Shelter_GpioConfig();          
	i2c_CfgGpio();		/* 配置GPIO */
	BH1750_Start();                  
	printf("Hardware init ok\r\n");
}



/*
检查网络状态
*/
void Check_Network()
{

	Net_status=(enum net_status)Check_Wifi();
}

////采集数据任务////
static void CheckSensor_Task(void *pvParameters)
{
	while(1)
	{
		portENTER_CRITICAL();
		printf("checkSensor\n");
		Check_sensor(&data_value);
		portEXIT_CRITICAL();
		vTaskDelay(5000/portTICK_RATE_MS);
	}
	
}

////////// 网络状态检查//
static void  CheckNetWork_Task(void *pvParameters)
{				

	while(1)
	{
		Check_Network();	
		vTaskDelay(5000/portTICK_RATE_MS);
	}
	
}
//////////网络任务
static void Net_Task(void *pvParameters)
{
	unsigned short heart_count=0,data_count=0,check_count;
	printf("Net_Task");
	while(1)
	{

		if(Net_status==Conneted)
		{
		 if(++heart_count>=40)          
			{
			 heart_count=0;
			 NET_Event_CallBack(NET_EVENT_Send_HeartBeat);
			 }
			else if(++data_count>=20)   //10s发送一次数据
		 {
			data_count=0;
			NET_Event_CallBack(NET_EVENT_Send_Data);
			}
		
		else if(check_count>=30)      //15s检查一次网络
			{			
			NET_Event_CallBack(NET_EVENT_Check_Status);
			}
		

	
	}
			else
		{
	NET_Event_CallBack(NET_EVENT_Connect_Err);  //错误回调函数
		}
	vTaskDelay(500/portTICK_RATE_MS);
}
}



//处理下发的命令 400ms为周期
static void ReceiveCmdTask(void *pvParameters) 
{
	while(1)
	{			
		OneNET_CmdHandle();
		NET_Event_CallBack(NET_EVENT_Recv);
		vTaskDelay(400/portTICK_RATE_MS);
	}
}



//网络任务回调函数
void NET_Event_CallBack(NET_EVENT net_event)
{

	switch((unsigned char)net_event)
	{
		case NET_EVENT_Send_HeartBeat:
		printf("SendHeart");
		OneNet_Send_heart();
		break;
		case NET_EVENT_Water:
		////////////浇水
		break;
		case NET_EVENT_Send_Data:
		printf("SendData\n");
		OneNet_SendData(&data_value);
		break;
		case NET_EVENT_Recv:
		break;			
		case NET_EVENT_Connect_Err:
		printf("重连网络");
		reLink();
		break;
	}
}




/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void) 	
{		

	Hardware_Init();
	
  while(OneNet_DevLink())			//接入OneNET
	mDelay(500);
	Net_status=Conneted;//初始化为connected状态


  printf("start TASK");
  xTaskCreate((TaskFunction_t)ReceiveCmdTask,"ReceiveCmdTask",ReceiveCmd_Stack,"ReceiveCmdTask",ReceiveCMd_Priority,&ReceiveCmdTask_Handler);
  xTaskCreate((TaskFunction_t)CheckSensor_Task,"CheckSensorTask",CheckSensor_Stack,"CheckSensorTask",CheckSensor_Priority,&CheckSensorTask_Handler);
  xTaskCreate((TaskFunction_t)Net_Task,"Net_Task",Net_Task_Stack,"Net_Task",Net_Task_Prioruty,&NetTask_Handler);
  vTaskStartScheduler();
	}


/*********************************************END OF FILE**********************/

