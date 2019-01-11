
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
	Light=conversion()/1.2;// �����ֲ��ȡ�����ݳ���1.2�͵õ���λλlx�Ĺ�ǿ�ȼ��ֵ��
	return Light;
}


unsigned short conversion()  //  ת���������
{  
  u16 light;
	light=rdat[1]<<8; //�߰�λ
	light+=0x00ff&rdat[0];
	light=(float)light/65535*100;
	return light;
	
	
}
