#include <msp430.h> 
/*
 * Kevin Miskovich
 * Hardware PWM
 * G2553
 */
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                  // Stop WDT

  P1DIR |= BIT0;                             // P1.0 output
  P1SEL |= BIT0;                             // P1.0 for TA0CCR1 
  TA0CCR0 = 1000;                            // PWM Frequency in Hz
  TA0CCTL1 = OUTMOD_7;                       // CCR1 reset/set mode
  TA0CCR1 = 500;                             // CCR1 50% PWM duty cycle
  TA0CTL = TASSEL_2 + MC_1;                  // SMCLK, up mode, 1MhZ

  P1IE |=  BIT3;                             // P1.3 interrupt enabled
  P1IES |= BIT3;                             // falling edge
  P1REN |= BIT3;                             // Enable resistor on P1.3
  P1OUT |= BIT3;                             // Pull up resistor
  P1IFG &= ~BIT3;                            // Clear flag

  __bis_SR_register(LPM0_bits + GIE);        // Enter LPM0 for CPUOFF
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1IE &= ~BIT3;                          //disable interrupt
    WDTCTL = WDT_MDLY_32;                   //Watchdog delay (ms)
    SFRIE1 |= WDTIE;                        //enable WDT interrupt
    P1IFG &=~BIT3;                          //clear flag
}
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR (void)
{
    SFRIE1 &= ~WDTIE;                          // disable WDT interrupt
    SFRIFG1 &= ~WDTIFG;                        // clear flag
    WDTCTL = WDTPW | WDTHOLD;                  // stop watchdog timer

    if (!(P1IN & BIT3))                        // check button status
    {    
        TA0CCR1 += 100;
        if(TA0CCR1==1100)
        {
            TA0CCR1=0;
        }
    }
    P1IE |= BIT3;                          //enable button interrupt
}
