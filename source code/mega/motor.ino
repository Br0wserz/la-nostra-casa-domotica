
#include "header.h"

#define 	FNC_CAN_DX 		 1 //  3
#define 	FNC_CAN_SX 		 4 // 19
#define 	FNC_TEN_UP		 5 // 18
#define 	FNC_TEN_DW		 0 //  2


void init_motors()
{//=======================================    
	gate.begin(M_DX);
	tenda.begin(M_DOWN);

	attachInterrupt(FNC_CAN_SX, stop_gate_SX,	RISING);
	attachInterrupt(FNC_CAN_DX, stop_gate_DX,	RISING);
	attachInterrupt(FNC_TEN_UP, stop_tenda_UP,	RISING);
	attachInterrupt(FNC_TEN_DW, stop_tenda_DW,	RISING);
}

void control_gate()
{//=======================================
	if(check_fotocellula() && gate.getState() == M_START)
	{
		gate.enableMotor(M_STOP);
		digitalWrite(CAN_LED, LOW);
		delay(500);

		gate.move(M_DX, 240);
		digitalWrite(CAN_LED, HIGH);
		tm_can = millis();
	}
	if(!check_fotocellula())
		if(millis() - tm_can > 7000)
		{
			gate.move(M_SX, 240);
			digitalWrite(CAN_LED, HIGH);
			delay(120);
		}
}

void stop_gate_SX()
{//=======================================
	if(gate.getDirection() == M_SX && gate.getState() == M_START)
	{
		gate.enableMotor(M_STOP);
		digitalWrite(CAN_LED, LOW);
		gate.reverse();
	}
}

void stop_gate_DX()
{//=======================================
	if(gate.getDirection() == M_DX && gate.getState() == M_START)
	{
		gate.enableMotor(M_STOP);
		digitalWrite(CAN_LED, LOW);
		gate.reverse();
	}
}

void stop_tenda_UP()
{//=======================================
	if(tenda.getDirection() == M_UP && tenda.getState() == M_START)
	{
		tenda.enableMotor(M_STOP);
		tenda.reverse();
	}
}

void stop_tenda_DW()
{//=======================================
	if(tenda.getDirection() == M_DOWN && tenda.getState() == M_START)
	{
		tenda.enableMotor(M_STOP);
		tenda.reverse();
	}
}

