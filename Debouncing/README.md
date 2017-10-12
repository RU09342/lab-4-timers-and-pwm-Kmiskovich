# Kevin Miskovich

## Software Debouncing
The codes in this project are written in C and are used to blink an LED with a 50% duty cycle on each of the boards listed below.
This code uses an if statement inside the watchdog timer ISR in order to check if the button is pressed in order to debounce the signal. 
The Port 1 interrupt is used to enable the watchdog timer interrupt and add a delay to the watchdog timer.

# The Following Boards Are Implemented:
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

## Dependencies
This library only depends on the MSP430.h header file for TI MSP430 processors. This file is included in each of the C files. No other header files are required.

### The only peripherals being used are LED outputs and button inputs on each board:
* G2443: P1.0 [LED1] and P1.3 [S2]
* F5529: P1.0 [LED1] and P1.1 [S2]
* FR5594: P1.0 [LED1] and P5.5 [S2]
* FR2311: P1.0 [LED1] and P1.1 [S1]
* FR6989: P1.0 [LED1] and P1.1 [S1]

### Differences Between Boards
Most of the code is exactly the same for each processor, with the exception of the MSP430FRx microcontrollers, in which case you must turn off high impedance mode. Other than that, the only differences are pins, which are differentiated above.

## Usage
The software debouncing codes work when the button specified is pressed. When the button isnt pressed, the watchdog ISR is checking if the button is pressed and if it is, the button interrupt is activated, which debounces the signal.
