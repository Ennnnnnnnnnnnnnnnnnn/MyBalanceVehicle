#ifndef _MPU6050_H
#define _MPU6050_H

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
void MPU6050_Init(void);
void MPU6050_GetData(int16_t* AccX,int16_t* AccY,int16_t* AccZ,int16_t* GryoX,int16_t* GryoY,int16_t* GryoZ);
uint8_t MPU6050_GetID(void);
#endif 

