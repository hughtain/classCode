#include <ioCC2530.h>
#define uint unsigned int
#define RLED   P1_0	        //����LED1ΪP10�ڿ���
#define GLED   P1_1	        //����LED2ΪP11�ڿ���
#define YLED   P1_4	        //����LED3ΪP14�ڿ���



void InitClock(void);
void InitLEDIO(void);
void InitT3(void);
void InitUART0(void);
void UartTX_Send_String(char *Data,int len);
void Delay(uint n);
// Data
typedef unsigned char       BYTE;

// Unsigned numbers
typedef unsigned char       UINT8;
typedef unsigned char       INT8U;
typedef unsigned short      UINT16;
typedef unsigned short      INT16U;
typedef unsigned long       UINT32;
typedef unsigned long       INT32U;

// Signed numbers
typedef signed char         INT8;
typedef signed short        INT16;
typedef signed long         INT32;

#define ADC_REF_1_25_V      0x00
#define ADC_14_BIT          0x30
#define ADC_TEMP_SENS       0x0E

#define DISABLE_ALL_INTERRUPTS() (IEN0 = IEN1 = IEN2 = 0x00)

#define ADC_SINGLE_CONVERSION(settings) \
   do{ ADCCON3 = (settings); }while(0)

#define ADC_SAMPLE_SINGLE() \
  do { ADC_STOP(); ADCCON1 |= 0x40;  } while (0)

#define ADC_SAMPLE_READY()  (ADCCON1 & 0x80)

#define ADC_STOP() \
  do { ADCCON1 |= 0x30; } while (0)

#define ADC14_TO_CELSIUS(ADC_VALUE)    ( ((ADC_VALUE) >> 4) - 335)

/**************************
ϵͳʱ�� ����Ƶ
����ʱ�� 32��Ƶ
**************************/
void InitClock(void)
{
    CLKCONCMD = 0x28;           //ʱ������ʱ���趨Ϊ1M Hz,  ϵͳʱ���趨Ϊ32 MHz 
    while(CLKCONSTA & 0x40);    //�Ⱦ����ȶ�
}
/****************************
//��ʼ��LED����IO�ڳ���
*****************************/
void InitLEDIO(void)
{
    P1DIR |= 0x13;  //P10��P11��P14����Ϊ���
    RLED = 0;
    GLED = 0;
    YLED = 0;	   //LED�Ƴ�ʼ��Ϊ��    
}
/****************************
T3��ʼ��
****************************/
void InitT3(void)
{
  T3CCTL0 = 0X44;        // T3CCTL0 (0xCC)��CH0 �ж�ʹ�ܣ�CH0 �Ƚ�ģʽ
  T3CC0 = 0xFA;          // T3CC0����Ϊ250
  T3CTL |= 0x9A;         // ����T3������������ʱ��Ϊ16��Ƶ��ʹ��MODULOģʽ
  IEN1 |= 0X08;     
  IEN0 |= 0X80;          //�����жϣ���T3�ж�
}
/*****************************************
 ���ڳ�ʼ����������ʼ������ UART0		
*****************************************/
void InitUART0(void)
{
	PERCFG = 0x00;				 //λ��1 P0��
	P0SEL = 0x3c;				 //P0��������
	
	P2DIR &= ~0XC0;                           //P0������ΪUART0    
        U0CSR |= 0x80;   	                  //��������ΪUART��ʽ
        U0GCR |= 11;				
        U0BAUD |= 216;		                  //��������Ϊ115200

	UTX0IF = 1;                               //UART0 TX�жϱ�־��ʼ��λ1  
        U0CSR |= 0X40;				  //�������
        IEN0 |= 0x84;				  //�����жϣ������ж�

}




/****************************************************************
  ��ʱ����				
****************************************************************/
void Delay(uint n)
{
	uint i,j;
        for(j=0; j<10; j++)
        {
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n; i++);
        }
}





