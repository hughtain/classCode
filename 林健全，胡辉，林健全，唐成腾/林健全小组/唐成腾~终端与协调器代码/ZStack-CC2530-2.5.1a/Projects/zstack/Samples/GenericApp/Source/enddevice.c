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
  PROVIDED �AS IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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

#define DATA_PIN_AO HAL_ADC_CHANNEL_6        //����ͨ��6Ϊģ������ڣ���P0_6��
#define DATA_PIN_DO P1_5        //����P1.5��Ϊ������DO�����
#define ID 0x01
/*********************************************************************
 * GLOBAL VARIABLES
 */
// This list should be filled with Application specific Cluster IDs.
const cId_t GenericApp_ClusterList[GENERICAPP_MAX_CLUSTERS] =
{
  GENERICAPP_CLUSTERID
};
//��ʼ���˿�������
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
endPointDesc_t GenericApp_epDesc;//�ڵ�������

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */
byte GenericApp_TaskID;   //�������ȼ�  
                          // Task ID for internal task/event processing
                          // This variable will be received when
                          // GenericApp_Init() is called.
devStates_t GenericApp_NwkState;


byte GenericApp_TransID; //���ݷ������к�  
                         // This is the unique message ID (counter)

afAddrType_t GenericApp_DstAddr;

devStates_t GenericApp_NwkState;//����ڵ�״̬

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
//�����ʼ������ 
void GenericApp_Init( uint8 task_id )
{
 
  GenericApp_TaskID = task_id;//��ʼ���������ȼ�
  GenericApp_NwkState = DEV_INIT;//��ʼ��ΪDEV_INIT,��ڵ�û�����ӵ�ZigBee����
  GenericApp_TransID = 0;//�������ݰ������кų�ʼ��Ϊ0
  //�Խڵ����������г�ʼ�� 
  GenericApp_epDesc.endPoint = GENERICAPP_ENDPOINT;
  GenericApp_epDesc.task_id = &GenericApp_TaskID;
  GenericApp_epDesc.simpleDesc
            = (SimpleDescriptionFormat_t *)&GenericApp_SimpleDesc;
  GenericApp_epDesc.latencyReq = noLatencyReqs;
  //afRegister()�������ڵ�����������ע�ᣬע���ſ���ʹ��OSAL�ṩ��ϵͳ����  
  // Register the endpoint description with the AF
  afRegister( &GenericApp_epDesc );
  
  //��ʼ��DO(P1_5)��
  P1DIR &= ~0x20;          //P1.5����Ϊ����� 
  P1INP &=~0x20;  
  P2INP |= 0x40;  //����
  P0DIR |= 0x80;          //P1.5����Ϊ����� 
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
//��Ϣ������
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
       

       
        case ZDO_STATE_CHANGE://��������󣬼������� 
          GenericApp_NwkState = (devStates_t)(MSGpkt->hdr.status);//��ȡ�ڵ���豸����  
          if ( (GenericApp_NwkState == DEV_ZB_COORD)
              || (GenericApp_NwkState == DEV_ROUTER)
              || (GenericApp_NwkState == DEV_END_DEVICE) )
          {
             HalLedBlink(HAL_LED_1,0,50,500);    //�Ѽ���LED1 ��˸����⣩ 
             
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
     HalLedBlink(HAL_LED_2,0,50,500);    //���һ���͵�����LED2 ��˸ ����⣩  
  
     sendTemp();
     sendTuRang();
     sendLight();
     
   osal_start_timerEx(GenericApp_TaskID,SEND_DATA_EVENT,5000);//��ʱ5000ms
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
  
   rftx.BUF.value[0]='T';//��ʾ�¶�����
   rftx.BUF.value[1]=wendu_shi+'0';
   rftx.BUF.value[2]=wendu_ge+'0';
   
    rftx.BUF.value[3]='H'; //��ʾʪ������ 
    rftx.BUF.value[4]=shidu_shi+'0';
    rftx.BUF.value[5]=shidu_ge+'0';
   
     
     osal_memcpy(rftx.BUF.head,"&&",2);
      rftx.BUF.deviceID[0]='I'; 
       rftx.BUF.deviceID[1]='D'; 
        rftx.BUF.deviceID[2]=ID+'0'; 
     nwk=NLME_GetShortAddr();//�ú������ظýڵ�������ַ
     To_string(rftx.BUF.myNWK,(uint8 *)&nwk,2);
     //ʹ�����ַ��16������ʽ���������
    
     
     afAddrType_t my_DstAddr;
     my_DstAddr.addrMode=(afAddrMode_t)Addr16Bit;//����Ϊ����
      my_DstAddr.endPoint=GENERICAPP_ENDPOINT;
       my_DstAddr.addr.shortAddr=0x0000;//0x0000��Э�����������ַ
       AF_DataRequest(&my_DstAddr,//�����˽ڵ�������ַ���������ݵĸ�ʽ�絥���ಥ
                      &GenericApp_epDesc,//�˿ں�
                       GENERICAPP_WENSHI_CLUSTERID ,//�����2
                      15,//���͵ĳ���
                      (uint8 *)&rftx,//��ŷ��͵�����
                      &GenericApp_TransID,//�������кţ����Լ�1�������ж��Ƿ񶪰�
                      AF_DISCV_ROUTE,
                      AF_DEFAULT_RADIUS
                      );
     
    //HalLedBlink(HAL_LED_2,0,50,500);
}

void sendTuRang(void)
{
    RFTX rftx;
    uint16 nwk;
 //   byte data_do=0;  //DO�ڵ�ƽ
    uint16 temp=0;//�ٷֱȵ�����ֵ
    byte str_adc[20]={0};//����ʪ�Ȱٷֱ��ַ���
    float vol=0.0; //adc������ѹ  
    byte len=19;
    uint16 adc= HalAdcRead(DATA_PIN_AO, HAL_ADC_RESOLUTION_14); //ADC����ֵ

    osal_memset(str_adc, 0, len);
    
    //������ֵ8192(��Ϊ���λ�Ƿ���λ)
    if(adc>=8192)
    {
        sprintf(str_adc, "error");
        len=5;
    }
    else
    { 
        adc=8192-adc;
        //����һ�£���Ϊ��ʪ��ʱAO������ϸߵ�ƽ,��ʪ��ʱAO������ϵ͵�ƽ   
        
        //ת��Ϊ�ٷֱ�
        vol=(float)((float)adc)/8192.0;
               
        //ȡ�ٷֱ���λ����
        temp=vol*100; //�Ӹ��㵽��������ʽת��
    }   
        //��ɿ��ӵ��ַ����  
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
                      GENERICAPP_TURANG_CLUSTERID ,//�����3
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
    temp_data=temp_data%10000;   //ȡ������
    qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //ȡ������
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //ȡ������
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //ȡ������
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
                      GENERICAPP_GUANG_CLUSTERID,//�����4
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