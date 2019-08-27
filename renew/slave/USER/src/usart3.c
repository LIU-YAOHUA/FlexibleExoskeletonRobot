#include "main.h"


/************************************************************
��������void usart3_init(u32 baud);
��  �Σ�u32 baud:������
����ֵ����
��  �ܣ�����3��ʼ��
��  �ߣ�meetwit
ʱ  �䣺2017��11��17��19:29:38
*************************************************************/
void usart3_init(u32 baud){
	/*
	1.��GPIOʱ��
	2.��ʼ��PB10(����	��������)  PB11(����	��������)
	3.������3ʱ��
	4.�ֳ���1����ʼλ��8������λ��1��ֹͣλ
	5.����ʹ��
	6.������
	7.����ʹ��
	*/
	float div,div_frr;
	u16 div_man;
	
	RCC ->APB2ENR |= (0x1<<3);//GPIOBʹ��
	GPIOB ->CRH &=~(0xF<<8);
	GPIOB ->CRH |=(0xB<<8);//��������
	
	GPIOB ->CRH &=~(0Xf<<12);
	GPIOB ->CRH |=(0X8<<12);//��������
	
	RCC ->APB1ENR |=(0x1<<18);//����3ʱ��ʹ��
	USART3->CR1 &=~(0x1<<12);//һ����ʼλ��8������λ
	USART3->CR2 &=~(0X3<<12);//һ��ֹͣλ
	USART3->CR1 |=(0x1<<3);//����ʹ��
	
	USART3->CR1|=(0x1<<2);    //����ʹ��
	USART3->CR1|=(1<<5);    //��USART_SR�е�ORE����RXNEΪ��1��ʱ������USART�ж�
	
	div=(float) 36000000/(baud * 16);
	div_man =div;
	div_frr=div-div_man;
	div_man <<= 4;
	
	USART3->BRR = div_man + (div_frr*16);
	
	/*�������ȼ�*/
	NVIC_SetPriority(USART3_IRQn,NVIC_EncodePriority(7-2,2,3));
	/*ʹ���ж�*/
	NVIC_EnableIRQ(USART3_IRQn);//NVIC_EnableIRQ������ʹ���ⲿ�жϵ�
	
	USART3->CR1 |=(0x1<<13);//����ʹ��	
}


/************************************************************
��������PcTx_Byte3(u8 Tx_data)
��  �Σ�u8 Tx_data
����ֵ����
��  �ܣ�����3����һ���ֽ�
��  �ߣ�meetwit
ʱ  �䣺2017��11��17��19:47:54
*************************************************************/
void PcTx_Byte3(char Tx_data){
	while(!(USART3->SR &(0x1<<7)));
	USART3 ->DR = Tx_data;
	
}

/************************************************************
��������PcTx_String3(u8 *str)
��  �Σ�u8 *str �ַ�����ַ
����ֵ����
��  �ܣ�����3�����ַ���
��  �ߣ�meetwit
ʱ  �䣺2017��11��17��19:47:38
*************************************************************/
void PcTx_String3(char *str){
		while(*str !='\0'){
			PcTx_Byte3(*(str++));
		}
}

void cope3(u8 data){
	static char len=0,d_rec[100];
	if(data=='S'){
		len=0;
	}
	d_rec[len]=data;
	len++;
	if(data=='E'){
		xnumx(d_rec,len,s3,usart3_m,REC_LEN3);
	}
}

/************************************************************
��������USART3_IRQHandler()
��  �Σ���
����ֵ����
��  �ܣ�����3�ж�
��  �ߣ�meetwit
ʱ  �䣺2017��11��17��19:47:27
*************************************************************/
	void USART3_IRQHandler(void)
{
	rt_interrupt_enter();
	u8 tempdata;
	if(USART3->SR&(0x1<<5))	//���յ�����
	{ 
		tempdata=USART3->DR;
		cope3(tempdata);
	}		
	rt_interrupt_leave();
}

void wifi_send(u8 type,float data){
	PcTx_Byte3(type);
	PcTx_Byte3(data);
	PcTx_Byte3(type);
}

