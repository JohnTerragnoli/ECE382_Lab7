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

Setting up the ADC10 subsystem:
* registers I will use:
  * ...
* the bits will I use from those registers:
  * ...
* initialization sequence:

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
