#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include "uart_spear.h"
#include "control_system_spear.h"
#include "timer_spear.h"


#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define BUF_SIZE 32
#define MAX_COMPARE_8_BIT 255



volatile int LOOP_RUN_FLAG = 0;
volatile int TIMER2A_FLAG = 0;

char INPUT_COMMAND_STRING[BUF_SIZE];
// TODO: refactor current_command
struct polar_coordinate CURRENT_COMMAND;

void setup_pins();

int main (void) 
{
	// Initialize
	CURRENT_COMMAND.mag = 0.0;
	CURRENT_COMMAND.dir = 0.0;
    struct motor_levels motor_output;
	
	setup_pins();
	avr_interrupt_timer_init();
    avr_pwm_timer_init();
	uart_init();
	uart_set_io_streams(stdin, stdout);
    stdin = &uart_input;
    stdout =  &uart_output;
	
	// Enable global interrupts
	sei();

	// Super loop
	while(1) 
	{
		while(LOOP_RUN_FLAG == 0);
		LOOP_RUN_FLAG = 0;
        
        // Compute skid steer levels
        motor_output = compute_levels(CURRENT_COMMAND);
        // Set timer compare register
        //printf("motor_output left: %i /100; right: %i /100\n", (int) motor_output.left_level*100, (int) motor_output.right_level*100);
        int left_count = (int) (motor_output.left_level * MAX_COMPARE_8_BIT);;
        int right_count = (int) (motor_output.right_level * MAX_COMPARE_8_BIT);
        OCR2A = left_count; //(int) (motor_output.left_level * MAX_COMPARE_8_BIT);
        OCR2B = right_count; //(int) (motor_output.right_level * MAX_COMPARE_8_BIT);
        
        // TODO: CURRENT_COMMAND is set in the interrupt handler, refactor that to set it here and make it not global
		//printf("mag: %i, dir %i\n", (int) CURRENT_COMMAND.mag, (int) CURRENT_COMMAND.dir);
        printf("left: %i, right: %i\n", left_count, right_count);
        PORTB ^= _BV(PORTB7);
	}
}

void setup_pins()
{
	DDRB |= _BV(DDB7) | _BV(DDB4);
	PORTB |= _BV(PORTB7) | _BV(PORTB4);
    DDRH |= _BV(DDH6);
    PORTH |= _BV(PORTH6);
}

// Incoming message interrupt
ISR(USART0_RX_vect)
{
	char receivedByte = UDR0; // Fetch incoming byte
    UDR0 = receivedByte;
	PORTB ^= _BV(PORTB7);
	if(receivedByte != '\n')
	{
		strncat(INPUT_COMMAND_STRING, &receivedByte, sizeof(receivedByte));
	}
	else
	{
		command_to_polar(INPUT_COMMAND_STRING, &CURRENT_COMMAND);
		memset(INPUT_COMMAND_STRING, 0, sizeof(INPUT_COMMAND_STRING));
	}
    LOOP_RUN_FLAG = 1;
}

// Timer interrupt
ISR(TIMER1_COMPA_vect)
{
	LOOP_RUN_FLAG = 1;
}



