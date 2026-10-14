#include "stm32f10x.h"                  // Device header
#include "MYI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS 0xD0


void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveACK();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveACK();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveACK();
	MyI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t data;
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveACK();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveACK();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS|0x01);  //原来地址是写地址
	MyI2C_ReceiveACK();
	data=MyI2C_ReceiveByte();
	MyI2C_SendACK(1);
	MyI2C_Stop();
	
	return data;
}

void MPU6050_ReadRegs(uint8_t RegAddress,uint8_t* DataArray,uint8_t count)
{
	uint8_t i;
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveACK();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveACK();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS|0x01);  //原来地址是写地址
	MyI2C_ReceiveACK();
	for(i=0;i<count;i++)
	{
		DataArray[i]=MyI2C_ReceiveByte();
		if(i<count-1)
		{
			MyI2C_SendACK(0);
		}
		else
		{
			MyI2C_SendACK(1);
		}
		
	}
		
	MyI2C_Stop();

}

void MPU6050_Init(void)
{
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);
}

//void MPU6050_GetData(int16_t* AccX,int16_t* AccY,int16_t* AccZ,int16_t* GryoX,int16_t* GryoY,int16_t* GryoZ)
//{
//	uint16_t DataH,DataL;
//	DataH=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
//	DataL=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
//	*AccX=(DataH<<8)|DataL;
//	
//	DataH=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
//	DataL=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
//	*AccY=(DataH<<8)|DataL;
//	
//	DataH=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
//	DataL=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
//	*AccZ=(DataH<<8)|DataL;
//	
//	
//	DataH=MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
//	DataL=MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
//	*GryoX=(DataH<<8)|DataL;
//	
//	DataH=MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
//	DataL=MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
//	*GryoY=(DataH<<8)|DataL;
//	
//	DataH=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
//	DataL=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
//	*GryoZ=(DataH<<8)|DataL;
//}

void MPU6050_GetData(int16_t* AccX,int16_t* AccY,int16_t* AccZ,int16_t* GryoX,int16_t* GryoY,int16_t* GryoZ)
{
	uint8_t Data[14];
	MPU6050_ReadRegs(MPU6050_ACCEL_XOUT_H,Data,14);
	*AccX=(Data[0]<<8)|Data[1];
	*AccY=(Data[2]<<8)|Data[3];
	*AccZ=(Data[4]<<8)|Data[5];
	
	*GryoX=(Data[8]<<8)|Data[9];
	*GryoY=(Data[10]<<8)|Data[11];
	*GryoZ=(Data[12]<<8)|Data[13];
}


uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

