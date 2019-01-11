#include "tftlcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"	 
#include "SysTick.h"	   


//LCDµÄ»­±ÊÑÕÉ«ºÍ±³¾°É«	   
u16 FRONT_COLOR=BLACK;	//»­±ÊÑÕÉ«
u16 BACK_COLOR=WHITE;  //±³¾°É« 

_tftlcd_data tftlcd_data; 
  

void TFTLCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG,ENABLE);//Ê¹ÄÜPORTD,E,GÊ±ÖÓ
	
 	//PORTD¸´ÓÃÍÆÍìÊä³ö  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD¸´ÓÃÍÆÍìÊä³ö  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //¸´ÓÃÍÆÍìÊä³ö   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure); 
  	 
	//PORTE¸´ÓÃÍÆÍìÊä³ö  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD¸´ÓÃÍÆÍìÊä³ö  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //¸´ÓÃÍÆÍìÊä³ö   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);    	    	 											 

   	//	//PORTG12¸´ÓÃÍÆÍìÊä³ö A10	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;	 //	//PORTG¸´ÓÃÍÆÍìÊä³ö  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //¸´ÓÃÍÆÍìÊä³ö   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure);  
	
}

void TFTLCD_FSMC_Init(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAMTimingInitTypeDef  FSMC_ReadTimingInitStructure; 
	FSMC_NORSRAMTimingInitTypeDef  FSMC_WriteTimingInitStructure;
	
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//Ê¹ÄÜFSMCÊ±ÖÓ
	

	FSMC_ReadTimingInitStructure.FSMC_AddressSetupTime = 0x01;	 //µØÖ·½¨Á¢Ê±¼ä£¨ADDSET£©Îª2¸öHCLK 1/36M=27ns
  	FSMC_ReadTimingInitStructure.FSMC_AddressHoldTime = 0x00;	 //µØÖ·±£³ÖÊ±¼ä£¨ADDHLD£©Ä£Ê½AÎ´ÓÃµ½	
  	FSMC_ReadTimingInitStructure.FSMC_DataSetupTime = 0x0f;		 // Êý¾Ý±£´æÊ±¼äÎª16¸öHCLK,ÒòÎªÒº¾§Çý¶¯ICµÄ¶ÁÊý¾ÝµÄÊ±ºò£¬ËÙ¶È²»ÄÜÌ«¿ì£¬ÓÈÆä¶Ô1289Õâ¸öIC¡£
  	FSMC_ReadTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_CLKDivision = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_DataLatency = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;	 //Ä£Ê½A 
    

#ifndef TFTLCD_ILI9486
	FSMC_WriteTimingInitStructure.FSMC_AddressSetupTime = 0x00;	 //µØÖ·½¨Á¢Ê±¼ä£¨ADDSET£©Îª1¸öHCLK  
  	FSMC_WriteTimingInitStructure.FSMC_AddressHoldTime = 0x00;	 //µØÖ·±£³ÖÊ±¼ä		
  	FSMC_WriteTimingInitStructure.FSMC_DataSetupTime = 0x03;		 //Êý¾Ý±£´æÊ±¼äÎª4¸öHCLK	
  	FSMC_WriteTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_CLKDivision = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_DataLatency = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;	 //Ä£Ê½A 
#else
	FSMC_WriteTimingInitStructure.FSMC_AddressSetupTime = 0x15;	 //µØÖ·½¨Á¢Ê±¼ä£¨ADDSET£©Îª16¸öHCLK  
  	FSMC_WriteTimingInitStructure.FSMC_AddressHoldTime = 0x15;	 //µØÖ·±£³ÖÊ±¼ä		
  	FSMC_WriteTimingInitStructure.FSMC_DataSetupTime = 0x05;		 //Êý¾Ý±£´æÊ±¼äÎª6¸öHCLK	
  	FSMC_WriteTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_CLKDivision = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_DataLatency = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;	 //Ä£Ê½A 	
#endif

 
  	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  ÕâÀïÎÒÃÇÊ¹ÓÃNE4 £¬Ò²¾Í¶ÔÓ¦BTCR[6],[7]¡£
  	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ²»¸´ÓÃÊý¾ÝµØÖ·
  	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
  	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//´æ´¢Æ÷Êý¾Ý¿í¶ÈÎª16bit   
  	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  ´æ´¢Æ÷Ð´Ê¹ÄÜ
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ¶ÁÐ´Ê¹ÓÃ²»Í¬µÄÊ±Ðò
  	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_ReadTimingInitStructure; //¶ÁÐ´Ê±Ðò
  	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_WriteTimingInitStructure;  //Ð´Ê±Ðò

  	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //³õÊ¼»¯FSMCÅäÖÃ

 	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // Ê¹ÄÜBANK1 
	
}
	 
//Ð´¼Ä´æÆ÷º¯Êý
//cmd:¼Ä´æÆ÷Öµ
void LCD_WriteCmd(u16 cmd)
{
#ifdef TFTLCD_HX8357D	
	TFTLCD->LCD_CMD=cmd;//Ð´ÈëÒªÐ´µÄ¼Ä´æÆ÷ÐòºÅ
#endif

#ifdef TFTLCD_R61509V	
	TFTLCD->LCD_CMD=cmd;//Ð´ÈëÒªÐ´µÄ¼Ä´æÆ÷ÐòºÅ
#endif

#ifdef TFTLCD_R61509V3	
	TFTLCD->LCD_CMD=cmd;//Ð´ÈëÒªÐ´µÄ¼Ä´æÆ÷ÐòºÅ
#endif
	
#ifdef TFTLCD_HX8352C
	TFTLCD->LCD_CMD=cmd<<8;
#endif

#ifdef TFTLCD_ILI9341
	TFTLCD->LCD_CMD=cmd<<8;
#endif
	
#ifdef TFTLCD_ILI9327
	TFTLCD->LCD_CMD=cmd;
#endif
	
#ifdef TFTLCD_ILI9486
	TFTLCD->LCD_CMD=cmd;
#endif

#ifdef TFTLCD_ST7793		
	TFTLCD->LCD_CMD=cmd>>8;
	TFTLCD->LCD_CMD=cmd&0xff;
#endif
	
#ifdef TFTLCD_NT5510		
		
#endif	
	
}

//Ð´Êý¾Ý
//data:ÒªÐ´ÈëµÄÖµ
void LCD_WriteData(u16 data)
{
#ifdef TFTLCD_HX8357D	
	TFTLCD->LCD_DATA=data;//Ð´ÈëÒªÐ´µÄ¼Ä´æÆ÷ÐòºÅ
#endif

#ifdef TFTLCD_R61509V	
	TFTLCD->LCD_DATA=data;//Ð´ÈëÒªÐ´µÄ¼Ä´æÆ÷ÐòºÅ
#endif

#ifdef TFTLCD_R61509V3	
	TFTLCD->LCD_DATA=data;//Ð´ÈëÒªÐ´µÄ¼Ä´æÆ÷ÐòºÅ
#endif
	
#ifdef TFTLCD_HX8352C
	TFTLCD->LCD_DATA=data<<8;
#endif

#ifdef TFTLCD_ILI9341
	TFTLCD->LCD_DATA=data<<8;
#endif

#ifdef TFTLCD_ILI9327
	TFTLCD->LCD_DATA=data;
#endif
	
#ifdef TFTLCD_ILI9486
	TFTLCD->LCD_DATA=data;
#endif
	
#ifdef TFTLCD_ST7793	
	TFTLCD->LCD_DATA=data>>8;	
	TFTLCD->LCD_DATA=data&0xff;	
#endif
	
#ifdef TFTLCD_NT5510		
		
#endif
}

void LCD_WriteCmdData(u16 cmd,u16 data)
{
	LCD_WriteCmd(cmd);
	LCD_WriteData(data);
}


void LCD_WriteData_Color(u16 color)
{
#ifdef TFTLCD_HX8357D
			TFTLCD->LCD_DATA=color;
#endif

#ifdef TFTLCD_R61509V
			TFTLCD->LCD_DATA=color;
#endif
	
#ifdef TFTLCD_R61509V3
			TFTLCD->LCD_DATA=color;
#endif

#ifdef TFTLCD_HX8352C
			TFTLCD->LCD_DATA=color&0xff00;
			TFTLCD->LCD_DATA=color<<8;
#endif	

#ifdef TFTLCD_ILI9341
			TFTLCD->LCD_DATA=color&0xff00;
			TFTLCD->LCD_DATA=color<<8;
#endif
	
#ifdef TFTLCD_ILI9327
			TFTLCD->LCD_DATA=color>>8;
			TFTLCD->LCD_DATA=color&0xff;
#endif

#ifdef TFTLCD_ILI9486
			TFTLCD->LCD_DATA=color;
#endif

#ifdef TFTLCD_ST7793
			TFTLCD->LCD_DATA=color>>8;
			TFTLCD->LCD_DATA=color&0xff;
#endif
	
#ifdef TFTLCD_NT5510
			
#endif
}

