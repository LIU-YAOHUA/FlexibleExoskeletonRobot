#include "main.h"


/************************************************************
��������void usart_init(u32 baud);
��  �Σ�u32 baud:������
����ֵ����
��  �ܣ�����1��ʼ��
��  �ߣ�meetwit
ʱ  �䣺2017��11��13��15:15:43
*************************************************************/
void usart_init(u32 baud){
	/*
	1.��GPIOʱ��
	2.��ʼ��PA9(����	��������)  PA10(����	��������)
	3.������1ʱ��
	4.�ֳ���1����ʼλ��8������λ��1��ֹͣλ
	5.����ʹ��
	6.������
	7.����ʹ��
	*/
	float div,div_frr;
	u16 div_man;
	
	RCC ->APB2ENR |= (0x1<<2);//GPIOAʹ��
	GPIOA ->CRH &=~(0xF<<4);
	GPIOA ->CRH |=(0xB<<4);//��������
	
	GPIOA ->CRH &=~(0Xf<<8);
	GPIOA ->CRH |=(0X8<<8);//��������
	
	RCC ->APB2ENR |=(0x1<<14);//����1ʱ��ʹ��
	USART1->CR1 &=~(0x1<<12);//һ����ʼλ��8������λ
	USART1->CR2 &=~(0X3<<12);//һ��ֹͣλ
	USART1->CR1 |=(0x1<<3);//����ʹ��
	
	USART1->CR1|=(0x1<<2);    //����ʹ��
	USART1->CR1|=(1<<5);    //��USART_SR�е�ORE����RXNEΪ��1��ʱ������USART�ж�
	
	div=(float) 72000000/(baud * 16);
	div_man =div;
	div_frr=div-div_man;
	div_man <<= 4;
	
	USART1->BRR = div_man + (div_frr*16);
	
	/*�������ȼ�*/
	NVIC_SetPriority(USART1_IRQn,NVIC_EncodePriority(7-2,2,1));
	/*ʹ���ж�*/
	NVIC_EnableIRQ(USART1_IRQn);//NVIC_EnableIRQ������ʹ���ⲿ�жϵ�
	
	USART1->CR1 |=(0x1<<13);//����ʹ��	
}


/************************************************************
��������PcTx_Byte(u8 Tx_data)
��  �Σ�u8 Tx_data
����ֵ����
��  �ܣ�����1����һ���ֽ�
��  �ߣ�meetwit
ʱ  �䣺2017��11��13��15:48:50
*************************************************************/
void PcTx_Byte(u8 Tx_data){
	while(!(USART1->SR &(0x1<<7)));
	USART1 ->DR = Tx_data;
	
}

/************************************************************
��������PcTx_String(u8 *str)
��  �Σ�u8 *str �ַ�����ַ
����ֵ����
��  �ܣ�����1�����ַ���
��  �ߣ�meetwit
ʱ  �䣺2017��11��13��15:48:50
*************************************************************/
void PcTx_String(u8 *str){
		while(*str !='\0'){
			PcTx_Byte(*(str++));
		}
}

void cope1(u8 data){
	static char len=0,d_rec[100];
	if(data=='S'){
		len=0;
	}
	d_rec[len]=data;
	len++;
	if(data=='E'){
		xnumx(d_rec,len,s1,usart1_m,REC_LEN1);
	}
}

/************************************************************
��������USART1_IRQHandler()
��  �Σ���
����ֵ����
��  �ܣ�����2�ж�
��  �ߣ�meetwit
ʱ  �䣺2017��11��19��11:27:43
*************************************************************/
	void USART1_IRQHandler(void)
{
		rt_interrupt_enter();
	u8 tempdata;
	if(USART1->SR&(0x1<<5))	//���յ�����
	{ 
		tempdata=USART1->DR;
		CopeSerialData(tempdata);
	}		
	rt_interrupt_leave();
}

