#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Timer.h"
#include "Key.h"
#include "MPU6050.h"
#include "Motor.h"
#include "Encoder.h"
#include "Serial.h"
#include "BlueSerial.h"


/*OLED和LED测试程序*/
//int main(void)
//{
//	OLED_Init();
//	LED_Init();
//	
//	OLED_Printf(0,0,OLED_8X16,"Hello,World!!");
//	OLED_Printf(0,16,OLED_6X8,"Hello,World!!");
//	OLED_Update();
//	

//	
//	while(1)
//	{
//		LED_ON();
//		Delay_ms(500);
//		LED_OFF();
//		Delay_ms(500);
//	}
//	
//}



/*定时中断和非阻塞式按键测试*/
//uint16_t count;
//uint8_t KeyNum,Num;

//int main(void)
//{
//	OLED_Init();
//	Key_Init();
//	Timer_Init();
//	
//	
//	OLED_Printf(0,56,OLED_6X8,"LWH,GENIUS!!!");
//	
//	while(1)
//	{
//		KeyNum=Key_GetNum();
//		if(KeyNum==1)
//		{
//			Num++;
//		}
//		if(KeyNum==2)
//		{
//			Num--;
//		}
//		if(KeyNum==3)
//		{
//			Num+=10;
//		}
//		if(KeyNum==4)
//		{
//			Num-=10;
//		}
//		
//		OLED_Printf(0,0,OLED_8X16,"count=%05d",count);
//		OLED_Printf(0,16,OLED_8X16,"Num=%03d",Num);
//		OLED_Update();
//	}
//}

//void TIM1_UP_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
//	{
//		Key_Tick();
//		
//		count++;
//		
//		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
//	}
//}




/*MPU6050测试*/
//int16_t AX,AY,AZ,GX,GY,GZ;
//uint8_t TimerErrorFlag=0;
//uint16_t TimerCount;
//int main(void)
//{
//	OLED_Init();
//	MPU6050_Init();
//	
//	Timer_Init();
//	while(1)
//	{
//		
//		OLED_Printf(0,0,OLED_8X16,"%+06d",AX);
//		OLED_Printf(0,16,OLED_8X16,"%+06d",AY);
//		OLED_Printf(0,32,OLED_8X16,"%+06d",AZ);
//		OLED_Printf(64,0,OLED_8X16,"%+06d",GX);
//		OLED_Printf(64,16,OLED_8X16,"%+06d",GY);
//		OLED_Printf(64,32,OLED_8X16,"%+06d",GZ);
//		OLED_Printf(0,48,OLED_8X16,"Flag:%1d",TimerErrorFlag);
//		OLED_Printf(64,48,OLED_8X16,"C:%05d",TimerCount);
//		OLED_Update();
//	}
//}

//void TIM1_UP_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
//	{
//		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
//		MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);
//		if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
//		{
//			TimerErrorFlag=1;
//			TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
//			
//		}
//		TimerCount=TIM_GetCounter(TIM1);
//	}
//}




/*直流电机和编码器测试*/
int8_t PWML,PWMR;
uint8_t KeyNum;
float SpeedL,SpeedR;

int main(void)
{
	OLED_Init();
	Key_Init();
	Motor_Init();
	Timer_Init();
	Encoder_Init();
	
	OLED_Printf(0,56,OLED_6X8,"LWH,GENIUS!!!");
	
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			PWML+=10;
		}
		if(KeyNum==2)
		{
			PWML-=10;
		}
		if(KeyNum==3)
		{
			PWMR+=10;
		}
		if(KeyNum==4)
		{
			PWMR-=10;
		}
		
		Motor_SetSpeed(1,PWML);
		Motor_SetSpeed(2,PWMR);
		
		
		OLED_Printf(0,0,OLED_8X16,"PWML=%+04d",PWML);
		OLED_Printf(0,16,OLED_8X16,"PWMR=%+04d",PWMR);
		OLED_Printf(0,32,OLED_8X16,"SpeedL=%+06.2f",SpeedL);
		OLED_Printf(0,48,OLED_8X16,"SpeedR=%+06.2f",SpeedR);
		
		OLED_Update();
	}
}

void TIM1_UP_IRQHandler(void)
{
	static uint16_t count;
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
	{
		Key_Tick();

		count++;
		if(count>=50)
		{
			count=0;
			SpeedL=Encoder_Get(1)/44.0/0.05/9.27666;
			SpeedR=Encoder_Get(2)/44.0/0.05/9.27666;
			
		}
		
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
	}
}


/*串口和蓝牙串口测试*/
//int main()
//{
//	OLED_Init();
//	Serial_Init();
//	BlueSerial_Init();
//	
//	Serial_SendString("HELLO");
//	printf(",WORLD");
//	printf("\r\nLWH,GENIUS!!!");

//	BlueSerial_SendString("NIHAO");
//	BlueSerial_Printf("World");
//	while(1)
//	{
//		if(Serial_GetRxFlag()==1)
//		{
//			uint8_t RXData=Serial_GetRxdata();
//			OLED_Printf(0,0,OLED_8X16,"RXData:%02X",RXData);
//			OLED_Update();
//		}
//		
//		if(BlueSerial_RxFlag==1)
//		{
//			OLED_Printf(0,0,OLED_8X16,"%s",BlueSerial_RxPacket);
//			OLED_Update();
//			
//			BlueSerial_RxFlag=0;
//		}
//	}
//}
