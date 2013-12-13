#include <msp430g2553.h>

#define LED1_MASK	0x01
#define LED2_MASK	0x40
#define PIN1_4		0x10
#define PIN1_5		0x20
#define PIN1_7		0x80
#define PIN2_0		0x01
#define PIN2_1		0x02
#define PIN2_2		0x04
#define PIN2_3		0x08
#define PIN2_4		0x10
#define PIN2_5		0x20

int main(void)
{
    volatile int i = 0;

    /* stop watch timer */
    WDTCTL = WDTPW | WDTHOLD;

    /* set P1 direction */
    P2DIR = PIN2_5;

    for (;;) {

	/* toggle leds */
	P2OUT ^= PIN2_5;

	/* delay */
	for (i = 0; i < 10000; i++);
    }

}
