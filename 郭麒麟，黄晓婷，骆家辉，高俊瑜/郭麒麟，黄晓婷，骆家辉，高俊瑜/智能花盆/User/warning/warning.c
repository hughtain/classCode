#include "warning.h"
#include "hwtimer.h"
#include "beep.h"
#include "iic.h"
#include "BH1750.h"
#include "soil_H.h"
#include "water.h"
#include "light_moto.h"



enum 
{
	Safe=0,
	Bringht,
	Dark,
	Wet,
	Dry
}alarm_mode;

extern int16_t light_max;
extern int16_t light_min;
extern u8 humi_max;
extern u8 humi_min;
extern _Bool water_flag;
extern _Bool shading_flag;

//读取数据对LED灯和蜂鸣器进行控制
void WARNING(uint8_t flag)
{
	switch (flag)
	{
		case Safe:
		break;										
		case Bringht:
			if(shading_flag==0)
			{
			Shadding();//遮光
			shading_flag=1;
			}
		break;
		case Dark:	
			if(shading_flag==1)
			{
			UnShadding();//不遮光
			shading_flag=0;
			}
				break;		
		case Wet:
			Water_Off;//不浇水
		break;
		case Dry:
			Water_ON;//浇水
		break;
		default: break;
	}
}


/*
************************************************************
*	函数名称：	DHT11_Check
*	函数功能：	温湿度越限检测
*	入口参数：	无
*	返回参数：	无
*	说明：		
************************************************************
*/
void DHT11_Check(DHT11_Data_TypeDef *DHT11_Data, uint16_t humi_max, uint16_t humi_min)
{
	
	//湿度越限检测
	if(DHT11_Data->humi_int >= humi_max)		//当前温度大于等于最高温度时,高温警告
	{
             
   alarm_mode=Wet;
		WARNING(Wet);
	}			
	else if(DHT11_Data->humi_int <= humi_min)	//当前温度小于等于最低温度时,低温警告
	{
		alarm_mode=Dry;
		WARNING(Dry);
	}

}


/////检查各个传感器的数据
void Check_sensor(volatile data_Stream *data_stram)
{
	DHT11_Data_TypeDef DH11_data;
	uint8_t Light;
	uint8_t Hum;
	DHT11_Read_TempAndHumidity(&DH11_data);//读取温度
	Light=Read_Light();////////读取光照指0-100
	Hum=Read_Soil();//读取土壤湿度
	Water_Off;
	if(Hum>humi_max)  //大于阈值
	{
		Water_Off;   //关水
	}
	else if(Hum<humi_min)
	{
	Water_ON;
	}
		else
	{
	alarm_mode=Safe;
	}
	if(Light>light_max&&shading_flag==0)
	{
		Shadding();		            //遮光
		shading_flag=1;
	}
	else if(Light<light_min&&shading_flag==1)
	{
			UnShadding();
	    shading_flag=0;
		
		
		
	}
UsartPrintf(USART_DEBUG, "--------------监测数据--------------\r\n");			
			UsartPrintf(USART_DEBUG, "温度：%d ℃\r\n",DH11_data.temp_int);
			UsartPrintf(USART_DEBUG, "湿度：%d ％RH\r\n",Hum);
			UsartPrintf(USART_DEBUG, " 光照%d lx\r\n",Light);	
    	UsartPrintf(USART_DEBUG, "最大光照：%d\r\n",light_max);
			UsartPrintf(USART_DEBUG, "最小光照：%d\r\n", light_min);
			UsartPrintf(USART_DEBUG, "最大湿度：%d\r\n", humi_max);
			UsartPrintf(USART_DEBUG, "最小湿度：%d\r\n", humi_min);	
			UsartPrintf(USART_DEBUG, "水泵%d\r\n",water_flag);	

		
	    data_stram->humidit=Hum;/////////给发送的结构体成员赋值
	    data_stram->temp=DH11_data.temp_int;
			data_stram->Light=Light;
			data_stram->hum_max=humi_max;
			data_stram->hum_min=humi_min;
			data_stram->light_max=light_max;
			data_stram->light_min;
			
}
