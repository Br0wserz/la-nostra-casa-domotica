#include <Signal.h>
#include <driverL293D.h>

#include "header.h"


Motor garage(11, 12, 6);
Motor tsolar(10,  8, 9);

Signal lg_gard(5, RL_OFF, OUTPUT);

short max = 0;
short sx, dx, ct;
short tollerance;

bool motor_dir;
bool ldr_flag = RL_OFF;

unsigned long tm_batt = millis();


void setup()
{//=======================================
	init_motor();

	pinMode(LG_GAR,  OUTPUT);
	pinMode(GAR_LED, OUTPUT);
    pinMode(BATTERY, OUTPUT);
    
    digitalWrite(BATTERY, RL_OFF);
	Serial.begin(9600);
}

void loop()
{//=======================================
	ldr_flag = (analogRead(LDR) < 300) ? RL_ON : RL_OFF;
	digitalWrite(LG_GAR, (garage.getDirection() == M_UP) && !ldr_flag);
	lg_gard.setState(ldr_flag);

	sx = analogRead(LDR_SX);
	dx = analogRead(LDR_DX);
	ct = analogRead(LDR_CT);

	tollerance = (short)(analogRead(LDR) * 0.015f);

	if((dx - sx) > +tollerance) max = dx, motor_dir = M_DX;
	if((dx - sx) < -tollerance) max = sx, motor_dir = M_SX;

	if((ct - max) > +tollerance || !ldr_flag)
		tsolar.enableMotor(M_STOP);
	else
		tsolar.move(motor_dir, 180);

	if(millis() - tm_batt > ONE_MINUTE)
	{
		tm_batt = millis();
		digitalWrite(BATTERY, RL_OFF);
		delay(400);

		if(analogRead(BAT_LV) < 980)
			digitalWrite(BATTERY, RL_ON);
	}

	if(Serial.available() && Serial.read() == 'G') 
	{
		garage.move((byte)(200));
		digitalWrite(GAR_LED, HIGH);
	}
}

