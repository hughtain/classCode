#include "OSAL.h"
#include "AF.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "ZDProfile.h"
#include <string.h>
#include <ioCC2530.h>
//#include "GenericApp.h"   
#include "DebugTrace.h"

#include "DH.h"  

#if !defined( WIN32 )
  #include "OnBoard.h"
#endif

/* HAL */
#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_uart.h"
unsigned char uartbuf[2];

// This list should be filled with Application specific Cluster IDs.
const cId_t GenericApp_ClusterList[GENERICAPP_MAX_CLUSTERS] =
{
  GENERICAPP_CLUSTERID  
};

const SimpleDescriptionFormat_t GenericApp_SimpleDesc =//���豸������
{
  GENERICAPP_ENDPOINT,              //  int Endpoint;
  GENERICAPP_PROFID,                //  uint16 AppProfId[2];
  GENERICAPP_DEVICEID,              //  uint16 AppDeviceId[2];
  GENERICAPP_DEVICE_VERSION,        //  int   AppDevVer:4;
  GENERICAPP_FLAGS,                 //  int   AppFlags:4;
  GENERICAPP_MAX_CLUSTERS,          //  byte  AppNumInClusters;
  (cId_t *)GenericApp_ClusterList,  //  byte *pAppInClusterList;
  0,          //  �� byte  AppNumInClusters;
  (cId_t *)NULL   //  �� byte *pAppInClusterList;
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
byte GenericApp_TaskID;   // Task ID for internal task/event processing�������ȼ�
                          // This variable will be received when
                          // GenericApp_Init() is called.


byte GenericApp_TransID;  // This is the unique message ID (counter)���ݷ������к�

 void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pckt ); //��Ϣ������
void GenericApp_SendTheMessage( void );//���ݷ��ͺ���
static void rxCB(uint8 port,uint8 event);


//static void rxCB(uint8 port,uint8 event);

void GenericApp_Init( byte task_id )//�����ʼ������
{
  halUARTCfg_t uartConfig;
  GenericApp_TaskID = task_id;
  GenericApp_TransID = 0;//�������а����㣬ÿ����һ�����������Լ�һ

  GenericApp_epDesc.endPoint = GENERICAPP_ENDPOINT;
  GenericApp_epDesc.task_id = &GenericApp_TaskID;
  GenericApp_epDesc.simpleDesc
            = (SimpleDescriptionFormat_t *)&GenericApp_SimpleDesc;
  GenericApp_epDesc.latencyReq = noLatencyReqs;

  // Register the endpoint description with the AF
  afRegister( &GenericApp_epDesc );//�ڵ�ע�ᣬע������ʹ��OSAL�ṩ��ϵͳ����

  uartConfig.configured   =TRUE;
  uartConfig.baudRate     =HAL_UART_BR_9600;
  uartConfig.flowControl  =FALSE;
  uartConfig.callBackFunc =rxCB;
  HalUARTOpen(0,&uartConfig);
}

static void rxCB(uint8 port,uint8 event)
{
    
    HalUARTRead(0,uartbuf,2);
   
    GenericApp_SendTheMessage();
    //HalLedBlink(HAL_LED_3,0,50,500);
}

UINT16 GenericApp_ProcessEvent( byte task_id, UINT16 events )
{
  afIncomingMSGPacket_t *MSGpkt;
  if ( events & SYS_EVENT_MSG )
  {
    MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( GenericApp_TaskID );
    while ( MSGpkt )
    {
      switch ( MSGpkt->hdr.event )
      {
        case AF_INCOMING_MSG_CMD://��ָ���յ��������ڵ�Ӧ�ò㷢���Լ������ݰ�
         
          GenericApp_MessageMSGCB( MSGpkt );
         // HalLedBlink(HAL_LED_3,0,50,500);
          break;
        default:
          break;
      }

     
      osal_msg_deallocate( (uint8 *)MSGpkt );//�ͷ��ڴ�

    
      MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( GenericApp_TaskID );
    }

 
    return (events ^ SYS_EVENT_MSG);
  }

  return 0;
}


void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pkt )//��Ϣ����
{
  unsigned char buffer[10];
  switch ( pkt->clusterId )
  {
    case GENERICAPP_CLUSTERID:
      // "the" message
       //HalLedBlink(HAL_LED_1,0,90,500);
      osal_memcpy(buffer,pkt->cmd.Data,5);//�����ݿ�����������
      // HalLedBlink(HAL_LED_1,0,90,500);
       
     HalUARTWrite(0,buffer,5);  //������д���ݣ�����PC
      HalLedBlink(HAL_LED_3,0,50,500);
    
      break;
  }
}



void GenericApp_SendTheMessage( void )
{
  //HalLedBlink(HAL_LED_1,0,50,800);
  afAddrType_t my_DstAddr;
  my_DstAddr.addrMode = (afAddrMode_t)AddrBroadcast;
  my_DstAddr.endPoint = GENERICAPP_ENDPOINT;
  my_DstAddr.addr.shortAddr = 0xFFFF;
  AF_DataRequest( &my_DstAddr, &GenericApp_epDesc,
                       GENERICAPP_CLUSTERID,
                       osal_strlen(uartbuf)+1,
                       uartbuf,
                       &GenericApp_TransID,
                       AF_DISCV_ROUTE, AF_DEFAULT_RADIUS );
  HalLedBlink(HAL_LED_1,0,50,800);

}
