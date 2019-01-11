#include "machine.h"

/*******************************************************************************
* �� �� ��         : LED_Init
* ��������		   : LED��ʼ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void MAC_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(MAC_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=MAC_PIN;  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(MAC_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
	//GPIO_SetBits(LED_PORT,LED_PIN);   //��LED�˿����ߣ�Ϩ������LED
}

void machine_goto(void)//˳ʱ��ת
{
	  MAC1=1;
	  MAC2=0;
	  MAC3=1;
}	



void machine_back(void)//��ʱ��ת
{
	  MAC1=0;
	  MAC2=1;
	  MAC3=1;
}	

void machine_fast_stop(void)//����ֹͣ
{
	  MAC1=1;
	  MAC2=1;
	  MAC3=1;
}	

void machine_stop(void)//ֹͣ
{
	  MAC1=0;
	  MAC2=0;
	  MAC3=0;
}	


void machine1_goto(void)//˳ʱ��ת
{
	  MAC0=1;
	  MAC5=0;
	  MAC7=1;
}	


void machine1_back(void)//��ʱ��ת
{
	  MAC0=0;
	  MAC5=1;
	  MAC7=1;
}	

void machine1_fast_stop(void)//����ֹͣ
{
	  MAC0=1;
	  MAC5=1;
	  MAC7=1;
}	

void machine1_stop(void)//ֹͣ
{
	  MAC0=0;
	  MAC5=0;
	  MAC7=0;
}	




