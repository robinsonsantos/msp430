#include <msp430g2553.h>

volatile unsigned int i=0;

void main(void) 
{
    // Stop WDT
    WDTCTL = WDTPW + WDTHOLD;
    
    // Enter low power mode 0
    // _BIS_SR(LPM0_bits + GIE);
    _BIS_SR(LPM0_bits);

    // Executes forever
    while(1) i++;
}
