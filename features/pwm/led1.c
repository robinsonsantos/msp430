#include <msp430g2553.h>

void main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW + WDTHOLD;

    // Set P1.0 to output direction
    P1DIR |= BIT0;

    // Set the red LED on
    P1OUT &= ~BIT0;

    // Count limit (16 bit)
    TA0CCR0 = 12000;

    // Enable counter interrupts, bit 4=1
    TA0CCTL0 = 0x10;

    // Timer A 0 witch ACLK @ 12KHz, count UP
    TA0CTL = TASSEL_1 + MC_1;

    // LPM0 (low power mode) with interrupts enabled
    _BIS_SR(LPM0_bits + GIE);
}

#pragma vector=TIMER0_A0_VECTOR

// Timer0 A0 interrupt service routine
__interrupt void Timer0_A0 (void)
{

    // Toggle red LED
    P1OUT ^= BIT0;
}
