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

#ifndef _MAIN_H
#define _MAIN_H

/* MCU frequency */
#define F_CPU 8000000

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

/* define the prescaler used during setup of timer0 */
#define PRESCALER 0

/* define here the delay time you want in seconds */
#define SECONDS 600

/* Overflows per second */
#define TIMER_OVERFL  (F_CPU/256.0)

/* setpoint is calculated as the time in seconds 
** multiplied by the time it takes for Timer0 to overflow
** note: counter is a 32bit variable so the maximum delay
** in seconds is  4294967295/0.032768 = 131071999969.4 seconds
** thats about 4156 years :) */
volatile uint32_t setpoint = SECONDS * TIMER_OVERFL;

#endif //_MAIN_H
