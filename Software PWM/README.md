# Kevin Miskovich

## Software PWM
The codes in this project are written in C and are used to blink an LED with varying duty cycles on each of the boards listed below.
The timer is set into upmode, which allows CCR0 to be used as a ceiling for the count incrementation. 
By using the value in CCR0 and increasing by the value in CCR1 with each button press, the duty cycle varies.

# The Following Boards Are Implemented:
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

## Dependencies
This library only depends on the MSP430.h header file for TI MSP430 processors. 
This file is included in each of the C files. 
No other header files are required.

### The only peripherals being used are LED outputs and button inputs on each board:
* G2443: P1.0 [LED1] and P1.3 [S2]
* F5529: P1.0 [LED1] and P1.1 [S2]
* FR5594: P1.0 [LED1] and P5.5 [S2]
* FR2311: P1.0 [LED1] and P1.1 [S1]
* FR6989: P1.0 [LED1] and P1.1 [S1]


### Differences Between Boards
Most of the code is exactly the same for each processor, with the exception of the MSP430FRx microcontrollers, in which case you must turn off high impedance mode. Other than that, the only differences are pins, which are differentiated above.
The FR2311 uses the Timer B module instead of the Timer A module that the others use.

### EXTRA: Linear Brightness
After consulting with other students, I was able to give each of the boards the capability to perform a brightness increase.
This is achieved by using a large multi-case statement that separated by logarithmic values in the capture compare register. 

