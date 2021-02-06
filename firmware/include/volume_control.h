#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "Descriptors.h"

#include <LUFA/Drivers/USB/USB.h>

// Type define for a Volume Control HID report. This report contains the bits to match the usages defined in the HID report of the
// device.  When set to true, the relevant volume control (up or down) on the host will be triggered.
typedef struct
{
	unsigned VolumeUp       : 1;
	unsigned VolumeDown     : 1;
	unsigned RESERVED       : 6;	// Pad the remaining bits.
} ATTR_PACKED USB_VolReport_Data_t;


// Function Prototypes:
void SetupHIDHardware(void);
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
void EVENT_USB_Device_StartOfFrame(void);

void create_volume_report(USB_VolReport_Data_t* const VolReportData, int8_t delta);
void send_volume(int8_t delta);
