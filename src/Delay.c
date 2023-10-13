#include "Delay.h"

void Delay(unsigned int x)		//@11.0592MHz
{
	unsigned char i, j;

	while (x--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}