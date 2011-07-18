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
#define prescaler 1024

/* define here the delay time you want in seconds */
#define seconds 120

/* this is the time it takes for Timer0 to increment @ 8MHz with 1024 prescale 
** (1/(F_CPU/prescaler)) = 0.000128 
** Timer0 is an 8bit timer so 256 increments are needed for an overflow. 
** (256/(F_CPU/prescaler)) = 0.032768 */
#define timer_overfl 0.032768

/* setpoint is calculated as the time in seconds 
** divided by the time it takes for Timer0 to overflow
** note: counter is a 32bit variable so the maximum delay
** in seconds is  4294967295/0.032768 = 131071999969.4 seconds
** thats about 4156 years :) */
//#define setpoint  (seconds/timer_overfl)
volatile uint32_t setpoint = (seconds/timer_overfl);

#endif //_MAIN_H
