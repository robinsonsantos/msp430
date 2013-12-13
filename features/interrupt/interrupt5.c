#include <msp430g2553.h>

#define pin0mask  (0x01 << 0)
#define pin3mask  (0x01 << 3)
#define pin6mask  (0x01 << 6)

int main(void) {
    /* Hold the watchdog timer so it doesn't reset our chip */
    WDTCTL = WDTPW + WDTHOLD;

    /* Configure pins 0,6 on port 1 as output pins */
    P1DIR = pin0mask | pin6mask;

    /* a flag to tell us when we've handled a button event */
    int buttonPushed = 0;

    /* we'll toggle between different modes */
    int blinkMode = 0;

    /* which lights we need to blink -- start red only */
    int blinkMask = pin0mask;

    /* make sure green (pin 6) is turned off */
    P1OUT &= ~pin6mask;

    /* infinite loop */
    for( ; ; ) {
        /* The following two lines implement a very crude delay loop.
         * The actual length of the delay can vary significantly.
         * This approach may not work with all compilers.
         */
        volatile int i;
        for( i = 0; i < 20000; i++ );

        /* Switch 2 is connected to pin 3.  If it is low, then change the
         * blinking behavior (unless it we have handled the press already)
         */
        if(( P1IN & pin3mask ) == 0 ) {
            if( !buttonPushed ) {
                /* remember so we don't try to handle this press again */
                buttonPushed = 1;

                blinkMode = (blinkMode + 1)%4;

                if( blinkMode == 0 ) {
                    /* blink red (bit 0) only */
                    blinkMask = pin0mask;

                    /* make sure (pin 6) green is off */
                    P1OUT &= ~pin6mask;
                } else if( blinkMode == 1 ) {
                    /* blink green (pin 6) only */
                    blinkMask = pin6mask;

                    /* make sure red (pin 0) is off */
                    P1OUT &= ~pin0mask;
                } else if( blinkMode == 2 ) {
                    /* blink both together */
                    blinkMask = pin0mask|pin6mask;

                    /* make sure both are on */
                    P1OUT |= pin0mask|pin6mask;
                } else {
                    /* blink both alternately */
                    blinkMask = pin0mask|pin6mask;

                    /* make sure red is off and green is on */
                    P1OUT &= ~pin0mask;
                    P1OUT |= pin6mask;
                }
            }
        } else {
            buttonPushed = 0;
        }

        P1OUT ^= blinkMask;
    }
}
