//×¢ï¿½â£ºï¿½Ä¼ï¿½hal_board_cfg.h ï¿½ï¿½2017 5 12ï¿½Þ¸ï¿½ï¿½Ë£ï¿½
//HAL_KEY



#include "OSAL.h"
#include "AF.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "ZDProfile.h"
#include "B_LUX_V22.h"
//#include "GenericApp.h"
#include "DebugTrace.h"
#include "DHT11.h"
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

//typedef unsigned char uchar;
//typedef unsigned int  uint;

#define LED1 P1_0       // P1.1ï¿½Ú¿ï¿½ï¿½ï¿½LED1   ??????
//#define KEY1 P0_3       // P0.4ï¿½Ú¿ï¿½ï¿½ï¿½S1,ï¿½Ã²ï¿½ï¿½ï¿½

#define TX_SIZE    20

unsigned char buffer[8] = "";

void GenericApp_SendLight( void );
void SampleApp_Send_P2P_Message( void );
void DelayMS(unsigned int msec);
/****************************************************************************
* ï¿½ï¿½    ï¿½ï¿½: DelayMS()
* ï¿½ï¿½    ï¿½ï¿½: ï¿½Ôºï¿½ï¿½ï¿½Îªï¿½ï¿½Î»ï¿½ï¿½Ê±ï¿½ï¿½ÏµÍ³Ê±ï¿½Ó²ï¿½ï¿½ï¿½ï¿½ï¿½Ê±Ä¬ï¿½ï¿½Îª16M(ï¿½ï¿½Ê¾ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½àµ±ï¿½ï¿½È·)
* ï¿½ï¿½ï¿½Ú²ï¿½ï¿½ï¿½: msec ï¿½ï¿½Ê±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÖµÔ½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê±Ô½ï¿½ï¿½
* ï¿½ï¿½ï¿½Ú²ï¿½ï¿½ï¿½: ï¿½ï¿½
****************************************************************************/
void DelayMS(unsigned int msec)
{
    unsigned int i,j;

    for (i=0; i<msec; i++)
        for (j=0; j<535; j++);
}

/****************************************************************************
* ï¿½ï¿½    ï¿½ï¿½: InitLed()
* ï¿½ï¿½    ï¿½ï¿½: ï¿½ï¿½ï¿½ï¿½LEDï¿½ï¿½ï¿½ï¿½Ó¦ï¿½ï¿½IOï¿½ï¿½
* ï¿½ï¿½ï¿½Ú²ï¿½ï¿½ï¿½: ï¿½ï¿½
* ï¿½ï¿½ï¿½Ú²ï¿½ï¿½ï¿½: ï¿½ï¿½
****************************************************************************/
void InitLed(void)
{
  //  P1DIR |= 0x11;   
    P1_1=0;           
    LED1 = 1;        
}

/****************************************************************************
* ï¿½ï¿½    ï¿½ï¿½: InitKey()
* ï¿½ï¿½    ï¿½ï¿½: ï¿½ï¿½ï¿½ï¿½KEYï¿½ï¿½Ó¦ï¿½ï¿½IOï¿½ï¿½,ï¿½ï¿½ï¿½ï¿½ï¿½Ð¶Ï·ï¿½Ê½
* ï¿½ï¿½ï¿½Ú²ï¿½ï¿½ï¿½: ï¿½ï¿½
* ï¿½ï¿½ï¿½Ú²ï¿½ï¿½ï¿½: ï¿½ï¿½
****************************************************************************/
/*void InitKey()   //12ï¿½ï¿½8ï¿½ï¿½ï¿½Þ¸ï¿½
{
  P0IEN |= 0X0f; 
  PICTL |= 0X01; 
  IEN1 |= 0Xff;   
  P0IFG = 0x00;   
  EA = 1;        
  P2DIR  =0xFE;
  P2SEL  =0xFE;


}*/




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
  (cId_t *)NULL,   // byte *pAppInClusterList;
  GENERICAPP_MAX_CLUSTERS,          //  byte  AppNumInClusters;
  (cId_t *)GenericApp_ClusterList,  //  byte *pAppInClusterList;

};

// This is the Endpoint/Interface description.  It is defined here, but
// filled-in in GenericApp_Init().  Another way to go would be to fill
// in the structure here and make it a "const" (in code space).  The
// way it's defined in this sample app it is define in RAM.
endPointDesc_t GenericApp_epDesc;
byte GenericApp_TaskID;
byte GenericApp_TransID;  // This is the unique message ID (counter)

