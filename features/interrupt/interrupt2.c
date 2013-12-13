#include <msp430g2553.h>

unsigned int wdtCounter = 0;

void main(void) 
{
    WDTCTL = WDT_MDLY_32;
    IE1 |= WDTIE;

    P1DIR |= BIT0;
    P1OUT |= BIT0;

    P1IE |= BIT3;
    P1DIR &= ~0x08;
    P1REN |= BIT3;
    P1IFG &= ~0x08;

    _BIS_SR(GIE);

    while(1);
}

#pragma vector=WDT_VECTOR
__interrupt void 
watchdog_timer(void) {
    if (wdtCounter == 249) {
	P1OUT &= ~0x01;
	wdtCounter = 0;
	_BIS_SR(LPM0_bits + GIE);
    }
    else
    	wdtCounter++;
}

#pragma vector=PORT1_VECTOR
__interrupt void
Port_1(void) {
    wdtCounter = 0;
    P1OUT |= 0x01;
    P1IFG &= ~0x08;
    _BIC_SR(LPM0_EXIT);
}
