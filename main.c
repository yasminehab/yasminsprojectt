/*
 * main.c
 *
 *  Created on: Oct 27, 2021
 *      Author: Basse
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_Interface.h"
#include"EXTI_Interface.h"
#include"GIE_Interface.h"
#include"TIMER_Interface.h"
#include"ADC_Interface.h"
#include "Program.h"
#include "INTERNAL_EEPROM_Interface.h"

u8 ADC_FLAG;
u8 up_down_counter;
u8 On_Off_Flag=0;
u8 up_counter=0;
u8 down_counter=0;
u8 set_temp=60;
u16 timer_counter=0;
u8 sev_segm_flag=0;
u8 avg_temp;
u8 timer_counter_Temp=0;
u8 timer_counter_7=0;
int main(void)
{
	/* Heating_cooling pins */
	DIO_u8SetPinDirection(DIO_PIN5,DIO_PORTC,PIN_HIGH);
	DIO_u8SetPinDirection(DIO_PIN6,DIO_PORTC,PIN_HIGH);
	DIO_u8SetPinDirection(DIO_PIN7,DIO_PORTC,PIN_HIGH);


	SevenSegment_voidInitPins();

	EXTI_voidINT0_Init();
	EXTI_voidINT1_Init();
	EXTI_voidINT2_Init();
	ADC_voidInit_Interrupt();

	TIMER0_voidSetCTCValue(250);
	u8 Temp_Temp=0;
	Temp_Temp=INTERNAL_EEPROM_voidReadByte(0x15);
	if(Temp_Temp!=0xFF)
	{
		set_temp=Temp_Temp;
	}


	TIMER0_voidInit();
	GIE_voidEnable();



	while(1)
	{
		if(On_Off_Flag==0)
		{
			// off all
			DIO_u8SetPinValue(DIO_PIN6,DIO_PORTC,PIN_LOW);
			DIO_u8SetPinValue(DIO_PIN5,DIO_PORTC,PIN_LOW);

			SevenSegment_voidDisable();
			DIO_u8SetPinValue(DIO_PIN7,DIO_PORTC,PIN_LOW);

		}

		else     //modes
		{

			if(up_down_counter>0)    // setting mode
			{
				DIO_u8SetPinValue(DIO_PIN6,DIO_PORTC,PIN_LOW);
				DIO_u8SetPinValue(DIO_PIN5,DIO_PORTC,PIN_LOW);
				DIO_u8SetPinValue(DIO_PIN7,DIO_PORTC,PIN_LOW);

				//print set temp on seven segment
				//blinking with sev_segm_flag
				if(sev_segm_flag==0)
				{
					SevenSegment_voidSendNumber(set_temp);
				}

				if(up_down_counter>1)
				{
					if(up_counter>0 && set_temp<=70)
					{
						set_temp = set_temp+5;
						up_counter=0;
					}

					if(down_counter>0 && set_temp>=40)
					{
						set_temp = set_temp-5;
						down_counter=0;
					}
					INTERNAL_EEPROM_voidWriteByte(0x15,set_temp);

				}


			}



			else      // sensing mode
			{

				// display avg_temp 3la al seven segment

				SevenSegment_voidSendNumber(avg_temp);

				if (avg_temp >= (set_temp+5))
				{
					DIO_u8SetPinValue(DIO_PIN5,DIO_PORTC,PIN_HIGH);
					DIO_u8SetPinValue(DIO_PIN7,DIO_PORTC,PIN_HIGH);
					//cooling element on
					DIO_u8SetPinValue(DIO_PIN6,DIO_PORTC,PIN_LOW);
				}

				if (avg_temp <= (set_temp-5))
				{
					DIO_u8SetPinValue(DIO_PIN6,DIO_PORTC,PIN_HIGH);
					if (sev_segm_flag==0)
					{
						DIO_u8SetPinValue(DIO_PIN7,DIO_PORTC,PIN_HIGH);
					}
					else
					{
						DIO_u8SetPinValue(DIO_PIN7,DIO_PORTC,PIN_LOW);

					}
					//heating element on
					DIO_u8SetPinValue(DIO_PIN5,DIO_PORTC,PIN_LOW);
				}


			}






		}



	}

	return 0;


}











void __vector_1(void) __attribute__((signal));    //ON & OFF  INTERUPT0    BUTTON 2

void __vector_1(void)
{
	if(On_Off_Flag==0)
	{On_Off_Flag=1;}
	else if(On_Off_Flag==1)
	{On_Off_Flag=0;}
}

void __vector_2(void) __attribute__((signal));    //up  INTERUPT1

void __vector_2(void)
{
	up_down_counter++;
	up_counter++;

	timer_counter=0;
}

void __vector_3(void) __attribute__((signal));    //down  INTERUPT0

void __vector_3(void)
{
	up_down_counter++;
	down_counter++;

	timer_counter=0;
}


void __vector_10(void) __attribute__((signal));    // timer 0  compare match

void __vector_10(void)
{

	timer_counter++;
	timer_counter_7++;
	timer_counter_Temp++;
	if(timer_counter_Temp==25)  // 100 milisec timer
	{
		ADC_u16StartConversion_Interrupt(1);
		timer_counter_Temp=0;
	}

	if(timer_counter_7%250==0)  // 1 sec timer
	{
		if(sev_segm_flag==0)
		{sev_segm_flag=1;}
		else if(sev_segm_flag==1)
		{sev_segm_flag=0;}
		timer_counter_7=0;
	}

	if(timer_counter==1250)    // 5 sec timer
	{
		up_counter=0;
		down_counter=0;
		up_down_counter=0;
		timer_counter=0;
	}

}

void __vector_16(void) __attribute__((signal));
void __vector_16 (void)
{
	avg_temp =  (u8)Avarege_temp();
}