//¶ÁÊý¾Ý
//·µ»ØÖµ:¶Áµ½µÄÖµ
u16 LCD_ReadData(void)
{
#ifdef TFTLCD_HX8357D
	return TFTLCD->LCD_DATA;
#endif

#ifdef TFTLCD_R61509V
	return TFTLCD->LCD_DATA;
#endif

#ifdef TFTLCD_R61509V3
	return TFTLCD->LCD_DATA;
#endif
	
#ifdef TFTLCD_HX8352C
	return ((TFTLCD->LCD_DATA<<8)|(TFTLCD->LCD_DATA));
#endif

#ifdef TFTLCD_ILI9341
	//return ((TFTLCD->LCD_DATA<<8)|(TFTLCD->LCD_DATA));
	return TFTLCD->LCD_DATA;
#endif

#ifdef TFTLCD_ILI9327		
	u16 ram;		
	ram=TFTLCD->LCD_DATA;
	ram=ram<<8;
	ram|=TFTLCD->LCD_DATA;	
	return ram;		
#endif

#ifdef TFTLCD_ILI9486
	return TFTLCD->LCD_DATA;
#endif

#ifdef TFTLCD_ST7793		
	u16 ram;		
	ram=TFTLCD->LCD_DATA;
	ram=ram<<8;
	ram|=TFTLCD->LCD_DATA;	
	return ram;		
#endif
	
#ifdef TFTLCD_NT5510		
		
#endif
}


//ÉèÖÃLCDÏÔÊ¾·½Ïò
//dir:0,ÊúÆÁ£»1,ºáÆÁ
void LCD_Display_Dir(u8 dir)
{
	if(dir==0)  //Ä¬ÈÏÊúÆÁ·½Ïò
	{		
#ifdef TFTLCD_HX8357D		
		LCD_WriteCmd(0x36);   //ÉèÖÃ²ÊÆÁÏÔÊ¾·½ÏòµÄ¼Ä´æÆ÷
		LCD_WriteData(0x4c);
		tftlcd_data.height=480;
		tftlcd_data.width=320;
#endif

#ifdef TFTLCD_R61509V		
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0100);
		LCD_WriteCmd(0x0003);
		LCD_WriteData(0x1030);
		tftlcd_data.height=400;
		tftlcd_data.width=240;
#endif
		
#ifdef TFTLCD_R61509V3		
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0100);
		LCD_WriteCmd(0x0003);
		LCD_WriteData(0x1030);
		tftlcd_data.height=400;
		tftlcd_data.width=240;
#endif

#ifdef TFTLCD_HX8352C
		LCD_WriteCmd(0x36);   //ÉèÖÃ²ÊÆÁÏÔÊ¾·½ÏòµÄ¼Ä´æÆ÷
		LCD_WriteData(0x03);  //03:U-D,L-R; 06:D-U,R-L;
		tftlcd_data.height=400;
		tftlcd_data.width=240;			
#endif

#ifdef TFTLCD_ILI9341
		LCD_WriteCmd(0x36);   //ÉèÖÃ²ÊÆÁÏÔÊ¾·½ÏòµÄ¼Ä´æÆ÷
		LCD_WriteData(0x08);  
		tftlcd_data.height=320;
		tftlcd_data.width=240;			
#endif

#ifdef TFTLCD_ILI9327
		LCD_WriteCmd(0x36);   //ÉèÖÃ²ÊÆÁÏÔÊ¾·½ÏòµÄ¼Ä´æÆ÷
		LCD_WriteData(0x48);  
		tftlcd_data.height=400;
		tftlcd_data.width=240;			
#endif

#ifdef TFTLCD_ILI9486
		LCD_WriteCmd(0x36);   //ÉèÖÃ²ÊÆÁÏÔÊ¾·½ÏòµÄ¼Ä´æÆ÷
		LCD_WriteData(0x00);  
		tftlcd_data.height=480;
		tftlcd_data.width=320;			
#endif

#ifdef TFTLCD_ST7793
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0100);
		LCD_WriteCmd(0x0003);
		LCD_WriteData(0x1030);
		tftlcd_data.height=400;
		tftlcd_data.width=240;			
#endif
		
#ifdef TFTLCD_NT5510	
		
		
#endif		
		tftlcd_data.dir=0;
		
	}
	else
	{	
#ifdef TFTLCD_HX8357D
		LCD_WriteCmd(0x36);   
		LCD_WriteData(0x2c);
		tftlcd_data.height=320;
		tftlcd_data.width=480;
#endif

#ifdef TFTLCD_R61509V		
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0000);
		LCD_WriteCmd(0x0003);
		LCD_WriteData(0x1038);
		tftlcd_data.height=240;
		tftlcd_data.width=400;
#endif

#ifdef TFTLCD_R61509V3		
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0000);
		LCD_WriteCmd(0x0003);
		LCD_WriteData(0x1038);
		tftlcd_data.height=240;
		tftlcd_data.width=400;
#endif
		
#ifdef TFTLCD_HX8352C
		LCD_WriteCmd(0x16);   //ÉèÖÃ²ÊÆÁÏÔÊ¾·½ÏòµÄ¼Ä´æÆ÷
		LCD_WriteData(0x60);  //60£ººáÆÁ  
		tftlcd_data.height=240;
		tftlcd_data.width=400;			
#endif

#ifdef TFTLCD_ILI9341
		LCD_WriteCmd(0x36);   //ÉèÖÃ²ÊÆ
		
		LCD_WriteData(0x68);  
		tftlcd_data.height=240;
		tftlcd_data.width=320;			
#endif

#ifdef TFTLCD_ILI9327
		LCD_WriteCmd(0x36);   //ÉèÖÃ²ÊÆÁÏÔÊ¾·½ÏòµÄ¼Ä´æÆ÷
		LCD_WriteData(0x28);  
		tftlcd_data.height=240;
		tftlcd_data.width=400;			
#endif

#ifdef TFTLCD_ILI9486
		LCD_WriteCmd(0x36);   //ÉèÖÃ²ÊÆÁÏÔÊ¾·½ÏòµÄ¼Ä´æÆ÷
		LCD_WriteData(0x60);  
		tftlcd_data.height=320;
		tftlcd_data.width=480;			
#endif

#ifdef TFTLCD_ST7793
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0000);
		LCD_WriteCmd(0x0003);
		LCD_WriteData(0x1038);
		tftlcd_data.height=240;
		tftlcd_data.width=400;			
#endif

#ifdef TFTLCD_NT5510	
		
#endif
		tftlcd_data.dir=1;
	}	
}

