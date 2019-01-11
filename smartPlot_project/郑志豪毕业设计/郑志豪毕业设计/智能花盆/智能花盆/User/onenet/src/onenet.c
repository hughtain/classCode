

//��Ƭ��ͷ�ļ�


//�����豸
#include "esp8266.h"

//Э���ļ�
#include "onenet.h"
#include "edpkit.h"


//Ӳ������
#include "./usart/bsp_usart.h"
#include "delay.h"
#include "iic.h"


//C��
#include <string.h>
#include <stdio.h>

#include "light_moto.h"
#include "water.h"







extern unsigned char esp8266_buf[1024];
short int light_max = 40;
short int light_min = 5;
u8 humi_max = 80;
u8 humi_min = 20;
_Bool water_flag=0;
_Bool shading_flag=0;
_Bool  heart_flag;




//==========================================================
//	�������ƣ�	OneNet_DevLink
//
//	�������ܣ�	��onenet��������
//
//	��ڲ�����	��
//
//	���ز�����	1-�ɹ�	0-ʧ��
//
//	˵����		��onenetƽ̨��������
//==========================================================
_Bool OneNet_DevLink(void)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};				//Э���

	unsigned char *dataPtr;
	
	unsigned char status = 1;
	
	UsartPrintf(USART_DEBUG, "OneNet_DevLink\r\n"
                        "DEVID: %s,     APIKEY: %s\r\n"
                        , DEVID, APIKEY);

	if(EDP_PacketConnect1(DEVID, APIKEY, 256, &edpPacket) == 0)		//����devid �� apikey��װЭ���
	{
		ESP8266_SendData(edpPacket._data, edpPacket._len);			//�ϴ�ƽ̨
		
		dataPtr = ESP8266_GetIPD(250);								//�ȴ�ƽ̨��Ӧ
		if(dataPtr != NULL)
		{
			if(EDP_UnPacketRecv(dataPtr) == CONNRESP)
			{
				switch(EDP_UnPacketConnectRsp(dataPtr))
				{
					case 0:UsartPrintf(USART_DEBUG, "Tips:	���ӳɹ�\r\n");status = 0;break;
					
					case 1:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�Э�����\r\n");break;
					case 2:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��豸ID��Ȩʧ��\r\n");break;
					case 3:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�������ʧ��\r\n");break;
					case 4:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��û�ID��Ȩʧ��\r\n");break;
					case 5:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�δ��Ȩ\r\n");break;
					case 6:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ���Ȩ����Ч\r\n");break;
					case 7:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�������δ����\r\n");break;
					case 8:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ����豸�ѱ�����\r\n");break;
					case 9:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��ظ��������������\r\n");break;
					
					default:UsartPrintf(USART_DEBUG, "ERR:	����ʧ�ܣ�δ֪����\r\n");break;
				}
			}
		}
		
		EDP_DeleteBuffer(&edpPacket);								//ɾ��
	}
	else
		UsartPrintf(USART_DEBUG, "WARN:	EDP_PacketConnect Failed\r\n");
	
	return status;
	
}

unsigned char OneNet_FillBuf(char *buf,data_Stream *data_stream)
{


	char text[16];
	
	memset(text, 0, sizeof(text));
	
	strcpy(buf, "{");
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Temperature\":%d,", data_stream->temp);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Humidity\":%d,",data_stream->humidit);
	strcat(buf, text);
	
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Light\":%d,", data_stream->Light);
	strcat(buf, text);
	
		memset(text, 0, sizeof(text));
	sprintf(text, "\"Water\":%d,", water_flag);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Light_Max\":%d,", data_stream->light_max);
	strcat(buf, text);

	memset(text, 0, sizeof(text));
	sprintf(text, "\"Light_Min\":%d,", data_stream->light_min);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Hum_Max\":%d,", data_stream->hum_max);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Hum_Min\":%d", data_stream->hum_min);
	strcat(buf, text);
	
	
	
	strcat(buf, "}");
	
	return strlen(buf);
}

//==========================================================
//	�������ƣ�	OneNet_SendData
//
//	�������ܣ�	�ϴ����ݵ�ƽ̨
//
//	��ڲ�����	type���������ݵĸ�ʽ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_SendData( data_Stream *data_stream)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};												//Э���
	
	char buf[128];
	
	short int body_len = 0, i = 0;
		
	memset(buf, 0, sizeof(buf));
	
	body_len = OneNet_FillBuf(buf,data_stream);																	//��ȡ��ǰ��Ҫ���͵����������ܳ���
	
	if(body_len)
	{
		if(EDP_PacketSaveData(DEVID, body_len, NULL, kTypeSimpleJsonWithoutTime, &edpPacket) == 0)	//���
		{
			for(; i < body_len; i++)
				edpPacket._data[edpPacket._len++] = buf[i];
			
			ESP8266_SendData(edpPacket._data, edpPacket._len);										//�ϴ����ݵ�ƽ̨
			//UsartPrintf(USART_DEBUG, "Send %d Bytes\r\n", edpPacket._len);
			//hexdump(edpPacket._data,edpPacket._len);
			EDP_DeleteBuffer(&edpPacket);
		}
		else
			UsartPrintf(USART_DEBUG, "WARN:	EDP_NewBuffer Failed\r\n");
	}
	//ESP8266_Clear();
	
}

