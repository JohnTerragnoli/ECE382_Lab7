ECE382_Lab7
===========

## *Functionality Update*
|Functionality|Status|Date Completed|Checked by|
|:-:|:-:|:-:|:-:|
| Required | Complete | 3 Dec 14 @ 1700 | ... |
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
* The registers I will use:
  * `P1DIR`: sets the LED to an output
  * `P1OUT`: toggles the LED ON and OFF
  * `ADC10CTL0`: turns the ADC ON and OFF; sets Vcc and Vss references
  * `ADC10CTL1`: determines the channel
  * `ADC10AE0`: determines analog input for desired pin
  * `ADC10SC`: starts conversion process
  * `ADC10BUSY`: signals busy while converting
  * `ADC10MEM`: holds the 10-bit value
* The bits will I use from those registers:
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
  
  * Here is the initialization sequence for pin 4 (refer to `lab7. c`):
```
	// Configure P1.4 to be the ADC input
	ADC10CTL0 = 0				// Turn off ADC subsystem
	ADC10CTL1 = INCH_4 | ADC10DIV_3 	// Channel 4, ADC10CLK/4
	ADC10AE0 = BIT4;			// Make P1.4 analog input
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;	// Vcc & Vss as reference

	ADC10CTL0 |= ADC10SC			// Start a conversion
	while(ADC10CTL1 & ADC10BUSY)		// Wait for conversion to complete
	sample[i] = ADC10MEM			// collect that 10-bit value
	if (sample[i] > 0x0200)	
		P1OUT |= BIT0			// toggle LED ON
	else
		P1OUT &= ~BIT0			// toggle LED OFF
	  
 	// continue for pins 3 and 5 consecutively...
```

Hardware interface:
* The ADC10 channels I will use:
  * I will use channels 3, 4, and 5. 
* The pins corresponding to those channels:
  * Intuitively, the channels I will use correspond with pins `P1.3`, `P1.4`, and `P1.5`.

Interface for the sensors:
* I will use the sensors one at a time. In the while loop, I will start the conversion for the LEFT sensor, then immediately start the CENTER sensor, then the RIGHT sensor. The loop will then start again from the beginning. 

## Lab
### Required Functionality
I started out by utilizing the same code from the prelab but for the other two pins as well (P1.3 and P1.5). As I mentioned in the prelab, I checked for the samples for each sensor consecutively in a while loop. I decided to implement a switch-case that would take in a parameter which will correspond to the LEFT, CENTER, and RIGHT sensors. 
```
switch(sensor) {
	case LEFT:
		ADC10CTL0 = 0;
		ADC10CTL1 = INCH_3 | ADC10DIV_3 ;			// Channel 4, ADC10CLK/3
		ADC10AE0 = BIT3;					// Make P1.3 analog input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;	// Vcc & Vss as reference
		ADC10CTL0 |= ADC10SC;					// Start a conversion
		while(ADC10CTL1 & ADC10BUSY);				// Wait for conversion to complete
		sample3[i] = ADC10MEM;					// collect that 10-bit value

		if (sample3[i] > 0x01FF)				// if the sample values are greater than a certain V
			P1OUT |= BIT0;					// turn on LED
		else
			P1OUT &= ~BIT0;					// turn off LED
			
		i = (i+1) & 0xF;					// This is a mod 16 increment
		
		sensor = CENTER;					// move onto next case
		break;		
	case CENTER:
		// same as above, but with different channel and pin
		
		sensor = RIGHT;
		break;
	case RIGHT:
		// same as above, but with different channel and pin
		
		sensor = LEFT;
		break;
}
```

This code worked with the following arrays and index variables:
```
	unsigned short sample3[16];	// LEFT
	unsigned short sample4[16];	// CENTER
	unsigned short sample5[16];	// RIGHT
	unsigned char i = 0;		// index into sample array
```

I then tried to create methods that would make the code better organized. I wanted to make methods for each sensor's sampling. I ran into problems with the scope of the sample arrays and the index. This made it difficult to check what values the sensors were taking in. I decided to abandon this approach and instead, get rid of the sampling arrays altogether. 

I did create three methods which corresponds with the three sensors (left, center, and right). These methods pretty much hold the same code from above with the sampling and index portions excluded. Here is the method I used for the LEFT sensor:
```
void leftSensor() {
	ADC10CTL0 = 0;						// turn off the ADC subsytem
	ADC10CTL1 = INCH_3 | ADC10DIV_3 ;			// set input channel 3 and ADC10CLK/3
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;	// Vcc & Vss as reference

	ADC10CTL0 |= ADC10SC;					// Start a conversion
	while(ADC10CTL1 & ADC10BUSY);				// Wait for conversion to complete

	if (ADC10MEM > DETECTVALUE)				// if the sample values are greater than the detected voltage
		RED_ON;						// red LED ON
	else	
		RED_OFF;					// red LED OFF
}
```

You may notice that the method is missing the line of code that enables the analog inputs for each pin. Instead of calling this line in each method, I decided to simply put this line of code before the while() loop since it only had to run once.
```
	ADC10AE0 = BIT3 | BIT4 | BIT5;		// make P1.3, P1.4, and P1.5 analog inputs
```

My sensors worked as expected. When I placed a piece of paper on the left side of the robot, the RED LED lit up. Likewise, when I placed the piece of paper on the right side, the green LED lit up. Finally, when the paper was placed in front of the robot, both LEDs lit up. 

**Required funcitonality achieved!**

I noticed that the sensors were a little bit too sensitive. Thus, I changed the voltage detection value by increasing it slightly from 0x0200 to 0x0232.

### B Functionality

### A Functionality

## Debugging
#### Prelab [Debugging]
I connected the DMM to each of the sensors. The left and center sensors gave out reasonable voltages, but the right sensor did not detect any significant voltage value. To double check, I used my cell-phone's camera to see if the transmitters were actually transmitting IR signals. Lo and behold, the left and center transmitters glowed purple, but the right transmitter did not. As a result, I exchanged the right transmitter. I double-checked this new transmitter and found good voltage values and the characteristic purple glow from the camera.

#### Required Functionality [Debugging]
I had problems with reading in the sample data when I tried creating specific methods for sampling each sensor. The problem was due to the different scopes of the array variables. In the end, I decided against using these methods, and got rid of the sampling arrays altogether. Instead, I directly compared `ADC10MEM` to my voltage detector value (arbitrarily set). This ended up working well and still allowed me to compartamentalize my code into prettier methods.

#### B Functionality [Debugging]
#### A Functionality [Debugging]

## Documentation
