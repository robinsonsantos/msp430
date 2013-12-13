#include <msp430g2553.h>

unsigned int counter = 0;

void main(void) 
{
    // Watchdog Timer interval to +/- 32ms
    WDTCTL = WDT_MDLY_32;

    // Enable WDT interrupt
    IE1 |= WDTIE;

    // Set red LED P1.0 to output direction
    P1DIR |= BIT0;

    // Enable interrupts
    _BIS_SR(GIE);

    while(1);
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    
    // 10 * 32 ms = 320 ms, +/- .3 s
    if (counter == 10) {
 
        // P1.0 toggle, red LED
        P1OUT ^= BIT0;        
        counter = 0;
    } else
        counter++;
}
