#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "header.h"


LiquidCrystal_I2C display(0x3F, 16, 2);

byte char_flag[][8] = {
/* 0 */		{  0,  0,  0,  0,  0,  0,  0,  0 }, // clear
/* 1 */		{  0,  0, 27, 10,  4, 10, 27,  0 }, // wind
/* 2 */		{  0, 31, 21, 21, 21, 21, 31,  0 }, // gates
/* 3 */		{  0,  4, 10, 21,  4,  4, 21, 31 }, // fontana
/* 4 */		{  6,  6,  0,  0,  0,  0,  0,  0 },	// gradi
};


void beep(byte pin)
{//=======================================
	digitalWrite(pin, HIGH);
	delay(120);
	digitalWrite(pin, LOW);
}

void welcome()
{//=======================================
	display.setCursor(0, 0);
	display.print("Benvenuti nella");
	display.setCursor(0, 1);
	display.print("casa domotica");

	set_indicator_font(ALL);
	beep(ALARM);
	delay(3000);
	beep(ALARM);
	set_indicator_font(CLEAR);
}

void set_indicator_font(byte color)
{//=======================================
	digitalWrite(Y_LED, (bool)(color & YELLOW));
	digitalWrite(G_LED, (bool)(color & GREEN));
	digitalWrite(R_LED, (bool)(color & RED));
}

void init_display()
{//=======================================
	display.begin();
	welcome();

	for(byte i = 0; i < NUM__FLAG; i++)
		display.createChar(byte(i), char_flag[i]);

	display.clear();
	display.setCursor(5, 0);
	display.write(GRAD);
	display.print("C");
	display.setCursor(14, 0);
	display.print("%");
}

void update_display(TH_info th_info)
{//=======================================
	for(byte flag = 0; flag < NUM__FLAG; flag++) 
	{
		display.setCursor((flag * 3) + 1, 1);
		display.write(lcd[flag]);
	}

	display.setCursor(0, 0);
	display.print(th_info.temp);
	display.setCursor(9, 0);
	display.print(th_info.hum);
}

