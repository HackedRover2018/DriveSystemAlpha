#ifndef TIMER_SPEAR_H_
#define TIMER_SPEAR_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define F_CLK_1024 F_CPU / 1024UL
#define F_CLK_256 F_CPU / 256UL
#define F_CLK_64 F_CPU / 64UL
#define F_CLK_8 F_CPU / 8UL

#define TIMER_PRESCALE 10

void avr_interrupt_timer_init();

void avr_pwm_timer_init();

#endif /* TIMER_SPEAR_H_ */