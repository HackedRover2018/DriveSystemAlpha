#include "timer_spear.h"
#include <avr/io.h>

void avr_timer_init()
{
    // Timer one (used for interrupts)
    TCCR1B |= _BV(WGM12); // configure timer1 for CTC mode
    TIMSK1 |= _BV(OCIE1A); // enable the CTC interrupt b
    TCCR1B |= _BV(CS10) | _BV(CS12); // start the timer at 16MHz/1024
    OCR1A = F_CLK_1024; // set the CTC compare value
    
    // Timer two (used for pwm)
    TCCR2A |= _BV(COM2A1) | _BV(COM2B1); // set none-inverting mode
    TCCR2A |= _BV(WGM10); // set PWN Phase Corrected
    TCCR2B |= _BV(CS21); // set pre-scaler to 8 and starts PWM
}

void avr_timer_one_init()
{
    //Timer 1
    //=============================================
    // set none-inverting mode
    TCCR1A |= _BV(COM1A1) | _BV(COM1B1);
    // set PWN Phase Corrected
    TCCR1A |= _BV(WGM10);
    // set pre-scaler to 8 and starts PWM
    TCCR1B |= _BV(CS11);
    //=============================================
}