void TFTLCD_Init(void)
{
	u16 i;
	TFTLCD_GPIO_Init();
	TFTLCD_FSMC_Init();
	
	delay_ms(50); 
	
#ifdef TFTLCD_HX8357D	
	LCD_WriteCmd(0Xd0);				   
	tftlcd_data.id=LCD_ReadData();	//dummy read 	
	tftlcd_data.id=LCD_ReadData();    
#endif 

#ifdef TFTLCD_R61509V	
	LCD_WriteCmd(0X0000);				   	
	tftlcd_data.id=LCD_ReadData();    
#endif

#ifdef TFTLCD_R61509V3	
	LCD_WriteCmd(0X0000);				   	
	tftlcd_data.id=LCD_ReadData();    
#endif
	
#ifdef TFTLCD_HX8352C
	LCD_WriteCmd(0X00);	
	tftlcd_data.id=TFTLCD->LCD_DATA>>8; 
#endif

#ifdef TFTLCD_ILI9341
	LCD_WriteCmd(0Xd3);	
	tftlcd_data.id=TFTLCD->LCD_DATA;	//dummy read 
	tftlcd_data.id=TFTLCD->LCD_DATA;  //00
	tftlcd_data.id=TFTLCD->LCD_DATA;  //93
	tftlcd_data.id|=TFTLCD->LCD_DATA>>8;  //41
#endif

#ifdef TFTLCD_ILI9327
	LCD_WriteCmd(0XEF);	
	tftlcd_data.id=TFTLCD->LCD_DATA;	//dummy read 
	tftlcd_data.id=TFTLCD->LCD_DATA;  //02
	tftlcd_data.id=TFTLCD->LCD_DATA;  //04
	tftlcd_data.id=TFTLCD->LCD_DATA;  //93
	tftlcd_data.id=(tftlcd_data.id<<8)|TFTLCD->LCD_DATA;  //27
#endif

#ifdef TFTLCD_ILI9486
	LCD_WriteCmd(0Xd3);	
	tftlcd_data.id=TFTLCD->LCD_DATA;	//dummy read 
	tftlcd_data.id=TFTLCD->LCD_DATA;  //00
	tftlcd_data.id=TFTLCD->LCD_DATA;  //94
	tftlcd_data.id<<=8;
	tftlcd_data.id|=TFTLCD->LCD_DATA;  //86
#endif

#ifdef TFTLCD_ST7793	
	LCD_WriteCmd(0X0000);				   	
	tftlcd_data.id=LCD_ReadData();	
#endif 
	
#ifdef TFTLCD_NT5510	
		
#endif 	
	
 	printf(" LCD ID:%x\r\n",tftlcd_data.id); //´òÓ¡LCD ID
	
#ifdef TFTLCD_HX8357D	
	LCD_WriteCmd(0xE9); 
	LCD_WriteData(0x20); 
	
	LCD_WriteCmd(0x11); //Exit Sleep 
	for(i=500; i>0; i--);
	
	LCD_WriteCmd(0x3A);
	LCD_WriteData(0x55);  //16Bit colors
	
	LCD_WriteCmd(0xD1); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x65); //µ÷ÊÔ´ËÖµ¸ÄÉÆË®ÎÆ
	LCD_WriteData(0x1F); 
	
	LCD_WriteCmd(0xD0); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x80); 
	
	LCD_WriteCmd(0x36); 	 //Set_address_mode
	LCD_WriteData(0x4c);   	//4c
	
	LCD_WriteCmd(0xC1); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x02); 
	LCD_WriteData(0x02); 
	
	LCD_WriteCmd(0xC0); //Set Default Gamma 
	LCD_WriteData(0x00);  
	LCD_WriteData(0x35); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x02); 

	LCD_WriteCmd(0xC4);			
	LCD_WriteData(0x03);

	LCD_WriteCmd(0xC5); //Set frame rate 
	LCD_WriteData(0x01); 
	
	LCD_WriteCmd(0xD2); //power setting 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x22); 

	LCD_WriteCmd(0xE7);			
	LCD_WriteData(0x38);
	
	LCD_WriteCmd(0xF3);			
    LCD_WriteData(0x08); 
	LCD_WriteData(0x12);
	LCD_WriteData(0x12);
	LCD_WriteData(0x08);

	LCD_WriteCmd(0xC8); //Set Gamma 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x52); 
	LCD_WriteData(0x37); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x0d); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x04); 
	LCD_WriteData(0x51); 
	LCD_WriteData(0x77); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x0d); 
	LCD_WriteData(0x08); 
	LCD_WriteData(0x80); 
	LCD_WriteData(0x00);

    LCD_WriteCmd(0x29);
#endif

#ifdef TFTLCD_R61509V
	LCD_WriteCmd(0x0000);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0000);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0000);LCD_WriteData(0x0000);
	
	LCD_WriteCmd(0x0400);LCD_WriteData(0x6200); 
	LCD_WriteCmd(0x0008);LCD_WriteData(0x0808); 


	LCD_WriteCmd(0x0001);LCD_WriteData(0x0100);
 	LCD_WriteCmd(0x0002);LCD_WriteData(0x0100);
	LCD_WriteCmd(0x0003);LCD_WriteData(0x1030);
	LCD_WriteCmd(0x0008);LCD_WriteData(0x0808);
	/*gamma set 20090423 BY LYJ*/

	 LCD_WriteCmd(0x0300);LCD_WriteData(0x000c); 
	 LCD_WriteCmd(0x0301);LCD_WriteData(0x5A0B); 
	 LCD_WriteCmd(0x0302);LCD_WriteData(0x0906); 
	 LCD_WriteCmd(0x0303);LCD_WriteData(0x1017); 
	 LCD_WriteCmd(0x0304);LCD_WriteData(0x2300); 
	 LCD_WriteCmd(0x0305);LCD_WriteData(0x1700); 
	 LCD_WriteCmd(0x0306);LCD_WriteData(0x6309); 
	 LCD_WriteCmd(0x0307);LCD_WriteData(0x0c09); 
	 LCD_WriteCmd(0x0308);LCD_WriteData(0x100c); 
	 LCD_WriteCmd(0x0309);LCD_WriteData(0x2232); 
	 /*power set*/
	  LCD_WriteCmd(0x0010);LCD_WriteData(0x0014);
	  LCD_WriteCmd(0x0011);LCD_WriteData(0x0101);  
	  LCD_WriteCmd(0x0100);LCD_WriteData(0x0230);//
		//for(i=500; i>0; i--);
		delay_ms(50);
	  LCD_WriteCmd(0x0101);LCD_WriteData(0x0247);//
		for(i=500; i>0; i--);
		delay_ms(50);
	  LCD_WriteCmd(0x0103);LCD_WriteData(0x0a00);//Starts VLOUT3,Sets the VREG1OUT.
		for(i=500; i>0; i--);
		delay_ms(10);
	  LCD_WriteCmd(0x0280);LCD_WriteData(0xf0ff);//VCOMH voltage   //0xcEff
		delay_ms(50);
		for(i=500; i>0; i--);
	  LCD_WriteCmd(0x0102);LCD_WriteData(0xB1b0);//Starts VLOUT3,Sets the VREG1OUT.
		for(i=500; i>0; i--);
		delay_ms(50);
	 /*window set*/
	  LCD_WriteCmd(0x0210);LCD_WriteData(0x0000);//Window Horizontal RAM Address Start
	  LCD_WriteCmd(0x0211);LCD_WriteData(0x00ef);//Window Horizontal RAM Address End
	  LCD_WriteCmd(0x0212);LCD_WriteData(0x0000);//Window Vertical RAM Address Start
	  LCD_WriteCmd(0x0213);LCD_WriteData(0x018f);//Window Vertical RAM Address End
	  LCD_WriteCmd(0x0200);LCD_WriteData(0x0000);//RAM Address Set (Horizontal Address)
	  LCD_WriteCmd(0x0201);LCD_WriteData(0x0000);//RAM Address Set (Vertical Address)
	  LCD_WriteCmd(0x0401);LCD_WriteData(0x0000);//Base Image Display
	  LCD_WriteCmd(0x0007);LCD_WriteData(0x0100);//Display Control 1
		for(i=500; i>0; i--);
		delay_ms(50);
	  LCD_WriteCmd(0x0202);
#endif

#ifdef TFTLCD_R61509V3
	/* --R61509V_CPT3.0 --- */

	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	delay_ms(10);
	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	delay_ms(10);
	
	LCD_WriteCmd(0x0400); LCD_WriteData(0x6200);
	LCD_WriteCmd(0x0008); LCD_WriteData(0x0808);
	
	LCD_WriteCmd(0x0300); LCD_WriteData(0x0005);//gamma
	LCD_WriteCmd(0x0301); LCD_WriteData(0x4C06);
	LCD_WriteCmd(0x0302); LCD_WriteData(0x0602);
	LCD_WriteCmd(0x0303); LCD_WriteData(0x050C);
	LCD_WriteCmd(0x0304); LCD_WriteData(0x3300);
	LCD_WriteCmd(0x0305); LCD_WriteData(0x0C05);
	LCD_WriteCmd(0x0306); LCD_WriteData(0x4206);
	LCD_WriteCmd(0x0307); LCD_WriteData(0x060C);
	LCD_WriteCmd(0x0308); LCD_WriteData(0x0500);
	LCD_WriteCmd(0x0309); LCD_WriteData(0x0033);
	
	LCD_WriteCmd(0x0010); LCD_WriteData(0x0014);//
	LCD_WriteCmd(0x0011); LCD_WriteData(0x0101);//
	LCD_WriteCmd(0x0012); LCD_WriteData(0x0000);//
	LCD_WriteCmd(0x0013); LCD_WriteData(0x0001);//
	
	LCD_WriteCmd(0x0100); LCD_WriteData(0x0330);//BT AP
	LCD_WriteCmd(0x0101); LCD_WriteData(0x0247);//DC0,DC1,VC
	LCD_WriteCmd(0x0103); LCD_WriteData(0x1000);//VDV
	LCD_WriteCmd(0x0280); LCD_WriteData(0xDE00);//VCM
	LCD_WriteCmd(0x0102); LCD_WriteData(0xD1B0);//VR,VCMR,PSON,PON
	delay_ms(10);
	
	LCD_WriteCmd(0x0001); LCD_WriteData(0x0100);
	LCD_WriteCmd(0x0002); LCD_WriteData(0x0100);
	LCD_WriteCmd(0x0003); LCD_WriteData(0x1030);
	LCD_WriteCmd(0x0009); LCD_WriteData(0x0001);
	LCD_WriteCmd(0x000C); LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0090); LCD_WriteData(0x8000);
	LCD_WriteCmd(0x000F); LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0210); LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0211); LCD_WriteData(0x00EF);
	LCD_WriteCmd(0x0212); LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0213); LCD_WriteData(0x018F);//432=1AF, 400=18F
	LCD_WriteCmd(0x0500); LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0501); LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0502); LCD_WriteData(0x005F);
	LCD_WriteCmd(0x0401); LCD_WriteData(0x0001);
	LCD_WriteCmd(0x0404); LCD_WriteData(0x0000);
	delay_ms(10);
							 
	LCD_WriteCmd(0x0007); LCD_WriteData(0x0100);//BASEE
	delay_ms(10);
	
	LCD_WriteCmd(0x0200); LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0201); LCD_WriteData(0x0000);
	delay_ms(10);
	LCD_WriteCmd(0x0202);
