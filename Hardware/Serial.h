#ifndef __SERIAL_H__
#define __SERIAL_H__

void Serial_Init();
void Serial_SendData(uint8_t data);
void Serial_SendString(char *str);

#endif