#ifndef _sta_tcpclent_test_H
#define _sta_tcpclent_test_H


#include "system.h"


#define User_ESP8266_SSID	  "13653031972"	      //Ҫ���ӵ��ȵ������
#define User_ESP8266_PWD	  "AB136530319"	  //Ҫ���ӵ��ȵ������

#define User_ESP8266_TCPServer_IP	  "183.55.194.81"	  //Ҫ���ӵķ�������IP
#define User_ESP8266_TCPServer_PORT	  "8080"	  //Ҫ���ӵķ������Ķ˿�


extern volatile uint8_t TcpClosedFlag;  //����һ��ȫ�ֱ���


void ESP8266_STA_TCPClient_Test(void);

void ESP8266_STA_TCPClient_Test_Send(char *str);
void ESP8266_STA_TCPClient_Test_Init(void);



#endif
