/**************************************/
/*           WeBee团队                 */
/*         Zigbee学习例程              */
/*例程名称：串口通讯2                  */
/*建立时间：2012/06/11                 */
/*描述：通过内部AD控制把温度信息通过
        串口发送给上位机,部分芯片误差
        较大，需要校准。手摸着芯片，温度
        明显变大。
**************************************/
#ifndef _IICLight_H_
#define _IICLight_H_
#define uchar unsigned char
#define   uint unsigned int

extern char Light[4];
extern char  BUF[1];

extern char  ge,shi,bai,qian,wan;            //显示变量




#define          SlaveAddress   0x46 


#define  IIC_WRITE      0                 // WRITE direction bit
#define  IIC_READ       1                 // READ direction bit
#define  TRUE  1
#define  FALSE 0


#define SCL P1_2
#define SDA P1_3

//定义延时函数
extern void Delay_1u(unsigned int times);
extern void Delay_1ms(unsigned int times);
extern void Delay_1s(unsigned int times);
extern void Delay5us(void);

//定义其他函数
extern void initTempSensor(void);
extern float getTemperature(void);
extern void lightinit(void) ;
extern void conversion(uint temp_data) ;
extern void WriteSDA1(void);
extern void WriteSDA0(void);
extern void WriteSCL1(void);
extern void WriteSCL0(void);
extern void ReadSDA(void);
extern void BH1750_Start(void);
extern void BH1750_Stop(void);
extern void BH1750_SendACK(uchar ack);
extern uchar BH1750_RecvACK(void);
extern void SEND_0_1(void);
extern void SEND_1_1(void);
 extern  void BH1750_SendByte(uchar dat);
 extern  uchar BH1750_RecvByte(void);
extern  void Single_Write_BH1750(uchar REG_Address);
 extern unsigned char Single_Read_BH1750(void);
extern unsigned short int getlight(void);

#endif