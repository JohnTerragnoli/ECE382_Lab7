//-------------------------------------------------------------------------------
//	Name:		C2C Sabin Park
//	Term:		Fall 2014
//	MCU:		MSP430G2553
//	Date:		3 December 2014
//	Note:		Lab 7: main file for utilizing the IR transmitters and receivers on the robot
//-------------------------------------------------------------------------------

#include "msp430g2553.h"
#include "robot.h"


void initMSP430();



//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	P1DIR = BIT0 | BIT6;										// Set the red and green LEDs as outputs

	int sensor = LEFT;

	ADC10AE0 = BIT3 | BIT4 | BIT5;	 							// make P1.3, P1.4, and P1.5 analog inputs

	while(1) {

		//moveForward(1);


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

void initMSP430() {

	IFG1=0; 							// clear interrupt flag1
	WDTCTL=WDTPW+WDTHOLD; 				// stop WD

	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	P2SEL  &= ~BIT6;					// Setup P2.6 as GPIO not XIN
	P2SEL2 &= ~BIT6;
	P2DIR &= ~BIT6;
	P2IFG &= ~BIT6;						// Clear any interrupt flag
	P2IE  |= BIT6;						// Enable PORT 2 interrupt on pin change

	HIGH_2_LOW;
	P1DIR |= BIT0 | BIT6;				// Enable updates to the LED
//	P1OUT &= ~(BIT0 | BIT6);			// And turn the LED off

	TA0CCR0 = 0x8000;					// create a 16mS roll-over period
	TACTL &= ~TAIFG;					// clear flag before enabling interrupts = good practice
	TACTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:1 presclar off MCLK and enable interrupts

	_enable_interrupt();
}


