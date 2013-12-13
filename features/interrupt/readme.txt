#include <msp430g2553.h>

// Enables P1.3 to generate interrupt
//   00000000
// + 00001000
//   00001000 

P1IE |= 0x08;

// Enables the push button P1.3
// Select Port 1 P1.3
//   00000000
// x 11110111
//   00000000

// Select Port 1 P1.3 
P1SEL &= ~0x08;

// Port 1 P1.3 as input
P1DIR &= ~0x08;

// Enables Port 1.3 pull-up resistor
P1REN |=  0x08;

// Enables CPU interrupt response
// Enables interrupts
__BIS_SR(GIE);

#pragma vector=PORT1_VECTOR
    __interrupt void Port_1(void)

P1IFG &= ~0x08;
