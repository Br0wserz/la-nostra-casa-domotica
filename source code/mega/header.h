#ifndef _HEADER_H_
#define _HEADER_H_

#define		RL_ON 			LOW
#define 	RL_OFF			HIGH

#define		VEL				11
#define		FUND			33
#define 	DHT22			39
#define		MQ05			41
#define 	ALARM			43

#define		TRIGG			42
#define		ECHO			44

#define 	CAN_LED			26
#define 	WND_LED			45

#define		LG_TEN			 8    
#define		LIGHT_1			 5
#define		LIGHT_2			 6

#define 	G_LED			50
#define 	Y_LED			52
#define 	R_LED			53

#define 	GREEN			B100 // 4
#define 	YELLOW			B010 // 2
#define 	RED				B001 // 1
#define 	ALL				B111

#define 	CLEAR			((byte)(0))
#define 	WIND			((byte)(1))
#define 	GATE			((byte)(2))
#define 	FONTANA			((byte)(3))
#define 	GRAD			((byte)(4))

#define		WATER			'A'
#define 	TENDA			'T'
#define 	GAS				'G'

#define 	GATE_FLAG		 0
#define 	FONT_FLAG		 1
#define 	WIND_FLAG		 2
#define		TEND_FLAG 		 3
#define 	GAS__FLAG		 4
#define 	NUM__FLAG		 5


typedef struct
{
	float temp;
	float hum;
} TH_info;


#endif

