//Media Controller source code.  Modified from mediacontroller LUFA example file.
//Modifications incorporate an optical rotary encoder providing 2-bit gray code and read to control volume.


/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the MediaControl project. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "MediaController.h"

/** Buffer to hold the previously generated Media Control HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevMediaControlHIDReportBuffer[sizeof(USB_MediaReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t MediaControl_HID_Interface =
 	{
		.Config =
			{
				.InterfaceNumber              = INTERFACE_ID_HID,
				.ReportINEndpoint             =
					{
						.Address              = MEDIACONTROL_HID_EPADDR,
						.Size                 = MEDIACONTROL_HID_EPSIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevMediaControlHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevMediaControlHIDReportBuffer),
			},
    };

	
	
//Global Variables
 volatile uint8_t volUp = 0;		//volUp is a global variable - only set to 1 from within pin-change interrupt 0 subroutine (PCINT0_vect) and used in the USB mediareport.
 volatile uint8_t volDown = 0;	//volDown is a global variable - only set to 1 from within pin-change interrupt 0 subroutine (PCINT0_vect) and used in the USB mediareport.

 
 ISR(PCINT0_vect)
 {	 
	static uint8_t old_AB = 3;		//lookup table index
	static int8_t encval = 0;			//encoder value  
	static const int8_t enc_states [] PROGMEM = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};  //encoder lookup table

	old_AB <<=2;  //remember previous state
	old_AB |= ( (PINB >> 6) & 0x03 );
	encval -= pgm_read_byte(&(enc_states[( old_AB & 0x0f )]));

	/* post "Navigation forward/reverse" event */
	if( encval > 1 ) //two steps forward
	{
		volUp = 1;
		encval = 0;
		printString("up\n\r");
	}
	else if( encval < -1 )//two steps backwards
	{
		volDown = 1;
		encval = 0;
		printString("dn\n\r");
	}

	HID_Device_USBTask(&MediaControl_HID_Interface);
	USB_USBTask();
	volUp = 0;
	volDown = 0;
 }
 
 /** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	GlobalInterruptEnable();
	
	//Test string for USART initialisation
	printString("\r\nMedia Controller\r\n");	
	
	//Main loop - continuously polls USB functions (thanks LUFA!)
	while(1)
	{
		HID_Device_USBTask(&MediaControl_HID_Interface);
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware()
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	USB_Init();
	
	//Initialise USART for serial comms
	initUSART();
	
	//Initialise interrupts - pin-change interrupt 0 to detect rotary encoder gray-code changes for volume control.
	PCICR |=  (1 << PCIE0);	//PCICR:Pin Change Interrupt Control Register, PCIE0: Pin Change Interrupt 0 Enable
	PCMSK0 |= (1 << PCINT7 | 1 << PCINT6);	//PCMSK0:Pin Change 0 Mask, PCINT7:6: Pin Change Interrupts 7 & 6
	
	//IO setup.
	DDRD = 0;		//Inputs
	PORTD = 0xFF;	//Pull-ups enabled
	DDRB = 0;		//Inputs
	PORTB = 0xFF;	//Pull-ups enabled
	
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;
	ConfigSuccess &= HID_Device_ConfigureEndpoints(&MediaControl_HID_Interface);
	USB_Device_EnableSOFEvents();
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&MediaControl_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&MediaControl_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	USB_MediaReport_Data_t* MediaReport = (USB_MediaReport_Data_t*)ReportData;

	/* Update the Media Control report with the user button presses */
	MediaReport->Play					= (false);
	MediaReport->Pause				= (false);
	MediaReport->FForward			= (false);
	MediaReport->Rewind			= (false);
	MediaReport->NextTrack		= (false);
	MediaReport->PreviousTrack	= (false);
	MediaReport->Stop				= (false);
	MediaReport->PlayPause		= (false);
	MediaReport->Mute				= ((bit_is_clear(PIND, PD0 )) ? true : false);
	MediaReport->VolumeUp		= volUp;		//volUp is a global variable - only set to 1 from within pin-change interrupt 0 subroutine (PCINT0_vect).
	MediaReport->VolumeDown	= volDown;	//volDown is a global variable - only set to 1 from within pin-change interrupt 0 subroutine (PCINT0_vect).
	
	*ReportSize = sizeof(USB_MediaReport_Data_t);
	return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	// Unused (but mandatory for the HID class driver) in this demo, since there are no Host->Device reports
}

