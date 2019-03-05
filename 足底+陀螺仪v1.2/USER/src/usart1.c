#include "usart1.h"
#include "usart2.h"
#include "string.h"
#include "stdio.h"
/*һ��.c��������*/
u8 Rx_Buf[Rx_Max];
u16 Rx_End,Rx_Len,Rx_Tm;

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
int _sys_exit(int x) 
{ 
	x = x;
return 0;	
} 
//�ض���fputc����
//printf�������ָ��fputc����fputc���������
//����ʹ�ô���1(USART1)���printf��Ϣ
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//�ȴ���һ�δ������ݷ������  
	USART1->DR = (u8) ch;      	//дDR,����1����������
	return ch;
}
#endif 
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

/************************************************************
��������USART1_IRQHandler()
��  �Σ���
����ֵ����
��  �ܣ�����1�ж�
��  �ߣ�meetwit
ʱ  �䣺2017��11��16��11:32:11
*************************************************************/
	void USART1_IRQHandler(void)
{
	u8 tempdata;
	if(USART1->SR&(0x1<<5))	//���յ�����
	{ 
		tempdata=USART1->DR;
		if((Rx_End==0)&&(Rx_Len<Rx_Max)){
				Rx_Buf[Rx_Len++]=tempdata;
				Rx_Tm=5;//ÿ�����¸�ֵ3
		}
	}		
}


/************************************************************
��������Task_Pc()
��  �Σ���
����ֵ����
��  �ܣ�����1������ɣ���ӡ
��  �ߣ�meetwit
ʱ  �䣺2017��11��16��11:32:11
*************************************************************/
void Task_Pc()
{
	if(Rx_End==1){
		
		Rx_End=0;
		Rx_Len=0;
		memset(Rx_Buf,0,sizeof(Rx_Buf));
	}
}
