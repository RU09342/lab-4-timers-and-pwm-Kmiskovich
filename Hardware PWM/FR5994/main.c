#include <msp430.h> 
/*
 * Kevin Miskovich
 * Hardware PWM
 * FR5994
 */
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                  // Stop WDT
  PM5CTL0 &= ~LOCKLPM5;                      // for FRx boards

  P1DIR |= BIT0;                             // P1.0 output
  P1SEL |= BIT0;                             // P1.0 for TA0CCR1
  TA0CCR0 = 1000;                            // PWM Frequency in Hz
  TA0CCTL1 = OUTMOD_7;                       // CCR1 reset/set mode
  TA0CCR1 = 500;                             // CCR1 50% PWM duty cycle
  TA0CTL = TASSEL_2 + MC_1;                  // SMCLK, up mode, 1MhZ

  P5IE |=  BIT5;                             // P5.5 interrupt enabled
  P5IES |= BIT5;                             // falling edge
  P5REN |= BIT5;                             // Enable resistor on P5.5
  P5OUT |= BIT5;                             // Pull up resistor
  P5IFG &= ~BIT5;                            // Clear flag

  __bis_SR_register(LPM0_bits + GIE);        // Enter LPM0 for CPUOFF
}
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
    P5IE &= ~BIT5;                          //disable interrupt
    WDTCTL = WDT_MDLY_32;                   //Watchdog delay (ms)
    SFRIE1 |= WDTIE;                        //enable WDT interrupt
    P5IFG &=~BIT5;                          //clear flag
}
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR (void)
{
    SFRIE1 &= ~WDTIE;                       // disable WDT interrupt
    SFRIFG1 &= ~WDTIFG;                     // clear flag
    WDTCTL = WDTPW | WDTHOLD;               // stop watchdog timer

    if (!(P5IN & BIT5))                     // check button status
    {
        TA0CCR1 += 100;
        if(TA0CCR1==1100)
        {
            TA0CCR1=0;
        }
    }
    P5IE |= BIT5;                          //enable button interrupt
}