#endif


#ifdef TFTLCD_HX8352C

	//************* Start Initial Sequence **********//	
	//##################################################################
	//Power Voltage Setting
	LCD_WriteCmdData(0x1A,0x02); //BT  0x02
	LCD_WriteCmdData(0x1B,0x88); //VRH  0x88
	LCD_WriteCmdData(0x1C,0x06); //AP[0:2]  //×Ô¼ºÌí¼Ó
	
	//****VCOM offset**///
	LCD_WriteCmdData(0x23,0x00); //SEL_VCM   00
	LCD_WriteCmdData(0x24,0x7f); //VCM    5f
	LCD_WriteCmdData(0x25,0x1f); //VDV   0x15
	LCD_WriteCmdData(0x2D,0x03); //NOW[2:0]=011
	//Power on Setting
	LCD_WriteCmdData(0x18,0x04); //Frame rate 72Hz
	LCD_WriteCmdData(0x19,0x01); //OSC_EN='1', start Osc
	LCD_WriteCmdData(0x01,0x00); //DP_STB='0', out deep sleep
	LCD_WriteCmdData(0x1F,0x88); //STB=0
	delay_ms(5);
	LCD_WriteCmdData(0x1F,0x80); //DK=0
	delay_ms(5);
	LCD_WriteCmdData(0x1F,0x90); //PON=1
	delay_ms(5);
	LCD_WriteCmdData(0x1F,0xD0); //VCOMG=1
	delay_ms(5);
	//262k/65k color selection
	LCD_WriteCmdData(0x17,0x05); //default 0x06 262k color // 0x05 65k color
	//SET PANEL
	LCD_WriteCmdData(0x36,0x13); //REV_P, SM_P, GS_P, BGR_P, SS_P   0x03
	LCD_WriteCmdData(0x29,0x31); //400 lines
	LCD_WriteCmdData(0x71,0x1A); //RTN
	//Gamma 2.2 Setting
	LCD_WriteCmdData(0x40,0x00);
	LCD_WriteCmdData(0x41,0x45);
	LCD_WriteCmdData(0x42,0x45);
	LCD_WriteCmdData(0x43,0x04);
	LCD_WriteCmdData(0x44,0x00);
	LCD_WriteCmdData(0x45,0x08);
	LCD_WriteCmdData(0x46,0x23);
	LCD_WriteCmdData(0x47,0x23);
	LCD_WriteCmdData(0x48,0x77);
	LCD_WriteCmdData(0x49,0x40);
	LCD_WriteCmdData(0x4A,0x04);
	LCD_WriteCmdData(0x4B,0x00);
	LCD_WriteCmdData(0x4C,0x88);
	LCD_WriteCmdData(0x4D,0x88);
	LCD_WriteCmdData(0x4E,0x88);
	//Set GRAM Area
	LCD_WriteCmdData(0x02,0x00);
	LCD_WriteCmdData(0x03,0x00); //Column Start
	LCD_WriteCmdData(0x04,0x00);
	LCD_WriteCmdData(0x05,0xEF); //Column End
	LCD_WriteCmdData(0x06,0x00);
	LCD_WriteCmdData(0x07,0x00); //Row Start
	LCD_WriteCmdData(0x08,0x01);
	LCD_WriteCmdData(0x09,0xAF); //Row End
	//Display ON Setting
	LCD_WriteCmdData(0x28,0x38); //GON=1, DTE=1, D=10
	delay_ms(40);
	LCD_WriteCmdData(0x28,0x3F); //GON=1, DTE=1, D=11  0x3C
	LCD_WriteCmd(0x22);
	 //Start GRAM write
	//##################################################################
	// Power Off Setting
	LCD_WriteCmdData(0x28,0x38); //GON=¡¯1¡¯ DTE=¡¯1¡¯ D[1:0]=¡¯10¡¯
	delay_ms(40);
	LCD_WriteCmdData(0x1F,0x89); // GAS=1, VOMG=0, PON=0, DK=1, XDK=0, DVDH_TRI=0, STB=1
	delay_ms(40);
	LCD_WriteCmdData(0x28,0x20); //GON=¡¯1¡¯ DTE=¡¯0¡¯ D[1:0]=¡¯00¡¯
	delay_ms(40);
	LCD_WriteCmdData(0x19,0x00); //OSC_EN=¡¯0¡¯
	delay_ms(40);
	//M51_WR_REG(U05_LCD_POWER_ON, 0x00); //VCI & IOVCC OFF
	//##################################################################
	// ENTER IDLE mode Setting
	LCD_WriteCmdData(0x18,0x07); //Frame Rate 60Hz
	LCD_WriteCmdData(0x01,0x04); //IDLE='1' , enter IDLE mode
	// EXIT IDLE mode Setting
	LCD_WriteCmdData(0x18,0x04); //Frame rate 72Hz
	LCD_WriteCmdData(0x01,0x00); //IDLE='0', EXIT IDLE mode
	//##################################################################
	// ENTER Partial mode Setting 32line
	LCD_WriteCmdData(0x18,0x04); //Frame rate 72Hz
	LCD_WriteCmdData(0x01,0x01); //PTL='1', Enter Partial mode
	LCD_WriteCmdData(0x0A,0x00); //PSL[15:8]=0x00
	LCD_WriteCmdData(0x0B,0x20); //PSL[7:0]=0x20
	LCD_WriteCmdData(0x0C,0x00); //PEL[15:8]=0x00
	LCD_WriteCmdData(0x0D,0x3F); //PEL[7:0]=0x3F
	// EXIT Partial mode Setting
	LCD_WriteCmdData(0x18,0x04); //Frame rate 72Hz
	LCD_WriteCmdData(0x01,0x00); //PTL='0', EXIT Partial mode
	//##################################################################
	// ENTER Partial + IDLE mode Setting 32line
	LCD_WriteCmdData(0x18,0x07); //Frame Rate 60Hz
	LCD_WriteCmdData(0x01,0x05); // PTL='1' IDLE=¡¯1¡¯, Enter Partial + IDLE mode
	LCD_WriteCmdData(0x0A,0x00); //PSL[15:8]=0x00
	LCD_WriteCmdData(0x0B,0x20); //PSL[7:0]=0x20
	LCD_WriteCmdData(0x0C,0x00); //PEL[15:8]=0x00
	LCD_WriteCmdData(0x0D,0x3F); //PEL[7:0]=0x3F
	// EXIT Partial + IDLE mode Setting
	LCD_WriteCmdData(0x18,0x04); //Frame rate 72Hz
	LCD_WriteCmdData(0x01,0x00); // PTL='0' IDLE=¡¯0¡¯, EXIT Partial + IDLE mode
	//##################################################################
	// Enter Sleep mode Setting
	LCD_WriteCmdData(0x28,0x38); //GON=¡¯1¡¯ DTE=¡¯1¡¯ D[1:0]=¡¯10¡¯
	delay_ms(40);
	LCD_WriteCmdData(0x1F,0x89); // GAS=1, VOMG=0, PON=0, DK=1, XDK=0, DVDH_TRI=0, STB=1
	delay_ms(40);
	LCD_WriteCmdData(0x28,0x20); //GON=¡¯1¡¯ DTE=¡¯0¡¯ D[1:0]=¡¯00¡¯
	delay_ms(40);
	LCD_WriteCmdData(0x19,0x00); //OSC_EN=¡¯0¡¯
	delay_ms(5);
	// Exit Sleep mode Setting
	LCD_WriteCmdData(0x19,0x01); //OSC_EN='1', start Osc
	LCD_WriteCmdData(0x1F,0x88); //STB=0
	delay_ms(5);
	LCD_WriteCmdData(0x1F,0x80); //DK=0
	delay_ms(5);
	LCD_WriteCmdData(0x1F,0x90); //PON=1
	delay_ms(5);
	LCD_WriteCmdData(0x1F,0xD0); //VCOMG=1
	delay_ms(5);
	LCD_WriteCmdData(0x28,0x38); //GON=1, DTE=1, D=10
	delay_ms(40);
	LCD_WriteCmdData(0x28,0x3C); //GON=1, DTE=1, D=11
	//##################################################################
	// Enter Deep Sleep mode Setting
	LCD_WriteCmdData(0x28,0x38); //GON=¡¯1¡¯ DTE=¡¯1¡¯ D[1:0]=¡¯10¡¯
	delay_ms(40);
	LCD_WriteCmdData(0x1F,0x89); // GAS=1, VOMG=0, PON=0, DK=1, XDK=0, DVDH_TRI=0, STB=1
	delay_ms(40);
	LCD_WriteCmdData(0x28,0x20); //GON=¡¯1¡¯ DTE=¡¯0¡¯ D[1:0]=¡¯00¡¯
	delay_ms(40);
	LCD_WriteCmdData(0x19,0x00); //OSC_EN=¡¯0¡¯
	delay_ms(5);
	LCD_WriteCmdData(0x01,0x80); //DP_STB=¡¯1¡¯
	// Exit Deep Sleep mode Setting
	LCD_WriteCmdData(0x01,0x00); //DP_STB='0', out deep sleep
	delay_ms(10);
	LCD_WriteCmdData(0x19,0x01); //OSC_EN='1', start Osc
	LCD_WriteCmdData(0x1F,0x88); //STB=0
	delay_ms(5);
	LCD_WriteCmdData(0x1F,0x80); //DK=0
	delay_ms(5);
	LCD_WriteCmdData(0x1F,0x90); //PON=1
	delay_ms(5);
	LCD_WriteCmdData(0x1F,0xD0); //VCOMG=1
	delay_ms(5);
	LCD_WriteCmdData(0x28,0x38); //GON=1, DTE=1, D=10
	delay_ms(40);
	LCD_WriteCmdData(0x28,0x3C); //GON=1, DTE=1, D=11

	LCD_WriteCmd(0x22);

