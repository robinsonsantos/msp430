#include <msp430g2553.h>

long sample;
long DegreeF;

void main(void) 
{
    // Stop watchdog timer
    WDTCTL = WDTPW + WDTHOLD;
    // P1.3 (push button) as input, 0 input
    P1DIR &= ~0x08;
    // Enable P1.3 (push button) resistor
    P1REN |= 0x08;
    // Select P1.3 (push button), 0 selects
    P1SEL &= ~0x08;
    // Temperature Sensor ADC10CLK/4
    ADC10CTL1 = INCH_10 + ADC10DIV_3;
    // Ref voltage/sample & hold time/
    // reference generator ON/ADC10 ON
    ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;

    while(1) {
        // Wait while button up
        while((P1IN & 0x08) == 0x08);
        // Sampling and conversion start
        ADC10CTL0 |= ENC + ADC10SC;
        // Waint for ADC to complete
        while(ADC10CTL1 & ADC10BUSY);
        // Read ADC sample
        sample = ADC10MEM;
        DegreeF = ((sample - 630) * 761) / 1024;
        // SET BREAKPOINT HERE
        __no_operation();
    }
} 
