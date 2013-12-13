 #include <msp430g2553.h>

void main(void) {

   WDTCTL = WDTPW + WDTHOLD;        // Stop watchdog timer

   P1DIR |= 0x40;                   // Set P1.6 (green LED) to output direction, 1 is output

   P1OUT &= ~0x40;                  // Set the green LED off
 

   P1DIR &= ~0x08;                  // Port 1 P1.3 (push button) as input, 0 is input

   P1SEL &= ~0x08;                  // Select Port 1 P1.3 (push button), 0 selects

   P1REN |=  0x08;                  // Enable Port 1 P1.3 (push button) pull-up resistor

        while( 1 ) {

       if( (P1IN & 0x08) == 0)      // Push button down when bit 3 == 0

          P1OUT |= 0x40;            // Set green LED on when button down

                   else

          P1OUT &= ~0x40;           // Set green LED off when button up

    }
}
