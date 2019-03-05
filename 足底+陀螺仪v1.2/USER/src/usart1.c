#include "usart1.h"
#include "usart2.h"
#include "string.h"
#include "stdio.h"
/*一般.c定义数据*/
u8 Rx_Buf[Rx_Max];
u16 Rx_End,Rx_Len,Rx_Tm;

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
int _sys_exit(int x) 
{ 
	x = x;
return 0;	
} 
//重定向fputc函数
//printf的输出，指向fputc，由fputc输出到串口
//这里使用串口1(USART1)输出printf信息
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成  
	USART1->DR = (u8) ch;      	//写DR,串口1将发送数据
	return ch;
}
#endif 
/************************************************************
函数名：void usart_init(u32 baud);
形  参：u32 baud:波特率
返回值：无
功  能：串口1初始化
作  者：meetwit
时  间：2017年11月13日15:15:43
*************************************************************/
void usart_init(u32 baud){
	/*
	1.开GPIO时钟
	2.初始化PA9(发送	复用推挽)  PA10(接收	浮空输入)
	3.开串口1时钟
	4.字长：1个起始位，8个数据位，1个停止位
	5.发送使能
	6.波特率
	7.串口使能
	*/
	float div,div_frr;
	u16 div_man;
	
	RCC ->APB2ENR |= (0x1<<2);//GPIOA使能
	GPIOA ->CRH &=~(0xF<<4);
	GPIOA ->CRH |=(0xB<<4);//复用推挽
	
	GPIOA ->CRH &=~(0Xf<<8);
	GPIOA ->CRH |=(0X8<<8);//浮空输入
	
	RCC ->APB2ENR |=(0x1<<14);//串口1时钟使能
	USART1->CR1 &=~(0x1<<12);//一个起始位，8个数据位
	USART1->CR2 &=~(0X3<<12);//一个停止位
	USART1->CR1 |=(0x1<<3);//发送使能
	
	USART1->CR1|=(0x1<<2);    //接收使能
	USART1->CR1|=(1<<5);    //当USART_SR中的ORE或者RXNE为’1’时，产生USART中断
	
	div=(float) 72000000/(baud * 16);
	div_man =div;
	div_frr=div-div_man;
	div_man <<= 4;
	
	USART1->BRR = div_man + (div_frr*16);
	
	/*设置优先级*/
	NVIC_SetPriority(USART1_IRQn,NVIC_EncodePriority(7-2,2,1));
	/*使能中断*/
	NVIC_EnableIRQ(USART1_IRQn);//NVIC_EnableIRQ是用来使能外部中断的
	
	USART1->CR1 |=(0x1<<13);//串口使能	
}


/************************************************************
函数名：PcTx_Byte(u8 Tx_data)
形  参：u8 Tx_data
返回值：无
功  能：串口1发送一个字节
作  者：meetwit
时  间：2017年11月13日15:48:50
*************************************************************/
void PcTx_Byte(u8 Tx_data){
	while(!(USART1->SR &(0x1<<7)));
	USART1 ->DR = Tx_data;
	
}

/************************************************************
函数名：PcTx_String(u8 *str)
形  参：u8 *str 字符串地址
返回值：无
功  能：串口1发送字符串
作  者：meetwit
时  间：2017年11月13日15:48:50
*************************************************************/
void PcTx_String(u8 *str){
		while(*str !='\0'){
			PcTx_Byte(*(str++));
		}
}

/************************************************************
函数名：USART1_IRQHandler()
形  参：无
返回值：无
功  能：串口1中断
作  者：meetwit
时  间：2017年11月16日11:32:11
*************************************************************/
	void USART1_IRQHandler(void)
{
	u8 tempdata;
	if(USART1->SR&(0x1<<5))	//接收到数据
	{ 
		tempdata=USART1->DR;
		if((Rx_End==0)&&(Rx_Len<Rx_Max)){
				Rx_Buf[Rx_Len++]=tempdata;
				Rx_Tm=5;//每次重新赋值3
		}
	}		
}


/************************************************************
函数名：Task_Pc()
形  参：无
返回值：无
功  能：串口1接收完成，打印
作  者：meetwit
时  间：2017年11月16日11:32:11
*************************************************************/
void Task_Pc()
{
	if(Rx_End==1){
		
		Rx_End=0;
		Rx_Len=0;
		memset(Rx_Buf,0,sizeof(Rx_Buf));
	}
}
