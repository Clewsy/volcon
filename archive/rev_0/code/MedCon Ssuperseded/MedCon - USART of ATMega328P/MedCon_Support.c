//GPS clock support functions.

#include <MedCon_Support.h>

//Interrupt subroutine triggered whenever the AVR receives a byte on the serial line (USART).  This was used for debugging.
ISR(USART_RX_vect)	//Interrupt subroutine triggered when the USART receives a byte.
{					
	transmitByte(receiveByte());	//Echos received byte.
	printString(" Ouch!\r\n");	//Echos received byte.
}

//The following function initialises the system clock
void initClock(void)
{
	//CLKPR: Clock Prescale Register.  Pre-scale the system clock.  The following setup will disable prescaling so the system clock will be the full 8MHz internal frequency (default is 1MHz).
	CLKPR = (1 << CLKPCE);		//CLKPCE: Clock Prescaler Change Enable.  Must set to one to enable changes to clock prescaler bits.
	CLKPR = 0;					//Once CLKPCE is enabled, Clock Prescaler Select Bits can be changed if done within 4 cycles.  In this case, clear all for prescaler value 1 (i.e. 8MHz system).
}
