#include "LED_CPU.h"

// ***************************
// *     ARITHMETIC UNIT     *
// ***************************

LED_ALU::LED_ALU()
{
	leds1 = new PCA9955(PCA_1_ADDRESS);
	leds2 = new PCA9955(PCA_2_ADDRESS);
	leds1->mode(PCA9955::PWM0);
	leds1->dutycycle(PWM_GREEN);
	leds1->dutycycle(12,PWM_RED); // eADDSUB
	leds1->dutycycle(13,PWM_RED); // eRA
	leds1->dutycycle(14,PWM_RED); // eRB
	leds1->dutycycle(15,PWM_RED); // eG1
	leds2->mode(PCA9955::PWM0);
	leds2->dutycycle(PWM_GREEN);
	leds2->dutycycle(4,PWM_RED);  // eRC
	leds2->dutycycle(5,PWM_BLUE); // neg
	leds2->dutycycle(6,PWM_BLUE); // overflow
	leds2->dutycycle(7,PWM_RED);   // eG2
}

unsigned char LED_ALU::reverse4bit(unsigned char x)
{
	unsigned char xout = 0;
	for (int n=0; n<4; n++)
		xout += (bitRead(x,n)<<(3-n));
	return xout;
}

void LED_ALU::update(unsigned char bus, unsigned char ra, unsigned char rb, 
				 		  unsigned char rc, unsigned char ctrl, unsigned char neg, 
				 		  unsigned char overflow)
{
	unsigned short leddata1 = (bus & 0x0F) + ((ra & 0x0F)<<4) 
	                        + ((reverse4bit(rb) & 0x0F)<<8) 
	                        + (bitRead(ctrl, CTRL_BIT_PM)<<12)
	                        + (bitRead(ctrl, CTRL_BIT_RA)<<13)
	                        + (bitRead(ctrl, CTRL_BIT_RB)<<14)
	                        + (bitRead(ctrl, CTRL_BIT_G1)<<15);
	unsigned short leddata2 = (reverse4bit(rc) & 0x0F)
	                        + (bitRead(ctrl, CTRL_BIT_RC)<<4)
	                        + ((neg & 1)<<5) + ((overflow & 1)<<6)
	                        + (bitRead(ctrl, CTRL_BIT_G2)<<7);
	leds1->set_leds(leddata1);
	leds2->set_leds(leddata2);
}

// **************************
// *     MANUAL CONTROL     *
// **************************

LED_MANUAL::LED_MANUAL()
{
	leds1 = new PCA9955(PCA_1_ADDRESS);
	leds1->mode(PCA9955::PWM0);
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

void LED_MANUAL::update(unsigned char data, unsigned char ctrl)
{
	unsigned short leddata1 = (data & 0x0F) + ((ctrl & 0x3F)<<4);
	leds1->set_leds(leddata1);
}

// ************************
// *     CONTROL UNIT     *
// ************************

LED_CONTROL::LED_CONTROL()
{
	leds1 = new PCA9955(PCA_2_ADDRESS);
	leds2 = new PCA9955(PCA_1_ADDRESS);
	leds1->mode(PCA9955::PWM0);
	leds1->dutycycle(PWM_GREEN);
	leds1->dutycycle(3,PWM_YELLOW); // count
	leds1->dutycycle(10,PWM_RED); // creset
	leds1->dutycycle(11,PWM_RED); // cset
	leds2->mode(PCA9955::PWM0);
	leds2->dutycycle(PWM_RED);
}

unsigned char LED_CONTROL::reverse4bit(unsigned char x)
{
	unsigned char xout = 0;
	for (int n=0; n<4; n++)
		xout += (bitRead(x,n)<<(3-n));
	return xout;
}

void LED_CONTROL::update(unsigned char bus, unsigned char ctrl, unsigned char counter, 
			unsigned char ccount, unsigned char cset, unsigned char creset,
			unsigned char pcount, unsigned char pset)
{
	unsigned short leddata1 = ((ccount & 1)<<3)
	                        + ((counter & 0x0F)<<4) 
	                        + ((creset & 1)<<10)
	                        + ((cset & 1)<<11)
	                        + ((reverse4bit(bus) & 0x0F)<<12);
	unsigned short leddata2 = (bitRead(ctrl, CTRL_BIT_G1)<<1)
	                        + (bitRead(ctrl, CTRL_BIT_RB)<<2)
	                        + (bitRead(ctrl, CTRL_BIT_RA)<<3)
	                        + (bitRead(ctrl, CTRL_BIT_PM)<<4)
	                        + (bitRead(ctrl, CTRL_BIT_RC)<<5)
	                        + (bitRead(ctrl, CTRL_BIT_G2)<<6)
	                        + ((pcount & 1)<<7)
	                        + ((pset & 1)<<8);
	leds1->set_leds(leddata1);
	leds2->set_leds(leddata2);
}
