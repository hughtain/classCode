#include<reg52.h>
#include <intrins.h>
#include <absacc.h>		  //头文件
#define uint unsigned int
#define uchar unsigned char	  //宏定义

//按键
sbit key1=P3^2;	   //布防
sbit key2=P3^3;	   //撤防
sbit key3=P3^4;	   //紧急报警

sbit BUZZ=P0^4;	   //蜂鸣器
sbit rsd=P2^4;	   //热释电输入
sbit LED_B=P2^3;   //布防指示灯
sbit LED_S=P2^0;   //发送消息指示灯

uchar code PhoneNO[]		="15046397767"; //接受号码

uchar code somebody[]		="8BF76CE8610FFF0167094EBA8FDB516562A58B66830356F4FF01";	//请注意！有人进入报警范围！												  

uint TIME_50ms=0;	   //计时的最小分辨率50ms
uint time_continue;	   //蜂鸣器鸣响时计时数据暂存
bit flag=0,flag_BF=0;  //flag：值为0时，是布防计时模式，值为1时，是一分钟等待模式。flag_BF：布防标志位
bit flag_time_start=0; //开始计时标志位
bit again=0;		   //一分钟等待标志位（当发送一条短信后，不能马上发送第二天，所以等待一分钟后再检测是否有人，有人再发送短信）
bit flag_alam;		   //报警标志位
bit SOS;			   //发送短信时是否是按下紧急按键
bit flag_continue;	   //继续计时
bit into_BF=0;

void delay(uint z)//延时函数
{
	uint x,y;
	for(x=z;x>0;x--)
	for(y=110;y>0;y--);
}

void Uart_init()
{
	TMOD= 0X20;		//T1  方式2  ，8位   自动重装   
	TH1=0Xfd;
	TL1=0Xfd;	    //9600波特率
	TR1=1; 		    // 定时器1启动  
	SM0=0;	    // 设置串口的工作模式
	SM1=1; 	    //方式1

	REN=0; 		 // 不允许串口接收数据 	 

	ES=0; 	     // 串口中断不允许 
	EA=1;		 // 开启中断总开关 
}

void SendASC(uchar d)	//串口发送字符
{
	
	SBUF=d;				//数据赋值到缓冲区
	while(!TI);			//发送完

	TI=0;				//清零
}

void SendString(uchar *str)	  //串口发送字符串
{
	while(*str)				  //判断是否发送完
	{
		SendASC(*str) ;		  //发送字符
		str++;				  //字符位置加
		//delay_uart(1);
	}
}

void TIME()						//计时函数
{
	if(flag==0)					//布防计时模式
	{
		delay(50);				//50ms
		TIME_50ms++;			//50ms变量加1
		if(TIME_50ms%10==0)		//每500ms（50ms*10）
		LED_B=!LED_B;			//布防指示灯取反一次
		
		if(TIME_50ms>=400)		//加到400次，也就是50ms*400=20000ms=20s
		{
			TIME_50ms=0;		//计时变量清零
			flag_BF=1;			//进入布防状态
			LED_B=0;			//布防指示灯长亮
			flag_time_start=0;	//停止计时
			again=1;			//关闭一分钟等待
		}	
	}
	else						//一分钟等待模式
	{
		delay(50);				//50ms
		TIME_50ms++;			//变量加
		if(TIME_50ms%10==0)		//每加500ms
		{
			LED_B=!LED_B;		//布防指示灯闪烁
			if(flag_alam==1)	//报警
			{
				if(flag_continue==0)//进入报警时
				{
					flag_continue=1;//此标志位置一，防止报警时进入
					time_continue=TIME_50ms; //将进入报警时的计时数据暂存
				}
				BUZZ=!BUZZ;		//蜂鸣器取反，也就是闪烁响
				if(TIME_50ms>=time_continue+100)//当报警时间达到5s时
				{
					BUZZ=1;						//关闭蜂鸣器
					flag_continue=0;			//标志位清零，等待下次报警
					flag_alam=0;				//报警变量清零，停止报警
					time_continue=0;			//暂存计时数据清零
				}	
			}
		}
		if(TIME_50ms>=1200)		   //计时达到60秒
		{
			LED_B=0;			   //布防指示灯长亮，准备检测热释电信号
			TIME_50ms=0;		   //计时变量清零
			flag_time_start=0;	   //停止计时
			again=1;			   //关闭一分钟等待
		}
	}
}

