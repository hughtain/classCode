#include "HC-SR501.h"


void HC_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(HC_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=HC_PIN;  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;	 //�������������ģʽģʽ
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(HC_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
	
}
