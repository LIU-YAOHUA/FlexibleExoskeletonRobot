#include "main.h"
/*一般.c定义数据*/
u8 Rx_Buf3[Rx_Max3];
s8 res3;
u16 Rx_End3,Rx_Len3,Rx_Tm3;

/************************************************************
函数名：void usart3_init(u32 baud);
形  参：u32 baud:波特率
返回值：无
功  能：串口3初始化
作  者：meetwit
时  间：2017年11月17日19:29:38
*************************************************************/
void uart3_init(u32 pclk2,u32 bound)
{  	 
		u32	temp;	   
	temp=(pclk2*1000000+bound/2)/bound;	//得到USARTDIV@OVER8=0,采用四舍五入计算
	RCC->AHB1ENR|=1<<1;   	//使能PORTB口时钟  
	RCC->APB1ENR|=1<<18;  	//使能串口2时钟 
	GPIO_Set(GPIOB,PIN10|PIN11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA2,PA3,复用功能,上拉输出
 	GPIO_AF_Set(GPIOB,10,7);	//PA2,AF7
	GPIO_AF_Set(GPIOB,11,7);//PA3,AF7  	   
	//波特率设置
 	USART3->BRR=temp; 		//波特率设置@OVER8=0 	
	USART3->CR1=0;		 	//清零CR1寄存器
	USART3->CR1|=0<<28;	 	//设置M1=0
	USART3->CR1|=0<<12;	 	//设置M0=0&M1=0,选择8位字长 
	USART3->CR1|=0<<15; 	//设置OVER8=0,16倍过采样 
	USART3->CR1|=1<<3;  	//串口发送使能 
	//使能接收中断 
	USART3->CR1|=1<<2;  	//串口接收使能
	USART3->CR1|=1<<5;    	//接收缓冲区非空中断使能	    	
	MY_NVIC_Init(3,3,USART3_IRQn,2);//组2，最低优先级 
	USART3->CR1|=1<<0;  	//串口使能
}


/************************************************************
函数名：PcTx_Byte3(u8 Tx_data)
形  参：u8 Tx_data
返回值：无
功  能：串口3发送一个字节
作  者：meetwit
时  间：2017年11月17日19:47:54
*************************************************************/
void PcTx_Byte3(u8 Tx_data){
	while(!(USART3->ISR &(0x1<<7)));
	USART3 ->TDR = Tx_data;
	
}

/************************************************************
函数名：PcTx_String3(u8 *str)
形  参：u8 *str 字符串地址
返回值：无
功  能：串口3发送字符串
作  者：meetwit
时  间：2017年11月17日19:47:38
*************************************************************/
void PcTx_String3(u8 *str){
		while(*str !='\0'){
			PcTx_Byte3(*(str++));
		}
}

/************************************************************
函数名：USART3_IRQHandler()
形  参：无
返回值：无
功  能：串口3中断
作  者：meetwit
时  间：2017年11月17日19:47:27
*************************************************************/
	void USART3_IRQHandler(void)
{
	//u8 tempdata;
	if(USART3->ISR&(0x1<<5))	//接收到数据
	{ 
		/*
		tempdata=USART3->DR;
		if((Rx_End3==0)&&(Rx_Len3<Rx_Max3)){
				Rx_Buf3[Rx_Len3++]=tempdata;
				Rx_Tm3=5;//每次重新赋值5
		}
		*/	
		res3 =	USART3->RDR; 
	}
}

/************************************************************
函数名：Task_Pc3()
形  参：无
返回值：无
功  能：串口3接收完成，打印
作  者：meetwit
时  间：2017年11月17日19:47:12
*************************************************************/
void Task_Pc3()
{
	if(Rx_End3==1){
		PcTx_String3(Rx_Buf3);
	
		Rx_End3=0;
		Rx_Len3=0;
		memset(Rx_Buf3,0,sizeof(Rx_Buf3));
	}
}
