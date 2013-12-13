/* Adapted from Aldo Briano's demo code */
#include <msp430g2553.h>

#define RED_LED 0x01
#define GRN_LED 0x40
#define BUTTON  0x08

int main(void)
{
    /* Stop the watchdog timer so it doesn't reset our chip */
    WDTCTL = WDTPW + WDTHOLD;

    /* Set both LED pins as output pins (and the rest are input pins) */
    P1DIR = (RED_LED + GRN_LED);

    /* Make sure both LEDs are off */
    P1OUT &= ~(RED_LED + GRN_LED);

    /* "Port 1 interrupts enable" for our BUTTON pin */
    P1IE |= BUTTON;

    /* Clear our BUTTON in the Port 1 interrupt flag.
     * This would be more important if our program handled
     * different kinds of interrupts, because we'd need
     * to check this flag to see which of the interrupts
     * were actually triggered.
     */
    P1IFG &= ~BUTTON;

    /* loop forever */
    for( ; ; ) {
        /* Go into low power mode 0, general interrupts enabled */
        __bis_SR_register( LPM0_bits + GIE );
    }
}


/* Port 1 interrupt service routine.  First, this prototype tells
 * the compiler that the function handles interrupts for
 * Port 1.  Then the function follows.
 */
void Port_1 (void) __attribute__((interrupt(PORT1_VECTOR)));
void Port_1(void)
{
    /* Toggle both LEDs by xoring with their bitmasks */
    P1OUT ^= (RED_LED + GRN_LED);

    /* Clear the interrupt flag */
    P1IFG &= ~BUTTON; // P1.3 IFG cleared

    /* Uncomment the next line if you want button releases also to trigger.
     * That is, we change the interrupt edge, and Hi-to-Low will
     * trigger the next interrupt.
     */
    // P1IES ^= BUTTON;

    /* This line is still magic to me.  I think it exits low power mode 0
     * so the main program can resume running.
     */
    __bic_SR_register_on_exit( LPM0_bits );
}
