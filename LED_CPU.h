// Value for NLEDDRIVER can be 1 = PCA9955, 2 = PCA9955B, or 3 = TLC59116
#define NLEDDRIVER 1
#include "Arduino.h"

#if NLEDDRIVER==1
	// For PCA9955:
	#include "PCA9955.h"
	#define LEDDRIVER PCA9955
	#define PCA_1_ADDRESS 0x60
	#define PCA_2_ADDRESS 0x61
	#define PWM_GREEN 30
	#define PWM_RED 6
	#define PWM_BLUE 20
	#define PWM_YELLOW 20
#elif NLEDDRIVER==2
	// For PCA9955B:
	#include "PCA9955B.h"
	#define LEDDRIVER PCA9955B
	#define PCA_1_ADDRESS 0x01
	#define PCA_2_ADDRESS 0x05
	#define PWM_GREEN 6
	#define PWM_RED 6
	#define PWM_BLUE 20
	#define PWM_YELLOW 20
#elif NLEDDRIVER==3
	// For TLC59116
	#include "TLC59116.h"
	#define LEDDRIVER TLC59116
	#define PCA_1_ADDRESS 0x60
	#define PCA_2_ADDRESS 0x61
	#define PWM_GREEN 10
	#define PWM_RED 10
	#define PWM_BLUE 10
	#define PWM_YELLOW 10
#endif

#define CTRL_BIT_G1 0
#define CTRL_BIT_RB 1
#define CTRL_BIT_RA 2
#define CTRL_BIT_PM 3
#define CTRL_BIT_RC 4
#define CTRL_BIT_G2 5

// LED connections on ALU board:
// =============================
// led1_0..led1_3 : bus 0..3
// led1_4..led1_7 : ra 0..3
// led1_8..led1_11 : rb 3..0
// led1_12 : ePM
// led1_13 : eRA
// led1_14 : eRB
// led1_15 : eG1

// led2_0..led2_3 : rc 3..0
// led2_4 : eRC
// led2_5 : neg
// led2_6 : overflow
// led2_7 : eG2

class LED_ALU
{
	private:
		LEDDRIVER *leds1, *leds2;
		unsigned char reverse4bit(unsigned char x);
	public:
		LED_ALU();
		void update(unsigned char bus, unsigned char ra, unsigned char rb,
  						 unsigned char rc, unsigned char ctrl, unsigned char neg,
  						 unsigned char overflow);
};

class LED_MANUAL
{
	private:
		LEDDRIVER *leds1;
		unsigned char reverse4bit(unsigned char x);
	public:
		LED_MANUAL();
		void update(unsigned char data, unsigned char ctrl);
};

class LED_CONTROL
{
	private:
		LEDDRIVER *leds1, *leds2;
		unsigned char reverse4bit(unsigned char x);
	public:
		LED_CONTROL();
		void update(unsigned char bus, unsigned char ctrl, unsigned char counter,
			unsigned char ccount, unsigned char cset, unsigned char creset,
			unsigned char pcount, unsigned char pset);
};

class LED_PROGRAM
{
	private:
		LEDDRIVER *leds1;
		unsigned char reverse4bit(unsigned char x);
	public:
		LED_PROGRAM();
		void update(unsigned char bus, unsigned char counter,
			unsigned char ccount, unsigned char cset);
};
