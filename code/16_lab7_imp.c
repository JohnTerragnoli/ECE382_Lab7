#include "msp430g2553.h"
#include "robot.h"


void leftSensor() {
	ADC10CTL0 = 0;											// turn off the ADC subsytem
	ADC10CTL1 = INCH_3 | ADC10DIV_3 ;						// set input channel 3 and ADC10CLK/3
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

	ADC10CTL0 |= ADC10SC;									// Start a conversion
	while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete

	if (ADC10MEM > DETECTVALUE) {
		RED_ON;
//		stop();
//		rotateRight(45);
	}
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

/*
 * stops the motors
 */
void stop() {

	LEFT_DISABLE;
	RIGHT_DISABLE;

	LEDS_OFF;

	_delay_cycles(SHORT_DELAY);
}

/*
 * enables the left and right PWMs
 */
void go() {
	LEFT_ENABLE;
	RIGHT_ENABLE;
}

/*
 * moves the robot forward
 */
void moveForward(int dist_delay) {

	go();

	LEFT_OM_HI;
	RIGHT_OM_HI;

	// LEFT MOTOR
	LEFT_SET_CCW;	// set the direction of left motor (CCW)

	// RIGHT MOTOR
	RIGHT_SET_CW;

	GREEN_ON;						// green LED ON
	RED_OFF;						// red LED OFF

	int i;

	switch(dist_delay) {
	case 1:
		_delay_cycles(SHORT_DELAY);
		break;
	case 100:
		_delay_cycles(LONG_DELAY);
		break;
	default:
		for(i=0; i<dist_delay; i++) {
			_delay_cycles(SHORT_DELAY);
		}
		break;
	}
}

/*
 * moves the robot forward SLOWLY
 */
void slowForward(int dist_delay) {

	go();

	LEFT_OM_LO;
	RIGHT_OM_LO;

	// LEFT MOTOR
	LEFT_SET_CCW;	// set the direction of left motor (CCW)

	// RIGHT MOTOR
	RIGHT_SET_CW;

	GREEN_ON;						// green LED ON
	RED_OFF;						// red LED OFF

	int i;

	switch(dist_delay) {
	case 1:
		_delay_cycles(SHORT_DELAY);
		break;
	case 100:
		_delay_cycles(LONG_DELAY);
		break;
	default:
		for(i=0; i<dist_delay; i++) {
			_delay_cycles(SHORT_DELAY);
		}
		break;
	}
}

/*
 * moves the robot backward
 */
void moveBackward(int dist_delay) {
	go();

	LEFT_OM_LO;
	RIGHT_OM_LO;

	// LEFT MOTOR
	LEFT_SET_CW;

	// RIGHT MOTOR
	RIGHT_SET_CCW;

	RED_ON;							// red LED ON
	GREEN_OFF;						// green LED OFF

	int i;

	switch(dist_delay) {
	case 1:
		_delay_cycles(SHORT_DELAY);
		break;
	case 100:
		_delay_cycles(LONG_DELAY);
		break;
	default:
		for(i=0; i<dist_delay; i++) {
			_delay_cycles(SHORT_DELAY);
		}
		break;
	}
}

/*
 * turns the robot CCW
 */
void rotateLeft(int deg_delay) {
	go();

	LEFT_OM_LO;
	RIGHT_OM_HI;

	// LEFT MOTOR
	LEFT_SET_CW;
	// RIGHT MOTOR
	RIGHT_SET_CW;

	RED_ON;							// red LED ON
	GREEN_OFF; 						// green LED OFF

	int i;

	switch(deg_delay) {
	case 15:
		_delay_cycles(DELAY_15);
		break;
	case 45:
		_delay_cycles(DELAY_45);
		break;
	case 90:
		_delay_cycles(DELAY_90);
		break;
	case 180:
		_delay_cycles(DELAY_180);
		break;
	case 360:
		_delay_cycles(DELAY_360);
		break;
	default:
		for(i=0; i<deg_delay; i++) {
			_delay_cycles(DELAY_360/DEG_360);
		}
	}
}

/*
 * turns the robot CW
 */
void rotateRight(int deg_delay) {
	go();

	LEFT_OM_HI;
	RIGHT_OM_LO;

	// LEFT MOTOR
	LEFT_SET_CCW;
	// RIGHT MOTOR
	RIGHT_SET_CCW;

	GREEN_ON;						// green LED ON
	RED_OFF;						// red LED OFF

	int i;

	switch(deg_delay) {
	case 15:
		_delay_cycles(DELAY_15);
		break;
	case 45:
		_delay_cycles(DELAY_45);
		break;
	case 90:
		_delay_cycles(DELAY_90);
		break;
	case 180:
		_delay_cycles(DELAY_180);
		break;
	case 360:
		_delay_cycles(DELAY_360);
		break;
	default:
		for(i=0; i<deg_delay; i++) {
			_delay_cycles(DELAY_360/DEG_360);
		}
	}
}

/*
 * NW turn
 */
void driveNW() {
	go();

	// LEFT MOTOR
	LEFT_SET_CCW;
	LEFT_OM_LO;

	// RIGHT MOTOR
	RIGHT_SET_CW;
	RIGHT_OM_HI;

	RED_ON;							// red LED ON
	GREEN_OFF;						// green LED OFF

	_delay_cycles(LONG_DELAY/2);
}

/*
 * NE turn
 */
void driveNE() {
	go();

	// LEFT MOTOR
	LEFT_SET_CCW;
	LEFT_OM_HI;

	// RIGHT MOTOR
	RIGHT_SET_CW;
	RIGHT_OM_LO;

	GREEN_ON;						// green LED ON
	RED_OFF;						// red LED OFF

	_delay_cycles(LONG_DELAY/2);
}

/*
 * SW turn
 */
void driveSW() {
	go();

	// LEFT MOTOR
	LEFT_SET_CW;
	LEFT_OM_HI;

	// RIGHT MOTOR
	RIGHT_SET_CCW;
	RIGHT_OM_LO;

	RED_ON;							// red LED ON
	GREEN_OFF;						// green LED OFF

	_delay_cycles(LONG_DELAY/2);
}

/*
 * SE turn
 */
void driveSE() {
	go();

	// LEFT MOTOR
	LEFT_SET_CW;
	LEFT_OM_LO;

	// RIGHT MOTOR
	RIGHT_SET_CCW;
	RIGHT_OM_HI;

	GREEN_ON;						// green LED ON
	RED_OFF;						// red LED OFF

	_delay_cycles(LONG_DELAY/2);
}

/*
 * updates the timer signal lengths
 */
void updateSignal() {
	TA1CCR2 = TA1CCR0-TA1CCR1;
}

/*
 * increase the duty cycle
 */
void increaseDC() {
	if(TA1CCR1 < 90) {
		TA1CCR1 += 5;
	}
	updateSignal();

	GREEN_ON;						// green LED ON
	RED_OFF;						// red LED OFF
}

/*
 * decrease the duty cycle
 */
void decreaseDC() {
	if(TA1CCR1 > 40) {
		TA1CCR1 -= 5;
	}
	updateSignal();

	GREEN_OFF;						// green LED OFF
	RED_ON	;						// red LED ON
}

/*
 * reset the duty cycle back to the original
 */
void resetSignal() {
	TA1CCR1 = 60;
	TA1CCR2 = TA1CCR0-TA1CCR1;

	GREEN_ON;						// green LED ON
	RED_ON;							// red LED ON
}

/*
 * checks the direction the robot moved last (forward, backward, still)
 */
void checkDirection(int direction) {
	if(direction == FORWARD) {
		moveForward(1);
	} else if(direction == BACKWARD) {
		moveBackward(1);
	} else {
		stop();
	}
}
