ECE382_Lab7
===========

## *Functionality Update*
|Functionality|Status|Date Completed|Checked by|
|:-:|:-:|:-:|:-:|
| Required | in progress |  |  |
| B | in progress |  |  |
| A | in progress |  |  |

## Overview
* Interface analog systems with digitial systems
* Learn how to use the ADC (analog-to-digital converter) for the MSP430.
  * Three pairs of IR emitters and detectors on the robot
  * Use these pairs to detect if the robot is approaching a wall in the front or the sides.

### Functionality
#### Required Functionality
* Use the ADC subsystem to light LEDs based on the presence of a wall.
* The presence of a wall next to the left sensor should light LED1 on your Launchpad board. 
* The presence of a wall next to the right sensor should light LED2 on your Launchpad board. 
* Demonstrate that the LEDs do not light until they come into close proximity with a wall.

#### B Functionality
* Create a standalone library for your ATD code and release it on Github. 
* This should be separate from your lab code. 
* It should have a thoughtful interface and README, capable of being reused in the robot maze laboratory.

#### A Functionality
* Since each robot's sensors are a little bit different, you need to fully characterize the sensor for your robot. 
* Create a table and graphical plot that shows the ATD values for a variety of distances from a maze wall. 
* This table/graph must be generated for each IR sensor. 
* Use these values to determine how the IR sensors work so you can properly use them to solve the maze.

## Prelab
Testing the sensors with a DMM:
* I used a DMM to check the voltages for each sensor. After initial difficulty with the right sensor, I eventually was able to read decent voltage values when I put a piece of paper near the sensors. I double-checked that the sensors worked by using my camera. Through the camera lense, I identified the characteristic purple glow from the IR transmitter. 
* Reference Values for the sensors

| Sensor | 1 inch | 4 inches | 8 inches |
|:-:|:-:|:-:|:-:|
| LEFT | 2.85 V | 1.50 V | 1.20 V |
| CENTER | 2.85 V | 1.10 V | 0.74 V |
| RIGHT | 1.74 V | 1.07 V | 0.91 V |

Setting up the ADC10 Subsystem:
* registers I will use:
  * `P1DIR`: sets the LED to an output
  * `P1OUT`: toggles the LED ON and OFF
  * `ADC10CTL0`: turns the ADC ON and OFF; sets Vcc and Vss references
  * `ADC10CTL1`: determines the channel
  * `ADC10AE0`: determines analog input for desired pin
  * `ADC10SC`: starts conversion process
  * `ADC10BUSY`: signals busy while converting
  * `ADC10MEM`: holds the 10-bit value
* the bits will I use from those registers:
  * I will use bits 3, 4, and 5 which correspond to the left, center, and right sensors, respectively.

| BIT | Sensor |
|:-:|:-:|
| BIT 3 | LEFT |
| BIT 4 | CENTER |
| BIT 5 | RIGHT |

* Initialization Sequence:
  * I will be doing something similar to what Dr. Coulston did in `lab7.c`
  * Here is my pseudo-code/code-outline:
```
// turn off the ADC subsystem at the very beginning (control register 0)
// set the input channel and clock (control register 1)
// set the left sensor's pin as an input (analog enable)
// set the references, sample-hold times, turn on the ADC, enable conversion

// start the conversion
// wait for completion

// collect the 10-bit sample
// if the sample is greater than an arbitrarily decided voltage value, turn the LED ON
// else turn the LED OFF

// move onto the CENTER sensor and repeat above
// move onto the RIGHT sensor and repeat above

// end the while loop and start from the beginning
```
  
  * Here is the initialization sequence for pin 4 (refer to `lab7. c'):
```
		// Configure P1.4 to be the ADC input
		ADC10CTL0 = 0;                         // Turn off ADC subsystem
		ADC10CTL1 = INCH_4 | ADC10DIV_3 ;      // Channel 4, ADC10CLK/4
		ADC10AE0 = BIT4;                       // Make P1.4 analog input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;                  // Start a conversion
		while(ADC10CTL1 & ADC10BUSY);          // Wait for conversion to complete
		sample[i] = ADC10MEM;                  // collect that 10-bit value
		if (sample[i] > 0x0200)	
		  P1OUT |= BIT0;                       // toggle LED ON
		else
		  P1OUT &= ~BIT0;                      // toggle LED OFF
		  
	 // continue for pins 3 and 5 consecutively...
```

Hardware interface:
* the ADC10 channels I will use:
  * ...
* the pins corresponding to those channels:
  * ...

Interface for the sensors:
* to use block or to use interrupts?
  * ...
* to convert one sensor at a time or multiple at a time?
  * ...

## Lab

## Debugging
### Prelab
I connected the DMM to each of the sensors. The left and center sensors gave out reasonable voltages, but the right sensor did not detect any significant voltage value. To double check, I used my cell-phone's camera to see if the transmitters were actually transmitting IR signals. Lo and behold, the left and center transmitters glowed purple, but the right transmitter did not. As a result, I exchanged the right transmitter. I double-checked this new transmitter and found good voltage values and the characteristic purple glow from the camera.
### Required Functionality
### B Functionality
### A Functionality

## Documentation
