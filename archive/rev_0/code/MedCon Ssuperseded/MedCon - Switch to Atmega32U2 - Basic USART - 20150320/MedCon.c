//GPS clock main programme function.

# include <MedCon_Support.h>

int main(void)
{
	initClock();							//Initialise the system clock.
	initUSART();							//Initialises the USART for receive/transmit data, 8-bit with 1 stop bit.
	printString("\r\n\nGame Over.\r\n");	//Initialisation test for USART.
	
	
	sei();									//Global enable interrupts (from avr/interrupt.h)



	DDRD |= (1 << PD0);	//Set PD0 to output.

	while (1)
	{	
		PORTD ^= (1 << PD0);	//XOR bit PD0 (i.e. toggle).
		_delay_ms(1000);

	}
	return(0);
	
}

;