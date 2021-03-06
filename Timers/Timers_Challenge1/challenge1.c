/*
 * TIMERS_CHALLENGE1.C
 *
 *  Created on: Sep 22, 2021
 *      Author: YASMINE AMER
 */

/*
 *
 *F_CPU = 8 MHZ
 *7_SEGMENT CONNECTED TO PORTC
 *PRESCALER 256
 *EVERY SECOND THE 7_SEGMENT SHOULD BE INCREMENT USING TIMER0
 *AFTER 9 OVERFLOW OCCOURS
 *
 */

/***CALCULATION**/
/*
 * F_TIMER = 8MHZ / 256
 * T_TIMER = 256 / 8MHZ = 0.032 ms
 * T_OVF = 256 * 0.032 = 8.192 ms
 * NUMBER OF OVF PER SECOND = 123
 */
#define F_CPU 8000000
#include<avr/io.h>
#include<avr/interrupt.h>

#define NUM_OVF_PER_SECOND 123
unsigned char g_ticks = 0 ;
unsigned char g_num = 0;

/***interrupt service routine**/

ISR(TIMER0_OVF_vect)
{
	g_ticks ++;

	if (g_ticks == NUM_OVF_PER_SECOND )
	{
		g_ticks = 0;
		if(g_num == 9)
		{
			g_num = 0;
			return;
		}
		g_num ++;
	}
}

void timer0_ovf_init(void)
{
	TCNT0 = 0 ;
	TIMSK |= (1<<TOIE0);

	TCCR0 = (1<<FOC0)|(1<<CS02);

}

int main(void)
{
	/*
	 * PORTC OUTPUT ==> SET ALL BITS
	 * PORTC INTIAL VALUE 0
	 */


	DDRC = 0XFF ;
	PORTC = 0xC0;
	SREG |= (1<<7);
	timer0_ovf_init();

	while(1)
	{
		switch(g_num)
		{
			case 0:
				PORTC = 0xC0;
				break;
			case 1:
				PORTC = 0xF9;
				break;
			case 2:
				PORTC = 0xA4;
				break;
			case 3:
				PORTC = 0xB0;
				break;
			case 4:
				PORTC = 0x99;
				break;
			case 5:
				PORTC = 0x92;
				break;
			case 6:
				PORTC = 0x82;
				break;
			case 7:
				PORTC = 0xF8;
				break;
			case 8:
				PORTC = 0x80;
				break;
			case 9:
				PORTC = 0x90;
				break;

		}
	}
	return 0;
}

//int main(void)
//{
//	unsigned char number[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
//	DDRC = 0XFF ;
//	PORTC = 0xC0;
//	SREG |= (1<<7);
//	timer0_ovf_init();
//
//	while(1)
//	{
//		PORTC = number[g_num];
//	}
//	return 0;
//} here code consume program memory 2.6% and data 1.2%
