/*
 *	@ Author: Christian Sannino
 */

#include "Signal.h"


Signal::Signal(byte p) 
{//===============================
	_pin = p;
	setMode(OUTPUT);
	write(LOW);
}

Signal::Signal(uint8_t p, State s, bool m) 
{//===============================
	_pin = p;
	setMode(m);
	write(s);
}

void Signal::setMode(bool m)
{//===============================
	_mode = m;
	pinMode(_pin, _mode);
}

State Signal::switchState()
{//===============================
	State s = !_state;

	setState(s);
	return s;
}

void Signal::write(State s)
{//===============================
	if(_mode == OUTPUT)
	{
		_state = s;
		digitalWrite(_pin, s);
	}
}

State Signal::read()
{//===============================
	if(_mode == INPUT)
		_state = digitalRead(_pin);

	return _state;
}

void Signal::pwm(byte d) 
{//===============================
	if(_mode == OUTPUT)
		analogWrite(_pin, d);
}

