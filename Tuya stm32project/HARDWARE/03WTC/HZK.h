#ifndef __HZK_H_
#define __HZK_H_

char weather_HZK_sheet[43][8] =
{
	//图标编号
	//暴雪 0
	{0xB4,0xF3,0xD1,0xA9,},//0大雪
	{0xB1,0xA9,0xD1,0xA9},//1暴雪
	//暴雨 1
	{0xB4,0xF3,0xD3,0xEA},//2大雨
	{0xB1,0xA9,0xD3,0xEA},//3暴雨
	{0xCC,0xD8,0xB4,0xF3,0xB1,0xA9,0xD3,0xEA},//4特大暴雨
	{0xB4,0xF3,0xB1,0xA9,0xD3,0xEA},//5大暴雨
	{0xD6,0xD0,0xD3,0xEA},//6中雨
	{0xD6,0xD0,0xB5,0xBD,0xB4,0xF3,0xD3,0xEA},//7中到大雨
	{0xB4,0xF3,0xB5,0xBD,0xB1,0xA9,0xD3,0xEA},//8大到暴雨
	//多云 4
	{0xB6,0xE0,0xD4,0xC6},//9多云
	//浮尘 6
	{0xB8,0xA1,0xB3,0xBE},//10浮尘
	{0xF6,0xB2},//11霾
	//雷阵雨 7
	{0xC0,0xD7,0xD5,0xF3,0xD3,0xEA},//12雷阵雨
	//晴天8
	{0xC7,0xE7},//13晴
	{0xB4,0xF3,0xB2,0xBF,0xC7,0xE7,0xC0,0xCA},//14大部晴朗
	//闪电 9
	{0xC0,0xD7,0xB5,0xE7},//15雷电
	{0xC0,0xD7,0xB1,0xA9},//16雷暴
	//少云 10
	{0xC9,0xD9,0xD4,0xC6},//17少云
	//特大雷阵雨 11
	
	//特大扬沙 12
	{0xC9,0xB3,0xB3,0xBE,0xB1,0xA9},//18沙尘暴
	{0xC7,0xBF,0xC9,0xB3,0xB3,0xBE,0xB1,0xA9},//19强沙尘暴
	//雾 17
	{0xB6,0xB3,0xCE,0xED},//20冻雾
	{0xCE,0xED},//21雾
	//小雨 18
	{0xD0,0xA1,0xD5,0xF3,0xD3,0xEA},//22小阵雨
	{0xD3,0xEA},//23雨
	{0xD0,0xA1,0xB5,0xBD,0xD6,0xD0,0xD3,0xEA},//24小到中雨
	{0xD0,0xA1,0xD3,0xEA},//25小雨
	//扬沙 19
	{0xD1,0xEF,0xC9,0xB3},//26扬沙
	{0xB3,0xBE,0xBE,0xED,0xB7,0xE7},//27尘卷风
	//阴 20
	{0xD2,0xF5},//28阴
	//雨夹雪 21
	{0xD3,0xEA,0xBC,0xD0,0xD1,0xA9},//29雨夹雪
	//阵雨 22
	{0xBE,0xD6,0xB2,0xBF,0xD5,0xF3,0xD3,0xEA},//30局部阵雨
	{0xD5,0xF3,0xD3,0xEA},//31阵雨
	{0xC7,0xBF,0xD5,0xF3,0xD3,0xEA},//32强阵雨
	
	//中雪 23
	{0xD0,0xA1,0xD1,0xA9},//33小雪
	{0xD1,0xA9},//34雪
	{0xD0,0xA1,0xB5,0xBD,0xD6,0xD0,0xD1,0xA9},//35小到中雪
	{0xD0,0xA1,0xD5,0xF3,0xD1,0xA9},//36小阵雪
	{0xD6,0xD0,0xD1,0xA9},//37中雪
	{0xD5,0xF3,0xD1,0xA9},//38阵雪
	
	//其他情况
	{0xB1,0xF9,0xC1,0xA3},//39冰粒
	{0xB1,0xF9,0xB1,0xA2},//40冰雹	
	{0xB1,0xF9,0xD5,0xEB},//41冰针
	{0xB6,0xB3,0xD3,0xEA},//42冻雨

};


#endif
