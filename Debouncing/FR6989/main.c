/*
 * Kevin Miskovich
 * Lab 4 Part 1
 * FR6989
 */
#include <msp430.h>
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   	      // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                     // for FRx boards

    P1IE |=  BIT1;                            // P1.1 interrupt enabled
    P1IES |= BIT1;                            //falling edge
    P1REN |= BIT1;                            // Enable resistor P1.1
    P1OUT |= BIT1;                            //Pull up resistor
    P1IFG &= ~BIT1;                           // P1.1 Interrupt Flag cleared
    P1DIR |= BIT0;                            // P1.0 pin output

    __bis_SR_register(LPM0_bits + GIE);       //timers needed, no CPU, interrupt enable
}
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR (void)
{
    SFRIE1 &= ~WDTIE;                        //disable WDT interrupt
    SFRIFG1 &= ~WDTIFG;                      //clear flag
    WDTCTL = WDTPW | WDTHOLD;                // stop watchdog timer

    if (!(P1IN & BIT1))                      //check if button is pressed
    {
        P1OUT ^= BIT0;                       //toggle LED
    }
    P1IE |= BIT1;                            //enable button interrupt P1.1
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1IE &= ~BIT1;                         //disable interrupt
    WDTCTL = WDT_MDLY_32;                  //Watchdog 32ms delay
    SFRIE1 |= WDTIE;                       //enable WDT interrupt
    P1IFG &=~BIT1;                         //clear flag
}