//==========================================================
//	�������ƣ�	OneNet_RevPro
//
//	�������ܣ�	ƽ̨�������ݼ��
//
//	��ڲ�����	dataPtr��ƽ̨���ص�����
//
//	���ز�����	��
//
//	˵����		
//==========================================================



void OneNet_RevPro(unsigned char *cmd)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};	//Э���
	
	char *cmdid_devid = NULL;
	unsigned short cmdid_len = 0;
	char *req = NULL;
	unsigned int req_len = 0;
	unsigned char type = 0;
	
	short result = 0;

	char *dataPtr = NULL;
	char numBuf[10];
	int num = 0;
	heart_flag=Heart_err;//�ȳ�ʼ��δ��ʧ
	hexdump(edpPacket._data,edpPacket._len);//��ӡ�յ�����Ϣ
	type = EDP_UnPacketRecv(cmd);
	switch(type)										//�ж���pushdata���������·�
	{
			case PUSHDATA:									//��pushdata��
			
			result = EDP_UnPacketPushData(cmd, &cmdid_devid, &req, &req_len);
		
			if(result == 0)
				UsartPrintf(USART_DEBUG, "src_devid: %s, req: %s, req_len: %d\r\n", cmdid_devid, req, req_len);
			
		break;
		case CMDREQ:									//�������
			
			result = EDP_UnPacketCmd(cmd, &cmdid_devid, &cmdid_len, &req, &req_len);
			
			if(result == 0)								//����ɹ������������ظ������
			{
				EDP_PacketCmdResp(cmdid_devid, cmdid_len, req, req_len, &edpPacket);
				UsartPrintf(USART_DEBUG, "cmdid: %s, req: %s, req_len: %d\r\n", cmdid_devid, req, req_len);
			}
			
		break;
			
		case SAVEACK:
			
			if(cmd[3] == MSG_ID_HIGH && cmd[4] == MSG_ID_LOW)
			{
				UsartPrintf(USART_DEBUG, "Tips:	Send %s\r\n", cmd[5] ? "Err" : "Ok");
			}
			else
				UsartPrintf(USART_DEBUG, "Tips:	Message ID Err\r\n");
			
		break;
		case PINGRESP:
			printf("������Ӧ");
			heart_flag=Heart_OK;
		break;
				
			
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();									//��ջ���
	
	if(result == -1)
		return;
	
	dataPtr = strchr(req, ':');							//����':'
	
	if(dataPtr != NULL)									//����ҵ���
	{
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//�ж��Ƿ����·��������������
		{
			numBuf[num++] = *dataPtr++;
		}
		
		num = atoi((const char *)numBuf);				//תΪ��ֵ��ʽ

		if(strstr((char *)req, "Water"))				//����"Fire"
		{
			
			if(num == 1)								//�����������Ϊ1������
			{
			water_flag=1;
			Water_ON;
			
			}
			else if(num == 0)							//�����������Ϊ0�������
			{
			water_flag=0;
			Water_Off;	
			}
		}
		
			
												//��ͬ
		else if(strstr((char *)req, "Hum_Max"))
		{
				humi_max=num;  ////////////���ø�����ֵ
		
			
		}
		else if(strstr((char *)req, "Hum_Min"))
		{
		humi_min=num;



		}
		else if(strstr((char *)req, "Light_Max"))
		{
			light_max=num;

	


		}
		else if(strstr((char *)req, "Light_Min"))
		{
			light_min=num;

	

		}
	}
	
	if(type == CMDREQ && result == 0)						//���������� �� ����ɹ�
	{
		EDP_FreeBuffer(cmdid_devid);						//�ͷ��ڴ�
		EDP_FreeBuffer(req);												//�ظ�����
		ESP8266_SendData(edpPacket._data, edpPacket._len);	//�ϴ�ƽ̨
		EDP_DeleteBuffer(&edpPacket);						//ɾ��
	}

}



void OneNet_Send_heart(void)
{
		EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};	
		if(!EDP_PacketPing(&edpPacket))
		{
		printf("send ping pkt to server, bytes: %d\r\n", edpPacket._len);
		ESP8266_SendData(edpPacket._data, edpPacket._len);				//�ϴ����ݵ�ƽ̨
		hexdump(edpPacket._data,edpPacket._len);
		EDP_DeleteBuffer(&edpPacket);									//ɾ��
		}
		else 
		printf("����ʧ��");
}





//==========================================================
//	�������ƣ�	OneNET_CmdHandle
//
//	�������ܣ�	��ȡƽ̨rb�е�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNET_CmdHandle(void)
{
	
	unsigned char *dataPtr = NULL;		//����ָ��
	dataPtr = ESP8266_GetIPD(5);		//����Ƿ���ƽ̨����
		if(dataPtr != NULL)
		{	
				OneNet_RevPro(dataPtr);					//���д���
			
	
		}
	
	

}

