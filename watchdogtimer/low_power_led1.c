#include <msp430g2553.h>

volatile unsigned int delay;

void main(void) 
{
    // WDT as internal timer (period 0.5 ms)
    WDTCTL = WDT_MDLY_0_5;
    
    // Enables WDT interrupt
    IE1 |= WDTIE;

    // Sets P1.6, green LED, as output
    P1DIR |= BIT6;

    // Green Led toggle period +/- 1000 ms
    delay = 2000;

    // Enter low power mode 0, WDT still active
    _BIS_SR(LPM0_bits + GIE);
}

// Watchdog Interval Timer interrupt service
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    if (--delay == 0) {
        // Toggle LED2 (P1.6) state
        P1OUT ^= BIT6;

        // reloads delay.
        delay = 2000;
    }
}
