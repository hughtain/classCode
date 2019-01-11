#include<reg52.h>
#include <intrins.h>
#include <absacc.h>		  //ͷ�ļ�
#define uint unsigned int
#define uchar unsigned char	  //�궨��

//����
sbit key1=P3^2;	   //����
sbit key2=P3^3;	   //����
sbit key3=P3^4;	   //��������

sbit BUZZ=P0^4;	   //������
sbit rsd=P2^4;	   //���͵�����
sbit LED_B=P2^3;   //����ָʾ��
sbit LED_S=P2^0;   //������Ϣָʾ��

uchar code PhoneNO[]		="15046397767"; //���ܺ���

uchar code somebody[]		="8BF76CE8610FFF0167094EBA8FDB516562A58B66830356F4FF01";	//��ע�⣡���˽��뱨����Χ��												  

uint TIME_50ms=0;	   //��ʱ����С�ֱ���50ms
uint time_continue;	   //����������ʱ��ʱ�����ݴ�
bit flag=0,flag_BF=0;  //flag��ֵΪ0ʱ���ǲ�����ʱģʽ��ֵΪ1ʱ����һ���ӵȴ�ģʽ��flag_BF��������־λ
bit flag_time_start=0; //��ʼ��ʱ��־λ
bit again=0;		   //һ���ӵȴ���־λ��������һ�����ź󣬲������Ϸ��͵ڶ��죬���Եȴ�һ���Ӻ��ټ���Ƿ����ˣ������ٷ��Ͷ��ţ�
bit flag_alam;		   //������־λ
bit SOS;			   //���Ͷ���ʱ�Ƿ��ǰ��½�������
bit flag_continue;	   //������ʱ
bit into_BF=0;

void delay(uint z)//��ʱ����
{
	uint x,y;
	for(x=z;x>0;x--)
	for(y=110;y>0;y--);
}

void Uart_init()
{
	TMOD= 0X20;		//T1  ��ʽ2  ��8λ   �Զ���װ   
	TH1=0Xfd;
	TL1=0Xfd;	    //9600������
	TR1=1; 		    // ��ʱ��1����  
	SM0=0;	    // ���ô��ڵĹ���ģʽ
	SM1=1; 	    //��ʽ1

	REN=0; 		 // �������ڽ������� 	 

	ES=0; 	     // �����жϲ����� 
	EA=1;		 // �����ж��ܿ��� 
}

void SendASC(uchar d)	//���ڷ����ַ�
{
	
	SBUF=d;				//���ݸ�ֵ��������
	while(!TI);			//������

	TI=0;				//����
}

void SendString(uchar *str)	  //���ڷ����ַ���
{
	while(*str)				  //�ж��Ƿ�����
	{
		SendASC(*str) ;		  //�����ַ�
		str++;				  //�ַ�λ�ü�
		//delay_uart(1);
	}
}

void TIME()						//��ʱ����
{
	if(flag==0)					//������ʱģʽ
	{
		delay(50);				//50ms
		TIME_50ms++;			//50ms������1
		if(TIME_50ms%10==0)		//ÿ500ms��50ms*10��
		LED_B=!LED_B;			//����ָʾ��ȡ��һ��
		
		if(TIME_50ms>=400)		//�ӵ�400�Σ�Ҳ����50ms*400=20000ms=20s
		{
			TIME_50ms=0;		//��ʱ��������
			flag_BF=1;			//���벼��״̬
			LED_B=0;			//����ָʾ�Ƴ���
			flag_time_start=0;	//ֹͣ��ʱ
			again=1;			//�ر�һ���ӵȴ�
		}	
	}
	else						//һ���ӵȴ�ģʽ
	{
		delay(50);				//50ms
		TIME_50ms++;			//������
		if(TIME_50ms%10==0)		//ÿ��500ms
		{
			LED_B=!LED_B;		//����ָʾ����˸
			if(flag_alam==1)	//����
			{
				if(flag_continue==0)//���뱨��ʱ
				{
					flag_continue=1;//�˱�־λ��һ����ֹ����ʱ����
					time_continue=TIME_50ms; //�����뱨��ʱ�ļ�ʱ�����ݴ�
				}
				BUZZ=!BUZZ;		//������ȡ����Ҳ������˸��
				if(TIME_50ms>=time_continue+100)//������ʱ��ﵽ5sʱ
				{
					BUZZ=1;						//�رշ�����
					flag_continue=0;			//��־λ���㣬�ȴ��´α���
					flag_alam=0;				//�����������㣬ֹͣ����
					time_continue=0;			//�ݴ��ʱ��������
				}	
			}
		}
		if(TIME_50ms>=1200)		   //��ʱ�ﵽ60��
		{
			LED_B=0;			   //����ָʾ�Ƴ�����׼��������͵��ź�
			TIME_50ms=0;		   //��ʱ��������
			flag_time_start=0;	   //ֹͣ��ʱ
			again=1;			   //�ر�һ���ӵȴ�
		}
	}
}

