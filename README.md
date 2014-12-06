ECE382_Lab7
===========

## *Functionality Update*
|Functionality|Status|Date Completed|Checked by|
|:-:|:-:|:-:|:-:|
| Required | Complete | 3 Dec 14 @ 1700 | Dr. Coulston |
| B | Complete | 3 Dec 14 @ 1700 | Dr. Coulston |
| A | Complete | 5 Dec 14 @ 1630 | Dr. York |

## Overview
* Interface analog systems with digitial systems
* Learn how to use the ADC (analog-to-digital converter) for the MSP430.
  * Three pairs of IR emitters and detectors on the robot
  * Use these pairs to detect if the robot is approaching a wall in the front or the sides.

### Functionality
#### Required Functionality
* Use the ADC subsystem to light LEDs based on the presence of a wall.
* The presence of a wall next to the left sensor should light LED1 on the Launchpad board. 
* The presence of a wall next to the right sensor should light LED2 on the Launchpad board. 
* Demonstrate that the LEDs do not light until they come into close proximity with a wall.

#### B Functionality
* Create a standalone library for my ATD code and release it on Github. 
* This should be separate from my lab code. 
* It should have a thoughtful interface and README, capable of being reused in the robot maze laboratory.

#### A Functionality
* Since each robot's sensors are a little bit different, I need to fully characterize the sensors for my robot. 
* Create a table and graphical plot that shows the ATD values for a variety of distances from a maze wall. 
* This table/graph must be generated for each IR sensor. 
* Use these values to determine how the IR sensors work so I can properly use them to solve the maze.

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
I began by double-checking the voltage signals for each of my sensors. With the sensors connected to the 5 V source, I was receiving a maximun voltage of about 2.5 V. Because of this, I decided that I did not need to convert the 5 V into 3.3 V just for the MSP430.

I utilized the same code from the prelab but for the other two pins as well (P1.3 and P1.5). As I mentioned in the prelab, I checked for the samples for each sensor consecutively in a while loop. I decided to implement a switch-case that would take in a parameter which will correspond to the LEFT, CENTER, and RIGHT sensors. 
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

**Required functionality achieved!**

I noticed that the sensors were a little bit too sensitive. Thus, I changed the voltage detection value by increasing it slightly from 0x0200 to 0x0232.

### B Functionality
For B functionality, all I did was create an implementation file (`16_lab7_imp.c`) and a library file (`robot.h)`. Within the library file, I defined various constants and created function prototypes. In the implementation, I put in all of my methods excluding main().

Specifically, I added three methods; one for each sensor. As you may guess, these methods are the ones I described earlier in the Required Functionality section.

Overall, by separating my code into distinct files made my code more eligible and easier to debug.

**B functionality achieved!**

### A Functionality
To get A functionality, I needed to characterize the various sensor values at different wall distances. I used a DMM (digital multimeter), a 12-inch ruler, and one of the robot mazes. I decided to measure the output voltages of the receiver for 4 different distances from the wall for each sensor. These four distances are: 1 inch, 2 inches, 4 inches, and 8 inches.

I started with the left sensor. Using the ruler, I ensured the sensor was perpendicular to the face of the wall at a distance of 1 inch. I took two more measurements using two different walls of the robot maze. I did this purposely to account for the different lighting throughout the maze. 

To get the best measurements, I realized that I should step a few feet away from the robot during measurements in order to minimize the effects from my shadows onto the IR receiver. Surprisingly, I was able to get good voltage which were all pretty close to each other's values.

With three measurements for each of the four distances, I was able to calculate decent averages. I then characterized the rest of the sensors as shown below:

![alt test](https://github.com/sabinpark/ECE382_Lab7/blob/master/images/sensor_characterization.PNG "sensor voltage characterization")

Here is a graphical display of these voltages.

![alt test](https://github.com/sabinpark/ECE382_Lab7/blob/master/images/sensor_graph.PNG "sensor graph")

Since I wanted my threshold voltage to trigger a certain response with some consistency, I knew there had to be a range of HEX values that did not overlap with other threshold values and was still big enough for my needs. As shown in the last four columns above, I found the min and max range of the threshold voltages. I found these values by dividing the difference between adjacent DEC values by 2. This difference was then added to a certain value to get the max, and subtracted from that value to get the min. The next threshold voltage's max would therefore be equal to the current threshold voltage's min - 1. Theoretically, at least, this should work for making my robot do various things. We shall find out in lab 8 whether this works as well as I wanted.

**A functionality achieved!**

After talking to Dr. York, I realized that there are other methods of finding good IR sensor characterizations. Currently, I am only measuring the output voltage of each sensor for various distances from walls. However, these are only theoretical values, and I cannot simply assume that these voltage readings perfectly match the threshold voltages I use in my code to properly toggle the LEDs. Thus, I will consider utilizing some different methods to get better IR sensor characterizations. 

IDEAS:
* set an arbitrary HEX value and then move the robot away from the wall until the sensor turns on the LED
  * measure that distance
  * do it for each sensor, but perhaps only for one distance characterization
  * try to get it to be around 2 to 3 inches
* consider what would happen if the motor starts running
  * would that affect the voltage characterization?
  * try testing out the robot with the sensors while the motors are running (set up on top of erasers)
* is the voltage difference between just running the battery and running with the MSP430 hooked up different?
  * It is...but is that difference a constant?
  * Using the first idea, maybe I can compare the hex values and find what that constant it.

## Debugging
#### Prelab [Debugging]
I connected the DMM to each of the sensors. The left and center sensors gave out reasonable voltages, but the right sensor did not detect any significant voltage value. To double check, I used my cell-phone's camera to see if the transmitters were actually transmitting IR signals. Lo and behold, the left and center transmitters glowed purple, but the right transmitter did not. As a result, I exchanged the right transmitter. I double-checked this new transmitter and found good voltage values and the characteristic purple glow from the camera.

#### Required Functionality [Debugging]
I had problems with reading in the sample data when I tried creating specific methods for sampling each sensor. The problem was due to the different scopes of the array variables. In the end, I decided against using these methods, and got rid of the sampling arrays altogether. Instead, I directly compared `ADC10MEM` to my voltage detector value (arbitrarily set). This ended up working well and still allowed me to compartamentalize my code into prettier methods.

Another problem I had was that some of the sensors produced very weak output voltages. I discovered that by adjusting the direction of the IR transmitter and receiver, I could receive much greater (or less, if I wanted) voltage values. The greatest voltage values corresponded to the when transmitter and receiver were parallel.

#### B Functionality [Debugging]
None.

#### A Functionality [Debugging]
When I first started to measure the voltages for each sensor, I noticed that the voltage values displayed on the DMM was very erratic. I soon discovered that I should place the robot and DMM on the maze, then make sure I was a few feet away. This helped to keep the lighting (shadows) around the robot more constant, effectively allowing the DMM values to be more constant as well. 

## Documentation
* Prelab: I used the code provided by Dr. Coulston to utilize one of the sensors. Using this code, I was able to read the two other sensors as well.
* Required Functionality: None.
* B Functionality: None.
* A Functionality: Dr. York gave me various ideas on accurately configuring the sensors with corresponding voltages and hexadecimal values used in the code.  
