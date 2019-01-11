/******************************************************************************
  Filename:       GenericApp.c
  Revised:        $Date: 2012-03-07 01:04:58 -0800 (Wed, 07 Mar 2012) $
  Revision:       $Revision: 29656 $

  Description:    Generic Application (no Profile).


  Copyright 2004-2012 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License"). You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product. Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED 揂S IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
******************************************************************************/

/*********************************************************************
  This application isn't intended to do anything useful, it is
  intended to be a simple example of an application's structure.

  This application sends "Hello World" to another "Generic"
  application every 5 seconds.  The application will also
  receives "Hello World" packets.

  The "Hello World" messages are sent/received as MSG type message.

  This applications doesn't have a profile, so it handles everything
  directly - itself.

  Key control:
    SW1:
    SW2:  initiates end device binding
    SW3:
    SW4:  initiates a match description request
*********************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include "OSAL.h"
#include "AF.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "ZDProfile.h"
#include <string.h>
#include "Coordinator.h"
#include "DebugTrace.h"
#include<stdlib.h>

#if !defined( WIN32 )
  #include "OnBoard.h"
#endif

/* HAL */
#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_uart.h"
#include "hal_adc.h"
#include"stdio.h"
#include "DHT11.h" 
#include "IICLight.h" 

#define SEND_DATA_EVENT 0x01

#define DATA_PIN_AO HAL_ADC_CHANNEL_6        //定义通道6为模拟采样口，即P0_6。
#define DATA_PIN_DO P1_5        //定义P1.5口为传感器DO输入端
#define ID 0x01
/*********************************************************************
 * GLOBAL VARIABLES
 */
// This list should be filled with Application specific Cluster IDs.
const cId_t GenericApp_ClusterList[GENERICAPP_MAX_CLUSTERS] =
{
  GENERICAPP_CLUSTERID
};
//初始化端口描述符
const SimpleDescriptionFormat_t GenericApp_SimpleDesc =
{
  GENERICAPP_ENDPOINT,              //  int Endpoint;
  GENERICAPP_PROFID,                //  uint16 AppProfId[2];
  GENERICAPP_DEVICEID,              //  uint16 AppDeviceId[2];
  GENERICAPP_DEVICE_VERSION,        //  int   AppDevVer:4;
  GENERICAPP_FLAGS,                 //  int   AppFlags:4;
  0 ,       //  byte  AppNumInClusters;
  (cId_t *)NULL,  //  byte *pAppInClusterList;
  GENERICAPP_MAX_CLUSTERS,          //  byte  AppNumInClusters;
  (cId_t *)GenericApp_ClusterList   //  byte *pAppInClusterList;
};                                                                           

// This is the Endpoint/Interface description.  It is defined here, but
// filled-in in GenericApp_Init().  Another way to go would be to fill
// in the structure here and make it a "const" (in code space).  The
// way it's defined in this sample app it is define in RAM.
endPointDesc_t GenericApp_epDesc;//节点描述符

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */
byte GenericApp_TaskID;   //任务优先级  
                          // Task ID for internal task/event processing
                          // This variable will be received when
                          // GenericApp_Init() is called.
devStates_t GenericApp_NwkState;


byte GenericApp_TransID; //数据发送序列号  
                         // This is the unique message ID (counter)

afAddrType_t GenericApp_DstAddr;

devStates_t GenericApp_NwkState;//保存节点状态

//void SendInfo(void);
void To_string(uint8 *dest,char *src,uint8 length);
void sendTuRang(void);
void sendTemp(void);
void sendLight(void);

/*********************************************************************
 * @fn      GenericApp_Init
 *
 * @brief   Initialization function for the Generic App Task.
 *          This is called during initialization and should contain
 *          any application specific initialization (ie. hardware
 *          initialization/setup, table initialization, power up
 *          notificaiton ... ).
 *
 * @param   task_id - the ID assigned by OSAL.  This ID should be
 *                    used to send messages and set timers.
 *
 * @return  none
 */
