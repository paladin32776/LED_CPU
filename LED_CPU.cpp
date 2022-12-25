#include "LED_CPU.h"

LED_ALU::LED_ALU()
{
	leds1 = new PCA9955B(01);
	leds2 = new PCA9955B(05);
	leds1->mode(PCA9955B::PWM0);
	leds1->dutycycle(PWM_GREEN);
	leds1->dutycycle(12,PWM_RED); // eADDSUB
	leds1->dutycycle(13,PWM_RED); // eRA
	leds1->dutycycle(14,PWM_RED); // eRB
	leds1->dutycycle(15,PWM_RED); // eG1
	leds2->mode(PCA9955B::PWM0);
	leds2->dutycycle(PWM_GREEN);
	leds2->dutycycle(4,PWM_RED);  // eRC
	leds2->dutycycle(5,PWM_BLUE); // NEG
	leds2->dutycycle(6,PWM_BLUE); // OVERFLOW
	leds2->dutycycle(7,PWM_RED);   // eG2
}

unsigned char LED_ALU::reverse4bit(unsigned char x)
{
	unsigned char xout = 0;
	for (int n=0; n<4; n++)
		xout += (bitRead(x,n)<<(3-n));
	return xout;
}

void LED_ALU::update(unsigned char BUS, unsigned char RA, unsigned char RB, 
				 		  unsigned char RC, unsigned char CTRL, unsigned char NEG, 
				 		  unsigned char OVERFLOW)
{
	unsigned short leddata1 = (BUS & 0x0F) + ((RA & 0x0F)<<4) 
	                        + ((reverse4bit(RB) & 0x0F)<<8) 
	                        + (bitRead(CTRL, CTRL_BIT_PM)<<12)
	                        + (bitRead(CTRL, CTRL_BIT_RA)<<13)
	                        + (bitRead(CTRL, CTRL_BIT_RB)<<14)
	                        + (bitRead(CTRL, CTRL_BIT_G1)<<15);
	unsigned short leddata2 = (reverse4bit(RC) & 0x0F)
	                        + (bitRead(CTRL, CTRL_BIT_RC)<<4)
	                        + ((NEG & 1)<<5) + ((OVERFLOW & 1)<<6)
	                        + (bitRead(CTRL, CTRL_BIT_G2)<<7);
	leds1->set_leds(leddata1);
	leds2->set_leds(leddata2);
}

LED_MANUAL::LED_MANUAL()
{
	leds1 = new PCA9955B(01);
	leds1->mode(PCA9955B::PWM0);
	leds1->dutycycle(PWM_GREEN);
	leds1->dutycycle(10,PWM_RED); // eADDSUB
	leds1->dutycycle(11,PWM_RED); // eRA
	leds1->dutycycle(12,PWM_RED); // eADDSUB
	leds1->dutycycle(13,PWM_RED); // eRA
	leds1->dutycycle(14,PWM_RED); // eRB
	leds1->dutycycle(15,PWM_RED); // eG1
}

unsigned char LED_MANUAL::reverse4bit(unsigned char x)
{
	unsigned char xout = 0;
	for (int n=0; n<4; n++)
		xout += (bitRead(x,n)<<(3-n));
	return xout;
}

void LED_MANUAL::update(unsigned char DATA, unsigned char CTRL)
{
	unsigned short leddata1 = (DATA & 0x0F) + ((CTRL & 0x3F)<<4);
	leds1->set_leds(leddata1);
}

