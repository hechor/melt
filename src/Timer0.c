#include <REGX52.H>

void Timer0_Init(void)		//1??@11.0592MHz
{
	TMOD &= 0xF0;		//��ʱ��0ģʽѡ��
	TMOD |= 0x01;
	TL0 = 0xFF;		//���ö�ʱ����ֵ
	TH0 = 0xFF;		
	TF0 = 0;		//���������־
	TR0 = 1;		//T0�����п���λ
	ET0 = 1;	//�����ж�Դ
	EA = 1;		//�����ж�
	PT0 = 0;	//�����ж����ȼ�
}