//����ɨ�躯��
void keyscan()
{
	if(key1==0&&flag_BF==0)//�ڷǲ���״̬ʱ������������
	{
		delay(5);//��ʱȥ��
		if(key1==0)		   //�ٴ��жϰ����Ƿ���
		{
			LED_B=0;	   //��������LED��
			flag=0;		   //��������
			flag_time_start=1;//��ʼ��ʱ������һ
		}
		while(key1==0);	   //�����ͷ�
	}
	if(flag_time_start==1)	//��ʼ��ʱ
	{
		TIME();				//���ü�ʱ����
	}
	if(key2==0)				//������������
	{			   
		delay(5);//��ʱȥ��
		if(key2==0)		   //�ٴ��жϰ����Ƿ���
		{
			BUZZ=1;			//�رշ����� 
			flag_alam=0;	//������������
			flag_BF=0;		//������������
			flag=0;			//��������
			flag_time_start=0;//��ʼ��ʱ��������
			LED_S=1;		//�رշ��Ͷ���ָʾ��
			LED_B=1;		//�رղ���ָʾ��
		}
		while(key2==0);		//�����ͷ�
	}
	if(key3==0)				//������������
	{
		delay(5);			//��ʱȥ��
		if(key3==0)			//�ٴ��жϰ����Ƿ���
		{
			SOS=1;			//�ֶ����Ͷ��ű�����һ��׼�����Ͷ���
			flag_alam=1;	//����������һ
		}
		while(key3==0);		//�����ͷ�
	}
} 

void GSM_work()				//����GSM����
{
	unsigned char send_number;	//���巢���ֻ��ŵı���
	if(rsd==0&&flag_BF==1)		//����״̬�����͵����ź�ʱ
	flag_alam=1;				//����������һ

	if((rsd==0&&flag_BF==1&&again==1)||SOS==1)//����״̬�����͵����ź�ʱ�Ҳ���һ���ӵȴ�ʱ����  ����   �ֶ����½�������
	{
		LED_S=0;								 //�򿪷��Ͷ���ָʾ��
		BUZZ=1;									 //�رշ�����
		SendString("AT+CMGF=1\r\n");			 //�����ı�ģʽ
		
		delay(1000);							 //��ʱ����GSMģ����һ����Ӧʱ��
		
		SendString("AT+CSCS=\"UCS2\"\r\n");		 //���ö��Ÿ�ʽ�����ͺ���ģʽ
		
		delay(1000);							 //��ʱ
		
		SendString("AT+CSMP=17,0,2,25\r\n");	 //���ö����ı�ģʽ�������������ݲο����������ڵ�ģ�����ϣ�
		
		delay(1000);							 //��ʱ
		
		SendString("AT+CMGS=");	//��Ϣ����ָ�� AT+CMGS=//
		SendASC('"');									 //����
		for(send_number=0;send_number<11;send_number++)	 //��ÿλ����ǰ��003
		{
			SendASC('0');
			SendASC('0');
			SendASC('3');
			SendASC(PhoneNO[send_number]);				 //�����ֻ�����
		}     
		SendASC('"');									//����
		SendASC('\r');			//���ͻس�ָ��//
		SendASC('\n');			//���ͻ���ָ��//
		
		delay(1000);				//��ʱ

		SendString(somebody);		//���Ͷ�������
	
		delay(1000);				//��ʱ
		
		SendASC(0x1a);				//ȷ�����Ͷ���
		
		if(SOS==0)					//���ǽ����������Ͷ���
		{
			again=0;				//again���㣬Ҳ���ǽ���һ���ӵȴ�������ʱ��һ���Ӻ󣬸ñ���������һ
			flag_time_start=1;		//��ʼ��ʱ
			flag_alam=1;			//����
		}
		else if(SOS==1&&flag_time_start==1)	 //�����������Ͷ��ź�
		{											  
			TIME_50ms=0;					 //��ʱ��������
			flag_BF=1;						 //����������һ
			LED_B=0;						 //��������ָʾ��
			flag_time_start=0;				 //ֹͣ��ʱ
			again=1;						 //������һ���ӵȴ�
		}
		
		LED_S=1;							 //Ϩ���Ͷ���ָʾ��
		SOS=0;								 //������������
		flag=1;								 //������һ
	}
}	
void main()									 //������
{	
	Uart_init();							 //�����жϳ�ʼ������
	while(1)								 //����whileѭ��
	{
		keyscan();							 //��������
		GSM_work();							 //���Ͷ��ź���
	}	  
}