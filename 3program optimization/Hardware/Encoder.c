#include "stm32f10x.h"                  // Device header


void Encoder_Init(void)
{
	/*TIM3*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
	TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TimeBaseInitStructure.TIM_Period=65536-1;//ARR
	TimeBaseInitStructure.TIM_Prescaler=1-1;//PSC
	TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TimeBaseInitStructure);

	
	TIM_ICInitTypeDef TIM_ICInitstructure;
	TIM_ICStructInit(&TIM_ICInitstructure);
	TIM_ICInitstructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitstructure.TIM_ICFilter=0xF;
	TIM_ICInit(TIM3,&TIM_ICInitstructure);
	TIM_ICInitstructure.TIM_Channel=TIM_Channel_2;
	TIM_ICInitstructure.TIM_ICFilter=0xF;
	TIM_ICInit(TIM3,&TIM_ICInitstructure);
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_Cmd(TIM3,ENABLE);
	
	
	/*TIM4*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	

	TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TimeBaseInitStructure.TIM_Period=65536-1;//ARR
	TimeBaseInitStructure.TIM_Prescaler=1-1;//PSC
	TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM4,&TimeBaseInitStructure);

	

	TIM_ICStructInit(&TIM_ICInitstructure);
	TIM_ICInitstructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitstructure.TIM_ICFilter=0xF;
	TIM_ICInit(TIM4,&TIM_ICInitstructure);
	TIM_ICInitstructure.TIM_Channel=TIM_Channel_2;
	TIM_ICInitstructure.TIM_ICFilter=0xF;
	TIM_ICInit(TIM4,&TIM_ICInitstructure);
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Falling);
	
	TIM_Cmd(TIM4,ENABLE);
}

int16_t Encoder_Get(uint8_t n)
{
	int16_t Temp;
	if(n==1)
	{
		Temp=TIM_GetCounter(TIM3);
		TIM_SetCounter(TIM3,0);
		return Temp;
	}
	else if(n==2)
	{
		Temp=TIM_GetCounter(TIM4);
		TIM_SetCounter(TIM4,0);
		return Temp;
	}
	return 0;
}


