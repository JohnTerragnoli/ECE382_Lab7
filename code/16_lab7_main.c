//-------------------------------------------------------------------------------
//	Name:		C2C Sabin Park
//	Term:		Fall 2014
//	MCU:		MSP430G2553
//	Date:		3 December 2014
//	Note:		Lab 7: main file for utilizing the IR transmitters and receivers on the robot
//-------------------------------------------------------------------------------

#include "msp430g2553.h"

#define LEFT 0
#define CENTER 1
#define RIGHT 2

#define DETECTVALUE 0x0232

#define GREEN_ON	P1OUT |= BIT6
#define GREEN_OFF	P1OUT &= ~BIT6
#define RED_ON		P1OUT |= BIT0
#define RED_OFF		P1OUT &= ~BIT0
#define LEDS_ON		P1OUT |= BIT0 | BIT6
#define LEDS_OFF	P1OUT &= ~(BIT0 | BIT6)

void initMSP430();

void leftSensor();
void centerSensor();
void rightSensor();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

	/*
	unsigned short sample3[16];									// LEFT
	unsigned short sample4[16];									// CENTER
	unsigned short sample5[16];									// RIGHT
	unsigned char i = 0;										// index into sample array
	*/

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	P1DIR = BIT0 | BIT6;										// Set the red and green LEDs as outputs

	int sensor = LEFT;

	ADC10AE0 = BIT3 | BIT4 | BIT5;	 							// make P1.3, P1.4, and P1.5 analog inputs

	while(1) {

		switch(sensor) {
		case LEFT:
			leftSensor();
			sensor = CENTER;
			break;
		case CENTER:
			centerSensor();
			sensor = RIGHT;
			break;
		case RIGHT:
			rightSensor();
			sensor = LEFT;
			break;
		}

	} // end infinite loop
} // end main

void leftSensor() {
	ADC10CTL0 = 0;											// turn off the ADC subsytem
	ADC10CTL1 = INCH_3 | ADC10DIV_3 ;						// set input channel 3 and ADC10CLK/3
//	ADC10AE0 = BIT3;	 									// make P1.3 analog input
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

	ADC10CTL0 |= ADC10SC;									// Start a conversion
	while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete

	if (ADC10MEM > DETECTVALUE)
		RED_ON;
	else
		RED_OFF;
}

void centerSensor() {
	ADC10CTL0 = 0;
	ADC10CTL1 = INCH_4 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/3
//	ADC10AE0 = BIT4;	 									// Make P1.3 analog input
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

	ADC10CTL0 |= ADC10SC;									// Start a conversion
	while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete

	if(ADC10MEM > DETECTVALUE)
		LEDS_ON;
	else
		LEDS_OFF;
}

void rightSensor() {
	ADC10CTL0 = 0;
	ADC10CTL1 = INCH_5 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/3
//	ADC10AE0 = BIT5;	 									// Make P1.3 analog input
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

	ADC10CTL0 |= ADC10SC;									// Start a conversion
	while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete

	if (ADC10MEM > DETECTVALUE)
		GREEN_ON;
	else
		GREEN_OFF;
}


/* this works, but is not as clean
		switch(sensor) {
		case LEFT:
			ADC10CTL0 = 0;
			ADC10CTL1 = INCH_3 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/3
			ADC10AE0 = BIT3;	 					// Make P1.3 analog input
			ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference
			ADC10CTL0 |= ADC10SC;									// Start a conversion
			while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
			sample3[i] = ADC10MEM;									// collect that 10-bit value

			if (sample3[i] > 0x01FF)
				P1OUT |= BIT0;
			else
				P1OUT &= ~BIT0;

			i = (i+1) & 0xF;										// This is a mod 16 increment

			sensor = CENTER;
			break;
		case CENTER:
			ADC10CTL0 = 0;
			ADC10CTL1 = INCH_4 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/3
			ADC10AE0 = BIT4;	 					// Make P1.3 analog input
			ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference
			ADC10CTL0 |= ADC10SC;									// Start a conversion
			while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
			sample4[i] = ADC10MEM;									// collect that 10-bit value

			if(sample4[i] > 0x01FF)
				P1OUT |= BIT0 | BIT6;
			else
				P1OUT &= ~BIT0 & ~BIT6;

			i = (i+1) & 0xF;

			sensor = RIGHT;
			break;
		case RIGHT:
			ADC10CTL0 = 0;
			ADC10CTL1 = INCH_5 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/3
			ADC10AE0 = BIT5;	 					// Make P1.3 analog input
			ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference
			ADC10CTL0 |= ADC10SC;									// Start a conversion
			while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
			sample5[i] = ADC10MEM;									// collect that 10-bit value

			if (sample5[i] > 0x01FF)
				P1OUT |= BIT6;
			else
				P1OUT &= ~BIT6;

			i = (i+1) & 0xF;										// This is a mod 16 increment

			sensor = LEFT;
			break;
		}
 */
