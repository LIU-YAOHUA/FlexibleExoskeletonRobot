#ifndef __USART1_H
#define __USART1_H	 

#include "stm32f10x.h"

void usart_init(u32 baud);	//≥ı ºªØ		
void PcTx_Byte(u8 Tx_data);
void PcTx_String(u8 *str);


#endif

