#endif

#ifdef TFTLCD_ILI9341

	//************* Start Initial Sequence **********//	
	LCD_WriteCmd(0xCB);  
	LCD_WriteData(0x39); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x34);  
	LCD_WriteData(0x02);   
	 
	LCD_WriteCmd(0xCF);  
	LCD_WriteData (0x00); 
	LCD_WriteData (0xa2); //c1
	LCD_WriteData (0Xf0);  //30
	 
	LCD_WriteCmd(0xE8);  
	LCD_WriteData (0x84); 	 //85
	LCD_WriteData (0x11); 	 //00
	LCD_WriteData (0x7a); 	 //79
	
	
	LCD_WriteCmd(0xEA);  
	LCD_WriteData (0x66);  //00
	LCD_WriteData (0x00); 
	
	LCD_WriteCmd(0xED);  
	LCD_WriteData (0x55); 	//64
	LCD_WriteData (0x01); 	//03
	LCD_WriteData (0X23); 	//12
	LCD_WriteData (0X01); 	//81
	 
	LCD_WriteCmd(0xF7);  
	LCD_WriteData (0x20); 	//20
	
	
	LCD_WriteCmd(0xC0);    //Power control 
	LCD_WriteData (0x1c);   //VRH[5:0] 	//1c
	 
	LCD_WriteCmd(0xC1);    //Power control 
	LCD_WriteData (0x13);   //SAP[2:0];BT[3:0] 	//13
	 
	LCD_WriteCmd(0xC5);    //VCM control 
	LCD_WriteData (0x23); 
	LCD_WriteData (0x3F); 
	 
	LCD_WriteCmd(0xC7);    //VCM control2 
	LCD_WriteData(0xA5); 
	
	LCD_WriteCmd(0xB1);  
	LCD_WriteData (0x00); 
	LCD_WriteData (0x17); 
	
	LCD_WriteCmd(0x3A);  
	LCD_WriteData (0x55); 
	
	LCD_WriteCmd(0xB6);  
	LCD_WriteData (0x0A);
	LCD_WriteData (0xa2);  //a2
	LCD_WriteData (0x27);
	LCD_WriteData (0x00); 
	 
	LCD_WriteCmd(0x36);    // Memory Access Control 
	LCD_WriteData (0x08); 	  //08	BGR
	 
	LCD_WriteCmd(0xF2);    // 3Gamma Function Disable 
	LCD_WriteData (0x02); 	//00
	 
	LCD_WriteCmd(0x26);    //Gamma curve selected 
	LCD_WriteData (0x01); 
	 
	LCD_WriteCmd(0xE0);    //Set Gamma 
	LCD_WriteData (0x0F); 
	LCD_WriteData (0x14); 
	LCD_WriteData (0x13); 
	LCD_WriteData (0x0C); 
	LCD_WriteData (0x0E); 
	LCD_WriteData (0x05); 
	LCD_WriteData (0x45); 
	LCD_WriteData (0x85); 
	LCD_WriteData (0x36); 
	LCD_WriteData (0x09); 
	LCD_WriteData (0x14); 
	LCD_WriteData (0x05); 
	LCD_WriteData (0x09); 
	LCD_WriteData (0x03); 
	LCD_WriteData (0x00); 
	 
	LCD_WriteCmd(0XE1);    //Set Gamma 
	LCD_WriteData (0x00); 
	LCD_WriteData (0x24); 
	LCD_WriteData (0x26); 
	LCD_WriteData (0x03); 
	LCD_WriteData (0x0F); 
	LCD_WriteData (0x04); 
	LCD_WriteData (0x3F); 
	LCD_WriteData (0x14); 
	LCD_WriteData (0x52); 
	LCD_WriteData (0x04); 
	LCD_WriteData (0x10); 
	LCD_WriteData (0x0E); 
	LCD_WriteData (0x38); 
	LCD_WriteData (0x39); 
	LCD_WriteData (0x0F); 

	LCD_WriteCmd(0x2A );
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0xEF);

	LCD_WriteCmd(0x2B );
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	LCD_WriteData(0x3F);
	 
	LCD_WriteCmd(0x11);    //Exit Sleep 
	delay_ms(120);

	LCD_WriteCmd(0x29);    //Display on

#endif

#ifdef TFTLCD_ILI9327
	//************* Start Initial Sequence **********// 

	LCD_WriteCmd(0xE9); 
	LCD_WriteData(0x20); 
	
	LCD_WriteCmd(0x11); //Exit Sleep 
	delay_ms(100); 
	
	LCD_WriteCmd(0x3A);
	LCD_WriteData(0x55);
	
	LCD_WriteCmd(0xD1); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x65); //µ÷ÊÔ´ËÖµ¸ÄÉÆË®ÎÆ
	LCD_WriteData(0x1F); 
	
	LCD_WriteCmd(0xD0); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x80); 
	
	LCD_WriteCmd(0x36); 
	LCD_WriteData(0x48); 
	
	LCD_WriteCmd(0xC1); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x02); 
	LCD_WriteData(0x02); 
	
	LCD_WriteCmd(0xC0); //Set Default Gamma 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x35); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x02); 
	
	LCD_WriteCmd(0xC5); //Set frame rate 
	LCD_WriteData(0x01); 
	
	LCD_WriteCmd(0xD2); //power setting 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x22); 
	
	LCD_WriteCmd(0xC8); //Set Gamma 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x52); 
	LCD_WriteData(0x37); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x0d); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x04); 
	LCD_WriteData(0x51); 
	LCD_WriteData(0x77); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x0d); 
	LCD_WriteData(0x08); 
	LCD_WriteData(0x80); 
	LCD_WriteData(0x00); 
	
	LCD_WriteCmd(0x29); //display on

#endif

