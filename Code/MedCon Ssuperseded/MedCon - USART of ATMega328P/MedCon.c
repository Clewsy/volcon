//GPS clock main programme function.

#include <MedCon_Support.h>

int main(void)
{
	initClock();							//Initialise the system clock.
	initUSART();							//Initialises the USART for receive/transmit data, 8-bit with 1 stop bit.
	printString("\r\n\n\nHello World\r\n");	//Initialisation test for USART.
	printString("\r\n\n\nThe quick brown fox jumped over the lazy dog.\r\n");	//Initialisation test for USART.
	
	sei();									//Global enable interrupts (from avr/interrupt.h)

	while (1)
	{	

	}
	return(0);
	
}

;