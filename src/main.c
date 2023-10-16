#include <REGX52.H>
#include "Timer0.h"
#include "Delay.h"

#define BEAT 150	//节拍
sbit buzzer = P2^5;	//蜂鸣器io口，不同型号mcu的io口不同，请查阅mcu原理图

unsigned int code NoteTable[60] = {62013,62211,62397,62574,62740,62897,63045,63185,63317,63441,63559,
63670,63775,63873,63967,64055,64138,64216,64290,64360,64426,64489,64547,64603,64655,64705,64751,
64795,64837,64876,64913,64948,64981,65012,65042,65069,65096,65120,65144,65166,65186,65206,65225,
65242,65259,65274,65289,65303,65316,65328,65340,65351,65361,65371,65380,65389,65397,65405,65412,
65419 };	//B大调-F大调	11.0592MHZ

enum note {b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12,
d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, f1, f2, f3,
f4, f5, f6, f7, f8, f9, f10, f11, f12, stop };	//音符

unsigned char code MusicScore[][2] = {	//乐谱
	{f5, 3}, {f3, 1}, {f1, 2}, {f1, 2},
	{f3, 2}, {f1, 2}, {f1, 4},
	{f5, 3}, {f3, 1}, {f1, 2}, {f1, 2},
	{f3, 2}, {f8, 2}, {f5, 4},
	{f5, 3}, {f3, 1}, {f1, 2}, {f1, 2},
	{f3, 2}, {f1, 2}, {f1, 2}, {f1, 1}, {f3, 1},
	{f4, 8},
	{f6, 8},
	{e5, 3}, {e3, 1}, {e1, 2}, {e1, 2},
	{e3, 2}, {e1, 2}, {e1, 4},
	{e5, 3}, {e3, 1}, {e1, 2}, {e1, 2},
	{e3, 2}, {e8, 2}, {e5, 4},
	{e5, 3}, {e3, 1}, {e1, 2}, {e1, 2},
	{e3, 2}, {e1, 2}, {e1, 2}, {e1, 1}, {e3, 1},
	{e4, 8},
	{e6, 8},
	{stop, 2}, {d3, 2}, {d3, 2}, {d1, 2},
	{d3, 1}, {d1, 1}, {c8, 4}, {c8, 2}, 
	{c8, 2}, {d1, 1}, {d3, 1}, {d3, 2}, {d1, 2},
	{d3, 2}, {d5, 2}, {d6, 2}, {d3, 2},
	{d1, 4}, {c12, 4},
	{d1, 4}, {c8, 3}, {c8, 1},
	{c8, 8},
	{stop, 2}, {d3, 2}, {d3, 2}, {d5, 2},
	{d6, 1}, {d5, 1}, {d1, 4}, {stop, 1}, {c8, 1},
	{c8, 2}, {d1, 1}, {d3, 1}, {d3, 2}, {d1, 2},
	{d3, 2}, {d5, 2}, {d6, 2}, {d3, 2},
	{d1, 4}, {c12, 4},
	{c10, 4}, {c8, 3}, {c8, 1},
	{c8, 8},
	{stop, 2}, {stop, 2}, {stop, 2}, {c12, 2},
	{d1, 2}, {c8, 2}, {d3, 2}, {c8, 2},
	{d5, 2}, {d3, 2}, {d6, 2}, {d6, 1}, {d5, 1},
	{d5, 2}, {d3, 2}, {d3, 2}, {d5, 2},
	{d5, 3}, {d3, 1}, {d3, 2}, {c8, 1}, {c8, 1},
	{d1, 2}, {c12, 2}, {d3, 2}, {d1, 2},
	{d6, 6}, {d5, 1}, {d3, 1},
	{d1, 8},
	{d6, 2},{d5, 2},{d6, 2},{d8, 2},
	{e1, 4}, {d12, 4},
	{d8, 2}, {d12, 2}, {e1, 2}, {e3, 2},
	{e5, 3}, {e1, 1}, {e1, 1}, {stop, 1}, {d8, 2},
	{e6, 2}, {e5, 2}, {e3, 2}, {e1, 2},
	{e3, 2}, {e5, 1}, {e5, 5},
	{stop, 2}, {d8, 2}, {e1, 2}, {d12, 2},
	{e1, 2}, {d8, 1}, {d8, 1}, {stop, 2}, {d8, 2},
	{e3, 2}, {e1, 1}, {e1, 1}, {stop, 2}, {d12, 2},
	{e1, 4}, {e3, 4},
	{d12, 2}, {d12, 2}, {e1, 2}, {e3, 2},
	{e5, 3}, {e1, 1}, {e1, 1}, {stop, 1}, {d8, 2},
	{e6, 2}, {e5, 2}, {e3, 2}, {e1, 2},
	{e3, 2}, {e5, 1}, {e5, 5},
	{stop, 2}, {d8, 2}, {e1, 2}, {d12, 2},
	{e1, 2}, {d8, 1}, {d8, 1}, {stop, 2}, {d8, 2},
	{e3, 2}, {e1, 1}, {e1, 1}, {stop, 2}, {d12, 2},
	{d12, 3}, {e1, 5},
	{stop, 2}, {stop, 2}, {stop, 2}, {d12, 2},
	{d12, 3}, {e1, 3}, {e3, 2},
	{e5, 3}, {e1, 3}, {d12, 2},
	{d12, 3}, {e1, 5},
	{stop, 3}, {d1, 1}, {d6, 1}, {d5, 1}, {d1, 1},
};

unsigned int p = 0;	//控制演奏指针，每隔指定拍数后移

void main()
{
	Timer0_Init();
	
	while(1)
	{
		Delay(BEAT*MusicScore[p][1]);
		TR0 = 0;
		Delay(5);
		TR0 = 1;	
		p++;
	}
}

void Timer0_Routine() interrupt 1 //定时器0中断
{
	if (MusicScore[p][0]!=stop)
	{
		TL0 = NoteTable[MusicScore[p][0]]%256;
		TH0 = NoteTable[MusicScore[p][0]]/256;
		buzzer = ~buzzer;
	}
	else
		buzzer = 0;
}
