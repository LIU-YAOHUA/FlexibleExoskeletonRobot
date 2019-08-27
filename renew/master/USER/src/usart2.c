#include "main.h"
/*一般.c定义数据*/
u8 Rx_Buf2[Rx_Max2];
s8 res2;
u16 Rx_End2,Rx_Len2,Rx_Tm2;

/************************************************************
函数名：void usart2_init(u32 baud);
形  参：u32 pclk2：串口2时钟频率， u32 baud:波特率
返回值：无
功  能：串口2初始化
作  者：meetwit
时  间：2018年8月1日10:37:34
*************************************************************/
void uart2_init(u32 pclk2,u32 bound)
{  	 
	u32	temp;	   
	temp=(pclk2*1000000+bound/2)/bound;	//得到USARTDIV@OVER8=0,采用四舍五入计算
	RCC->AHB1ENR|=1<<0;   	//使能PORTA口时钟  
	RCC->APB1ENR|=1<<17;  	//使能串口2时钟 
	GPIO_Set(GPIOA,PIN2|PIN3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA2,PA3,复用功能,上拉输出
 	GPIO_AF_Set(GPIOA,2,7);	//PA2,AF7
	GPIO_AF_Set(GPIOA,3,7);//PA3,AF7  	   
	//波特率设置
 	USART2->BRR=temp; 		//波特率设置@OVER8=0 	
	USART2->CR1=0;		 	//清零CR1寄存器
	USART2->CR1|=0<<28;	 	//设置M1=0
	USART2->CR1|=0<<12;	 	//设置M0=0&M1=0,选择8位字长 
	USART2->CR1|=0<<15; 	//设置OVER8=0,16倍过采样 
	USART2->CR1|=1<<3;  	//串口发送使能 
	//使能接收中断 
	USART2->CR1|=1<<2;  	//串口接收使能
	USART2->CR1|=1<<5;    	//接收缓冲区非空中断使能	    	
	MY_NVIC_Init(3,3,USART2_IRQn,2);//组2，最低优先级 
	USART2->CR1|=1<<0;  	//串口使能
}






/************************************************************
函数名：PcTx_Byte2(u8 Tx_data)
形  参：u8 Tx_data
返回值：无
功  能：串口2发送一个字节
作  者：meetwit
时  间：2017年11月19日11:26:55
*************************************************************/
void PcTx_Byte2(u8 Tx_data){
	while(!(USART2->ISR &(0x1<<7)));
	USART2 ->TDR = Tx_data;
	//while((USART1->ISR&0X40)==0);//等待发送结束
}

/************************************************************
函数名：PcTx_String2(u8 *str)
形  参：u8 *str 字符串地址
返回值：无
功  能：串口2发送字符串
作  者：meetwit
时  间：2017年11月19日11:27:21
*************************************************************/
void PcTx_String2(u8 *str){
		while(*str !='\0'){
			PcTx_Byte2(*(str++));
		}
}

/************************************************************
函数名：USART2_IRQHandler()
形  参：无
返回值：无
功  能：串口2中断
作  者：meetwit
时  间：2017年11月19日11:27:43
*************************************************************/
	void USART2_IRQHandler(void)
{
	//u8 res;
		if(USART2->ISR&(1<<5))//接收到数据
	{	 
		/*
		res=USART2->DR; 
		if((Rx_End2==0)&&(Rx_Len2<Rx_Max2)){
				Rx_Buf2[Rx_Len2++]=res;
				Rx_Tm2=3;//每次重新赋值5
		}
		*/
		res2=USART2->RDR;
	}		
}

/************************************************************
函数名：Task_Pc2()
形  参：无
返回值：无
功  能：串口2接收完成，打印
作  者：meetwit
时  间：2017年11月19日11:28:38
*************************************************************/
void Task_Pc2()
{
	if(Rx_End2==1){
		//PcTx_String2(Rx_Buf2);
		
		Rx_End2=0;
		Rx_Len2=0;
		memset(Rx_Buf2,0,sizeof(Rx_Buf2));
	}
}
