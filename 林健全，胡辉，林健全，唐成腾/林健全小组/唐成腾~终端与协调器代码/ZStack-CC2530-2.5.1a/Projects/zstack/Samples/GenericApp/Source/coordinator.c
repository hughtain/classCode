
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

#if !defined( WIN32 )
  #include "OnBoard.h"
#endif

/* HAL */
#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_uart.h"
#include "OSAL_Nv.h"
#include "aps_groups.h"
#include"IICLight.h"
#define SEND_TO_ALL_EVENT 0x01


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
  GENERICAPP_MAX_CLUSTERS,          //  byte  AppNumInClusters;
  (cId_t *)GenericApp_ClusterList,  //  byte *pAppInClusterList;
  0   ,   //  byte  AppNumInClusters;
  (cId_t *)NULL   //  byte *pAppInClusterList;
};

// This is the Endpoint/Interface description.  It is defined here, but
// filled-in in GenericApp_Init().  Another way to go would be to fill
// in the structure here and make it a "const" (in code space).  The
// way it's defined in this sample app it is define in RAM.
endPointDesc_t GenericApp_epDesc;

byte GenericApp_TaskID;   // Task ID for internal task/event processing
                          // This variable will be received when
                          // GenericApp_Init() is called.
devStates_t GenericApp_NwkState;


byte GenericApp_TransID;  // This is the unique message ID (counter)


/*********************************************************************
 * LOCAL FUNCTIONS
 */

 void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pckt );
 void GenericApp_SendTheMessage( void );
 void rxCB(uint8 port,uint8 event);




void GenericApp_Init( byte task_id )
{
  GenericApp_TaskID = task_id;
  GenericApp_TransID = 0;


// Fill out the endpoint description.
  GenericApp_epDesc.endPoint = GENERICAPP_ENDPOINT;
  GenericApp_epDesc.task_id = &GenericApp_TaskID;
  GenericApp_epDesc.simpleDesc
            = (SimpleDescriptionFormat_t *)&GenericApp_SimpleDesc;
  GenericApp_epDesc.latencyReq = noLatencyReqs;  
// Register the endpoint description with the AF
  afRegister( &GenericApp_epDesc );
  
  
//初始化串口
   halUARTCfg_t uartConfig;//定义一个串口结构体
   uartConfig.configured             =TRUE;//串口配置为真
   uartConfig.baudRate               =HAL_UART_BR_9600;//波特率为9600
   uartConfig.flowControl            =FALSE;//流控制为假
   uartConfig.callBackFunc       =    NULL;
   HalUARTOpen(0,&uartConfig);// 打开串口0
  
 
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
        
        case AF_INCOMING_MSG_CMD:
          GenericApp_MessageMSGCB( MSGpkt );
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

 
  return 0;
}


/*********************************************************************
 * @fn      GenericApp_MessageMSGCB
 *
 * @brief   Data message processor callback.  This function processes
 *          any incoming data - probably from other devices.  So, based
 *          on cluster ID, perform the intended action.
 *
 * @param   none
 *
 * @return  none
 */
static void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pkt )
{
  RFTX rftx;
  unsigned char changeline[2]={0x0A,0x0D};
  switch ( pkt->clusterId )
  { 
       case GENERICAPP_WENSHI_CLUSTERID://节点数据
       osal_memcpy(&rftx,pkt->cmd.Data,sizeof(rftx));
      // HalUARTWrite(0,"NWK:",4);
      // HalUARTWrite(0,&rftx.databuf[2],4);
      // HalUARTWrite(0," deviceID:",10);
      // HalUARTWrite(0,&rftx.databuf[8],1);
       HalUARTWrite(0," temp:",6);
       HalUARTWrite(0,&rftx.databuf[10],2);
       HalUARTWrite(0," hum:",5);
       HalUARTWrite(0,&rftx.databuf[13],2);
       HalUARTWrite(0,changeline,2);
        break;
      /*  case GENERICAPP_TURANG_CLUSTERID://节点数据
       osal_memcpy(&rftx,pkt->cmd.Data,sizeof(rftx));
       HalUARTWrite(0,"NWK:",4);
       HalUARTWrite(0,&rftx.databuf[2],4);
       HalUARTWrite(0," deviceID:",10);
       HalUARTWrite(0,&rftx.databuf[8],1);
       HalUARTWrite(0," soil:",6);
       HalUARTWrite(0,&rftx.databuf[10],2);
       HalUARTWrite(0,changeline,2);
       break;*/
      /* case GENERICAPP_GUANG_CLUSTERID://节点数据
       osal_memcpy(&rftx,pkt->cmd.Data,sizeof(rftx));
       HalUARTWrite(0,"NWK:",4);
       HalUARTWrite(0,&rftx.databuf[2],4);
       HalUARTWrite(0," deviceID:",10);
       HalUARTWrite(0,&rftx.databuf[8],1);
       HalUARTWrite(0," light:",7);
       HalUARTWrite(0,&rftx.databuf[10],5);
       HalUARTWrite(0,changeline,2);
       break;
*/
  }
}

