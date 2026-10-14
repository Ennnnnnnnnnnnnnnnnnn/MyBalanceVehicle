#ifndef _SERIAL_H
#define _SERIAL_H
#include <stdio.h>

void Serial_Init(void);
void Serial_SendByte(uint8_t byte);
void Serial_SendArray(uint8_t* array,uint16_t length);
void Serial_SendString(char* string);
void Serial_SendNum(uint32_t number,uint8_t length);
void Serial_Printf(char* format,...);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxdata(void);
#endif
