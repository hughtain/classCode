#include <stdio.h>
#include "OSAL.h"
#include "AF.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "ZDProfile.h"
#include <string.h>
#include <ioCC2530.h>
//#include "GenericApp.h"   
#include "DebugTrace.h"

#include "Coordinator.h" 

#if !defined( WIN32 )
  #include "OnBoard.h"
#endif

/* HAL */
#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_uart.h"

#define SEND_DATA_EVENT 0x01

#define DATA_PIN P0_7

void Delay_us(void); //1 us��ʱ
void Delay_10us(void); //10 us��ʱ

void COM(void); // ��ʪд��
void DHT11(void) ;  //��ʪ��������


#define uchar unsigned char



//��ʪ�ȶ���
uchar shidu_shi,shidu_ge,wendu_shi,wendu_ge;
uchar ucharFLAG,uchartemp;

uchar ucharT_data_H,ucharT_data_L,ucharRH_data_H,ucharRH_data_L,ucharcheckdata;
uchar ucharT_data_H_temp,ucharT_data_L_temp,ucharRH_data_H_temp,ucharRH_data_L_temp,ucharcheckdata_temp;
uchar ucharcomdata;
//--------------------------------
//-----ʪ�ȶ�ȡ�ӳ��� ------------
//--------------------------------
//----���±�����Ϊȫ�ֱ���--------
//----�¶ȸ�8λ== U8T_data_H------
//----�¶ȵ�8λ== U8T_data_L------
//----ʪ�ȸ�8λ== U8RH_data_H-----
//----ʪ�ȵ�8λ== U8RH_data_L-----
//----У�� 8λ == U8checkdata-----
//----��������ӳ�������----------
//---- Delay();, Delay_10us();,COM(); 
//--------------------------------

//��ʱ����
void Delay_us() //1 us��ʱ
{

    MicroWait(1); 

}
void Delay_10us() //10 us��ʱ
{  
  MicroWait(10);
}

void Delay_ms(uint Time)//n ms��ʱ
{
    unsigned char i;
    while(Time--)
    {
        for(i=0;i<100;i++)
            Delay_10us();
    }
}

//��ʪ�ȴ���
void COM(void)    // ��ʪд��
{     
    uchar i;         
    for(i=0;i<8;i++)    
    {
        ucharFLAG=2; 
        while((!DATA_PIN)&&ucharFLAG++);
        Delay_10us();
        Delay_10us();
        Delay_10us();
        uchartemp=0;
        if(DATA_PIN)uchartemp=1;//�������30us��û��0��������Ϊ1����0��������Ϊ0
        ucharFLAG=2;
        while((DATA_PIN)&&ucharFLAG++); //�ȴ���0  
        if(ucharFLAG==1)break;    
        ucharcomdata<<=1;//ucharcomdata����һλ��ֵ��ucharcomdata
        ucharcomdata|=uchartemp;//������������Ǹ����λ��ֵ
    }    
}

void DHT11(void)   //��ʪ��������
{
    DATA_PIN=0;//�õ͵�ƽ
    Delay_ms(19);  //>18MS
    DATA_PIN=1; //�øߵ�ƽ����ʼ�źŷ��ͽ���
    P0DIR &= ~0x80; //��������IO�ڷ�������
    Delay_10us();
    Delay_10us();                        
    Delay_10us();
    Delay_10us();  //�ߵ�ƽ����ʱ40us�ȴ�
    if(!DATA_PIN) //�����ƽ��ͣ���֤����⵽��ʼ�ź�
    {
        ucharFLAG=2; 
        while((!DATA_PIN)&&ucharFLAG++);//�͵�ƽ���ȴ���Ӧ����
        ucharFLAG=2;
        while((DATA_PIN)&&ucharFLAG++); //�ߵ�ƽ��׼�����
        COM();
        ucharRH_data_H_temp=ucharcomdata;//ʪ�ȸ߰�λ
        COM();
        ucharRH_data_L_temp=ucharcomdata;//ʪ�ȵͰ�λ
        COM();
        ucharT_data_H_temp=ucharcomdata;//�¶ȸ߰�λ
        COM();
        ucharT_data_L_temp=ucharcomdata;//�¶ȵͰ�λ
        COM();
        ucharcheckdata_temp=ucharcomdata;//У���λ
        DATA_PIN=1; //�øߣ�����״̬
        uchartemp=(ucharT_data_H_temp+ucharT_data_L_temp+ucharRH_data_H_temp+ucharRH_data_L_temp);
        if(uchartemp==ucharcheckdata_temp)//У��
        {
            ucharRH_data_H=ucharRH_data_H_temp;
            ucharRH_data_L=ucharRH_data_L_temp;
            ucharT_data_H=ucharT_data_H_temp;
            ucharT_data_L=ucharT_data_L_temp;
            ucharcheckdata=ucharcheckdata_temp;
        }
        wendu_shi=ucharT_data_H/10; 
        wendu_ge=ucharT_data_H%10;
        
        shidu_shi=ucharRH_data_H/10; 
        shidu_ge=ucharRH_data_H%10;        
    } 
    else //û�óɹ���ȡ������0
    {
        wendu_shi=0; 
        wendu_ge=0;
        
        shidu_shi=0; 
        shidu_ge=0;  
    } 
    
    P0DIR |= 0x80; //IO����Ҫ�������� 
}

// This list should be filled with Application specific Cluster IDs.
const cId_t GenericApp_ClusterList[GENERICAPP_MAX_CLUSTERS] =
{
  GENERICAPP_CLUSTERID
};

