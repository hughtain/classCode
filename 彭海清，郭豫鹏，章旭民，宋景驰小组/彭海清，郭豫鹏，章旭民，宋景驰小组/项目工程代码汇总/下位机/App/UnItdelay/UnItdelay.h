#ifndef _UnItdelay_H
#define _UnItdelay_H

#include "system.h"
#include "includes.h"



 

//OS_EXT  INT32U       OSIdleCtrRun;
//OS_EXT  INT32U       OSIdleCtrMax;


void unitdelay_us(u16 time);
void unitdelay_ms(u16 time);
void ToString(char array[], int array_size);
void reqorder(char *input,char *output,int counter);




#endif

//#ifdef   fan_GLOBALS
//#define  fan_EXT
//#else
//#define  fan_EXT extern
//#endif

//fan_EXT  int  fanmodel;