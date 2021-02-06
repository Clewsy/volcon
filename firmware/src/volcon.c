#include "volcon.h"




ISR(OPTO_A_VECT)
{
	handle_opto();
}

ISR(OPTO_B_VECT)
{
	handle_opto();
}

//volatile uint8_t volUp = 0;		//volUp is a global variable - only set to 1 from within pin-change interrupt 0 subroutine (PCINT0_vect) and used in the USB mediareport.
//volatile uint8_t volDown = 0;	//

void handle_opto(void)
{	 
	static uint8_t old_AB = 3;		//lookup table index
	static int8_t encval = 0;		//encoder value  
	static const int8_t enc_states [] PROGMEM = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};  //encoder lookup table

int8_t delta = 0;

	old_AB <<=2;  //remember previous state
//	old_AB |= ( (PINB >> 6) & 0x03 );
	old_AB |= (OPTO_PINS & OPTO_PIN_MASK);
	encval -= pgm_read_byte(&(enc_states[( old_AB & 0x0f )]));

	/* post "Navigation forward/reverse" event */
	if( encval > 1 ) //two steps forward
	{
		delta = -1;
		encval = 0;
	}
	else if( encval < -1 )//two steps backwards
	{
		delta = 1;
		encval = 0;
	}

//	HID_Device_USBTask(&MediaControl_HID_Interface);
//	USB_USBTask();
HID_Task(delta);	// In Keyboard.c

//	volUp = 0;
//	volDown = 0;
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

	SetupHIDHardware();	// Defined in Keyboard.c
}

// Main program entry point.
 int main(void)
{
	hardware_init();
	GlobalInterruptEnable();

	while(true)
	{
		HID_Task(0);	// In Keyboard.c
		USB_USBTask();	// In the lufa library.
	}
}
