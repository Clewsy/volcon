// This version of Keyboard.c has been modified from the original demo in Dean Camera's LUFA repository.
// Effectively I have used combinations of my own functions in addition to functions from the following .c files:
// - Keyboard.c at https://github.com/abcminiuser/lufa/tree/790ac4d125c1c5d72016b52c2b9ad58f5e5f8c62/Demos/Device/LowLevel/Keyboard
// - KeyboardMouse.c at https://github.com/abcminiuser/lufa/tree/790ac4d125c1c5d72016b52c2b9ad58f5e5f8c62/Demos/Device/LowLevel/KeyboardMouse
// - MediaController.c at https://github.com/abcminiuser/lufa/tree/790ac4d125c1c5d72016b52c2b9ad58f5e5f8c62/Projects/MediaController
//
// Significant changes and additions noted in comments prepended with "clewsy".

/*
             LUFA Library
     Copyright (C) Dean Camera, 2020.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2020  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Denver Gingerich (denver [at] ossguy [dot] com)

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

#include "volume_control.h"

// Indicates what report mode the host has requested, true for normal HID reporting mode, false for special boot
// protocol reporting mode.
static bool UsingReportProtocol = true;

// Current Idle period. This is set by the host via a Set Idle HID class request to silence the device's reports for 
// either the entire idle duration, or until the report status changes (e.g. the user presses a key).
static uint16_t IdleCount = 500;

// Current Idle period remaining. When the IdleCount value is set, tracks the remaining number of idle milliseconds.
// This is separate to the IdleCount timer and is incremented and compared as the host may request the current idle
// period via a Get Idle HID class request, thus its value must be preserved.
static uint16_t IdleMSRemaining = 0;

// clewsy: Declaration of a keyscan_report_t structure that will be used to pass current keypresses to the keyboard
// reports and the media controller reports. 
//static keyscan_report_t keyscan_report;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// clewsy: main function taken out of Keyboard.c and is instead in macr0.c
//int main(void)
//{
//	SetupHardware();
//
//	GlobalInterruptEnable();
//
//	for (;;)
//	{
//		HID_Task();
//		USB_USBTask();
//	}
//}

// Configures the board hardware and chip peripherals.
// clewsy: Use case is specifically an ATmega32U4 (ARCH_AVR8) so requirements for other architectures can be removed.
void SetupHIDHardware(void)
{
	// Disable watchdog if enabled by bootloader/fuses.
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	// Disable clock division.
	clock_prescale_set(clock_div_1);

	// Hardware Initialization
	USB_Init();
}

// Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and starts
// the library USB task to begin the enumeration and USB management process.
void EVENT_USB_Device_Connect(void)
{
	// Indicate USB enumerating.
//	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
	// Default to report protocol on connect.
	UsingReportProtocol = true;
}

// Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void)
{
	// Indicate USB not ready.
//	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

// Event handler for the USB_ConfigurationChanged event. This is fired when the host sets the current configuration of
// the USB device after enumeration, and configures the keyboard device endpoints.
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	// Setup HID Report Endpoints.
//	ConfigSuccess &= Endpoint_ConfigureEndpoint(KEYBOARD_IN_EPADDR, EP_TYPE_INTERRUPT, HID_EPSIZE, 1);
//	ConfigSuccess &= Endpoint_ConfigureEndpoint(KEYBOARD_OUT_EPADDR, EP_TYPE_INTERRUPT, HID_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(MEDIACONTROL_HID_EPADDR, EP_TYPE_INTERRUPT, MEDIACONTROL_HID_EPSIZE, 1);

	// Turn on Start-of-Frame events for tracking HID report period expiry.
	USB_Device_EnableSOFEvents();

	// Indicate endpoint configuration success or failure.
//	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

// Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to the device
// from the USB host before passing along unhandled control requests to the library for processing internally.
void EVENT_USB_Device_ControlRequest(void)
{
	// Handle HID Class specific requests.
	switch (USB_ControlRequest.bRequest)
	{
		case HID_REQ_GetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				// Create the next media controller report for transmission to the host.
				USB_MediaReport_Data_t MediaControllerReportData;
				create_volume_report(&MediaControllerReportData, 0);
				// Write the report data to the control endpoint.
				Endpoint_Write_Control_Stream_LE(&MediaControllerReportData, sizeof(MediaControllerReportData));

				Endpoint_ClearOUT();
				
				Endpoint_ClearSETUP();
			}
			break;

		case HID_REQ_SetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				// Wait until the LED report has been sent by the host.
				while (!(Endpoint_IsOUTReceived()))
				{
					if (USB_DeviceState == DEVICE_STATE_Unattached)
					  return;
				}

				Endpoint_ClearOUT();
				Endpoint_ClearStatusStage();
			}
			break;

		case HID_REQ_GetProtocol:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				// Write the current protocol flag to the host.
				Endpoint_Write_8(UsingReportProtocol);

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}
			break;

		case HID_REQ_SetProtocol:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_ClearStatusStage();

				// Set or clear the flag depending on what the host indicates is the current Protocol.
				UsingReportProtocol = (USB_ControlRequest.wValue != 0);
			}
			break;

		case HID_REQ_SetIdle:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_ClearStatusStage();

				// Get idle period in MSB, IdleCount must be multiplied by 4 to get milliseconds.
				IdleCount = ((USB_ControlRequest.wValue & 0xFF00) >> 6);
			}
			break;

		case HID_REQ_GetIdle:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				// Write the current idle duration to the host.  Must be divided by 4 before send.
				Endpoint_Write_8(IdleCount >> 2);

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}
			break;
	}
}

// Event handler for the USB device Start Of Frame event.
void EVENT_USB_Device_StartOfFrame(void)
{
	// One millisecond has elapsed, decrement the idle time remaining counter if it has not already elapsed.
	if (IdleMSRemaining) IdleMSRemaining--;
}

// Fills the given HID report data structure with the next media controller HID input report to send to the host.
// MediaReportData:  Pointer to a HID report data structure to be filled.
// clewsy: created this function from scratch, same concept as keyboard version.
void create_volume_report(USB_MediaReport_Data_t* const MediaReportData, int8_t delta)
{
	// Clear the report contents.
	memset(MediaReportData, 0, sizeof(USB_MediaReport_Data_t));

	// Update the Media Control report flags from the latest keyscan report.
	MediaReportData->VolumeUp	= ((delta > 0)	? true : false);
	MediaReportData->VolumeDown	= ((delta < 0)	? true : false);
}

// Sends the next media controller HID report to the host, via the keyboard data endpoint.
// clewsy: This function is very similar to the keyboard equivalent but was created for media controller reports.
void send_volume(int8_t delta)
{
if (USB_DeviceState != DEVICE_STATE_Configured) return;

	static USB_MediaReport_Data_t	PrevMediaControllerReportData;
	USB_MediaReport_Data_t		MediaControllerReportData;
	bool				SendReport = false;

	// Create the next keyboard report for transmission to the host.
	create_volume_report(&MediaControllerReportData, delta);

	// Check if the idle period is set and has elapsed.
	if (IdleCount && (!(IdleMSRemaining)))
	{
		// Reset the idle time remaining counter.
		IdleMSRemaining = IdleCount;

		// Idle period is set and has elapsed, must send a report to the host.
		SendReport = true;
	}
	else
	{
		// Check to see if the report data has changed - if so a report MUST be sent.
		SendReport = (memcmp(&PrevMediaControllerReportData, &MediaControllerReportData, sizeof(USB_MediaReport_Data_t)) != 0);
	}

	// Select the Keyboard Report Endpoint.
	Endpoint_SelectEndpoint(MEDIACONTROL_HID_EPADDR);

	// Check if Keyboard Endpoint Ready for Read/Write and if we should send a new report.
	if (Endpoint_IsReadWriteAllowed() && SendReport)
	{
		// Save the current report data for later comparison to check for changes.
		PrevMediaControllerReportData = MediaControllerReportData;

		// Write Keyboard Report Data */
		Endpoint_Write_Stream_LE(&MediaControllerReportData, sizeof(MediaControllerReportData), NULL);

		// Finalize the stream transfer to send the last packet.
		Endpoint_ClearIN();
	}
}
