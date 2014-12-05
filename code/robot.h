/*
 * robot.h
 *
 *  Created on: Dec 5, 2014
 *      Author: C16Sabin.Park
 */

//-----------------------------------------------------------------
// Page 76 : MSP430 Optimizing C/C++ Compiler v 4.3 User's Guide
//-----------------------------------------------------------------
typedef		unsigned char		int8;
typedef		unsigned short		int16;
typedef		unsigned long		int32;
typedef		unsigned long long	int64;

#define		TRUE				1
#define		FALSE				0

#define		FORWARD				1
#define		STOP				0
#define		BACKWARD			-1

//-----------------------------------------------------------------
// Function prototypes found in lab5.c
//-----------------------------------------------------------------
void initMSP430();
__interrupt void pinChange (void);
__interrupt void timerOverflow (void);


//-----------------------------------------------------------------
// Each PxIES bit selects the interrupt edge for the corresponding I/O pin.
//	Bit = 0: The PxIFGx flag is set with a low-to-high transition
//	Bit = 1: The PxIFGx flag is set with a high-to-low transition
//-----------------------------------------------------------------

#define		IR_PIN			(P2IN & BIT6)
#define		HIGH_2_LOW		P2IES |= BIT6
#define		LOW_2_HIGH		P2IES &= ~BIT6

#define		averageLogic0Pulse	544
#define		averageLogic1Pulse	1615
#define		averageStartPulse	4340
#define		minLogic0Pulse		averageLogic0Pulse - 100
#define		maxLogic0Pulse		averageLogic0Pulse + 100
#define		minLogic1Pulse		averageLogic1Pulse - 100
#define		maxLogic1Pulse		averageLogic1Pulse + 100
#define		minStartPulse		averageStartPulse - 100
#define		maxStartPulse		averageStartPulse + 100

// constants for the remote control buttons
#define		BTN_PWR		0x30DFA857		//
#define		BTN_2		0x30DF609F		// Forward
#define		BTN_4		0x30DF10EF		// Rotate Left
#define		BTN_5		0x30DF906F		// Stop
#define		BTN_6		0x30DF50AF		// Rotate Right
#define		BTN_8		0x30DF30CF		// Backward
#define		BTN_CH_HI	0x30DF40BF		// Increase duty cycle
#define		BTN_CH_LO	0x30DFC03F		// Decrease duty cycle
#define		BTN_1		0x30DFA05F		// turn NW
#define		BTN_3		0x30DFE01F		// turn NE
#define		BTN_7		0x30DFD02F		// turn SW
#define		BTN_9		0x30DFB04F		// turn SE
#define		BTN_0		0x30DF20DF		// continuous CW rotation
#define		BTN_DASH	0x30DF6C93		// continuous CCW rotation
#define		BTN_OK		0x30DF18E7		//


// constants for motor delays
#define SHORT_DELAY					5000000
#define LONG_DELAY					15000000

#define DELAY_360					9000000			// the delay it takes for (approximately) 360 degrees of rotation
#define DELAY_180					4800000			// for (appx) 180 degrees
#define DELAY_90					2700000			// for (appx) 90 degrees
#define DELAY_45					1400000			// for (appx) 45 degrees
#define DELAY_15					800000			// for (appx) 15 degrees

#define DEG_360						360				// constant to define 360 degrees

// sets the PWN direction bits to output
#define LEFT_PWN_ENABLE_SET_OUTPUT	P2DIR |= BIT2
#define RIGHT_PWN_ENABLE_SET_OUTPUT	P2DIR |= BIT4
// chooses the proper function for use with the timers
#define LEFT_P2SEL_SET				P2SEL |= BIT2
#define RIGHT_P2SEL_SET				P2SEL |= BIT4

// left motor enable
#define LEFT_ENABLE_SET_OUTPUT		P2DIR |= BIT0	// sets direction pin to output
#define LEFT_ENABLE					P2OUT |= BIT0	// enable left motor
#define LEFT_DISABLE				P2OUT &= ~BIT0	// disable left motor
// right motor enable
#define RIGHT_ENABLE_SET_OUTPUT		P2DIR |= BIT5	// sets direction pin to output
#define RIGHT_ENABLE				P2OUT |= BIT5	// enable right motor
#define RIGHT_DISABLE				P2OUT &= ~BIT5	// disable right motor

// left motor direction
#define LEFT_SET_OUTPUT				P2DIR |= BIT1	// sets direction pin to output
#define LEFT_SET_CW					P2OUT &= ~BIT1	// left motor turns clockwise
#define	LEFT_SET_CCW				P2OUT |= BIT1	// left motor turuns counter-clockwise
// right motor direction
#define RIGHT_SET_OUTPUT			P2DIR |= BIT3	// sets direction pin to output
#define RIGHT_SET_CW				P2OUT &= ~BIT3	// right motor turns clockwise
#define RIGHT_SET_CCW				P2OUT |= BIT3	// right motor turns counter-clockwise

// left motor outmode
#define LEFT_OM_HI					TA1CCTL1 = OUTMOD_3;
#define LEFT_OM_LO					TA1CCTL1 = OUTMOD_7;
// right motor outmode
#define RIGHT_OM_HI					TA1CCTL2 = OUTMOD_3;
#define RIGHT_OM_LO					TA1CCTL2 = OUTMOD_7;

#define GREEN_ON					P1OUT |= BIT6
#define GREEN_OFF					P1OUT &= ~BIT6
#define RED_ON						P1OUT |= BIT0
#define RED_OFF						P1OUT &= ~BIT0
#define LEDS_OFF					P1OUT &= ~(BIT0 | BIT6)


#define LEFT 0
#define CENTER 1
#define RIGHT 2

#define DETECTVALUE 0x0232

#define LEDS_ON		P1OUT |= BIT0 | BIT6
//----------------------------------------------------------------------------------------------------------

void leftSensor();
void centerSensor();
void rightSensor();

//----------------------------------------------------------------------------------------------------------


