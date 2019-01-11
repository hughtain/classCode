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

//��ȡ���ݶ�LED�ƺͷ��������п���
void WARNING(uint8_t flag)
{
	switch (flag)
	{
		case Safe:
		break;										
		case Bringht:
			if(shading_flag==0)
			{
			Shadding();//�ڹ�
			shading_flag=1;
			}
		break;
		case Dark:	
			if(shading_flag==1)
			{
			UnShadding();//���ڹ�
			shading_flag=0;
			}
				break;		
		case Wet:
			Water_Off;//����ˮ
		break;
		case Dry:
			Water_ON;//��ˮ
		break;
		default: break;
	}
}


/*
************************************************************
*	�������ƣ�	DHT11_Check
*	�������ܣ�	��ʪ��Խ�޼��
*	��ڲ�����	��
*	���ز�����	��
*	˵����		
************************************************************
*/
void DHT11_Check(DHT11_Data_TypeDef *DHT11_Data, uint16_t humi_max, uint16_t humi_min)
{
	
	//ʪ��Խ�޼��
	if(DHT11_Data->humi_int >= humi_max)		//��ǰ�¶ȴ��ڵ�������¶�ʱ,���¾���
	{
             
   alarm_mode=Wet;
		WARNING(Wet);
	}			
	else if(DHT11_Data->humi_int <= humi_min)	//��ǰ�¶�С�ڵ�������¶�ʱ,���¾���
	{
		alarm_mode=Dry;
		WARNING(Dry);
	}

}


/////������������������
void Check_sensor(volatile data_Stream *data_stram)
{
	DHT11_Data_TypeDef DH11_data;
	uint8_t Light;
	uint8_t Hum;
	DHT11_Read_TempAndHumidity(&DH11_data);//��ȡ�¶�
	Light=Read_Light();////////��ȡ����ָ0-100
	Hum=Read_Soil();//��ȡ����ʪ��
	Water_Off;
	if(Hum>humi_max)  //������ֵ
	{
		Water_Off;   //��ˮ
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
		Shadding();		            //�ڹ�
		shading_flag=1;
	}
	else if(Light<light_min&&shading_flag==1)
	{
			UnShadding();
	    shading_flag=0;
		
		
		
	}
UsartPrintf(USART_DEBUG, "--------------�������--------------\r\n");			
			UsartPrintf(USART_DEBUG, "�¶ȣ�%d ��\r\n",DH11_data.temp_int);
			UsartPrintf(USART_DEBUG, "ʪ�ȣ�%d ��RH\r\n",Hum);
			UsartPrintf(USART_DEBUG, " ����%d lx\r\n",Light);	
    	UsartPrintf(USART_DEBUG, "�����գ�%d\r\n",light_max);
			UsartPrintf(USART_DEBUG, "��С���գ�%d\r\n", light_min);
			UsartPrintf(USART_DEBUG, "���ʪ�ȣ�%d\r\n", humi_max);
			UsartPrintf(USART_DEBUG, "��Сʪ�ȣ�%d\r\n", humi_min);	
			UsartPrintf(USART_DEBUG, "ˮ��%d\r\n",water_flag);	

		
	    data_stram->humidit=Hum;/////////�����͵Ľṹ���Ա��ֵ
	    data_stram->temp=DH11_data.temp_int;
			data_stram->Light=Light;
			data_stram->hum_max=humi_max;
			data_stram->hum_min=humi_min;
			data_stram->light_max=light_max;
			data_stram->light_min;
			
}
