#include "sta_tcpclent_test.h"
#include "SysTick.h"
#include "usart.h"
#include "esp8266_drive.h"
#include "includes.h"

#include "adc_temp.h"



volatile u8 TcpClosedFlag = 0;
void ESP8266_STA_TCPClient_Test_Init(void)
{
	
	printf ( "\r\n��������ESP8266�����ĵȴ�...\r\n" );
  
	ESP8266_Init(115200);
	
	ESP8266_CH_PD_Pin_SetH;

	ESP8266_AT_Test();
	ESP8266_Net_Mode_Choose(STA);
	while(!ESP8266_JoinAP(User_ESP8266_SSID, User_ESP8266_PWD));
	ESP8266_Enable_MultipleId ( DISABLE );
	while(!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer_IP, User_ESP8266_TCPServer_PORT, Single_ID_0));
	
	while(!ESP8266_UnvarnishSend());
	printf ( "\r\n����ESP8266 OK��\r\n" );
}
void ESP8266_STA_TCPClient_Test_Send(char *str)
{
	   u8 res;
	   CPU_SR_ALLOC();
	 
		 OS_CRITICAL_ENTER();	//�����ٽ���
	  ESP8266_SendString ( ENABLE, str, 0, Single_ID_0 );
		if(TcpClosedFlag) //����Ƿ�ʧȥ����
		{
			ESP8266_ExitUnvarnishSend(); //�˳�͸��ģʽ
			do
			{
				res = ESP8266_Get_LinkStatus();     //��ȡ����״̬
			} 	
			while(!res);
			
			if(res == 4)                     //ȷ��ʧȥ���Ӻ�����
			{
				printf ( "\r\n���Եȣ����������ȵ�ͷ�����...\r\n" );
				
				while (!ESP8266_JoinAP(User_ESP8266_SSID, User_ESP8266_PWD ) );
				
				while (!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer_IP, User_ESP8266_TCPServer_PORT, Single_ID_0 ) );
				
				printf ( "\r\n�����ȵ�ͷ������ɹ�\r\n" );
			} 
			while(!ESP8266_UnvarnishSend());					
		}
				OS_CRITICAL_EXIT();     //�˳��ٽ���

}


void ESP8266_STA_TCPClient_Test(void)
{
	u8 res;
	float rtemp;
	char str[100]={0};
		char str1[100]={0};
			u8 buffer[5];
        double hum=10.99;
        double temp=32.99;
		ADC_Temp_Init();
	
	printf ( "\r\n��������ESP8266�����ĵȴ�...\r\n" );

	ESP8266_CH_PD_Pin_SetH;

	ESP8266_AT_Test();
	ESP8266_Net_Mode_Choose(STA);
	while(!ESP8266_JoinAP(User_ESP8266_SSID, User_ESP8266_PWD));
	ESP8266_Enable_MultipleId ( DISABLE );
	while(!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer_IP, User_ESP8266_TCPServer_PORT, Single_ID_0));
	
	while(!ESP8266_UnvarnishSend());
	printf ( "\r\n����ESP8266 OK��\r\n" );
	
	while ( 1 )
	{		
		rtemp=Get_Temperture();
		/*if (dht11_read_data(buffer) == 0)
        {
            hum = buffer[0] + buffer[1] / 10.0;
            temp = buffer[2] + buffer[3] / 10.0;
        }
*/		
		
	
		//sprintf(str,"wendu 11:00 %.1f\r\n",temp);
		//sprintf(str1,"shidu 11:00 %.1f\r\n",hum);
	  sprintf(str,"wendu 11:00 %.1f\r\n",rtemp);
  	sprintf(str1,"shidu 11:00 %.1f\r\n",rtemp);
		//sprintf (str,"www.prechin.cn\r\n" );
		ESP8266_SendString ( ENABLE, str, 0, Single_ID_0 );
		delay_ms(1000);
			ESP8266_SendString ( ENABLE, str1, 0, Single_ID_0 );
		delay_ms(1000);
		if(TcpClosedFlag) //����Ƿ�ʧȥ����
		{
			ESP8266_ExitUnvarnishSend(); //�˳�͸��ģʽ
			do
			{
				res = ESP8266_Get_LinkStatus();     //��ȡ����״̬
			} 	
			while(!res);
			
			if(res == 4)                     //ȷ��ʧȥ���Ӻ�����
			{
				printf ( "\r\n���Եȣ����������ȵ�ͷ�����...\r\n" );
				
				while (!ESP8266_JoinAP(User_ESP8266_SSID, User_ESP8266_PWD ) );
				
				while (!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer_IP, User_ESP8266_TCPServer_PORT, Single_ID_0 ) );
				
				printf ( "\r\n�����ȵ�ͷ������ɹ�\r\n" );
			} 
			while(!ESP8266_UnvarnishSend());					
		}
	}
		
}



