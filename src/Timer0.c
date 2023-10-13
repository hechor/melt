#include <REGX52.H>

void Timer0_Init(void)		//11.0592MHz
{
	TMOD &= 0xF0;		//定时器0模式选择
	TMOD |= 0x01;
	TL0 = 0xFF;		//设置定时器初值
	TH0 = 0xFF;		
	TF0 = 0;		//计数溢出标志
	TR0 = 1;		//T0的运行控制位
	ET0 = 1;	//设置中断源
	EA = 1;		//开启中断
	PT0 = 0;	//设置中断优先级
}