const SimpleDescriptionFormat_t GenericApp_SimpleDesc =
{
  GENERICAPP_ENDPOINT,              //  int Endpoint;
  GENERICAPP_PROFID,                //  uint16 AppProfId[2];
  GENERICAPP_DEVICEID,              //  uint16 AppDeviceId[2];
  GENERICAPP_DEVICE_VERSION,        //  int   AppDevVer:4;
  GENERICAPP_FLAGS,                 //  int   AppFlags:4;
    0,
  (cId_t *)NULL,   //  �� byte *pAppInClusterList;
  GENERICAPP_MAX_CLUSTERS,          //  byte  AppNumInClusters;//�����ID�ĸ��� 
  (cId_t *)GenericApp_ClusterList,  //  byte *pAppInClusterList;

};

// This is the Endpoint/Interface description.  It is defined here, but
// filled-in in GenericApp_Init().  Another way to go would be to fill
// in the structure here and make it a "const" (in code space).  The
// way it's defined in this sample app it is define in RAM.
endPointDesc_t GenericApp_epDesc;
byte GenericApp_TaskID;   
byte GenericApp_TransID;  // This is the unique message ID (counter)

devStates_t GenericApp_NwkState;//���ڱ���ڵ�״̬��Ϣ

void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pckt );//��Ϣ������
void GenericApp_SendTheMessage( void );

void GenericApp_Init( byte task_id )
{
   
 
  
  GenericApp_TaskID = task_id;
  GenericApp_NwkState = DEV_INIT;//�ڵ�״̬��ʼ��ΪDEV_INIT����ʾδ���ӵ�zigbee��
  GenericApp_TransID = 0;
 
  GenericApp_epDesc.endPoint = GENERICAPP_ENDPOINT;
  GenericApp_epDesc.task_id = &GenericApp_TaskID;
  GenericApp_epDesc.simpleDesc
            = (SimpleDescriptionFormat_t *)&GenericApp_SimpleDesc;
  GenericApp_epDesc.latencyReq = noLatencyReqs;

}


UINT16 GenericApp_ProcessEvent( byte task_id, UINT16 events )
{
  afIncomingMSGPacket_t *MSGpkt;
  

  if ( events & SYS_EVENT_MSG )
  {
    MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( GenericApp_TaskID );
    //��ȡ�ڵ���豸����
    while ( MSGpkt )
    {
      switch ( MSGpkt->hdr.event )
      {
        
        case ZDO_STATE_CHANGE:
      case AF_INCOMING_MSG_CMD:
          
         GenericApp_MessageMSGCB(MSGpkt);
         
          GenericApp_NwkState = (devStates_t)(MSGpkt->hdr.status);
          if (GenericApp_NwkState == DEV_END_DEVICE )
         {
            // Start sending "the" message in a regular interval.
        
            GenericApp_SendTheMessage();
            osal_set_event(GenericApp_TaskID,SEND_DATA_EVENT);
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
  if(events & SEND_DATA_EVENT)
  {
    ///HalLedBlink(HAL_LED_1,0,50,500);
    GenericApp_SendTheMessage();
    //HalLedBlink(HAL_LED_1,0,50,500);
     //check();
     osal_start_timerEx(GenericApp_TaskID,SEND_DATA_EVENT,1500);//��ʱ1200ms
     return(events^SEND_DATA_EVENT);
  
  }
   //Discard unknown events
  return 0;
}

uchar wen[6];

 void GenericApp_SendTheMessage( void )
{
  
  afAddrType_t my_DstAddr;
 my_DstAddr.addrMode=(afAddrMode_t)Addr16Bit;
 my_DstAddr.endPoint=GENERICAPP_ENDPOINT;
 my_DstAddr.addr.shortAddr=0x0000;
 
 DHT11();

 wen[0]=wendu_shi+0x30;
 wen[1]=wendu_ge%10+0x30;
 wen[2]=':';
 wen[3]= shidu_shi+0x30;
 wen[4]=shidu_ge%10+0x30;
 
 AF_DataRequest( &my_DstAddr, &GenericApp_epDesc,
                       GENERICAPP_CLUSTERID,
                        osal_strlen(wen)+1, 
                       wen,
                      //theMessageData,
                       &GenericApp_TransID,
                       AF_DISCV_ROUTE, AF_DEFAULT_RADIUS);
  //HalLedBlink(HAL_LED_1,0,50,500);
 //HalLedBlink(HAL_LED_1,0,90,500);
  
  }

void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pkt )//��Ϣ����
{
  HalLedBlink(HAL_LED_1,0,50,500);
  unsigned char buffer[2];
  switch ( pkt->clusterId )
  {
    case GENERICAPP_CLUSTERID:
      // "the" message
      
      osal_memcpy(buffer,pkt->cmd.Data,1);//�����ݿ�����������
      
      if(buffer[0]=='2'){
        
        //HalLedBlink(HAL_LED_1,0,50,500);
        P2_0=1;
        P2_1=0;
      //HalLedBlink(HAL_LED_1,0,50,500);
        //osal_memcpy(theMessageData,"OFF",20);//�����ݿ�����������
      
      }
      else if(buffer[0]=='3'){
        P2_0=0;
        P2_1=0;
        HalLedBlink(HAL_LED_1,0,50,500);
      }
     //HalUARTWrite(0,buffer,20);
      break;
  }
  
}