#ifdef TFTLCD_ILI9486
/*
	LCD_WriteCmd (0xC0); //µçÔ´¿ØÖÆ1
    LCD_WriteData(0x13);
    LCD_WriteData(0x10);
delay_ms(50);
	LCD_WriteCmd (0xC1); //µçÔ´¿ØÖÆ2
    LCD_WriteData(0x43);
    LCD_WriteData(0x00);	   
delay_ms(50);	
	LCD_WriteCmd (0xC2); //µçÔ´¿ØÖÆ3
    LCD_WriteData(0x22);
delay_ms(50);	
	LCD_WriteCmd (0xC5); //VCOM Control
    LCD_WriteData(0x00);
    LCD_WriteData(0x4D);
    LCD_WriteData(0x80); 
delay_ms(50);	
	LCD_WriteCmd (0xB1); //Frame Rate Control
    LCD_WriteData(0xC0);
    LCD_WriteData(0x11);
delay_ms(50);
	LCD_WriteCmd (0xB4); //Display Inversion Control
    LCD_WriteData(0x01);
delay_ms(50);	
	LCD_WriteCmd (0xB6); //Display Function Control 
    LCD_WriteData(0x00);
    LCD_WriteData(0x42);
    LCD_WriteData(0x3B); 
delay_ms(50);	
	LCD_WriteCmd(0x36);  
	LCD_WriteData(0x00);
	LCD_WriteCmd(0x3A);
	LCD_WriteData(0x55);
delay_ms(50);
	LCD_WriteCmd (0x11); //¹Ø±ÕË¯ÃßÄ£Ê½
delay_ms(50);
	LCD_WriteCmd (0x29); //Display ON
delay_ms(50);
*/
/*
	LCD_WriteCmd(0x11); 
	delay_ms(20); 
	LCD_WriteCmd(0xD0); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x42); 
	LCD_WriteData(0x18); 

	LCD_WriteCmd(0xD1); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x07);//07 
	LCD_WriteData(0x10); 

	LCD_WriteCmd(0xD2); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x02); 

	LCD_WriteCmd(0xC0); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x3B); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x02); 
	LCD_WriteData(0x11); 

	LCD_WriteCmd(0xC5); 
	LCD_WriteData(0x03); 

	LCD_WriteCmd(0xC8); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x32); 
	LCD_WriteData(0x36); 
	LCD_WriteData(0x45); 
	LCD_WriteData(0x06); 
	LCD_WriteData(0x16); 
	LCD_WriteData(0x37); 
	LCD_WriteData(0x75); 
	LCD_WriteData(0x77); 
	LCD_WriteData(0x54); 
	LCD_WriteData(0x0C); 
	LCD_WriteData(0x00); 

	LCD_WriteCmd(0x36); 
	LCD_WriteData(0x00); 

	LCD_WriteCmd(0x3A); 
	LCD_WriteData(0x55); 

	LCD_WriteCmd(0x2A); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x3F); 

	LCD_WriteCmd(0x2B); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0xdf); 
	delay_ms(120); 
	LCD_WriteCmd(0x29);
*/

	LCD_WriteCmd(0xB0);
	LCD_WriteData(0x00);
	LCD_WriteCmd(0x11);
	delay_ms(20);

	LCD_WriteCmd(0xB3);
	LCD_WriteData(0x02);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0xC0);
	LCD_WriteData(0x10);//13
	LCD_WriteData(0x3B);//480
	LCD_WriteData(0x00);
	LCD_WriteData(0x02);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	LCD_WriteData(0x00);//NW
	LCD_WriteData(0x43);

	LCD_WriteCmd(0xC1);
	LCD_WriteData(0x10);//LCD_WriteData(0x08);
	LCD_WriteData(0x10);//LCD_WriteData(0x16);//CLOCK
	LCD_WriteData(0x08);
	LCD_WriteData(0x08);

	LCD_WriteCmd(0xC4);
	LCD_WriteData(0x11);
	LCD_WriteData(0x07);
	LCD_WriteData(0x03);
	LCD_WriteData(0x03);

	LCD_WriteCmd(0xC6);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0xC8);//GAMMA
	LCD_WriteData(0x03);
	LCD_WriteData(0x03);
	LCD_WriteData(0x13);
	LCD_WriteData(0x5C);
	LCD_WriteData(0x03);
	LCD_WriteData(0x07);
	LCD_WriteData(0x14);
	LCD_WriteData(0x08);
	LCD_WriteData(0x00);
	LCD_WriteData(0x21);
	LCD_WriteData(0x08);
	LCD_WriteData(0x14);
	LCD_WriteData(0x07);
	LCD_WriteData(0x53);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x13);
	LCD_WriteData(0x03);
	LCD_WriteData(0x03);
	LCD_WriteData(0x21);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0x35);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0x36);  
	LCD_WriteData(0x00);

	LCD_WriteCmd(0x3A);
	LCD_WriteData(0x55);

	LCD_WriteCmd(0x44);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);

	LCD_WriteCmd(0xB6);
	LCD_WriteData(0x00);
	LCD_WriteData(0x22);//0 GS SS SM ISC[3:0];ÆäÖÐGS SS¿ØÖÆÏÔÊ¾·½Ïò£¬Í¬Ê±ÐÞ¸ÄR36
	LCD_WriteData(0x3B);

	LCD_WriteCmd(0xD0);
	LCD_WriteData(0x07);
	LCD_WriteData(0x07);//VCI1
	LCD_WriteData(0x1D);//VRH

	LCD_WriteCmd(0xD1);
	LCD_WriteData(0x00);
	LCD_WriteData(0x03);//VCM
	LCD_WriteData(0x00);//VDV

	LCD_WriteCmd(0xD2);
	LCD_WriteData(0x03);
	LCD_WriteData(0x14);
	LCD_WriteData(0x04);

	LCD_WriteCmd(0x29);
	delay_ms(20);

	LCD_WriteCmd(0xB4);
	LCD_WriteData(0x00);
	delay_ms(20);
	LCD_WriteCmd(0x2C);

#endif

#ifdef TFTLCD_ST7793	
	for(i=500; i>0; i--);
	LCD_WriteCmd(0x0001);
	LCD_WriteData(0x0100);
	LCD_WriteCmd(0x0003);
	LCD_WriteData(0x1030); //16bit 565 
	
	LCD_WriteCmd(0x0008);
	LCD_WriteData(0x0808);
	LCD_WriteCmd(0x0090);
	LCD_WriteData(0x8000);
	LCD_WriteCmd(0x0400);
	LCD_WriteData(0x6200);
	LCD_WriteCmd(0x0401);
	LCD_WriteData(0x0001);

	LCD_WriteCmd(0x00ff);
	LCD_WriteData(0x0001);
	LCD_WriteCmd(0x0102);
	LCD_WriteData(0x01b0);
	LCD_WriteCmd(0x0710);
	LCD_WriteData(0x0016);
	LCD_WriteCmd(0x0712);
	LCD_WriteData(0x000f);
	LCD_WriteCmd(0x0752);
	LCD_WriteData(0x002f);
	LCD_WriteCmd(0x0724);
	LCD_WriteData(0x001a);
	LCD_WriteCmd(0x0754);	
	LCD_WriteData(0x0018);
	for(i=500; i>0; i--);
    
    /* Gamma */
	LCD_WriteCmd(0x0380);
	LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0381);
	LCD_WriteData(0x5F10);//5f10
	LCD_WriteCmd(0x0382);
	LCD_WriteData(0x0B02);//0b02
	LCD_WriteCmd(0x0383);
	LCD_WriteData(0x0614);
	LCD_WriteCmd(0x0384);
	LCD_WriteData(0x0111);
	LCD_WriteCmd(0x0385);
	LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0386);
	LCD_WriteData(0xA90B);//a90b
	LCD_WriteCmd(0x0387);
	LCD_WriteData(0x0606);//0606
	LCD_WriteCmd(0x0388);
	LCD_WriteData(0x0612);
	LCD_WriteCmd(0x0389);
	LCD_WriteData(0x0111);	  


    /* Gamma Setting */
    /* Setting */
	LCD_WriteCmd(0x0702);
	LCD_WriteData(0x003b);//003b
	LCD_WriteCmd(0x00ff);
	LCD_WriteData(0x0000);


    /* Vcom Setting */
	LCD_WriteCmd(0x0007);
	LCD_WriteData(0x0100);
	for(i=500; i>0; i--); 
	LCD_WriteCmd(0x0200);
	LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0201);                  
	LCD_WriteData(0x0000);	
#endif

#ifdef TFTLCD_NT5510	
		
#endif

	LCD_Display_Dir(0);		//0£ºÊúÆÁ  1£ººáÆÁ  Ä¬ÈÏÊúÆÁ
	LCD_Clear(WHITE);
}


