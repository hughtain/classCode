#include "OSAL.h"
#include "AF.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "ZDProfile.h"

//#include "GenericApp.h"   
#include "DebugTrace.h"

#include "Coordinator.h"                        //add

#if !defined( WIN32 )
  #include "OnBoard.h"
#endif

/* HAL */
#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_uart.h"

#define SEND_DATA_EVENT 0x01

// This list should be filled with Application specific Cluster IDs.
const cId_t GenericApp_ClusterList[GENERICAPP_MAX_CLUSTERS] =
{
  GENERICAPP_CLUSTERID  
};

const SimpleDescriptionFormat_t GenericApp_SimpleDesc =//简单设备描述符
{
  GENERICAPP_ENDPOINT,              //  int Endpoint;
  GENERICAPP_PROFID,                //  uint16 AppProfId[2];
  GENERICAPP_DEVICEID,              //  uint16 AppDeviceId[2];
  GENERICAPP_DEVICE_VERSION,        //  int   AppDevVer:4;
  GENERICAPP_FLAGS,                 //  int   AppFlags:4;
  GENERICAPP_MAX_CLUSTERS,          //  byte  AppNumInClusters;
  (cId_t *)GenericApp_ClusterList,  //  byte *pAppInClusterList;
  0,          //  改 byte  AppNumInClusters;
  (cId_t *)NULL   //  改 byte *pAppInClusterList;
};

// This is the Endpoint/Interface description.  It is defined here, but
// filled-in in GenericApp_Init().  Another way to go would be to fill
// in the structure here and make it a "const" (in code space).  The
// way it's defined in this sample app it is define in RAM.
endPointDesc_t GenericApp_epDesc;//节点描述符
devStates_t GenericApp_NwkState;
/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */
byte GenericApp_TaskID;   // Task ID for internal task/event processing任务优先级
                          // This variable will be received when
                          // GenericApp_Init() is called.


byte GenericApp_TransID;  // This is the unique message ID (counter)数据发送序列号
unsigned char uartbuf[128];
unsigned char uartbuf2[128] = "wrong";
void check();

/*********************************************************************
 * LOCAL FUNCTIONS
 */
void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pkt ); //消息处理函数
void GenericApp_SendTheMessage( void );//数据发送函数
static void rxCB(uint8 port,uint8 event);

/*********************************************************************
 * NETWORK LAYER CALLBACKS
 */

/*********************************************************************
 * PUBLIC FUNCTIONS
 */


void GenericApp_Init( byte task_id )//任务初始化函数
{
  halUARTCfg_t uartConfig;
  GenericApp_TaskID = task_id;
  GenericApp_TransID = 0;//发送序列包置零，每发送一个包，序列自加一

  // Device hardware initialization can be added here or in main() (Zmain.c).
  // If the hardware is application specific - add it here.
  // If the hardware is other parts of the device add it in main().

 
  GenericApp_epDesc.endPoint = GENERICAPP_ENDPOINT;
  GenericApp_epDesc.task_id = &GenericApp_TaskID;
  GenericApp_epDesc.simpleDesc
            = (SimpleDescriptionFormat_t *)&GenericApp_SimpleDesc;
  GenericApp_epDesc.latencyReq = noLatencyReqs;

  // Register the endpoint description with the AF
  afRegister( &GenericApp_epDesc );//节点注册，注册后才能使用OSAL提供的系统服务
  
  uartConfig.configured   =TRUE;
  uartConfig.baudRate     =HAL_UART_BR_115200;
  uartConfig.flowControl  =FALSE;
  uartConfig.callBackFunc =rxCB;
  HalUARTOpen(0,&uartConfig);
  // Register for all key events - This app will handle all key events

  P1DIR |= 0x11;   //P1.4定义为输出口，即P0_4
  P1_1=1;
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
        case AF_INCOMING_MSG_CMD://是指的收到从其他节点应用层发给自己的数据包
          HalLedBlink(HAL_LED_1,0,50,800);
          GenericApp_MessageMSGCB( MSGpkt );
          break;
        case ZDO_STATE_CHANGE:  //网络状态发生变化
          GenericApp_NwkState = (devStates_t)(MSGpkt->hdr.status);
          if (GenericApp_NwkState == DEV_ZB_COORD )//
          {  // HalLedBlink(HAL_LED_1,0,50,800);

            // Start sending "the" message in a regular interval.
            //GenericApp_SendTheMessage();
            //osal_start_timerEx(GenericApp_TaskID,SEND_DATA_EVENT,5000);
          }
          break;
        default:
          break;
      }

      // Release the memory
      osal_msg_deallocate( (uint8 *)MSGpkt );//释放内存

      // Next
      MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( GenericApp_TaskID );
    }

    // return unprocessed events
    return (events ^ SYS_EVENT_MSG);
  }
  /* if(events & SEND_DATA_EVENT)
  {
    // check();
    //GenericApp_SendTheMessage();
    //osal_start_timerEx(GenericApp_TaskID,SEND_DATA_EVENT,2000);
    return(events^SEND_DATA_EVENT);
  
  }*/

  // Discard unknown events
  return 0;
}

