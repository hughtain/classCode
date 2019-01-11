/**************************************/
/*           WeBee�Ŷ�                 */
/*         Zigbeeѧϰ����              */
/*�������ƣ�����ͨѶ2                  */
/*����ʱ�䣺2012/06/11                 */
/*������ͨ���ڲ�AD���ư��¶���Ϣͨ��
        ���ڷ��͸���λ��,����оƬ���
        �ϴ���ҪУ׼��������оƬ���¶�
        ���Ա��
**************************************/
#include <ioCC2530.h>
#include "OnBoard.h"  //ע����option������·�� 
#include "stdio.h"
#include"IICLight.h"

char Light[4];
char  BUF[1];

char  ge,shi,bai,qian,wan;            //��ʾ����

#define   uint unsigned int
#define   uchar unsigned char
typedef   unsigned char BYTE;
typedef   unsigned short WORD;
#define  SlaveAddress   0x46 

#define  IIC_WRITE      0                 // WRITE direction bit
#define  IIC_READ       1                 // READ direction bit
#define  TRUE  1
#define  FALSE 0

//I2C������������SDA��ʱ���ź���SCL���ɴ������ߣ��ɷ��ͺͽ������ݡ�
#define SCL P1_2
#define SDA P1_3

void lightinit()     //cc2530��GPIO����
{ 
  
  P1SEL &= 0XF3;     //����P1.2��P1.3Ϊ��ͨIO��  
  P1INP &= 0xF3;     //��P1.2��P1.3��������,��Ӱ��
}

unsigned char buffer[];
   
//*********************************************************
void conversion(uint temp_data)  //  ����ת���� ����ʮ���٣�ǧ����
{  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //ȡ������
    qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //ȡ������
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //ȡ������
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //ȡ������
    ge=temp_data+0x30;         
    Light[0]=(unsigned char)wan;
    Light[1]=(unsigned char)qian;
    Light[2]=(unsigned char)bai;
    Light[3]=(unsigned char)shi;
    Light[4]=(unsigned char)ge;
}

/***********************************************************************************
* Function: Delay_us;
*
* Description: ��ʱ����, ��ʱʱ�䷶Χ: 0~65535us;
*
* Input:  times, ��ʱʱ�����;
*
* Output: none;
*
* Return: none;
*
* Note:   ��ʱʱ�������65535us;
************************************************************************************/
void Delay_1u(unsigned int times)
{
   //  uint i,j;
//for(i=times;i>0;i--)
   //for(j=1;j>0;j--);

while(times--)

  {

      asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
      asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
      asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
      asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
      asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
      asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
      asm("nop"); asm("nop");

  }

}


void Delay_1ms(unsigned int times)
{
    unsigned int i;
        
        for (i=0; i<times; i++)        
                Delay_1u(1000);         // ������ʱ����,��ʱ1ms                
}

void Delay_1s(unsigned int times)
{
        unsigned int i;
        
        for (i=0; i<times; i++)
                Delay_1ms(1000);           // ������ʱ����,��ʱ1s
}


void Delay5us()
{
    Delay_1u(5);
}

/**************************************
��ʼ�ź�
**************************************/
void WriteSDA1(void)//SDA ���1,�൱��51�����SDA=1   
{
          
            P1DIR |= 0x08;
          SDA = 1;
     }
     
void WriteSDA0(void)//SDA ���0   
{
          //P1DIR |= 0x20;
          P1DIR |= 0x08;
          SDA = 0;
     }
     
void WriteSCL1(void)//SCL ���1   
{
          //P1DIR |= 0x10;
            P1DIR |= 0x04;
          SCL = 1;
     }
     
void WriteSCL0(void)//SCL ���0   
{
          //P1DIR |= 0x10;
            P1DIR |= 0x04;
          SCL = 0;
     }
     
void ReadSDA(void)//��������SDA��ӦIO��DIR���Խ�������   
{
          //P1DIR &= 0xDF;
         P1DIR &= 0xF7;
     }

void BH1750_Start()
{
         WriteSDA1();
         WriteSCL1();
         Delay_1u(5);
         WriteSDA0();
         Delay_1u(5);
         WriteSCL0();
         Delay_1u(5);

}

