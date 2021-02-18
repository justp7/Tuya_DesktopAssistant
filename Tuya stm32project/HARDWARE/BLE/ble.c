#include "ble.h"
#include <jansson.h>
#include "03WTC.h"

int up_net,down_net;
u8 up_status,down_status;
u8 memory_rate,cpu_rate;

u8 PC_Data(u8* Data)
{
	json_error_t error;
	json_t *root;

	root = json_loads((const char*)Data, 0, &error);
	if(json_is_object(root))
	{
		up_net = json_integer_value(json_object_get(root, "ni"));
		down_net = json_integer_value(json_object_get(root, "no"));
		up_status = json_integer_value(json_object_get(root, "si"));
		down_status = json_integer_value(json_object_get(root, "so"));
		memory_rate = json_integer_value(json_object_get(root, "m"));
		cpu_rate = json_integer_value(json_object_get(root, "c"));
	}
	else
	{
			return 1;
	}
	json_decref(root);//重要！！！必须释放  释放JSON空间
	return 0;
}
void PC_Show(void)
{
	//网速
	Data_set(up_data,(u16)up_net);
	Data_set(down_data,(u16)down_net);
	//网速
	if(up_status == 0)
		Text_set(up_text,"B/s ",4);
	else if(up_status == 1)
		Text_set(up_text,"KB/s",4);
	else if(up_status == 2)
		Text_set(up_text,"M/s ",4);
	else if(up_status == 3)
		Text_set(up_text,"G/s ",4);
	//网速
	if(down_status == 0)
		Text_set(down_text,"B/s ",4);
	else if(down_status == 1)
		Text_set(down_text,"KB/s",4);
	else if(down_status == 2)
		Text_set(down_text,"M/s ",4);
	else if(down_status == 3)
		Text_set(down_text,"G/s ",4);
	
	Icon_Rotate(spin_icon,(u16)((100-memory_rate)*3.6));//内存图标旋转
	Curve_set(cpu_rate);//CPU数据刷新
	Data_set(CPU_data,(u16)cpu_rate);//CPU数据显示
}

