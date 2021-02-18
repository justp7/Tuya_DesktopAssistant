#ifndef __BLE_H__
#define __BLE_H__
#include "sys.h"

extern int up_net,down_net;
extern u8 up_status,down_status;
extern u8 memory_rate,cpu_rate;

u8 PC_Data(u8* Data);
void PC_Show(void);

#endif