devStates_t GenericApp_NwkState;
void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pckt );
void GenericApp_SendTheMessage( void );

void GenericApp_Init( byte task_id )
{
  GenericApp_TaskID = task_id;
  GenericApp_NwkState = DEV_INIT;

  GenericApp_epDesc.endPoint = GENERICAPP_ENDPOINT;
  GenericApp_epDesc.task_id = &GenericApp_TaskID;
  GenericApp_epDesc.simpleDesc
            = (SimpleDescriptionFormat_t *)&GenericApp_SimpleDesc;
  GenericApp_epDesc.latencyReq = noLatencyReqs;
  P0SEL &= 0x7f; 
  // Register the endpoint description with the AF
  afRegister( &GenericApp_epDesc );
  //B_LUX_Init();
  //LockInit();
  //InitLed();  
 //   InitKey();  

}

UINT16 GenericApp_ProcessEvent( byte task_id, UINT16 events )
{
  afIncomingMSGPacket_t *MSGpkt;
  //afDataConfirm_t *afDataConfirm;

  // Data Confirmation message fields
  //byte sentEP;
  //ZStatus_t sentStatus;
  //byte sentTransID;       // This should match the value sent
  //(void)task_id;  // Intentionally unreferenced parameter

  if ( events & SYS_EVENT_MSG )
  {
    MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( GenericApp_TaskID );
    while ( MSGpkt )
    {
      switch ( MSGpkt->hdr.event )
      {
        case AF_INCOMING_MSG_CMD:
           GenericApp_MessageMSGCB( MSGpkt );
          break;
        case ZDO_STATE_CHANGE: 
          GenericApp_NwkState = (devStates_t)(MSGpkt->hdr.status);
          if (GenericApp_NwkState == DEV_END_DEVICE )//
          {
            osal_set_event(GenericApp_TaskID,SEND_DATA_EVENT);
            // Start sending "the" message in a regular interval.
            //GenericApp_SendTheMessage();
            //osal_start_timerEx(GenericApp_TaskID,SEND_DATA_EVENT,5000);
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
   
    SampleApp_Send_P2P_Message();
    osal_start_timerEx(GenericApp_TaskID,SEND_DATA_EVENT,2000);
    return(events^SEND_DATA_EVENT);

  }
  // Discard unknown events
  return 0;
}

unsigned char theMessageData[20];




void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pkt )//ÖÕ¶ËÏûÏ¢´¦Àíº¯Êý
{

  switch (pkt->clusterId)
  {
    case GENERICAPP_CLUSTERID:

      osal_memcpy(buffer,pkt->cmd.Data,2);
      if(buffer[0]=='t' && buffer[1]=='r')
      { 
        HalLedBlink(HAL_LED_1,0,50,200);
        P1_2 = 0;//Ëø¿ª
      }
      if(buffer[0]=='f'&&buffer[1]=='a')
      { 
        HalLedBlink(HAL_LED_1,0,50,1000);
        P1_2 = 1;//Ëø¹Ø
      }
      break;
  }
}
void SampleApp_Send_P2P_Message( void )
{
  char temp[3], humidity[3], strTemp[7];
  
  DHT11();             //»ñÈ¡ÎÂÊª¶È

  //½«ÎÂÊª¶ÈµÄ×ª»»³É×Ö·û´®,¹©LCDÏÔÊ¾  
  temp[0] = wendu_shi+0x30;
  temp[1] = wendu_ge+0x30;
  temp[2] = '\0';
  humidity[0] = shidu_shi+0x30;
  humidity[1] = shidu_ge+0x30;
  humidity[2] = '\0';
  //½«Êý¾ÝÕûºÏºó·½±ã·¢¸øÐ­µ÷Æ÷ÏÔÊ¾
  osal_memcpy(strTemp, temp, 2); 
  osal_memcpy(&strTemp[2], "  ", 2);
  osal_memcpy(&strTemp[4], humidity, 3);
  
  //»ñµÃµÄÎÂÊª¶ÈÍ¨¹ý´®¿ÚÊä³öµ½µçÄÔÏÔÊ¾
  HalUARTWrite(0, "T&H:", 4);
  HalUARTWrite(0, (uint8 *)strTemp, 6);
  HalUARTWrite(0, "\n",1);
  
  //Êä³öµ½LCDÏÔÊ¾

  afAddrType_t my_DstAddr;
  my_DstAddr.addrMode = (afAddrMode_t)Addr16Bit;
  my_DstAddr.endPoint = GENERICAPP_ENDPOINT;
  my_DstAddr.addr.shortAddr = 0x0000;
  if ( AF_DataRequest( &my_DstAddr, &GenericApp_epDesc,
                       0x0001,
                       6,
                       (uint8 *)strTemp,
                       &GenericApp_TransID,
                       AF_DISCV_ROUTE,
                       AF_DEFAULT_RADIUS ) == afStatus_SUCCESS )
  {

  }
  else
  {
    // Error occurred in request to send.
  }
}

/*void mode(void)
{ char comp[4]="0000";

  uint32 vLux = 0;
  uint32 vTemp = 0;
  vLux=B_LUX_GetLux();
  vTemp = vLux;
  theMessageData[0] = ( (vLux/100000)+0x30 );
  vTemp = vLux%100000;
  theMessageData[1] = ( (vTemp/10000)+0x30 );
  vTemp = vTemp%10000;
  theMessageData[2] = ( (vTemp/1000)+0x30);
  vTemp = vTemp%1000;
  theMessageData[3] =( (vTemp/100)+0x30);
  vTemp = vTemp%100;
  theMessageData[4] = ( (vTemp/10)+0x30);
  vTemp = vTemp%10;
  theMessageData[5] =( vTemp+0x30);
  
  theMessageData[6] = 'N';
  if(P2_0 == 0){
    theMessageData[6] = 'Y';
    if(osal_memcmp(theMessageData,comp,4))
      {
       HalLedBlink(HAL_LED_1,0,50,800); //led on
      }
    
  }
  else
    HalLedSet(HAL_LED_1,HAL_LED_MODE_OFF);//ÃðµÆ
  
  afAddrType_t my_DstAddr;
  my_DstAddr.addrMode = (afAddrMode_t)Addr16Bit;
  my_DstAddr.endPoint = GENERICAPP_ENDPOINT;
  my_DstAddr.addr.shortAddr = 0x0000;
  AF_DataRequest( &my_DstAddr, 
              &GenericApp_epDesc,
                    0x0001,
                    osal_strlen("1234567") + 1,
                    (uint8*)&theMessageData,
                    &GenericApp_TransID, 
                    AF_DISCV_ROUTE, AF_DEFAULT_RADIUS );
}

*/
/*#pragma vector = P0INT_VECTOR   
__interrupt void P0_ISR(void) 
{
    DelayMS(200);    
    LED3 = ~LED3;    
    P0IFG = 0;       
    P0IF = 0;        


    GenericApp_SendTheMessage();
  GenericApp_SendTheMessage();

}
*/


/*void GenericApp_SendLight( void )
{ 
  uint32 vLux = 0;
  uint32 vTemp = 0;
  vLux=B_LUX_GetLux();
  vTemp = vLux;
  theMessageData[0] = ( (vLux/100000)+0x30 );
  vTemp = vLux%100000;
  theMessageData[1] = ( (vTemp/10000)+0x30 );
  vTemp = vTemp%10000;
  theMessageData[2] = ( (vTemp/1000)+0x30);
  vTemp = vTemp%1000;
  theMessageData[3] =( (vTemp/100)+0x30);
  vTemp = vTemp%100;
  theMessageData[4] = ( (vTemp/10)+0x30);
  vTemp = vTemp%10;
  theMessageData[5] =( vTemp+0x30);
  HalLedBlink(HAL_LED_1,0,50,500);

  afAddrType_t my_DstAddr;
  my_DstAddr.addrMode = (afAddrMode_t)Addr16Bit;
  my_DstAddr.endPoint = GENERICAPP_ENDPOINT;
  my_DstAddr.addr.shortAddr = 0x0000;
  AF_DataRequest( &my_DstAddr, 
                 &GenericApp_epDesc,
                       0x0001,
                       osal_strlen("123456")+1,
                       (uint8*)&theMessageData,
                       &GenericApp_TransID,
                       AF_DISCV_ROUTE, AF_DEFAULT_RADIUS );
}*/