//ÉèÖÃ´°¿Ú,²¢×Ô¶¯ÉèÖÃ»­µã×ø±êµ½´°¿Ú×óÉÏ½Ç(sx,sy).
//sx,sy:´°¿ÚÆðÊ¼×ø±ê(×óÉÏ½Ç)
//width,height:´°¿Ú¿í¶ÈºÍ¸ß¶È,±ØÐë´óÓÚ0!!
//´°Ìå´óÐ¡:width*height. 
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
{    
#ifdef TFTLCD_HX8357D	
	LCD_WriteCmd(0x2A);
    LCD_WriteData(sx>>8);
    LCD_WriteData(sx&0XFF);
    LCD_WriteData(width>>8);
    LCD_WriteData(width&0XFF);

    LCD_WriteCmd(0x2b);
    LCD_WriteData(sy>>8);
    LCD_WriteData(sy&0XFF);
    LCD_WriteData(height>>8);
    LCD_WriteData(height&0XFF);
    LCD_WriteCmd(0x2c); 
#endif

#ifdef TFTLCD_R61509V	
	if(tftlcd_data.dir==0)
	{
		LCD_WriteCmd(0x0210);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0211);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0212);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0213);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0200);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0201);   
	    LCD_WriteData(sy);	
	}   	
	else
	{
		LCD_WriteCmd(0x0212);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0213);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0210);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0211);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0201);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0200);   
	    LCD_WriteData(sy);	
	}
	LCD_WriteCmd(0x0202);
#endif	

#ifdef TFTLCD_R61509V3	
	if(tftlcd_data.dir==0)
	{
		LCD_WriteCmd(0x0210);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0211);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0212);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0213);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0200);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0201);   
	    LCD_WriteData(sy);	
	}   	
	else
	{
		LCD_WriteCmd(0x0212);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0213);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0210);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0211);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0201);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0200);   
	    LCD_WriteData(sy);	
	}
	LCD_WriteCmd(0x0202);
#endif
	
#ifdef TFTLCD_HX8352C
	LCD_WriteCmd(0x02);LCD_WriteData(sx/256);   
	LCD_WriteCmd(0x03);LCD_WriteData(sx%256); 	 
	LCD_WriteCmd(0x04);LCD_WriteData(width/256); 
	LCD_WriteCmd(0x05);LCD_WriteData(width%256);
	
	LCD_WriteCmd(0x06);LCD_WriteData(sy/256);  
	LCD_WriteCmd(0x07);LCD_WriteData(sy%256);
	LCD_WriteCmd(0x08);LCD_WriteData(height/256); 
	LCD_WriteCmd(0x09);LCD_WriteData(height%256); 	

	LCD_WriteCmd(0x22);

#endif

#ifdef TFTLCD_ILI9341
	LCD_WriteCmd(0x2A);
	LCD_WriteData(sx/256);   
	LCD_WriteData(sx%256); 	 
	LCD_WriteData(width/256); 
	LCD_WriteData(width%256);
	
	LCD_WriteCmd(0x2B);
	LCD_WriteData(sy/256);  
	LCD_WriteData(sy%256);
	LCD_WriteData(height/256); 
	LCD_WriteData(height%256); 	

	LCD_WriteCmd(0x2C);

#endif

#ifdef TFTLCD_ILI9327
	LCD_WriteCmd(0x2A);
	LCD_WriteData(sx/256);   
	LCD_WriteData(sx%256); 	 
	LCD_WriteData(width/256); 
	LCD_WriteData(width%256);
	
	LCD_WriteCmd(0x2B);
	LCD_WriteData(sy/256);  
	LCD_WriteData(sy%256);
	LCD_WriteData(height/256); 
	LCD_WriteData(height%256); 	

	LCD_WriteCmd(0x2C);

#endif

#ifdef TFTLCD_ILI9486
	LCD_WriteCmd(0x2A);
	LCD_WriteData(sx/256);   
	LCD_WriteData(sx%256); 	 
	LCD_WriteData(width/256); 
	LCD_WriteData(width%256);
	
	LCD_WriteCmd(0x2B);
	LCD_WriteData(sy/256);  
	LCD_WriteData(sy%256);
	LCD_WriteData(height/256); 
	LCD_WriteData(height%256); 	

	LCD_WriteCmd(0x2C);

#endif

#ifdef TFTLCD_ST7793	
	if(tftlcd_data.dir==0)
	{
		LCD_WriteCmd(0x0210);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0211);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0212);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0213);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0200);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0201);   
	    LCD_WriteData(sy);	
	}   	
	else
	{
		LCD_WriteCmd(0x0212);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0213);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0210);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0211);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0201);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0200);   
	    LCD_WriteData(sy);	
	}
	LCD_WriteCmd(0x0202);		
#endif

#ifdef TFTLCD_NT5510	
		
#endif	
}

//ÇåÆÁº¯Êý
//color:ÒªÇåÆÁµÄÌî³äÉ«
void LCD_Clear(u16 color)
{
	uint16_t i, j ;

	LCD_Set_Window(0, 0, tftlcd_data.width-1, tftlcd_data.height-1);	 //×÷ÓÃÇøÓò
  	for(i=0; i<tftlcd_data.width; i++)
	{
		for (j=0; j<tftlcd_data.height; j++)
		{
			LCD_WriteData_Color(color);
		}
	} 
}


//ÔÚÖ¸¶¨ÇøÓòÄÚÌî³äµ¥¸öÑÕÉ«
//(sx,sy),(ex,ey):Ìî³ä¾ØÐÎ¶Ô½Ç×ø±ê,ÇøÓò´óÐ¡Îª:(ex-sx+1)*(ey-sy+1)   
//color:ÒªÌî³äµÄÑÕÉ«
void LCD_Fill(u16 xState,u16 yState,u16 xEnd,u16 yEnd,u16 color)
{          
	uint16_t temp;

    if((xState > xEnd) || (yState > yEnd))
    {
        return;
    }   
	LCD_Set_Window(xState, yState, xEnd-1, yEnd-1); 
    xState = xEnd - xState + 1;
	yState = yEnd - yState + 1;

	while(xState--)
	{
	 	temp = yState;
		while (temp--)
	 	{			
			LCD_WriteData_Color(color);	
		}
	}	
} 

//»­µã
//x,y:×ø±ê
//FRONT_COLOR:´ËµãµÄÑÕÉ«
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_Set_Window(x, y, x, y);  //ÉèÖÃµãµÄÎ»ÖÃ
	LCD_WriteData_Color(FRONT_COLOR);	
}

//¿ìËÙ»­µã
//x,y:×ø±ê
//color:ÑÕÉ«
void LCD_DrawFRONT_COLOR(u16 x,u16 y,u16 color)
{	   
	LCD_Set_Window(x, y, x, y);
	LCD_WriteData_Color(color);	
} 

//¶ÁÈ¡¸öÄ³µãµÄÑÕÉ«Öµ	 
//x,y:×ø±ê
//·µ»ØÖµ:´ËµãµÄÑÕÉ«
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;
	if(x>=tftlcd_data.width||y>=tftlcd_data.height)return 0;	//³¬¹ýÁË·¶Î§,Ö±½Ó·µ»Ø		     
	LCD_Set_Window(x, y, x, y);
	
#ifdef TFTLCD_HX8357D	
	LCD_WriteCmd(0X2E);     		 				    
 	r=LCD_ReadData();								//dummy Read	   
 	r=LCD_ReadData();  		  						//Êµ¼Ê×ø±êÑÕÉ«
#endif

#ifdef TFTLCD_R61509V	
	LCD_WriteCmd(0X0202);     		 				    
 	r=LCD_ReadData();								//dummy Read	   
 	r=LCD_ReadData(); 
	r=LCD_ReadData();	  						
#endif

#ifdef TFTLCD_R61509V3	
	LCD_WriteCmd(0X0202);     		 				    
 	r=LCD_ReadData();								//dummy Read	   
 	r=LCD_ReadData(); 
	r=LCD_ReadData();	  						
#endif

#ifdef TFTLCD_HX8352C	
	LCD_WriteCmd(0X22);     		 				    
 	r=TFTLCD->LCD_DATA;	
	r=LCD_ReadData();
#endif	

#ifdef TFTLCD_ILI9341	
	LCD_WriteCmd(0X2e);
	r=LCD_ReadData();								//dummy Read     		 				    
	r=LCD_ReadData();								//Êµ¼Ê×ø±êÑÕÉ«	
	//printf("r=%X\r\n",r);
	g=LCD_ReadData();
	b=LCD_ReadData(); 
	//printf("b=%X\r\n",b);
	//printf("g=%X\r\n",g);
	return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));
#endif

#ifdef TFTLCD_ILI9327	
	LCD_WriteCmd(0X2e);
	r=LCD_ReadData();								//dummy Read     		 				    
	r=LCD_ReadData();								//Êµ¼Ê×ø±êÑÕÉ«	
	r=(r<<8)|(r>>8);
	return r;
#endif

#ifdef TFTLCD_ILI9486	
	LCD_WriteCmd(0X2e);
	r=LCD_ReadData();								//dummy Read     		 				    
	r=LCD_ReadData();								//Êµ¼Ê×ø±êÑÕÉ«	
	//printf("r=%X\r\n",r);
	b=LCD_ReadData();
	g=LCD_ReadData(); 
	//printf("g=%X\r\n",g);
	//printf("b=%X\r\n",b);
	return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));
