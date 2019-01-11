

//单片机头文件


//网络设备
#include "esp8266.h"

//协议文件
#include "onenet.h"
#include "edpkit.h"


//硬件驱动
#include "./usart/bsp_usart.h"
#include "delay.h"
#include "iic.h"


//C库
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
//	函数名称：	OneNet_DevLink
//
//	函数功能：	与onenet创建连接
//
//	入口参数：	无
//
//	返回参数：	1-成功	0-失败
//
//	说明：		与onenet平台建立连接
//==========================================================
_Bool OneNet_DevLink(void)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};				//协议包

	unsigned char *dataPtr;
	
	unsigned char status = 1;
	
	UsartPrintf(USART_DEBUG, "OneNet_DevLink\r\n"
                        "DEVID: %s,     APIKEY: %s\r\n"
                        , DEVID, APIKEY);

	if(EDP_PacketConnect1(DEVID, APIKEY, 256, &edpPacket) == 0)		//根据devid 和 apikey封装协议包
	{
		ESP8266_SendData(edpPacket._data, edpPacket._len);			//上传平台
		
		dataPtr = ESP8266_GetIPD(250);								//等待平台响应
		if(dataPtr != NULL)
		{
			if(EDP_UnPacketRecv(dataPtr) == CONNRESP)
			{
				switch(EDP_UnPacketConnectRsp(dataPtr))
				{
					case 0:UsartPrintf(USART_DEBUG, "Tips:	连接成功\r\n");status = 0;break;
					
					case 1:UsartPrintf(USART_DEBUG, "WARN:	连接失败：协议错误\r\n");break;
					case 2:UsartPrintf(USART_DEBUG, "WARN:	连接失败：设备ID鉴权失败\r\n");break;
					case 3:UsartPrintf(USART_DEBUG, "WARN:	连接失败：服务器失败\r\n");break;
					case 4:UsartPrintf(USART_DEBUG, "WARN:	连接失败：用户ID鉴权失败\r\n");break;
					case 5:UsartPrintf(USART_DEBUG, "WARN:	连接失败：未授权\r\n");break;
					case 6:UsartPrintf(USART_DEBUG, "WARN:	连接失败：授权码无效\r\n");break;
					case 7:UsartPrintf(USART_DEBUG, "WARN:	连接失败：激活码未分配\r\n");break;
					case 8:UsartPrintf(USART_DEBUG, "WARN:	连接失败：该设备已被激活\r\n");break;
					case 9:UsartPrintf(USART_DEBUG, "WARN:	连接失败：重复发送连接请求包\r\n");break;
					
					default:UsartPrintf(USART_DEBUG, "ERR:	连接失败：未知错误\r\n");break;
				}
			}
		}
		
		EDP_DeleteBuffer(&edpPacket);								//删包
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
//	函数名称：	OneNet_SendData
//
//	函数功能：	上传数据到平台
//
//	入口参数：	type：发送数据的格式
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_SendData( data_Stream *data_stream)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};												//协议包
	
	char buf[128];
	
	short int body_len = 0, i = 0;
		
	memset(buf, 0, sizeof(buf));
	
	body_len = OneNet_FillBuf(buf,data_stream);																	//获取当前需要发送的数据流的总长度
	
	if(body_len)
	{
		if(EDP_PacketSaveData(DEVID, body_len, NULL, kTypeSimpleJsonWithoutTime, &edpPacket) == 0)	//封包
		{
			for(; i < body_len; i++)
				edpPacket._data[edpPacket._len++] = buf[i];
			
			ESP8266_SendData(edpPacket._data, edpPacket._len);										//上传数据到平台
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
//	函数名称：	OneNet_RevPro
//
//	函数功能：	平台返回数据检测
//
//	入口参数：	dataPtr：平台返回的数据
//
//	返回参数：	无
//
//	说明：		
//==========================================================



void OneNet_RevPro(unsigned char *cmd)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};	//协议包
	
	char *cmdid_devid = NULL;
	unsigned short cmdid_len = 0;
	char *req = NULL;
	unsigned int req_len = 0;
	unsigned char type = 0;
	
	short result = 0;

	char *dataPtr = NULL;
	char numBuf[10];
	int num = 0;
	heart_flag=Heart_err;//先初始化未丢失
	hexdump(edpPacket._data,edpPacket._len);//打印收到的信息
	type = EDP_UnPacketRecv(cmd);
	switch(type)										//判断是pushdata还是命令下发
	{
			case PUSHDATA:									//解pushdata包
			
			result = EDP_UnPacketPushData(cmd, &cmdid_devid, &req, &req_len);
		
			if(result == 0)
				UsartPrintf(USART_DEBUG, "src_devid: %s, req: %s, req_len: %d\r\n", cmdid_devid, req, req_len);
			
		break;
		case CMDREQ:									//解命令包
			
			result = EDP_UnPacketCmd(cmd, &cmdid_devid, &cmdid_len, &req, &req_len);
			
			if(result == 0)								//解包成功，则进行命令回复的组包
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
			printf("心跳回应");
			heart_flag=Heart_OK;
		break;
				
			
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();									//清空缓存
	
	if(result == -1)
		return;
	
	dataPtr = strchr(req, ':');							//搜索':'
	
	if(dataPtr != NULL)									//如果找到了
	{
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//判断是否是下发的命令控制数据
		{
			numBuf[num++] = *dataPtr++;
		}
		
		num = atoi((const char *)numBuf);				//转为数值形式

		if(strstr((char *)req, "Water"))				//搜索"Fire"
		{
			
			if(num == 1)								//控制数据如果为1，代表开
			{
			water_flag=1;
			Water_ON;
			
			}
			else if(num == 0)							//控制数据如果为0，代表关
			{
			water_flag=0;
			Water_Off;	
			}
		}
		
			
												//下同
		else if(strstr((char *)req, "Hum_Max"))
		{
				humi_max=num;  ////////////设置各种阈值
		
			
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
	
	if(type == CMDREQ && result == 0)						//如果是命令包 且 解包成功
	{
		EDP_FreeBuffer(cmdid_devid);						//释放内存
		EDP_FreeBuffer(req);												//回复命令
		ESP8266_SendData(edpPacket._data, edpPacket._len);	//上传平台
		EDP_DeleteBuffer(&edpPacket);						//删包
	}

}



void OneNet_Send_heart(void)
{
		EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};	
		if(!EDP_PacketPing(&edpPacket))
		{
		printf("send ping pkt to server, bytes: %d\r\n", edpPacket._len);
		ESP8266_SendData(edpPacket._data, edpPacket._len);				//上传数据到平台
		hexdump(edpPacket._data,edpPacket._len);
		EDP_DeleteBuffer(&edpPacket);									//删包
		}
		else 
		printf("心跳失败");
}





//==========================================================
//	函数名称：	OneNET_CmdHandle
//
//	函数功能：	读取平台rb中的数据
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNET_CmdHandle(void)
{
	
	unsigned char *dataPtr = NULL;		//数据指针
	dataPtr = ESP8266_GetIPD(5);		//检查是否是平台数据
		if(dataPtr != NULL)
		{	
				OneNet_RevPro(dataPtr);					//集中处理
			
	
		}
	
	

}

