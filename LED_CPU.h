#include "Arduino.h"
#include "PCA9955.h"

// #define PCA_1_ADDRESS 0x01
// #define PCA_2_ADDRESS 0x05

#define PCA_1_ADDRESS 0x60
#define PCA_2_ADDRESS 0x61

#define PWM_GREEN 6
#define PWM_RED 6
#define PWM_BLUE 20
#define PWM_YELLOW 20

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
		PCA9955 *leds1, *leds2;
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
		PCA9955 *leds1;
		unsigned char reverse4bit(unsigned char x);
	public:
		LED_MANUAL();
		void update(unsigned char data, unsigned char ctrl);
};

class LED_CONTROL
{
	private:
		PCA9955 *leds1, *leds2;
		unsigned char reverse4bit(unsigned char x);
	public:
		LED_CONTROL();
		void update(unsigned char bus, unsigned char ctrl, unsigned char counter,
			unsigned char ccount, unsigned char cset, unsigned char creset,
			unsigned char pcount, unsigned char pset);
};