#endif

#ifdef TFTLCD_ST7793	
	if(x>=tftlcd_data.width||y>=tftlcd_data.height)return 0;	//³¬¹ýÁË·¶Î§,Ö±½Ó·µ»Ø		     
	LCD_Set_Window(x, y, x, y);
	LCD_WriteCmd(0x0202);     		 				    
 	r=LCD_ReadData();  		  						//Êµ¼Ê×ø±êÑÕÉ«
#endif
	
#ifdef TFTLCD_NT5510	
	
#endif	
 	return r;						
}

//»­Ïß
//x1,y1:Æðµã×ø±ê
//x2,y2:ÖÕµã×ø±ê  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //¼ÆËã×ø±êÔöÁ¿ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //ÉèÖÃµ¥²½·½Ïò 
	else if(delta_x==0)incx=0;//´¹Ö±Ïß 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//Ë®Æ½Ïß 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //Ñ¡È¡»ù±¾ÔöÁ¿×ø±êÖá 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//»­ÏßÊä³ö 
	{  
		LCD_DrawPoint(uRow,uCol);//»­µã 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

void LCD_DrawLine_Color(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //¼ÆËã×ø±êÔöÁ¿ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //ÉèÖÃµ¥²½·½Ïò 
	else if(delta_x==0)incx=0;//´¹Ö±Ïß 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//Ë®Æ½Ïß 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //Ñ¡È¡»ù±¾ÔöÁ¿×ø±êÖá 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//»­ÏßÊä³ö 
	{  
		LCD_DrawFRONT_COLOR(uRow,uCol,color);//»­µã 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 


// »­Ò»¸öÊ®×ÖµÄ±ê¼Ç
// x£º±ê¼ÇµÄX×ø±ê
// y£º±ê¼ÇµÄY×ø±ê
// color£º±ê¼ÇµÄÑÕÉ«
void LCD_DrowSign(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t i;

    /* »­µã */
    LCD_Set_Window(x-1, y-1, x+1, y+1);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color);   
    }

    /* »­Êú */
    LCD_Set_Window(x-4, y, x+4, y);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }

    /* »­ºá */
    LCD_Set_Window(x, y-4, x, y+4);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }
}

//»­¾ØÐÎ	  
//(x1,y1),(x2,y2):¾ØÐÎµÄ¶Ô½Ç×ø±ê
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//ÔÚÖ¸¶¨Î»ÖÃ»­Ò»¸öÖ¸¶¨´óÐ¡µÄÔ²
//(x,y):ÖÐÐÄµã
//r    :°ë¾¶
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //ÅÐ¶ÏÏÂ¸öµãÎ»ÖÃµÄ±êÖ¾
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//Ê¹ÓÃBresenhamËã·¨»­Ô²     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 

//ÔÚÖ¸¶¨Î»ÖÃÏÔÊ¾Ò»¸ö×Ö·û
//x,y:ÆðÊ¼×ø±ê
//num:ÒªÏÔÊ¾µÄ×Ö·û:" "--->"~"
//size:×ÖÌå´óÐ¡ 12/16/24
//mode:µþ¼Ó·½Ê½(1)»¹ÊÇ·Çµþ¼Ó·½Ê½(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//µÃµ½×ÖÌåÒ»¸ö×Ö·û¶ÔÓ¦µãÕó¼¯ËùÕ¼µÄ×Ö½ÚÊý	
 	num=num-' ';//µÃµ½Æ«ÒÆºóµÄÖµ£¨ASCII×Ö¿âÊÇ´Ó¿Õ¸ñ¿ªÊ¼È¡Ä££¬ËùÒÔ-' '¾ÍÊÇ¶ÔÓ¦×Ö·ûµÄ×Ö¿â£©
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=ascii_1206[num][t]; 	 	//µ÷ÓÃ1206×ÖÌå
		else if(size==16)temp=ascii_1608[num][t];	//µ÷ÓÃ1608×ÖÌå
		else if(size==24)temp=ascii_2412[num][t];	//µ÷ÓÃ2412×ÖÌå
		else return;								//Ã»ÓÐµÄ×Ö¿â
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawFRONT_COLOR(x,y,FRONT_COLOR);
			else if(mode==0)LCD_DrawFRONT_COLOR(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=tftlcd_data.height)return;		//³¬ÇøÓòÁË
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=tftlcd_data.width)return;	//³¬ÇøÓòÁË
				break;
			}
		}  	 
	}  	    	   	 	  
}   
//m^nº¯Êý
//·µ»ØÖµ:m^n´Î·½.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//ÏÔÊ¾Êý×Ö,¸ßÎ»Îª0,Ôò²»ÏÔÊ¾
//x,y :Æðµã×ø±ê	 
//len :Êý×ÖµÄÎ»Êý
//size:×ÖÌå´óÐ¡
//color:ÑÕÉ« 
//num:ÊýÖµ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 
//ÏÔÊ¾Êý×Ö,¸ßÎ»Îª0,»¹ÊÇÏÔÊ¾
//x,y:Æðµã×ø±ê
//num:ÊýÖµ(0~999999999);	 
//len:³¤¶È(¼´ÒªÏÔÊ¾µÄÎ»Êý)
//size:×ÖÌå´óÐ¡
//mode:
//[7]:0,²»Ìî³ä;1,Ìî³ä0.
//[6:1]:±£Áô
//[0]:0,·Çµþ¼ÓÏÔÊ¾;1,µþ¼ÓÏÔÊ¾.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//ÏÔÊ¾×Ö·û´®
//x,y:Æðµã×ø±ê
//width,height:ÇøÓò´óÐ¡  
//size:×ÖÌå´óÐ¡
//*p:×Ö·û´®ÆðÊ¼µØÖ·		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//ÅÐ¶ÏÊÇ²»ÊÇ·Ç·¨×Ö·û!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//ÍË³ö
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}

/****************************************************************************
*º¯ÊýÃû£ºLCD_ShowFontHZ
*Êä  Èë£ºx£ººº×ÖÏÔÊ¾µÄX×ø±ê
*      * y£ººº×ÖÏÔÊ¾µÄY×ø±ê
*      * cn£ºÒªÏÔÊ¾µÄºº×Ö
*      * wordColor£ºÎÄ×ÖµÄÑÕÉ«
*      * backColor£º±³¾°ÑÕÉ«
*Êä  ³ö£º
*¹¦  ÄÜ£ºÐ´¶þºÅ¿¬Ìåºº×Ö
****************************************************************************/
#if 0
void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn)	 
{  
	u8 i, j, wordNum;
	u16 color;
	while (*cn != '\0')
	{
		LCD_Set_Window(x, y, x+31, y+28);
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumÉ¨Ãè×Ö¿âµÄ×ÖÊý
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<116; i++) 
				{	//MSKµÄÎ»Êý
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_WriteData_Color(FRONT_COLOR); 						
						} 						
						else
						{
							LCD_WriteData_Color(BACK_COLOR); 
						} 
						color<<=1;
					}//for(j=0;j<8;j++)½áÊø
				}    
			}
		} //for (wordNum=0; wordNum<20; wordNum++)½áÊø 	
		cn += 2;
		x += 32;
	}
}
#endif


#if 1
void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn)
{
	u8 i, j, wordNum;
	u16 color;
	u16 x0=x; 
	u16 y0=y; 
	while (*cn != '\0')
	{
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumÉ¨Ãè×Ö¿âµÄ×ÖÊý
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<116; i++) 
				{	//MSKµÄÎ»Êý
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_DrawFRONT_COLOR(x,y,FRONT_COLOR);
						} 						
						else
						{
							LCD_DrawFRONT_COLOR(x,y,BACK_COLOR);
						} 
						color<<=1;
						x++;
						if((x-x0)==32)
						{
							x=x0;
							y++;
							if((y-y0)==29)
							{
								y=y0;
							}
						}
					}//for(j=0;j<8;j++)½áÊø
				}	
			}
			
		} //for (wordNum=0; wordNum<20; wordNum++)½áÊø 	
		cn += 2;
		x += 32;
		x0=x;
	}
}	
#endif

void LCD_ShowPicture(u16 x, u16 y, u16 wide, u16 high,u8 *pic)
{
	u16 temp = 0;
	long tmp=0,num=0;
	LCD_Set_Window(x, y, x+wide-1, y+high-1);
	num = wide * high*2 ;
	do
	{  
		temp = pic[tmp + 1];
		temp = temp << 8;
		temp = temp | pic[tmp];
		LCD_WriteData_Color(temp);//ÖðµãÏÔÊ¾
		tmp += 2;
	}
	while(tmp < num);	
}
