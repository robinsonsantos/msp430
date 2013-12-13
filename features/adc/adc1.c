#include <msp430g2553.h>

long sample;
long DegreeF = 0;

void main(void) 
{
    // Stop watchdog timer
    WDTCTL = WDTPW + WDTHOLD;

    // Set P1.0 to output direction
    P1DIR |= BIT0;
    // Set the LED on
    P1OUT &= ~BIT0;
    // Set P1.6 to output direction
    P1DIR |= BIT6;
    // Set the green LED on
    P1OUT &= ~BIT6;

    // Temperature Sensor ADC10CLK/4
    ADC10CTL1 = INCH_10 + ADC10DIV_3;
    // Ref voltage/sample & hold time
    // reference generator ON/ADC10 ON/Int Enabled
    ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE;

    // Count limit (16 bit)
    TA0CCR0 = 12000;
    // Enable Timer A0 interrupts, bit 4=1
    TA0CCTL0 = 0x10;
    // Timer A0 with ACLK, count UP
    TA0CTL = TASSEL_1 + MC_1;
     
    // LPM0 (low power mode) interrupts enabled
    _BIS_SR(LPM0_bits + GIE);    
}

// Timer0 A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
    __interrupt void Timer0_A0 (void) {
    // Toggle green LED
    P1OUT ^= BIT6;
    // ADC sampling and conversion start
    ADC10CTL0 |= ENC + ADC10SC;
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
    __interrupt void ADC10_ISR (void) {
    // Read ADC sample
    sample = ADC10MEM;
    DegreeF = ((sample - 630) * 761) / 1024;
    P1OUT ^= BIT0;
}
