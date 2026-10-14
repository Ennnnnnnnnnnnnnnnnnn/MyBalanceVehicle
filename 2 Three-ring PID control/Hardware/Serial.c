#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t Serial_rxdata;
uint8_t Serial_rxflag;

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	
	USART_Cmd(USART1,ENABLE);
}

void Serial_SendByte(uint8_t byte)
{
	USART_SendData(USART1,byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//Transmit data register empty flag
	
}

void Serial_SendArray(uint8_t* array,uint16_t length)
{
	uint16_t i;
	for(i=0;i<length;i++)
	{
		Serial_SendByte(array[i]);
	}
}

void Serial_SendString(char* string)
{
	uint16_t i;
	for(i=0;string[i]!='\0';i++)
	{
		Serial_SendByte(string[i]);
	}
}

uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
	uint32_t result=1;
	while(Y--)
	{
		result*=X;
	}
	return result;
}

void Serial_SendNum(uint32_t number,uint8_t length)
{
	uint8_t i;
	for(i=0;i<length;i++)
	{
		Serial_SendByte(number/Serial_Pow(10,length-i-1)%10+'0');//要加偏移    ‘0’对应0x30
	}
}

int fputc(int ch,FILE* f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char* format,...)
{
	char string[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(string,format,arg);
	va_end(arg);
	Serial_SendString(string);
}

uint8_t Serial_GetRxFlag(void)
{
	if(Serial_rxflag==1)
	{
		Serial_rxflag=0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxdata(void)
{
	return Serial_rxdata;
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		Serial_rxdata=USART_ReceiveData(USART1);
		Serial_rxflag=1;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
