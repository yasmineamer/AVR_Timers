/*
 * Timers_ex5.c
 *
 *  Created on: Sep 26, 2021
 *      Author: YASMINE AMER
 */


/*
 * CONTROL THE LED BRIGHTNESS USING FAST PWM
 * USE TIMER0
 * PRESCALER =8
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void timer0_pwm_init (void)
{
	TCNT0 = 0;
	OCR0 = 5;
	DDRB |= (1<<PB3);
	/*
	 * FOC0 ==> clear BIT (PWM MODE)
	 * WGM00,WGM01 ==> SET BIT (FAST PWM)
	 * COM01,COM00 ==> SET BIT (CLEAR OCR0 ON COMPARE MATCH _INVERTING)
	 * CS02,00 ==> CLEAR BIT, CS01 ==> SET BIT  (8 PRESCALLER)
	 */

	TCCR0 =(1<<WGM00)|(1<<WGM01)|(1<<COM00)|(1<<COM01)|(1<<CS01);
}

//function to control the OCR0 value
void set_duty (unsigned char duty)
{
	OCR0 = duty;
}


int main (void)
{
	unsigned char flag = 0;
	unsigned char duty = 0;

	timer0_pwm_init();

	while(1)
	{
		if (flag == 0)
		{
			duty ++;
			set_duty(duty);
			_delay_ms(20);
			if(duty == 256)
			{
				flag = 1;
			}
		}
		else
		{
			duty --;
			set_duty(duty);
			_delay_ms(20);
			if(duty == 256)
			{
				flag = 0;
			}
		}
	}

}
