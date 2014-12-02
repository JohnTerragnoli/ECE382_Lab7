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
*  * Three pairs of IR emitters and detectors on the robot
*  * Use these pairs to detect if the robot is approaching a wall in the front or the sides.

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

Setting up the ADC10 subsystem:
* registers I will use:
*  * ...
* the bits will I use from those registers:
*  * ...
* initialization sequence:

Hardware interface:
* the ADC10 channels I will use:
*  * ...
* the pins corresponding to those channels:
*  * ...

Interface for the sensors:
* to use block or to use interrupts?
*  * ...
* to convert one sensor at a time or multiple at a time?
*  * ...

## Lab

## Debugging

## Documentation
