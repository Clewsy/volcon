//Functions used for serial communications via USART

#include <USART.h>

//Initialise the USART peripheral
void initUSART(void)
{
	//Utilising USART0
	UBRR1H = UBRRH_VALUE;	//USART Baud Rate Register 1 High -Value defined in util/setbaud.h
	UBRR1L = UBRRL_VALUE;	//USART Baud Rate Register 1 Low  -Value defined in util/setbaud.h

	#if USE_2X						//Double-Speed detemined in util/setbaud.h.  Needed is defined BAUD not achieavable without U2X1 
		UCSR1A |= (1 << U2X1);		//UCSR1A = USART 1 Control and Status Register A
	#else							//U2X1 = Double USART 1 Transmission Speed Enable
		UCSR1A &= ~(1 << U2X1);
	#endif
	
	UCSR1B = (1 << RXCIE1) | (1 << TXEN1) | (1 << RXEN1);		//UCSR1B = USART 1 Control and Status Register B
																//RXCIE1 = USART 1 RX Complete Interrupt Enable
																//TXEN1 = Transmit Enable USART1
																//RXEN1 = Receive Enable USART1
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);					//UCSR1C = USART 1 Control and Status Register C
																//UCSZ12:0 = Usart Character Size, Set to 0b011 for 8-bit.
																//(USBS = Usart Stop Bit Select, Stays at 0b0 for 1 stop bit)
}

//Sets a variable to whatever was received by the USART
uint8_t receiveByte(void)
{

	while (!(UCSR1A & (1 << RXC1))) {}		//Wait until the USART 0 receive complete flag is set 
	return UDR1;							//Returns received data.  UDR0 = USART 0 Data Register
}


//Transmits a byte from the USART
void transmitByte(uint8_t data)
{
	while (!(UCSR1A & (1 << UDRE1))) {}	//Wait until the USART 0 data register is empty (ready to transmit). Otherwise operates too fast and drops characters.
	UDR1 = data;							//UDR0 = USART 0 Data Register
}

//Transmits a string of characters.
void printString(const char string[])
{			
	uint8_t i = 0;								//Counter to increment for every character in the string.
	while ((string[i]) != '\0')				//Until null character (end of string).
	{
		transmitByte(string[i]);				//UCSR0A = USART 0 Control and Status Register A
		i++;									//UDRE0 = USART 0 Data Register Empty Flag
	}
}

//Takes an integer and transmits the characters
void printByte(uint8_t byte)
{
	//(modified to only print last 2 digits (tens & ones)).
	//while (!(UCSR1A & (1 << UDRE1))) {}	//Wait until the USART 0 data register is empty (ready to transmit).
	//transmitByte('0'+ (byte/100));		//Hundreds
	while (!(UCSR1A & (1 << UDRE1))) {}	//Wait until the USART 0 data register is empty (ready to transmit).
	transmitByte('0'+ ((byte/10) % 10));	//Tens
	while (!(UCSR1A & (1 << UDRE1))) {}	//Wait until the USART 0 data register is empty (ready to transmit).
	transmitByte('0'+ (byte % 10));		//Ones
}

//Takes an integer and prints the binary equivalent.
void printBinaryByte(uint8_t byte)
{
	uint8_t bit;
	for(bit=1; bit<255; bit--)	//For full 8-bits, modify to: "for(bit=7; bit<255; bit--)".
	{
		if(bit_is_set(byte, bit))
		{
			transmitByte('1');
		}
		else
		{
			transmitByte('0');
		}
	}
}