#include <msp430g2553.h> 

#define LED1_MASK	0x01
#define LED2_MASK	0x40
#define BTN1_MASK	0x08

int main(void)
{

    volatile int i = 0;

    // stop watchdog timer
    WDTCTL = WDTPW + WDTHOLD;

    // set P1 to output direction 
    P1DIR |= (LED1_MASK + LED2_MASK);

    // P1.3 must stay at input
    P1OUT &= ~(LED1_MASK + LED2_MASK);

    //P1IE |= BUTTON; // P1.3 interrupt enabled

    for (;;) {

	// toggle leds
        P1OUT ^= (LED1_MASK | LED2_MASK);

	// delay
	for (i = 0; i < 10000; i++);
    }
}

