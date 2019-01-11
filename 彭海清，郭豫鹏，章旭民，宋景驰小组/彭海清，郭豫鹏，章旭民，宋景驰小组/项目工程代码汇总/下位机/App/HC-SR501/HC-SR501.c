#include "HC-SR501.h"


void HC_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//¶¨Òå½á¹¹Ìå±äÁ¿
	
	RCC_APB2PeriphClockCmd(HC_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=HC_PIN;  //Ñ¡ÔñÄãÒªÉèÖÃµÄIO¿Ú
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;	 //ÉèÖÃÍÊäÈëÏÂÀ­Ä£Ê½Ä£Ê½
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //ÉèÖÃ´«ÊäËÙÂÊ
	GPIO_Init(HC_PORT,&GPIO_InitStructure); 	   /* ³õÊ¼»¯GPIO */
	
	
}
