/*
 * Kevin Miskovich
 * Lab 4 Part 1
 * FR5994
 */
#include <msp430.h>
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   	      // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                     // for FRx boards

    P5IE |=  BIT5;                            // P5.5 interrupt enabled
    P5IES |= BIT5;                            //falling edge
    P5REN |= BIT5;                            // Enable resistor P5.5
    P5OUT |= BIT5;                            //Pull up resistor
    P5IFG &= ~BIT5;                           // P5.5 Interrupt Flag cleared
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
    P5IE |= BIT5;                            //enable button interrupt P5.5
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_5(void)
{
    P5IE &= ~BIT5;                         //disable interrupt
    WDTCTL = WDT_MDLY_32;                  //Watchdog 32ms delay
    SFRIE1 |= WDTIE;                       //enable WDT interrupt
    P5IFG &=~BIT5;                         //clear flag
}
