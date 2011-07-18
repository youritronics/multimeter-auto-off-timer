/****************************************************************************
*																			*
*       Multimeter auto off timer v1.0										*
*       License: creative commons - attribution, share-alike 				*
*       Copyright Florin Cocos 2011											*
*       http://www.youritronics.com											*
*																			*
*		device: ATtiny25													*
*		fuse:	CKDIV8 disabled												*
*																			*
****************************************************************************/
#include "main.h"

volatile uint8_t start_flag;
volatile uint32_t counter;


int main(void)
{
DDRB |= _BV(4);		//output for transistor
PORTB &= ~_BV(4);	//start as low (transistor off)
DDRB &= ~_BV(2);	//INT0 input for switch on 

// The low level of INT0 generates an interrupt request.
MCUCR |= (0 << ISC00) | (0 << ISC01); 

// Enable INT0 pin change 
GIMSK |= (1 << INT0);

// Select Timer0 clock prescaler 0 (no prescale for better acuracy)
TCCR0B |= (1 << CS00);

// Enable Timer0 overflow interrupt
TIMSK |= (1 << TOIE0);

// Enable the Global Interrupt Enable flag so that interrupts can be processed 
sei(); 

// Prepare for sleep mode in Power Down mode
set_sleep_mode(SLEEP_MODE_PWR_DOWN);

while(1)
{
// Leep the MCU in sleep mode all the time
sleep_mode();
}

}



ISR(INT0_vect)       
{
PORTB |= _BV(4);	// Enable the transistor output
counter = 0;		// Reset the counter
start_flag = 1; 	// Set start flag to 1 so we start counting in Timer0 interrupt routine

// Prepare for sleep mode in Idle mode so Timer0 can continue working and providing interrupts
set_sleep_mode(SLEEP_MODE_IDLE); 
}


ISR(TIMER0_OVF_vect)
{
if(start_flag)
	{
	if(counter < setpoint)
		{
		counter++;			// increment counter until setpoint is reached
		} 
	else 
		{
		
		PORTB &= ~_BV(4); 	// setpoint reached turn off transistor output
		start_flag = 0;		// setpoint reached, stop counting in Timer0 interrupt routine
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);	// Prepare for sleep mode in Power Down mode
		}
	}
}
