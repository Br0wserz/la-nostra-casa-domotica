
#include "header.h"

#define		LDR_SNR			A0
#define 	WTR_LV			A1
#define 	WND_SNR			A2


byte check_gas()
{//=======================================
	byte gas = (digitalRead(MQ05) == 0) ? GAS : CLEAR;
	digitalWrite(ALARM, (bool)gas);

	return gas;
}

byte check_wind_sensor()
{//=======================================
	bool light = (analogRead(LDR_SNR) < 300) ? HIGH : LOW;
	byte wind  = (analogRead(WND_SNR) >  30) ? WIND : CLEAR;

	digitalWrite(WND_LED, (bool)wind);

	if(tenda.getDirection() == M_UP)
	{
		if(wind) 
			tenda.move((byte)230);
		digitalWrite(LG_TEN, light);
	}
	else
		digitalWrite(LG_TEN, LOW);
		
	return wind;
}

byte check_wtr_lv()
{//=======================================
	static const byte led[] = { RED,   YELLOW,	GREEN 	};
	static const byte flg[] = { CLEAR, WATER, 	FONTANA };

	static unsigned long tm = millis();
	byte index = (fontana.getState()) ? 0 : 2;

	digitalWrite(FUND, HIGH);
	delayMicroseconds(5);

	if(analogRead(WTR_LV) < 600)
	{
		index = 1;
		fontana.setState(RL_OFF);
	}

	digitalWrite(FUND, LOW);
	set_indicator_font(led[index]);

	return flg[index];
}

bool check_dht(TH_info* th_info)
{//=======================================
	static const unsigned short
	DELAY_DHT = dht.getMinimumSamplingPeriod();

	static unsigned long
	LAST_TIME = millis();

	if(millis() - LAST_TIME > DELAY_DHT)
	{
		LAST_TIME = millis();

		th_info->temp = dht.getTemperature();
		th_info->hum  = dht.getHumidity();		

		return true;
	}
	return false;
}

bool check_sensors()
{//=======================================
	static unsigned long tm = millis();
	byte flag[NUM__FLAG] = { CLEAR };

	for(byte f = 0; f < NUM__FLAG; f++)
		flag[f] = lcd[f];

	if(millis() - tm > 2000)
	{
		tm = millis();
		lcd[FONT_FLAG] = check_wtr_lv();
	}

	lcd[GAS__FLAG] = check_gas();
	lcd[WIND_FLAG] = check_wind_sensor();
	lcd[GATE_FLAG] = (gate.getDirection()  == M_DX)   ? CLEAR : GATE;
	lcd[TEND_FLAG] = (tenda.getDirection() == M_DOWN) ? CLEAR : TENDA;

	for(byte f = 0; f < NUM__FLAG; f++)
		if(lcd[f] != flag[f]) return true;

	return false;
}

bool check_fotocellula()
{//=======================================
	float time = 0.0f;

	digitalWrite(TRIGG, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGG, LOW);

	time = pulseIn(ECHO, HIGH) / 58.0f;

	return (time < 11.0f) ? HIGH : LOW;
}

