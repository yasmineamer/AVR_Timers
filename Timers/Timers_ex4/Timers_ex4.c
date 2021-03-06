/*
 * Timers_ex4.c
 *
 *  Created on: Sep 25, 2021
 *      Author:YASMINE AMER
 */


                                   /*TASK*/

/*
 *generate a 500Hz clock using PWM
 * presacler = 8
 *
 */

                              /**calculation**/

/*
 * F_CPU = 1MHZ
 * F_TIME = 1/8 MHZ
 * TIMER_TIME_PERIOD = 8 MICROSECOND
 * DUTY CYCLE = 0.5
 * TIME_ON = 0.5*8MICROSECOND =4 MICROSECOND
 * TO GET 50% DUTY CYCLE ==> OCR0 = 128
 * DELAY 5000 MS
 * TO GET 25% DUTY CYCLE ==> OCR0 = 64
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void timer0_pwm_init (void)
{
	TCNT0 = 0;
	OCR0 = 128;
	DDRB |= (1<<PB3);
	/*
	 * FOC0 ==> clear BIT (PWM MODE)
	 * WGM00,WGM01 ==> SET BIT (FAST PWM)
	 * COM01,COM00 ==> SET BIT (CLEAR OCR0 ON COMPARE MATCH _INVERTING)
	 * CS02,00 ==> CLEAR BIT, CS01 ==> SET BIT  (8 PRESCALLER)
	 */

	TCCR0 =(1<<WGM00)|(1<<WGM01)|(1<<COM00)|(1<<COM01)|(1<<CS01);
}


void set_duty (unsigned char duty)
{
	OCR0 = duty;
}


int main (void)
{

	timer0_pwm_init();

	_delay_ms(5000);

	set_duty(192);

	while(1)
	{

	}

}
