// This file developed by drawing from the following examples:
// - Keyboard.c at https://github.com/abcminiuser/lufa/tree/790ac4d125c1c5d72016b52c2b9ad58f5e5f8c62/Demos/Device/LowLevel/Keyboard
// - KeyboardMouse.c at https://github.com/abcminiuser/lufa/tree/790ac4d125c1c5d72016b52c2b9ad58f5e5f8c62/Demos/Device/LowLevel/KeyboardMouse
// - MediaController.c at https://github.com/abcminiuser/lufa/tree/790ac4d125c1c5d72016b52c2b9ad58f5e5f8c62/Projects/MediaController
//
// clewsy - https://clews.pro

#include "volume_control.h"

// Indicates what report mode the host has requested, true for normal HID reporting mode, false for special boot protocol reporting
// mode.
static bool UsingReportProtocol = true;

// Current Idle period. This is set by the host via a Set Idle HID class request to silence the device's reports for  either the
// entire idle duration, or until the report status changes (e.g. the user presses a key).
static uint16_t IdleCount = 500;

// Current Idle period remaining. When the IdleCount value is set, tracks the remaining number of idle milliseconds.  This is
// separate to the IdleCount timer and is incremented and compared as the host may request the current idle period via a Get Idle
// HID class request, thus its value must be preserved.
static uint16_t IdleMSRemaining = 0;

// Configures the board hardware and chip peripherals.
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

// Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and starts the library
// USB task to begin the enumeration and USB management process.
void EVENT_USB_Device_Connect(void)
{
	// Default to report protocol on connect.
	UsingReportProtocol = true;
}

// Event handler for the USB_ConfigurationChanged event. This is fired when the host sets the current configuration of the USB
// device after enumeration, and configures the volume control device endpoints.
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	// Setup HID Report Endpoint.
	ConfigSuccess &= Endpoint_ConfigureEndpoint(VOLCONTROL_HID_EPADDR, EP_TYPE_INTERRUPT, VOLCONTROL_HID_EPSIZE, 1);

	// Turn on Start-of-Frame events for tracking HID report period expiry.
	USB_Device_EnableSOFEvents();
}

// Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to the device from the
// USB host before passing along unhandled control requests to the library for processing internally.
void EVENT_USB_Device_ControlRequest(void)
{
	// Handle HID Class specific requests.
	switch (USB_ControlRequest.bRequest)
	{
		case HID_REQ_GetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				// Create the next volume controller report for transmission to the host.
				USB_VolReport_Data_t VolControllerReportData;
				create_volume_report(&VolControllerReportData, 0);

				// Write the report data to the control endpoint.
				Endpoint_Write_Control_Stream_LE(&VolControllerReportData, sizeof(VolControllerReportData));

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
					if (USB_DeviceState == DEVICE_STATE_Unattached) return;
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

// Fills the given HID report data structure with the next volume controller HID input report to send to the host.
// VolReportData:  Pointer to a HID report data structure to be filled.
void create_volume_report(USB_VolReport_Data_t* const VolReportData, int8_t delta)
{
	// Clear the report contents.
	memset(VolReportData, 0, sizeof(USB_VolReport_Data_t));

	// Update the Volume Control report flags from the latest keyscan report.
	VolReportData->VolumeUp		= ((delta > 0) ? true : false);
	VolReportData->VolumeDown	= ((delta < 0) ? true : false);
}

// Sends the next volume controller HID report to the host, via the volume data endpoint.
void send_volume(int8_t delta)
{
	// Exit this function if the usb device state is not yet configured.
	if (USB_DeviceState != DEVICE_STATE_Configured) return;

	// Save the last report for comparison, create the new report.
	static USB_VolReport_Data_t	PrevVolControllerReportData;
	USB_VolReport_Data_t		VolControllerReportData;
	bool				SendReport = false;

	// Create the next volume report for transmission to the host.
	create_volume_report(&VolControllerReportData, delta);

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
		SendReport = (memcmp(&PrevVolControllerReportData, &VolControllerReportData, sizeof(USB_VolReport_Data_t)) != 0);
	}

	// Select the Volume Report Endpoint.
	Endpoint_SelectEndpoint(VOLCONTROL_HID_EPADDR);

	// Check if Volume Endpoint Ready for Read/Write and if we should send a new report.
	if (Endpoint_IsReadWriteAllowed() && SendReport)
	{
		// Save the current report data for later comparison to check for changes.
		PrevVolControllerReportData = VolControllerReportData;

		// Write Volume Report Data.
		Endpoint_Write_Stream_LE(&VolControllerReportData, sizeof(VolControllerReportData), NULL);

		// Finalize the stream transfer to send the last packet.
		Endpoint_ClearIN();
	}
}