//unsigned char buffer[20]={'1','2','3','4'};
static void rxCB(uint8 port,uint8 event) //串口接受到数据就调用回调函数
{ 
  HalUARTRead(0,uartbuf,2);
  if(uartbuf[0] == 't'&&uartbuf[1]=='r')
  { 
    //HalLedBlink(HAL_LED_1,0,50,800);
   GenericApp_SendTheMessage();
  }
  else if(uartbuf[0] == 'f'&&uartbuf[1]=='a')
  { 
    GenericApp_SendTheMessage();
  }
  //GenericApp_SendTheMessage();
}

void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pkt )//消息处理
{
  unsigned char buffer[20];
  HalLedBlink(HAL_LED_1,0,50,800);
  switch ( pkt->clusterId )
  {
    case GENERICAPP_CLUSTERID:
      // "the" message
     
      osal_memcpy(buffer,pkt->cmd.Data,20);//将数据拷贝到缓冲区
      HalUARTWrite(0, "T&H:", 4);
      // HalUARTWrite(0,"the light is:",13);
      HalUARTWrite(0,buffer,6);  //往串口写数据，送往PC
      HalUARTWrite(0, "\n",1);
      break;
  }
}

unsigned char data1[4]="true";        //存储发送字符串，节点1
unsigned char data2[5]="false";        //存储发送字符串，节点2

void GenericApp_SendTheMessage( void )
{ 
  
  //unsigned char *tmd;
  //osal_memcpy(tmd,uartbuf,1);
  if(uartbuf[1] == 'r')
  {
    afAddrType_t my_DstAddr;
    my_DstAddr.addrMode = (afAddrMode_t)AddrBroadcast;//设置为广播
    my_DstAddr.endPoint = GENERICAPP_ENDPOINT;
    my_DstAddr.addr.shortAddr = 0xFFFF;//0xffff是zd的网络地址
    AF_DataRequest( &my_DstAddr, &GenericApp_epDesc,
                       GENERICAPP_CLUSTERID,
                       osal_strlen("true") + 1,
                       (uint8*)&data1,
                       &GenericApp_TransID,
                       AF_DISCV_ROUTE, AF_DEFAULT_RADIUS );
  }
  else if(uartbuf[1]=='a')
  { 
    afAddrType_t my_DstAddr;
    my_DstAddr.addrMode = (afAddrMode_t)AddrBroadcast;//设置为广播
    my_DstAddr.endPoint = GENERICAPP_ENDPOINT;
    my_DstAddr.addr.shortAddr = 0xFFFF;//0xffff是zd的网络地址
    AF_DataRequest( &my_DstAddr, &GenericApp_epDesc,
                       GENERICAPP_CLUSTERID,
                       osal_strlen("12345") + 1,
                       (uint8*)data2,
                       &GenericApp_TransID,
                       AF_DISCV_ROUTE, AF_DEFAULT_RADIUS );
  
  }
  osal_memset(uartbuf,NULL,128);
}

