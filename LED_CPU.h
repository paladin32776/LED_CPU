#include "Arduino.h"
#include "PCA9955B.h"

#define PWM_GREEN 6
#define PWM_RED 6
#define PWM_BLUE 20

#define CTRL_BIT_G1 0
#define CTRL_BIT_RB 1
#define CTRL_BIT_RA 2
#define CTRL_BIT_PM 3
#define CTRL_BIT_RC 4
#define CTRL_BIT_G2 5

// LED connections on ALU board:
// =============================
// led1_0..led1_3 : BUS 0..3
// led1_4..led1_7 : RA 0..3
// led1_8..led1_11 : RB 3..0
// led1_12 : ePM
// led1_13 : eRA
// led1_14 : eRB
// led1_15 : eG1

// led2_0..led2_3 : RC 3..0
// led2_4 : eRC
// led2_5 : NEG
// led2_6 : OVERFLOW
// led2_7 : eG2

class LED_ALU
{
	private:
		PCA9955B *leds1, *leds2;
		unsigned char reverse4bit(unsigned char x);
	public:
		LED_ALU();
		void update(unsigned char BUS, unsigned char RA, unsigned char RB, 
  						 unsigned char RC, unsigned char CTRL, unsigned char NEG, 
  						 unsigned char OVERFLOW);
};

class LED_MANUAL
{
	private:
		PCA9955B *leds1;
		unsigned char reverse4bit(unsigned char x);
	public:
		LED_MANUAL();
		void update(unsigned char DATA, unsigned char CTRL);
};