#include "volcon.h"

ISR(OPTO_A_VECT) {handle_opto();}

ISR(OPTO_B_VECT) {handle_opto();}

void handle_opto(void)
{	
	// The first 4 bits of variable a_b are used.
	// bits 3:2 become the previous state of the encoder.  
	// bits 1:0 become the current state of the encoder.  
	// The bit pars are compared to determine the direction the encoder has rotated.
	// Static to retain every time this function is called.
	static uint8_t a_b = 0b11;

	// Encoder lookup table.  Use this table to register every pulse.
	//static const int8_t enc_table [] PROGMEM = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
	// Encoder lookup table.  Use this table to register every second pulse.
	static const int8_t enc_table [] PROGMEM = {0,0,0,0,1,0,0,-1,-1,0,0,1,0,0,0,0};
	// Look-up table for registering every pulse:
	// enc_table table element
	// |   Previous State
	// |   |    Current State
	// |   |    |      Delta (-1 for couter-clock-wise, 1 for clock-wise)
	// |   |    |      |
	// |   BA : BA     |
	// 00  00 : 00 ->  0
	// 01  00 : 01 -> -1
	// 02  00 : 10 ->  1
	// 03  00 : 11 ->  0 (impossible)
	// 04  01 : 00 ->  1
	// 05  01 : 01 ->  0
	// 06  01 : 10 ->  0 (impossible)
	// 07  01 : 11 -> -1
	// 08  10 : 00 -> -1
	// 09  10 : 01 ->  0 (impossible)
	// 10  10 : 10 ->  0
	// 11  10 : 11 ->  1
	// 12  11 : 00 ->  0 (impossible)
	// 13  11 : 01 ->  1
	// 14  11 : 10 -> -1
	// 15  11 : 11 ->  0

	// "Remember" previous state of the channels.
	a_b <<= 2;

	// Read in the current state of the channels.
	a_b |= (OPTO_PINS & OPTO_PIN_MASK);

	// Look-up the desired voluje delta (-1, 0 ot 1) and send to the send_volume(delta) function.
	send_volume(pgm_read_byte(&(enc_table[( a_b & 0x0f )])));	// In Keyboard.c
}


// Initialise the hardware peripherals.
void hardware_init(void)
{
	// Set pins connected to opto sensor outputs as inputs, enable pull-ups.
	OPTO_DDR &= ~((1 << OPTO_A_PIN) | (1 << OPTO_B_PIN));
	OPTO_PORT |= ((1 << OPTO_A_PIN) | (1 << OPTO_B_PIN));

	// Set external pins to trigger interrupt on either rising or falling edge.
	OPTO_EICRA |= ((1 << OPTO_ISCA0) | (1 << OPTO_ISCB0));

	// Enable external interrupts on the pins connected to opto channels A & B.
	OPTO_EIMSK |= ((1 << OPTO_INTA) | (1 << OPTO_INTB));

	// Globally enable all interrupts.
	sei();

	// Defined in volume_control.c
	SetupHIDHardware();
}

// Main entry point.
 int main(void)
{
	hardware_init();
	GlobalInterruptEnable();

	while(true)
	{
		send_volume(0);
		USB_USBTask();
	}
}
