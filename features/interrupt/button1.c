#include <msp430g2553.h>

#define greenLED 0x40

long i=0;

void main(void) 
{
    WDTCTL = WDTPW + WDTHOLD;

    P1DIR |= greenLED;
    P1OUT &= ~greenLED;

    P1SEL &= ~0x08;
    P1DIR &= ~0x08;
    P1REN |= 0x08;
    P1IE  |= 0x08;
    P1IFG &= ~0x08;
    _BIS_SR(GIE);
    while(1) i++;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) 
{
    P1IFG &= ~0x08;
    P1OUT ^= greenLED;

    i = 0;
}
