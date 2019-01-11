#ifndef _BH1750_H_
#define _BH1750_H_
#include <stm32f10x.h>
#include "iic.h"
#include "stdio.h"

#define BHAddWrite     0x46      //从机地址+最后写方向位
#define BHAddRead      0x47      //从机地址+最后读方向位
#define BHPowDown      0x00      //关闭模块
#define BHPowOn        0x01      //打开模块等待测量指令
#define BHReset        0x07      //重置数据寄存器值在PowerOn模式下有效
#define BHModeH1       0x10      //高分辨率 单位1lx 测量时间120ms
#define BHModeH2       0x11      //高分辨率模式2 单位0.5lx 测量时间120ms
#define BHModeL        0x13      //低分辨率 单位4lx 测量时间16ms

void BH1750_Start(void);
unsigned short conversion(void );  //  转换测量结果
unsigned char Read_Light(void);






#endif

