#ifndef __USART2_H
#define __USART2_H	 

#include "sys.h"

#define Rx_Max2 512
extern u8 Rx_Buf2[Rx_Max2];
extern s8 res2;
extern u16 Rx_End2,Rx_Len2,Rx_Tm2;

void uart2_init(u32 pclk2,u32 bound);	//≥ı ºªØ		
void PcTx_Byte2(u8 Tx_data);
void PcTx_String2(u8 *str);
void Task_Pc2(void);



#endif

















