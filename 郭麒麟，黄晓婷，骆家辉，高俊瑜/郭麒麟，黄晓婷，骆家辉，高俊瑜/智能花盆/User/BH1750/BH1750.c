
#include "BH1750.h"

uint8_t rdat[2]={0};


void BH1750_Start()
{
ee_WriteBytes(BHAddWrite,BHPowOn);
}

unsigned char  Read_Light()
{
  //ee_WriteBytes(BHAddWrite,BHPowOn);
	uint16_t Light;
	ee_WriteBytes(BHAddWrite,BHModeH1);
	ee_Delay(250);
	ee_ReadBytes(rdat,BHAddRead,2);
	ee_Delay(250);
	Light=conversion()/1.2;// 根据手册读取的数据除以1.2就得到单位位lx的光强度检测值。
	return Light;
}


unsigned short conversion()  //  转换测量结果
{  
  u16 light;
	light=rdat[1]<<8; //高八位
	light+=0x00ff&rdat[0];
	light=(float)light/65535*100;
	return light;
	
	
}