//按键扫描函数
void keyscan()
{
	if(key1==0&&flag_BF==0)//在非布防状态时布防按键按下
	{
		delay(5);//延时去抖
		if(key1==0)		   //再次判断按键是否按下
		{
			LED_B=0;	   //点亮布防LED灯
			flag=0;		   //变量清零
			flag_time_start=1;//开始计时变量置一
		}
		while(key1==0);	   //按键释放
	}
	if(flag_time_start==1)	//开始计时
	{
		TIME();				//调用计时函数
	}
	if(key2==0)				//撤防按键按下
	{			   
		delay(5);//延时去抖
		if(key2==0)		   //再次判断按键是否按下
		{
			BUZZ=1;			//关闭蜂鸣器 
			flag_alam=0;	//报警变量清零
			flag_BF=0;		//布防变量清零
			flag=0;			//变量清零
			flag_time_start=0;//开始计时变量清零
			LED_S=1;		//关闭发送短信指示灯
			LED_B=1;		//关闭布防指示灯
		}
		while(key2==0);		//按键释放
	}
	if(key3==0)				//紧急按键按下
	{
		delay(5);			//延时去抖
		if(key3==0)			//再次判断按键是否按下
		{
			SOS=1;			//手动发送短信变量置一，准备发送短信
			flag_alam=1;	//报警变量置一
		}
		while(key3==0);		//按键释放
	}
} 

void GSM_work()				//发送GSM短信
{
	unsigned char send_number;	//定义发送手机号的变量
	if(rsd==0&&flag_BF==1)		//布防状态且热释电有信号时
	flag_alam=1;				//报警变量置一

	if((rsd==0&&flag_BF==1&&again==1)||SOS==1)//布防状态且热释电有信号时且不在一分钟等待时间内  或者   手动按下紧急按键
	{
		LED_S=0;								 //打开发送短信指示灯
		BUZZ=1;									 //关闭蜂鸣器
		SendString("AT+CMGF=1\r\n");			 //设置文本模式
		
		delay(1000);							 //延时，让GSM模块有一个反应时间
		
		SendString("AT+CSCS=\"UCS2\"\r\n");		 //设置短信格式，发送汉字模式
		
		delay(1000);							 //延时
		
		SendString("AT+CSMP=17,0,2,25\r\n");	 //设置短信文本模式参数（具体内容参考开发资料内的模块资料）
		
		delay(1000);							 //延时
		
		SendString("AT+CMGS=");	//信息发送指令 AT+CMGS=//
		SendASC('"');									 //引号
		for(send_number=0;send_number<11;send_number++)	 //在每位号码前加003
		{
			SendASC('0');
			SendASC('0');
			SendASC('3');
			SendASC(PhoneNO[send_number]);				 //接收手机号码
		}     
		SendASC('"');									//引号
		SendASC('\r');			//发送回车指令//
		SendASC('\n');			//发送换行指令//
		
		delay(1000);				//延时

		SendString(somebody);		//发送短信内容
	
		delay(1000);				//延时
		
		SendASC(0x1a);				//确定发送短信
		
		if(SOS==0)					//不是紧急按键发送短信
		{
			again=0;				//again清零，也就是进入一分钟等待，当计时到一分钟后，该变量重新置一
			flag_time_start=1;		//开始计时
			flag_alam=1;			//报警
		}
		else if(SOS==1&&flag_time_start==1)	 //紧急按键发送短信后
		{											  
			TIME_50ms=0;					 //计时数据清零
			flag_BF=1;						 //布防变量置一
			LED_B=0;						 //点亮布防指示灯
			flag_time_start=0;				 //停止计时
			again=1;						 //不进入一分钟等待
		}
		
		LED_S=1;							 //熄灭发送短信指示灯
		SOS=0;								 //紧急变量清零
		flag=1;								 //变量置一
	}
}	
void main()									 //主函数
{	
	Uart_init();							 //调用中断初始化函数
	while(1)								 //进入while循环
	{
		keyscan();							 //按键函数
		GSM_work();							 //发送短信函数
	}	  
}