#ifndef __WEATHER_H
#define __WEATHER_H


//��������б��� ���� else�ж�
char weather_sheet[43][12] =
{
	//ͼ����
	//��ѩ 0
	{0xE5,0xA4,0xA7 ,0xE9,0x9B,0xAA},//0��ѩ
	{0xE6,0x9A,0xB4 ,0xE9,0x9B,0xAA},//1��ѩ
	//���� 1
	{0xE5,0xA4,0xA7 ,0xE9,0x9B,0xA8},//2����
	{0xE6,0x9A,0xB4 ,0xE9,0x9B,0xA8},//3����
	{0xE7,0x89,0xB9 ,0xE5,0xA4,0xA7 ,0xE6,0x9A,0xB4,0xE9,0x9B,0xA8},//4�ش���
	{0xE5,0xA4,0xA7 ,0xE6,0x9A,0xB4 ,0xE9,0x9B,0xA8},//5����
	{0xE4,0xB8,0xAD ,0xE9,0x9B,0xA8},//6����
	{0xE4,0xB8,0xAD ,0xE5,0x88,0xB0 ,0xE5,0xA4,0xA7 ,0xE9,0x9B,0xA8},//7�е�����
	{0xE5,0xA4,0xA7 ,0xE5,0x88,0xB0 ,0xE6,0x9A,0xB4 ,0xE9,0x9B,0xA8},//8�󵽱���
	//���� 4
	{0xE5,0xA4,0x9A ,0xE4,0xBA,0x91},//9����
	//���� 6
	{0xE6,0xB5,0xAE ,0xE5,0xB0,0x98},//10����
	{0xE9,0x9C,0xBE},//11��
	//������ 7
	{0xE9,0x9B,0xB7 ,0xE9,0x98,0xB5 ,0xE9,0x9B,0xA8},//12������
	//����8
	{0xE6,0x99,0xB4},//13��
	{0xE5,0xA4,0xA7 ,0xE9,0x83,0xA8 ,0xE6,0x99,0xB4 ,0xE6,0x9C,0x97},//14������
	//���� 9
	{0xE9,0x9B,0xB7 ,0xE7,0x94,0xB5},//15�׵�
	{0xE9,0x9B,0xB7 ,0xE6,0x9A,0xB4},//16�ױ�
	//���� 10
	{0xE5,0xB0,0x91 ,0xE4,0xBA,0x91},//17����
	//�ش������� 11
	
	//�ش���ɳ 12
	{0xE6,0xB2,0x99 ,0xE5,0xB0,0x98,0xE6,0x9A,0xB4},//18ɳ����
	{0xE5,0xBC,0xBA ,0xE6,0xB2,0x99 ,0xE5,0xB0,0x98 ,0xE6,0x9A,0xB4},//19ǿɳ����
	//�� 17
	{0xE5,0x86,0xBB ,0xE9,0x9B,0xBE},//20����
	{0xE9,0x9B,0xBE},//21��
	//С�� 18
	{0xE5,0xB0,0x8F ,0xE9,0x98,0xB5 ,0xE9,0x9B,0xA8},//22С����
	{0xE9,0x9B,0xA8},//23��
	{0xE5,0xB0,0x8F ,0xE5,0x88,0xB0 ,0xE4,0xB8,0xAD ,0xE9,0x9B,0xA8},//24С������
	{0xE5,0xB0,0x8F ,0xE9,0x9B,0xA8},//25С��
	//��ɳ 19
	{0xE6,0x89,0xAC ,0xE6,0xB2,0x99},//26��ɳ
	{0xE5,0xB0,0x98 ,0xE5,0x8D,0xB7 ,0xE9,0xA3,0x8E},//27������
	//�� 20
	{0xE9,0x98,0xB4},//28��
	//���ѩ 21
	{0xE9,0x9B,0xA8 ,0xE5,0xA4,0xB9 ,0xE9,0x9B,0xAA},//29���ѩ
	//���� 22
	{0xE5,0xB1,0x80 ,0xE9,0x83,0xA8 ,0xE9,0x98,0xB5 ,0xE9,0x9B,0xA8},//30�ֲ�����
	{0xE9,0x98,0xB5 ,0xE9,0x9B,0xA8},//31����
	{0xE5,0xBC,0xBA ,0xE9,0x98,0xB5 ,0xE9,0x9B,0xA8},//32ǿ����
	
	//��ѩ 23
	{0xE5,0xB0,0x8F ,0xE9,0x9B,0xAA},//33Сѩ
	{0xE9,0x9B,0xAA},//34ѩ
	{0xE5,0xB0,0x8F ,0xE5,0x88,0xB0 ,0xE4,0xB8,0xAD ,0xE9,0x9B,0xAA},//35С����ѩ
	{0xE5,0xB0,0x8F ,0xE9,0x98,0xB5 ,0xE9,0x9B,0xAA},//36С��ѩ
	{0xE4,0xB8,0xAD ,0xE9,0x9B,0xAA},//37��ѩ
	{0xE9,0x98,0xB5 ,0xE9,0x9B,0xAA},//38��ѩ
	
	//�������
	{0xE5,0x86,0xB0 ,0xE7,0xB2,0x92},//39����
	{0xE5,0x86,0xB0 ,0xE9,0x9B,0xB9},//40����	
	{0xE5,0x86,0xB0 ,0xE9,0x92,0x88},//41����
	{0xE5,0x86,0xBB ,0xE9,0x9B,0xA8},//42����
};

#endif
