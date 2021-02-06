#include <avr/io.h>

#include "volume_control.h"	// Pulls in all the lufa library defines.


// GPIO configuration definitions.
#define OPTO_PORT	PORTD	// Hardware Port definition for setting pull-ups.
#define OPTO_PINS	PIND	// Hardware Pins definition for opto sensor inputs.
#define OPTO_DDR	DDRD	// Hardware data direction register.
#define OPTO_A_PIN	PD0	// GPIO pin connected to opto sensor channel A.
#define OPTO_B_PIN	PD1	// GPIO pin connected to opto sensor channel B.
#define OPTO_PIN_MASK	0x03	// And (&) with OPTP_PINS to read only the channel A and B pins.

// Interrupt configuration definitions.
#define OPTO_EICRA	EICRA   	// External Interrupt control register A.
#define OPTO_ISCA0	ISC00   	// external Interrupt Sense Control bit 0 (channel A).
#define OPTO_ISCA1	ISC01   	// external Interrupt Sense Control bit 1 (channel A).
#define OPTO_ISCB0	ISC10   	// external Interrupt Sense Control bit 0 (channel B).
#define OPTO_ISCB1	ISC11   	// external Interrupt Sense Control bit 1 (channel B).
#define OPTO_EIMSK	EIMSK   	// External Interrupt Mask.
#define OPTO_INTA	INT0    	// Interrupt enable bit for opto channel A.
#define OPTO_INTB	INT1    	// Interrupt enable bit for opto channel B.
#define OPTO_A_VECT	INT0_vect       // Interrupt subroutine vector fot channel A.
#define OPTO_B_VECT	INT1_vect       // Interrupt subroutine vector fot channel B.

void handle_opto(void);