/**************************************
ֹͣ�ź�
**************************************/
void BH1750_Stop()
{
         WriteSDA0();
         WriteSCL1();
         Delay_1u(5);
         WriteSDA1();
         Delay_1u(5);
         WriteSCL0();
         Delay_1u(5);

}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK(uchar ack)
{
   if(ack)
           {
              WriteSDA1();
           }
           else
           {
              WriteSDA0();
           }  
     
         Delay_1u(5);
         WriteSCL1();   
         Delay_1u(5);
         WriteSCL0();  
                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
uchar BH1750_RecvACK()
{        
         unsigned short i=10;
         ReadSDA();F0=SDA;
         WriteSCL1();
         Delay_1u(5);
         WriteSCL0();
         Delay_1u(5);
         P1DIR |= 0x08;
         return F0;

}

/*����0����SCLΪ�ߵ�ƽʱʹSDA�ź�Ϊ��*/
     void SEND_0_1(void)   /* SEND ACK */
     {
         WriteSDA0();
         Delay_1u(5);
         WriteSCL1();
         Delay_1u(5);
         WriteSCL0();
         Delay_1u(5);
     }

     /*����1����SCLΪ�ߵ�ƽʱʹSDA�ź�Ϊ��*/
     void SEND_1_1(void)
     {
         WriteSDA1();
         Delay_1u(5);
         WriteSCL1();
         Delay_1u(5);
         WriteSCL0();
         Delay_1u(5);
     }
/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void BH1750_SendByte(uchar dat)
{
         char i;
         WriteSCL0();
         for(i=0;i<8;i++)
         {
           if((dat<<i)&0x80)
           {
              SEND_1_1();
           }
           else
           {
              SEND_0_1();
           }
         }
        BH1750_RecvACK();
        
}

/**************************************
��IIC���߽���һ���ֽ����ݣ���һ�֣�
**************************************/
uchar BH1750_RecvByte()
{
         char b=0,i;
         
         WriteSCL0(); 
         Delay_1u(5);
         
         for(i=0;i<8;i++)
         {   
             ReadSDA();
             WriteSCL1();
             Delay_1u(5);
             
          F0=SDA;//�Ĵ����е�һλ,���ڴ洢SDA�е�һλ����

           if(F0)
             {
               b=b<<1;
               b=b|0x01;
             }
             else
               {b=b<<1;}
           WriteSCL0();
           Delay_1u(5);
         }
         
         
         P1DIR |= 0x08;
          return b; 
}
//*********************************

void Single_Write_BH1750(uchar REG_Address)
{   
    uchar REG_data;
    BH1750_Start();                  //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    BH1750_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ 
    BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ 
    BH1750_Stop();                   //����ֹͣ�ź�
}

unsigned char Single_Read_BH1750(void)     //��������BH1750�ڲ�����
{   uchar i;uchar t0;uchar t1;uchar t;
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    if(F0)
      { 
        BH1750_Start();                          //��ʼ�ź�
        BH1750_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
       }
    BH1750_SendByte(0x00);                   // �ϵ�
    if(F0)
      { 
        BH1750_SendByte(0x00);       
       }
    BH1750_Stop();
    Delay_1ms(30); 

    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    if(F0)
      { 
        BH1750_Start();                          //��ʼ�ź�
        BH1750_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
       }
    BH1750_SendByte(0x01);                   // �ϵ�
    if(F0)
      { 
        BH1750_SendByte(0x01);       
       }
    BH1750_Stop();

    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    if(F0)
      { 
        BH1750_Start();                          //��ʼ�ź�
        BH1750_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
       }
    BH1750_SendByte(0x10);                  // H- resolution mode
    if(F0)
      { 
        BH1750_SendByte(0x10);       
       }
    BH1750_Stop();
    Delay_1ms(180);               //��ʱ180ms                //���ʹ洢��Ԫ��ַ����0��ʼ        
    
  
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    if(F0)
      { 
        BH1750_Start();                          //��ʼ�ź�
        BH1750_SendByte(SlaveAddress+1);           //�����豸��ַ+д�ź�
       }
    
    t0= BH1750_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
    BH1750_SendACK(0);                //���һ��������Ҫ��NOACK

    t1= BH1750_RecvByte();
    BH1750_SendACK(1);                //��ӦACK
       
    BH1750_Stop();                           //ֹͣ�ź�
    t=((t0<<8)+t1)/1.2;
    Delay_1ms(5);
    return t;
}

/**************************************************************** 
������   
****************************************************************/ 
unsigned short int getlight(void) 
{   
       
       unsigned short int lx;
        lightinit();
        while(1) 
        { 
         
        lx=Single_Read_BH1750();      //�����������ݣ��洢��lx��  
        return lx;
       
        }
}
