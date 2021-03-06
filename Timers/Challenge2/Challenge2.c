/*
 * Challenge2.c
 *
 *  Created on: Sep 25, 2021
 *      Author: Yasmine Amer
 */


                               /*task*/
/*
 * generate 3 digital clocks with frequency 10khz
 * 5khz and 2.5khz using timer0 ctc_mode
 */

                               /*calculations*/
/*
 * cpu_frequency = 8MHZ
 * Prescaler = 8
 * T_timer = 1MHZ
 * timer counts = 0.1ms / 1microsecond = 100
 * duty cycle 50% ==> OCR0 = 50
 */
#define F_CPU 8000000

#include<avr/io.h>
#include<avr/interrupt.h>
unsigned char g_tick = 0;

ISR(TIMER0_COMP_vect)
{
	g_tick++;
	PORTC ^= (1<<PC0);
	if(g_tick == 2)
	{
		PORTC ^= (1<<PC1);
	}
	if (g_tick == 4)
	{
		PORTC ^= (1<<PC2);
		PORTC ^= (1<<PC1);

		g_tick = 0;
	}
}

void TIMER0_COMP_init (int compare_value)
{
	TCNT0 = 0;
	OCR0 = 50;
	// Enable Timer0 Compare Interrupt
	TIMSK |= (1<< OCIE0); //ENABLE MODULE INTERRUPT

	/*
	 * FOC0 ==> SET BIT
	 * WGM00 ==> CLEAR BIT, WGM01 ==> SET BIT (CTC_MODE)
	 * COM01 ==> CLEAR BIT ,COM00 ==> SET BIT (TOGGEL ON COMPARE MATCH)
	 * CS00,CS02 ==> CLEAR BITS, CS01 ==>SET BIT (TIMER CLOCK)
	 */
	TCCR0 = (1<<FOC0)|(1<<WGM01)|(1<<COM00)|(1<<CS01);
}


int main (void)
{
	//first 3pins of PORTC are output pins ==> set these bits

	DDRC |= 0X07;
	PORTC |= 0X07;

	//ENABLE GLOBAL INTERRUPT BIT (I-BIT)
	SREG |= (1<<7);

	TIMER0_COMP_init (50);

	while(1)
	{

	}
	return 0;

}
