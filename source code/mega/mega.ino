#include <DHT.h>
#include <Signal.h>
#include <driverL293D.h>

#include "header.h"


DHT dht;
TH_info th_info = { 0.0, 0.0 };


Motor gate (29, 28, 10);
Motor tenda(36, 37,  9);

Signal fontana(40, RL_OFF, OUTPUT);
Signal ventola( 4, RL_OFF, OUTPUT);

byte pwm_state[] = { 0, 70, 230 };
byte lcd[NUM__FLAG] = { CLEAR };

byte lux1 = 0;
byte lux2 = 0;
byte vent = 0;

unsigned long tm_can = 0L;

const byte led[] = {
	TRIGG,		ALARM,		CAN_LED, 
	R_LED,		G_LED,		Y_LED,
	WND_LED, 	LIGHT_1, 	LIGHT_2,
	LG_TEN
};


void setup()
{//=======================================
	for(byte l = 0; l < 10; l++)
		pinMode(led[l], OUTPUT);

	pinMode(FUND, OUTPUT);
	pinMode(VEL,  OUTPUT);
	pinMode(ECHO, INPUT);
	pinMode(MQ05, INPUT);

	dht.setup(DHT22);

	init_display();
	init_motors();

	Serial.begin(9600);
}

void loop()
{//=======================================
	if(gate.getDirection() == M_SX)
		control_gate();

	if(Serial.available())
		switch(Serial.read())
		{
			case 'T':
				if(lcd[WIND_FLAG] != WIND)
					if(tenda.getState() == M_UP)
						tenda.move((byte)190);
					else
						tenda.move((byte)220);
			break;
			case 'V':
				vent = (++vent) % 3;

				switch(vent)
				{
					case 0:
						ventola.setState(RL_OFF);
					break;
					case 1:
						analogWrite(VEL, 0);
						ventola.setState(RL_ON);
					break;
					case 2:
						analogWrite(VEL, 255);
					break;
				}
			break;
			case 'L':
				lux1 = (++lux1) % 3;
				analogWrite(LIGHT_1, pwm_state[lux1]);
			break;
			case 'l':
				lux2 = (++lux2) % 3;
				analogWrite(LIGHT_2, pwm_state[lux2]);
			break;
			case 'C':
				gate.move((byte)240);
				digitalWrite(CAN_LED, HIGH);
				
				if(gate.getDirection() == M_DX)
					tm_can = millis();
				delay(150);
			break;
			case 'F':
				if(lcd[FONT_FLAG] != WATER)
				{
					if(fontana.switchState() == RL_ON)
					{
						set_indicator_font(GREEN);
						lcd[FONT_FLAG] = FONTANA;
					}
					else
					{
						set_indicator_font(RED);
						lcd[FONT_FLAG] = CLEAR;
					}
				}
				else
				{
					beep(ALARM);

					for(byte i = 0; i < 4; i++)
					{
						set_indicator_font((i % 2) ? RED : CLEAR);
						delay(80);
					}
					set_indicator_font(CLEAR);
				}
			break;
		}

	if(check_sensors() || check_dht(&th_info))
		update_display(th_info);
}

