
//Definitions and declarations for the GPS clock support functions.

#include <avr/io.h>			//From standard AVR libraries - used for calling standard registers etc.
#include <util/delay.h>		//From the standard AVR libraries - used to call delay_ms() and delay_us() functions.
#include <avr/eeprom.h>		//EEPROM used to store timezone/UTC-offset to survive power cycle.
#include <avr/interrupt.h>	//Used to utilise interrups, defines sei/90; to enable global interrupts

#define BAUD  4800			//This is the speed for the USART serial comms.  Set to 4800 for compatibility with GPS default speed.
#include <USART.h>			//Used for serial communications via USART 0

//The following function initialises the system clock
void initClock(void);