#ifndef __USART3_H
#define __USART3_H	 

#include "sys.h"

#define Rx_Max3 512
extern u8 Rx_Buf3[Rx_Max3];
extern s8 res3;

extern u16 Rx_End3,Rx_Len3,Rx_Tm3;

void uart3_init(u32 pclk2,u32 bound);
void PcTx_Byte3(u8 Tx_data);
void PcTx_String3(u8 *str);
void Task_Pc3(void);


#endif

















