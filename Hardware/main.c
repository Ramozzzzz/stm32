#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Motor.h"
#include "Serial.h"
#include "Car.h"
#include "Ultrasonic.h"
#include "Timer.h"
#include "Delay.h"

extern uint8_t RxFlag;
extern uint8_t Serial_RxPacket;
extern int8_t Car_Speed;
uint8_t Mode=1;
extern uint64_t time_now;
extern uint64_t time_end;

int main()
{
	OLED_Init();
	Motor_Init();
	Motor_SpeedSet(0,3);
	Motor_SpeedSet(0,4);
	Serial_Init();
	Ultrasonic_Init();
	Timer_Init();
	OLED_ShowString(1,1,"Speed:");
	OLED_ShowString(2,1,"State:");
	OLED_ShowString(3,1,"Distance:");
	while(1){
		OLED_ShowSignedNum(4,1,Ultrasonic_Measure(),10);
		Delay_ms(50);
		if(Mode==1){			
			if(RxFlag==1){
		
				if(Serial_RxPacket==0xcc){
					Car_SpeedUp();
					if(Car_Speed<0){
						OLED_ShowString(1,8,"-");
						OLED_ShowHexNum(1,9,-Car_Speed,2);
						OLED_ShowString(2,8,"Backward ");
					}	
					else{
						OLED_ShowString(1,8,"+");
						OLED_ShowHexNum(1,9,Car_Speed,2);
						OLED_ShowString(2,8,"Forward  ");
					}	
				}
				else if(Serial_RxPacket==0xdd){
					Car_SpeedDown();
					if(Car_Speed<0){
						OLED_ShowString(1,8,"-");
						OLED_ShowHexNum(1,9,-Car_Speed,2);
						OLED_ShowString(2,8,"Backward ");
					}	
					else{
						OLED_ShowString(1,8,"+");
						OLED_ShowHexNum(1,9,Car_Speed,2);
						OLED_ShowString(2,8,"Forward  ");
					}
				}
				else if(Serial_RxPacket==0xaa){
					Car_TurnLeft();
					OLED_ShowHexNum(1,9,Car_Speed,2);
					OLED_ShowString(2,8,"Turnleft ");
				}
				else if(Serial_RxPacket==0xbb){
					Car_TurnRight();
					OLED_ShowHexNum(1,9,Car_Speed,2);
					OLED_ShowString(2,8,"TurnRight");
				}
				else if(Serial_RxPacket==0xee){
					Car_Stop();
					OLED_ShowHexNum(1,9,Car_Speed,2);
					OLED_ShowString(2,8,"Stop     ");
				}
				else if(Serial_RxPacket==0x50){
					Car_Forward(50);
					OLED_ShowHexNum(1,9,Car_Speed,2);
					OLED_ShowString(2,8,"Forward");
				}
				else if(Serial_RxPacket==0x55){
					Car_Backward(50);
					OLED_ShowHexNum(1,9,Car_Speed,2);
					OLED_ShowString(2,8,"Backward");
				}
				else if(Serial_RxPacket==0x22)
					Mode=2;
					
					Serial_SendString("OK\r\n");
					RxFlag=0;
			}
		}
		else if(Mode==2){
			Car_Forward(50);
			while(Ultrasonic_Measure()>200 && RxFlag==0);
			if(RxFlag==1){
				Car_Stop();
				Mode=1;
				RxFlag=0;
			}
			else{
				Car_Stop();
				Car_TurnLeft();
				time_now=0;
				while(time_now<150000);
				//while(Ultrasonic_Measure()<200);
				Car_Stop();
				//Car_Forward(50);
			}
		}
		
	}
}
