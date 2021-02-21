# volcon

A USB volume controller that uses a VCR head drum for the knob.

More photos and information can be found [here][link_clews_volcon].

Proudly mentioned at [hackaday.com][link_web_hackaday_volcon], and also on [episode 106][link_web_hackaday_podcast_106] of the [hackaday podcast][link_web_hackaday_podcast].

## Revision 1

This project began as an experiment when I wanted to learn how an optical [quadrature encoder][link_web_quadrature_encoder] worked (FYI, 2-bit [Gray code][link_web_gray_code]).

It transformed into a learning experience around USB - specifically the [HID protocol][link_web_hid].  Ultimately I ended up with a simple gadget that now sits on my desk and allows me to control the PC volume.

A salvaged optical encoder was used to detect rotation along with a reclaimed [head drum][link_web_head_drum] from a [VCR][link_web_vcr] which was repurposed as a control knob. I very much like the smooth bearings combined with the heavy mass that let the drum spin forever.

Key concepts for the project were:

* The optical encoder parts (sensors and disk) were salvaged from an old track-ball.
* The "knob" was made from the head drum of a VHS VCR (remember those?). This is the part that spins and is used to adjust volume on my PC.
* This assembly is mounted to a custom PCB with some nylon stand-offs. The PCB became the base of the whole unit.
* The optical disk was fixed to the shaft and optical sensors mounted to one of the nylon standoffs.
* I cut some wooden rings to enclose the electronics and the base of the VCR drum.
* The original custom PCB was designed in eagle and etched at home from some single-sided copper-clad board. The circuit was designed around an AVR AT90usb162.
* The code is written in C and implements the LUFA library developed by Dean Camera.
* The whole unit plugs into a PC via USB and is automatically identified as a HID - no drivers required (tested in Debian, Ubuntu and Windows).
* It's a very simple device - rotate clockwise to increase volume, counter-clockwise to decrease.

I used the [LUFA][link_web_lufa] (lightweight USB Framework for AVRs) library to implement the USB HID protocol.

After some time (about six years!) of having this device in-use on my desk, I got sick of the simple (ugly) stained pine wood enclosure. With some scrap spotted gum and a router (with a Roman ogee and a roundover bit) I made a slightly nicer enclosure for volcon.

## Revision 2

After even more time, I gave the project an overhaul. Revision 2 uses the same head drum, optical encoder sensors and wooden enclosure. The upgrades from revision 1 include:
* Schematic and PCB layout completely redone but using [KiCad][link_web_kicad] instead of Eagle.
* Microcontroller changed from an AT90usb162 AVR to an ATmega32U4 (simply because I have a few of these).
* Remove the serial Tx/Rx connector (only used this for debugging revision 1).
* Remove the reset tact-switch (also was only used when debugging).
* Use smd components instead of through-hole.
* Connect with a USB type-C connector instead of a USB type-B.
* Have the PCB fabricated (JLCPCB) instead of the home-made copper-etch method.
* A couple of LEDs on the bottom of the PCB purely to visualise the gray code (revision 1 had LEDs, but they only barely shone through etched sections of the PCB).
* Generally improved and cleaner code (still using the LUFA library).

![The completed volcon.][link_image_volcon]

[link_image_volcon]:volcon.jpg

[link_clews_volcon]:https://clews.pro/projects/volcon.php

[link_web_gray_code]:https://en.wikipedia.org/wiki/Gray_code
[link_web_hackaday_podcast]:https://hackaday.com/category/podcasts/
[link_web_hackaday_podcast_106]:https://hackaday.com/2021/02/19/hackaday-podcast-106-connector-kerfuffle-tuning-fork-time-spinach-contact-prints-and-teslas-permanent-memory/
[link_web_hackaday_volcon]:https://hackaday.com/2021/02/15/a-volume-control-from-a-vcr-drum/
[link_web_head_drum]:https://en.wikipedia.org/wiki/File:Kopftrommel_2.jpg
[link_web_hid]:https://en.wikipedia.org/wiki/USB_human_interface_device_class
[link_web_kicad]:https://www.kicad.org/
[link_web_lufa]:http://fourwalledcubicle.com/LUFA.php
[link_web_quadrature_encoder]:https://en.wikipedia.org/wiki/Quadrature_encoder
[link_web_vcr]:https://en.wikipedia.org/wiki/Videocassette_recorder
