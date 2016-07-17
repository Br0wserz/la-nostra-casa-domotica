/*
 *	@ Author: Christian Sannino
 */

#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <Arduino.h>


#define	PWM_25		0x40
#define	PWM_50		0x80
#define	PWM_75		0xC0
#define PWM_MAX		0xFF


typedef bool State;


class Signal
{
	public:
		Signal(byte p);
		Signal(byte p, State s, bool m);

		void  setMode(State m);
		void  pwm(byte d);
		void  write(State s);

		State switchState();
		State read();

		byte  getPin()		const { return _pin;   }
		State getState()	const { return _state; }
		bool  getMode()		const { return _mode;  }

		void setState(State s) { write(s); }

	private:
		byte _pin;
		bool _mode;
		volatile State _state;
};

#endif

