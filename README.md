# volcon

A USB volume controller that uses a VCR head drum for the knob.

This project began as an experiment when I inexplicably decided to learn how an optical rotary encoder worked (FYI, 2-bit Gray code).

It transformed into a learning experience around USB - specifically the HID protocol. Ultimately I ended up with a simple gadget that now sits on my desk and allows me to control the PC volume.

A salvaged optical encoder was used to detect rotation along with a reclaimed head drum from a VCR which was repurposed as a control knob. I very much like the smooth bearings combined with the heavy mass that let the drum spin forever.

Key concepts for the project were:

    The optical encoder parts (sensors and disk) were salvaged from an old track-ball.
    The "knob" was made from the head drum of a VHS VCR (remember those?). This is the part that spins and is used to adjust volume on my PC.
    The optical disk was fixed to the shaft and optical sensors mounted off some strip-board and attached to the base of the drum.
    This assembly is mounted to a custom PCB with some nylon stand-offs. The PCB became the base of the whole unit.
    I cut some wooden rings to enclose the electronics and the base of the VCR drum.
    The custom PCB was designed in eagle and etched at home from some single-sided copper-clad board. The circuit was designed around an AVR at90usb162.
    The code is written in C and implements the LUFA library developed by Dean Camera.
    The whole unit plugs into a PC via USB and is automatically identified as a HID - no drivers required (tested in Debian Linux and Windows).
    It's a very simple device - rotate clockwise to increase volume, counter-clockwise to decrease.
    Code and PCB design are available via gitlab). Here are some reference links:
        VolCon gitlab repo - for code and eagle design (PCB)
        LUFA (lightweight USB Framework for AVRs) main page

After some time (about six years!) of having this device in-use on my desk, I finally got sick of the simple (gross) stained pine wood enclosure. With some scrap spotted gum and a router (with a Roman ogee and a roundover bit) I made a slightly nicer enclosure for volcon.
Rev 2 - Demo of gray code LED visualisation.
Revision 2

After even more time, I decided to do an overhaul. Revision 2 would use the same head drum, optical encoder sensors and wooden enclosure. The upgrades from revision 1 include:

    Schematic and PCB layout completely redone but using KiCad instead of Eagle.
    Microcontroller changed from an AT90usb162 AVR to an ATmega32U4.
    Remove the serial Tx/Rx connector.
    Remove the reset tact-switch.
    Use smd components instead of through-hole.
    Connect with a USB type C connector instead of a USB type B.
    Have the PCB fabricated (JLCPCB) instead of the home-made copper-etch method.
    A couple of LEDs on the bottom of the PCB purely to visualise the gray code (Rev 1 had LEDs but they only barely shone through etched sections of the PCB).
    Generally improved and cleaner code (still using the LUFA library).
