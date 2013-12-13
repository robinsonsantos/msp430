#include "msp430g2553.h"

#define	LED1	0x01
#define BTN1	0x08

void configureClocks();

volatile unsigned int i;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;

    configureClocks();
    // volatile to prevent optimization
    // Stop watchdog timer
    // Configure LED on P1.0 // P1.0 output

    P1DIR = LED1; // P1.0 output LOW, LED Off

    P1OUT &= ~LED1; 

    // Configure Switch on P1.3 // P1.3 Enable Pullup/Pulldown
    P1REN |= BTN1; // P1.3 pullup

    P1OUT = BTN1; 

    while (1) {
        if (P1IN & ~BTN1) {
            P1OUT ^= LED1;
        }
    }
    // P1.2 is Low?
    // Toggle LED at P1.0
}

void configureClocks()
{
    // Set system DCO to 8MHz
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ;
    // Set LFXT1 to the VLO @ 12kHz
    BCSCTL3 |= LFXT1S_2;
}
