
void init_motor()
{//=======================================
	garage.begin(M_DOWN);
	tsolar.begin(M_SX);

	attachInterrupt(FNC_GAR_UP, stop_garage_UP,	RISING);
	attachInterrupt(FNC_GAR_DW, stop_garage_DW,	RISING);
}

void stop_garage_UP()
{//=======================================
	if(garage.getDirection() == M_UP && garage.getState() == M_START)
	{
		garage.enableMotor(M_STOP);
		digitalWrite(GAR_LED, LOW);		
		garage.reverse();
	}
}

void stop_garage_DW()
{//=======================================
	if(garage.getDirection() == M_DOWN && garage.getState() == M_START)
	{
		garage.enableMotor(M_STOP);
		digitalWrite(GAR_LED, LOW);
		garage.reverse();
	}
}