//任务初始化函数 
void GenericApp_Init( uint8 task_id )
{
 
  GenericApp_TaskID = task_id;//初始化任务优先级
  GenericApp_NwkState = DEV_INIT;//初始化为DEV_INIT,表节点没有连接到ZigBee网络
  GenericApp_TransID = 0;//发送数据包的序列号初始化为0
  //对节点描述符进行初始化 
  GenericApp_epDesc.endPoint = GENERICAPP_ENDPOINT;
  GenericApp_epDesc.task_id = &GenericApp_TaskID;
  GenericApp_epDesc.simpleDesc
            = (SimpleDescriptionFormat_t *)&GenericApp_SimpleDesc;
  GenericApp_epDesc.latencyReq = noLatencyReqs;
  //afRegister()函数将节点描述符进行注册，注册后才可以使用OSAL提供的系统服务  
  // Register the endpoint description with the AF
  afRegister( &GenericApp_epDesc );
  
  //初始化DO(P1_5)口
  P1DIR &= ~0x20;          //P1.5定义为输入口 
  P1INP &=~0x20;  
  P2INP |= 0x40;  //下拉
  P0DIR |= 0x80;          //P1.5定义为输出口 
}
/*********************************************************************
 * @fn      GenericApp_ProcessEvent
 *
 * @brief   Generic Application Task event processor.  This function
 *          is called to process all events for the task.  Events
 *          include timers, messages and any other user defined events.
 *
 * @param   task_id  - The OSAL assigned task ID.
 * @param   events - events to process.  This is a bit map and can
 *                   contain more than one event.
 *
 * @return  none
 */
//消息处理函数
uint16 GenericApp_ProcessEvent( uint8 task_id, uint16 events )
{
  afIncomingMSGPacket_t *MSGpkt;


  if ( events & SYS_EVENT_MSG )
  {
    MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( GenericApp_TaskID );
    while ( MSGpkt )
    {
      switch ( MSGpkt->hdr.event )
      {
       

       
        case ZDO_STATE_CHANGE://加入网络后，加入族中 
          GenericApp_NwkState = (devStates_t)(MSGpkt->hdr.status);//读取节点的设备类型  
          if ( (GenericApp_NwkState == DEV_ZB_COORD)
              || (GenericApp_NwkState == DEV_ROUTER)
              || (GenericApp_NwkState == DEV_END_DEVICE) )
          {
             HalLedBlink(HAL_LED_1,0,50,500);    //已加入LED1 闪烁（检测） 
             
            // Start sending "the" message in a regular interval.
            osal_set_event( GenericApp_TaskID,
                                SEND_DATA_EVENT);
          }
          break;

        default:
          break;
      }

      // Release the memory
      osal_msg_deallocate( (uint8 *)MSGpkt );

      // Next
      MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( GenericApp_TaskID );
    }

    // return unprocessed events
    return (events ^ SYS_EVENT_MSG);
  }

  // Send a message out - This event is generated by a timer
  //  (setup in GenericApp_Init()).
  if ( events & SEND_DATA_EVENT )
  {
     HalLedBlink(HAL_LED_2,0,50,500);    //结果一发送到串口LED2 闪烁 （检测）  
  
     sendTemp();
     sendTuRang();
     sendLight();
     
   osal_start_timerEx(GenericApp_TaskID,SEND_DATA_EVENT,5000);//定时5000ms
    return (events ^ SEND_DATA_EVENT);
  }

  

  return 0;
}

void sendTemp(void)
{
  RFTX rftx;
 // uint16 tempvalue;
  uint16 nwk;
  DHT11_TEST();
  
   rftx.BUF.value[0]='T';//表示温度数据
   rftx.BUF.value[1]=wendu_shi+'0';
   rftx.BUF.value[2]=wendu_ge+'0';
   
    rftx.BUF.value[3]='H'; //表示湿度数据 
    rftx.BUF.value[4]=shidu_shi+'0';
    rftx.BUF.value[5]=shidu_ge+'0';
   
     
     osal_memcpy(rftx.BUF.head,"&&",2);
      rftx.BUF.deviceID[0]='I'; 
       rftx.BUF.deviceID[1]='D'; 
        rftx.BUF.deviceID[2]=ID+'0'; 
     nwk=NLME_GetShortAddr();//该函数返回该节点的网络地址
     To_string(rftx.BUF.myNWK,(uint8 *)&nwk,2);
     //使网络地址以16进制形式输出到串口
    
     
     afAddrType_t my_DstAddr;
     my_DstAddr.addrMode=(afAddrMode_t)Addr16Bit;//设置为单播
      my_DstAddr.endPoint=GENERICAPP_ENDPOINT;
       my_DstAddr.addr.shortAddr=0x0000;//0x0000是协调器的网络地址
       AF_DataRequest(&my_DstAddr,//包含了节点的网络地址，发送数据的格式如单播多播
                      &GenericApp_epDesc,//端口号
                       GENERICAPP_WENSHI_CLUSTERID ,//命令号2
                      15,//发送的长度
                      (uint8 *)&rftx,//存放发送的内容
                      &GenericApp_TransID,//发送序列号，会自加1，用于判断是否丢包
                      AF_DISCV_ROUTE,
                      AF_DEFAULT_RADIUS
                      );
     
    //HalLedBlink(HAL_LED_2,0,50,500);
}

