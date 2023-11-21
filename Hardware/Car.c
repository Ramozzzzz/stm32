#include "stm32f10x.h"
#include "Motor.h"
#include "Serial.h"

int8_t Car_Speed;

void Car_Stop()
{
    Motor_SpeedSet(0,3);
    Motor_SpeedSet(0,4);
    Car_Speed=0;
    Serial_SendString("Stop\r\n");
}

void Car_Forward(int8_t speed)
{
    Motor_SpeedSet(speed,3);
    Motor_SpeedSet(speed,4);
    Car_Speed=speed;
    Serial_SendString("Forward\r\n");
}

void Car_Backward(int8_t speed)
{
    Motor_SpeedSet(-speed,3);
    Motor_SpeedSet(-speed,4);
    Car_Speed=-speed;
    Serial_SendString("Backward\r\n");
}

void Car_TurnLeft()
{
    Car_Speed=0;
    Motor_SpeedSet(-40,3);
    Motor_SpeedSet(40,4);
    Serial_SendString("Turn Left\r\n");
}

void Car_TurnRight()
{
    Car_Speed=0;
    Motor_SpeedSet(40,3);
    Motor_SpeedSet(-40,4);
    Serial_SendString("Turn Right\r\n");
}

void Car_SpeedUp()
{
    if(Car_Speed<0x70){
        Car_Speed+=0x10;
        Motor_SpeedSet(Car_Speed,3);
        Motor_SpeedSet(Car_Speed,4);
        Serial_SendString("Speed Up\r\n");
    }
}

void Car_SpeedDown()
{
    if(-Car_Speed<0x70){
        Car_Speed-=0x10;
        Motor_SpeedSet(Car_Speed,3);
        Motor_SpeedSet(Car_Speed,4);
        Serial_SendString("SPeed Down\r\n");
    }
}
