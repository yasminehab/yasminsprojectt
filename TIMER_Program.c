/*
 * Timer_Program.c
 *
 *  Created on: Sep 19, 2021
 *      Author: msqotb
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_Private.h"
#include "TIMER_Config.h"

void TIMER0_voidInit(void)
{
#if 	TIMER0_MODE==TIMER0_NORMAL_MODE
	/* Set Normal Mode*/
	CLR_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
	/* OVERFLOW INTERRUPT ENABLE */
	SET_BIT(TIMSK,0);
#elif	TIMER0_MODE==TIMER0_CTC_MODE
		/* Set CTC Mode*/
		CLR_BIT(TCCR0,6);
		SET_BIT(TCCR0,3);
		/* CTC INTERRUPT ENABLE */
		SET_BIT(TIMSK,1);

#elif	TIMER0_MODE==TIMER0_PWM_PHASECORRECT_MODE
	/* Set PHASECORRECT Mode*/
	SET_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);


#elif	TIMER0_MODE==TIMER0_PWM_FAST_MODE
	/* Set FAST PWM Mode*/
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);

#else
#error"You have error in set TIMER0 MODE"
#endif

	/*Set Prescaler*/

	TCCR0&=TIMER0_BITMASK_PRESCALER;
	TCCR0|=TIMER0_PRESCALER;

	/* OC0 MODES */
#if	OC0_PIN_MODE==OC0_PIN_DISCONNECTED
	CLR_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);
#elif	OC0_PIN_MODE==OC0_PIN_TOGGLE
	SET_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);
#elif	OC0_PIN_MODE==OC0_PIN_CLEAR
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#elif	OC0_PIN_MODE==OC0_PIN_SET
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#else
#error"You have error in set TIMER0 MODE"
#endif

}

void TIMER0_voidSetPreloadValue(u8 Copy_u8Preload)
{
	TCNT0=Copy_u8Preload;
}
void TIMER0_voidSetCTCValue(u8 Copy_u8CTC_Value)
{
	OCR0=Copy_u8CTC_Value;
}
