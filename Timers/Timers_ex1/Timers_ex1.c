/*
 * Timers_EX1.c
 *
 *  Created on: Sep 21, 2021
 *      Author: Yasmine Amer
 *
 */


/*** TOGGLE LED EVERY HALF SECOND
 * CONTROL LED BY TIMER0
 */

                                   /*** CALCULATIONS****/
/*
 * F_CPU = 1 MHZ
 * F_TIMER = 1 MHZ / 1024
 * T_TIMER = 1024 / 1MHZ =1.024 ms
 * T_OVERFLOW = 256*1.024 = 262.144 ms
 * TIMER_COUNTS = REQUIRED DELAY /T_TIMER =488 COUNTS
 * NO OF OVER FLOW PER SECOND = 1 / T_OVERFLOW = 4
 * LED TOGGLE ERVERY HALF SECOND SO AFTER TWO OVERFLOW
 *
 */

#include<avr/io.h>
#include<avr/interrupt.h>
unsigned char g_ovf_count = 0;

                           /*****interrupt service routine timer0*****/
ISR(TIMER0_OVF_vect)
{
	g_ovf_count ++;
	if (g_ovf_count == 2)
	{
		PORTC ^= (1<<0);
		g_ovf_count = 0;

	}

}

void timer0_ovf_init(void)
{

	TCNT0 = 0; //Set Timer initial value to 0
	TIMSK |= (1<<TOIE0); // ENABLE MODULE INTERRUPT
	/*NORMAL MODE ==> FOC0 ACTIVE
	 * WGM00 AND WGM01 ==> CLEAR BITS
	 * COM01:00 ==> CLEAR BITS
	 * CLOCK SELECT ==> SET BITS CS02 & CS00 , CLEAR BIT CS01
	 * TCCRO = 10000101 ASSIGN THIS VALUE TO THE REGISTER
	 */
	TCCR0 = (1<<FOC0)|(1<<CS02)|(1<<CS00);

}


int main (void)
{
	/* PCO OUTPUT PIN ==> DDRC SET BIT NUMBER 0
	 * OUTPUT ZERO ON THIS PIN AS INITIAL VALUE
	 */
	DDRC |= (1<<0);
	PORTC &= 0XFE;
	SREG |= (1<<7); //ENABLE GLOBAL INTERRUPT BIT I-BIT
	timer0_ovf_init();

	while(1)
	{

	}

	return 0;

}
