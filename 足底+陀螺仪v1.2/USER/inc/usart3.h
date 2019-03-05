#ifndef __USART3_H
#define __USART3_H	 

#include "stm32f10x.h"

#define Rx_Max3 512
extern u8 Rx_Buf3[Rx_Max3];
extern u16 Rx_End3,Rx_Len3,Rx_Tm3;

void usart3_init(u32 baud);	//≥ı ºªØ		
void PcTx_Byte3(u8 Tx_data);
void PcTx_String3(u8 *str);
void PcTx_String3x(u8 *str);
void Task_Pc3(void);



#endif

















