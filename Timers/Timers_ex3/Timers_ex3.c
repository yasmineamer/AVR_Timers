/*
 * Timers_ex3.c
 *
 *  Created on: Sep 24, 2021
 *      Author: YASMINE AMER
 */


                     /* GENERATE SQUARE WAVE 2KHZ USING TIMER0 COMPARE MODE */
                                           /*CALCULATION*/

/*
 * SQ_WAVE =2KHZ
 * period OF SQ WAVE = 0.5 ms
 * T_TIMER = 1 MICRO SECOND
 * TIMER_COUNT = 500 COUNTS FOR ONE CYCLE
 * TO HALF CYCLE COUNT  = 250
 */

#include<avr/io.h>
#include<avr/interrupt.h>

void Timer0_comp_init(void)
{
	TCNT0 = 0;
	OCR0 = 250;
	DDRB = DDRB | (1<<PB3); // Configure PB3/OC0 Pin as output pin
//	TIMSK |= (1<<OCIE0); NO NEED FOR INTERRUPT HERE IT WILL TOGGEL AUTOMATICALLY
	/*
	 * FOC0 ==> SET BIT
	 * WGM00 ==> CLEAR BIT, WGM01 ==> SET BIT (CTC)
	 * COM01 ==> CLEAR BIT, COM00 ==> SET BIT TO TOGGEL ON COMPARE MATCH
	 * CS02,01 ==> CLEAR BIT, CS00 ==> SET BIT  (NO PRESCALLING)
	 */

	TCCR0 = (1<<FOC0)|(1<<WGM01)|(1<<COM00)|(1<<CS00);

}

int main (void)
{
	SREG |= (1<<7); //ENABLE GLOBAL INTERRUPT BIT I-BIT (NO NEED FOR IT)
	Timer0_comp_init();
	while(1)
	{

	}

}