void sendTuRang(void)
{
    RFTX rftx;
    uint16 nwk;
 //   byte data_do=0;  //DO口电平
    uint16 temp=0;//百分比的整数值
    byte str_adc[20]={0};//土壤湿度百分比字符串
    float vol=0.0; //adc采样电压  
    byte len=19;
    uint16 adc= HalAdcRead(DATA_PIN_AO, HAL_ADC_RESOLUTION_14); //ADC采样值

    osal_memset(str_adc, 0, len);
    
    //最大采样值8192(因为最高位是符号位)
    if(adc>=8192)
    {
        sprintf(str_adc, "error");
        len=5;
    }
    else
    { 
        adc=8192-adc;
        //反相一下，因为低湿度时AO口输出较高电平,高湿度时AO口输出较低电平   
        
        //转化为百分比
        vol=(float)((float)adc)/8192.0;
               
        //取百分比两位数字
        temp=vol*100; //从浮点到整数的隐式转换
    }   
        //变成可视的字符输出  
   rftx.BUF.value[0]='R';
   rftx.BUF.value[1]=temp/10+'0';
   rftx.BUF.value[2]=temp%10+'0';
   rftx.BUF.value[3]='%';
   rftx.BUF.value[4]='*';
   rftx.BUF.value[5]='*';
     osal_memcpy(rftx.BUF.head,"&&",2);
     
     nwk=NLME_GetShortAddr();
     To_string(rftx.BUF.myNWK,(uint8 *)&nwk,2);
     
    rftx.BUF.deviceID[0]='I'; 
       rftx.BUF.deviceID[1]='D'; 
        rftx.BUF.deviceID[2]=ID+'0'; 
     
     
     afAddrType_t my_DstAddr;
     my_DstAddr.addrMode=(afAddrMode_t)Addr16Bit;
      my_DstAddr.endPoint=GENERICAPP_ENDPOINT;
       my_DstAddr.addr.shortAddr=0x0000;
       AF_DataRequest(&my_DstAddr,&GenericApp_epDesc,
                      GENERICAPP_TURANG_CLUSTERID ,//命令号3
                      15,
                      (uint8 *)&rftx,
                      &GenericApp_TransID,
                      AF_DISCV_ROUTE,
                      AF_DEFAULT_RADIUS
                      );
     
    
}

void sendLight(void)
{
  RFTX rftx;
  uint16 wan,qian,bai,shi,ge;
  uint16 nwk;
   unsigned short int temp_data=getlight();
  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //取余运算
    qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data+0x30; 
    
   rftx.BUF.value[0]='S';
   rftx.BUF.value[1]=(unsigned char)wan;
   rftx.BUF.value[2]=(unsigned char)qian;
   rftx.BUF.value[3]=(unsigned char)bai;
   rftx.BUF.value[4]=(unsigned char)shi;  
   rftx.BUF.value[5]=(unsigned char)ge; 
    
     
     osal_memcpy(rftx.BUF.head,"&&",2);
     
     nwk=NLME_GetShortAddr();
     To_string(rftx.BUF.myNWK,(uint8 *)&nwk,2);
                
     
     rftx.BUF.deviceID[0]='I'; 
       rftx.BUF.deviceID[1]='D'; 
        rftx.BUF.deviceID[2]=ID+'0'; 
     
     
     
     afAddrType_t my_DstAddr;
     my_DstAddr.addrMode=(afAddrMode_t)Addr16Bit;
      my_DstAddr.endPoint=GENERICAPP_ENDPOINT;
       my_DstAddr.addr.shortAddr=0x0000;
       AF_DataRequest(&my_DstAddr,&GenericApp_epDesc,
                      GENERICAPP_GUANG_CLUSTERID,//命令号4
                      15,
                      (uint8 *)&rftx,
                      &GenericApp_TransID,
                      AF_DISCV_ROUTE,
                      AF_DEFAULT_RADIUS
                      );
     
    
}

void To_string(uint8 *dest,char * src,uint8 length)
{
  uint8 *xad;
  uint8 i=0;
  uint8 ch;
  xad=src+length-1;
  for(i=0;i<length;i++,xad--)
  {
    ch=(*xad>>4)&0x0F;
    dest[i<<1]=ch+((ch<10)?'0':'7');
    ch=*xad&0x0F;
    dest[(i<<1)+1]=ch+((ch<10)?'0':'7');
  }
}