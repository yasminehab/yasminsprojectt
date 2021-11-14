/*
 * Timer_Private.h
 *
 *  Created on: Sep 19, 2021
 *      Author: msqotb
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/* Registers */
#define TIMSK	*((volatile u8*)0x59)
#define TCCR0	*((volatile u8*)0x53)
#define TCNT0	*((volatile u8*)0x52)

/* Timer0 Mode options */
#define TIMER0_NORMAL_MODE				0
#define TIMER0_PWM_PHASECORRECT_MODE	1
#define TIMER0_CTC_MODE					2
#define TIMER0_PWM_FAST_MODE			3

/* prescaler select */
#define TIMER0_BITMASK_PRESCALER	0xF8

#define TIMER0_NO_PRESCALER				1
#define TIMER0_8_PRESCALER				2
#define TIMER0_64_PRESCALER				3
#define TIMER0_256_PRESCALER			4
#define TIMER0_1024_PRESCALER			5

#define TIMER0_EXTERNAL_SOURCE_FALLING	6
#define TIMER0_EXTERNAL_SOURCE_RISING	7


/*OC0 CONFIG*/
#define	OC0_PIN_DISCONNECTED	0
#define OC0_PIN_TOGGLE			1
#define	OC0_PIN_CLEAR			2
#define OC0_PIN_SET				3

#define OCR0	*((volatile u8*)0x5C)



#endif /* TIMER_PRIVATE_H_ */
