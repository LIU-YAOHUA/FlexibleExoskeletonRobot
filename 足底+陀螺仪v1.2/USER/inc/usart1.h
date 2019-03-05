#ifndef __USART1_H
#define __USART1_H	 

#include "stm32f10x.h"

#define Rx_Max 512
extern u8 Rx_Buf[Rx_Max];
extern u16 Rx_End,Rx_Len,Rx_Tm;

void usart_init(u32 baud);	//≥ı ºªØ		
void PcTx_Byte(u8 Tx_data);
void PcTx_String(u8 *str);
void Task_Pc(void);


#endif

















