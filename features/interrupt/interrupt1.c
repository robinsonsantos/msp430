#include <msp430g2553.h>
// Native gcc syntax
long i=0;

void main(void) 
{
    WDTCTL = WDTPW + WDTHOLD;

    P1SEL &= ~0x08;
    P1DIR &= ~0x08;
    P1REN |= 0x08;
    P1IE |= 0x08;
    P1IFG &= ~0x08;
    _BIS_SR(GIE);

    while(1) i++;
}

static void
__attribute__((__interrupt__(PORT1_VECTOR)))
 
Port_1(void) {	
    P1IFG &= ~0x08;
    i = 0;
}
    
