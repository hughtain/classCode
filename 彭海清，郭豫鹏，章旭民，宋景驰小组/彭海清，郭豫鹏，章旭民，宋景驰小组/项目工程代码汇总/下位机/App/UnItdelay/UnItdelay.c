#include "UnItdelay.h"
#include "system.h"
#include "string.h"
#include "includes.h"
#include <stdio.h>






void ToString(char array[], int array_size)
{
			char *p;
			int i;
			p = (char*)malloc(array_size + 1);
			for(i = 0; i < array_size; i++)
			{
			*(p+i) = '0' + array[i];
			}
			*(p+i) = '\0';
			//printf("int array is string %s\n", p);
			//return *p;
}



void reqorder(char *input,char *output,int counter)//���ָ���ȡ�ַ���
{
    int i=0, j=0;
    char *p=input;
    char *buf=NULL;

    while((char)(*p)!='\0')
    {
        if((char)(*p)=='?')
        {
            if(i==counter)
            {
                buf=p+1;
                while((char)(*buf)!='\0' && (char)(*buf)!='?')
                {
                    j++;
                    buf++;
                }
                strncpy(output,p+1,j);
                return;
            }
            i++;
        }
        p++;
    }
}




void unitdelay_us(u16 time)//���ж�΢��
{    
   u16 i=0;  
   while(time--)
   {
      i=10;  //????
      while(i--) ;    
   }
}
//??????
void unitdelay_ms(u16 time)//���жϺ���
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //????
      while(i--) ;    
   }
}