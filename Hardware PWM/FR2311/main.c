#include <msp430.h> 
/*
 * Kevin Miskovich
 * Hardware PWM
 * FR2311
 */
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                  // Stop WDT
  PM5CTL0 &= ~LOCKLPM5;                      // for FRx boards

  P1DIR |= BIT0;                             // P1.0 output
  P1SEL |= BIT0;                             // P1.0 for TB0CCR1
  TB0CCR0 = 1000;                            // PWM Frequency in Hz
  TB0CCTL1 = OUTMOD_7;                       // CCR1 reset/set mode
  TB0CCR1 = 500;                             // CCR1 50% PWM duty cycle
  TB0CTL = TASSEL_2 + MC_1;                  // SMCLK, up mode, 1MhZ

  P1IE |=  BIT1;                             // P1.1 interrupt enabled
  P1IES |= BIT1;                             // falling edge
  P1REN |= BIT1;                             // Enable resistor on P1.1
  P1OUT |= BIT1;                             // Pull up resistor
  P1IFG &= ~BIT1;                            // Clear flag

  __bis_SR_register(LPM0_bits + GIE);        // Enter LPM0 for CPUOFF
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1IE &= ~BIT1;                          //disable interrupt
    WDTCTL = WDT_MDLY_32;                   //Watchdog delay (ms)
    SFRIE1 |= WDTIE;                        //enable WDT interrupt
    P1IFG &=~BIT1;                          //clear flag
}
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR (void)
{
    SFRIE1 &= ~WDTIE;                       // disable WDT interrupt
    SFRIFG1 &= ~WDTIFG;                     // clear flag
    WDTCTL = WDTPW | WDTHOLD;               // stop watchdog timer

    if (!(P1IN & BIT1))                     // check button status
    {
        TB0CCR1 += 100;
        if(TB0CCR1==1100)
        {
            TB0CCR1=0;
        }
    }
    P1IE |= BIT1;                          //enable button interrupt
}
