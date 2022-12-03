
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "DIO_int.h"
#include <avr/io.h>
#include <util/delay.h>

/* IO s */
void DIO_SetPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORTD) && (u8PinIdCopy <= PIN7))
	{
		if (u8PinValCopy == HIGH)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORTA: SET_BIT(PORTA,u8PinIdCopy); break;
				case PORTB: SET_BIT(PORTB,u8PinIdCopy); break;
				case PORTC: SET_BIT(PORTC,u8PinIdCopy); break;
				case PORTD: SET_BIT(PORTD,u8PinIdCopy); break;
			}
		
		}
		
		else if (u8PinValCopy == LOW)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORTA: CLR_BIT(PORTA,u8PinIdCopy); break;
				case PORTB: CLR_BIT(PORTB,u8PinIdCopy); break;
				case PORTC: CLR_BIT(PORTC,u8PinIdCopy); break;
				case PORTD: CLR_BIT(PORTD,u8PinIdCopy); break;
			}
		}
	
		else
		{
			/* Do nothing, Wrong value to set */
		}
	}
	
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}

u8 DIO_GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy)
{
	/* Define Local Variable to get the BIT Value */
	u8 u8ResultLocal;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORTD) && (u8PinIdCopy <= PIN7))
	{
		/* Check on the Required PORT Number */
		switch (u8PortIdCopy)
		{
			case PORTA: u8ResultLocal= GET_BIT(PINA,u8PinIdCopy); break;
			case PORTB: u8ResultLocal= GET_BIT(PINB,u8PinIdCopy); break;
			case PORTC: u8ResultLocal= GET_BIT(PINC,u8PinIdCopy); break;
			case PORTD: u8ResultLocal= GET_BIT(PIND,u8PinIdCopy); break;
		}
	}
	
	else
	{
		/* return 0xff in case of error in the Pin ID or PORT ID */
		u8ResultLocal = 0xFF;
	}
	
	return u8ResultLocal;
}

void DIO_SetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORTD) && (u8PinIdCopy <= PIN7))
	{
		if ( u8PinDirCopy == OUTPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORTA: SET_BIT(DDRA,u8PinIdCopy); break;
				case PORTB: SET_BIT(DDRB,u8PinIdCopy); break;
				case PORTC: SET_BIT(DDRC,u8PinIdCopy); break;
				case PORTD: SET_BIT(DDRD,u8PinIdCopy); break;
			}
		}
		
		else if ( u8PinDirCopy == INPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORTA: CLR_BIT(DDRA,u8PinIdCopy); break;
				case PORTB: CLR_BIT(DDRB,u8PinIdCopy); break;
				case PORTC: CLR_BIT(DDRC,u8PinIdCopy); break;
				case PORTD: CLR_BIT(DDRD,u8PinIdCopy); break;
			}
		}
		
		else
		{
			/* Do nothing, Wrong Direction Required */
		}
	}
	
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}


/* IO Ports */
void DIO_SetPortDirection (u8 u8PortId, u8 u8PortDir)
{
	/* Check on the Required PORT Number */
	switch (u8PortId)
	{
		case     PORTA: DDRA = u8PortDir; break;
		case     PORTB: DDRB = u8PortDir; break;
		case     PORTC: DDRC = u8PortDir; break;
		case     PORTD: DDRD = u8PortDir; break;
		default: /* Wrong Port ID */       break;
	}
}

void DIO_SetPortValue (u8 u8PortId, u8 u8PortVal)
{
	/* Check on the Required PORT Number */
	switch (u8PortId)
	{
		case     PORTA: PORTA = u8PortVal; break;
		case     PORTB: PORTB = u8PortVal; break;
		case     PORTC: PORTC = u8PortVal; break;
		case     PORTD: PORTD = u8PortVal; break;
		default: /* Wrong Port ID */        break;
	}
}
