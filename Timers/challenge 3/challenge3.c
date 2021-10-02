/*
 * challenge3.c
 *
 *  Created on: Sep 26, 2021
 *      Author: Yasmine Amer
 */

/*
 * generate a 4khz clock using Timer0 pwm mode
 * YOU CHOOSE THE REQUIRED FREQUENCY PRE_SCALER
 */

/*
 * TIME PERIOD = 0.125 MICROSECOND
 * DUTY CYCLE = 0.5
 * USE THE EQUATION SLIDE 161
 */

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>

void timer0_pwm_init (unsigned char duty)
{
	TCNT0 = 0;
	OCR0 = duty;

	DDRB |=(1<<PB3);
	/*
	 * FOC0 ==> clear BIT (PWM MODE)
	 * WGM00,WGM01 ==> SET BIT (FAST PWM)
	 * COM01,COM00 ==> SET BIT (CLEAR OCR0 ON COMPARE MATCH _INVERTING)
	 * CS02,00 ==> CLEAR BIT, CS01 ==> SET BIT  (8 PRESCALLER)
	 */
	TCCR0 =(1<<WGM00)|(1<<WGM01)|(1<<COM00)|(1<<COM01)|(1<<CS01);
}

int main (void)
{
	timer0_pwm_init(128);

	while(1)
	{

	}
}
