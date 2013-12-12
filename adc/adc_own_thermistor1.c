#include <msp430g2553.h>

long sample;
long DegreeF;

void main(void) 
{
    // Stop watchdog timer
    WDTCTL = WDTPW + WDTHOLD;
    // Temperature Sensor ADC10CLK/4
    ADC10CTL1 = INCH_10 + ADC10DIV_3;
    // Ref voltage/sample & hold time/
    // reference generator ON/ADC10 ON
    ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC100N;

    while(1) {
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
