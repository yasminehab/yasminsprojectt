/*
 * PROGRAM.C
 *
 *  Created on: Oct 28, 2021
 *      Author: Basse
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_Interface.h"
#include"ADC_Interface.h"
#include "util/delay.h"

u32 Get_Temp(void)
{

	u32 temp=0;
	temp=ADC_u16DigitalRead();
	temp= (temp*500)/1024;
	return temp;
}


u32 Avarege_temp(void)
{
	u16 avg=0;
	u16 sum=0;
	static u16 arr[10];
	static u8 i=0 ,j;
	arr[i]=Get_Temp( );
	i++;
	if (i==10)
	{
		i=0;
	}
	for(j=0;j<10;j++)
	{
		sum=sum+arr[j];
	}
	avg=sum/(10);
	return avg;
}

void SevenSegment_voidInitPins (void)
{
	DIO_u8SetPinDirection(DIO_PIN1,DIO_PORTB,PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN0,DIO_PORTB,PIN_OUTPUT);

	DIO_u8SetPinValue(DIO_PIN1,DIO_PORTB,PIN_HIGH);
	DIO_u8SetPinValue(DIO_PIN0,DIO_PORTB,PIN_HIGH);

	DIO_u8SetNippleBitsDirection(DIO_PORTA,MOST_NIPPLE,0xFF);
}

void SevenSegment_voidSendNumber (u8 Copy_u8Number)
{
	u8 i;
	u8 temp1=0,temp2=0;
	temp1=(Copy_u8Number%10)|((Copy_u8Number%10)<<4);
	temp2=(Copy_u8Number/10)|((Copy_u8Number/10)<<4);

	for (i=0;i<2;i++)
	{
		if (0==i)
		{
			DIO_u8SetNippleBitsValue(DIO_PORTA,MOST_NIPPLE,temp2);
			DIO_u8SetPinValue(DIO_PIN0,DIO_PORTB,PIN_LOW);
			_delay_ms(5);
			DIO_u8SetPinValue(DIO_PIN0,DIO_PORTB,PIN_HIGH);

		}
		else
		{
			DIO_u8SetNippleBitsValue(DIO_PORTA,MOST_NIPPLE,temp1);
			DIO_u8SetPinValue(DIO_PIN1,DIO_PORTB,PIN_LOW);
			_delay_ms(5);
			DIO_u8SetPinValue(DIO_PIN1,DIO_PORTB,PIN_HIGH);

		}
	}


}
void SevenSegment_voidDisable (void)
{
	DIO_u8SetNippleBitsValue(DIO_PORTA,MOST_NIPPLE,0x00);
	DIO_u8SetPinValue(DIO_PIN1,DIO_PORTB,PIN_HIGH);
	DIO_u8SetPinValue(DIO_PIN0,DIO_PORTB,PIN_HIGH);

}





