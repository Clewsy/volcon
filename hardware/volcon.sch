EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L volcon:usb-c_2.0 J1
U 1 1 600F6220
P 7000 3250
F 0 "J1" H 7050 3250 50  0000 R CNN
F 1 "usb-c_2.0" H 7050 3100 50  0000 R CNN
F 2 "Connector_USB:USB_C_Receptacle_GCT_USB4085" H 7000 3250 50  0001 C CNN
F 3 "" H 7000 3250 50  0001 C CNN
	1    7000 3250
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATmega:ATmega32U4-AU U1
U 1 1 600F6611
P 3300 4400
F 0 "U1" H 3200 4050 50  0000 C CNN
F 1 "ATmega32U4-AU" H 3200 4150 50  0000 C CNN
F 2 "Package_QFP:TQFP-44_10x10mm_P0.8mm" H 3300 4400 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Datasheet.pdf" H 3300 4400 50  0001 C CNN
	1    3300 4400
	1    0    0    -1  
$EndComp
$Comp
L Connector:AVR-ISP-6 J2
U 1 1 600F6F82
P 9000 5000
F 0 "J2" H 8900 5050 50  0000 R CNN
F 1 "AVR-ISP-6" H 9400 4650 50  0000 R CNN
F 2 "Connector_IDC:IDC-Header_2x03_P2.54mm_Vertical" V 8750 5050 50  0001 C CNN
F 3 " ~" H 7725 4450 50  0001 C CNN
	1    9000 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 600F7370
P 2150 3000
F 0 "C1" V 2200 2900 50  0000 C CNN
F 1 "22pF" V 2000 2950 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2188 2850 50  0001 C CNN
F 3 "~" H 2150 3000 50  0001 C CNN
	1    2150 3000
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 600F7534
P 2150 3400
F 0 "C2" V 2200 3300 50  0000 C CNN
F 1 "22pF" V 2000 3350 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2188 3250 50  0001 C CNN
F 3 "~" H 2150 3400 50  0001 C CNN
	1    2150 3400
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 600F7777
P 2650 4400
F 0 "C3" H 2550 4500 50  0000 L CNN
F 1 "1uF" H 2500 4300 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2688 4250 50  0001 C CNN
F 3 "~" H 2650 4400 50  0001 C CNN
	1    2650 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 600F795D
P 7350 2550
F 0 "C4" V 7300 2650 50  0000 C CNN
F 1 "10uF" V 7200 2600 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 7388 2400 50  0001 C CNN
F 3 "~" H 7350 2550 50  0001 C CNN
	1    7350 2550
	0    1    1    0   
$EndComp
$Comp
L Device:R R01
U 1 1 600F7E6B
P 2650 2700
F 0 "R01" V 2650 2600 50  0000 L CNN
F 1 "10k" H 2700 2750 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 2580 2700 50  0001 C CNN
F 3 "~" H 2650 2700 50  0001 C CNN
	1    2650 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R02
U 1 1 600F81D0
P 7650 3000
F 0 "R02" V 7650 3000 50  0000 C CNN
F 1 "5k1" V 7550 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7580 3000 50  0001 C CNN
F 3 "~" H 7650 3000 50  0001 C CNN
	1    7650 3000
	0    1    1    0   
$EndComp
$Comp
L Device:R R03
U 1 1 600F84FF
P 7650 3100
F 0 "R03" V 7650 3100 50  0000 C CNN
F 1 "5k1" V 7750 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7580 3100 50  0001 C CNN
F 3 "~" H 7650 3100 50  0001 C CNN
	1    7650 3100
	0    1    1    0   
$EndComp
$Comp
L Device:R R04
U 1 1 600F8971
P 7700 3400
F 0 "R04" V 7700 3400 50  0000 C CNN
F 1 "22" V 7600 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7630 3400 50  0001 C CNN
F 3 "~" H 7700 3400 50  0001 C CNN
	1    7700 3400
	0    1    1    0   
$EndComp
$Comp
L Device:R R05
U 1 1 600F8B55
P 7700 3600
F 0 "R05" V 7700 3600 50  0000 C CNN
F 1 "22" V 7800 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7630 3600 50  0001 C CNN
F 3 "~" H 7700 3600 50  0001 C CNN
	1    7700 3600
	0    1    1    0   
$EndComp
$Comp
L Device:Crystal Y1
U 1 1 600F900E
P 2350 3200
F 0 "Y1" V 2250 3300 50  0000 C CNN
F 1 "16MHz" V 2500 3350 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_HC49-SD" H 2350 3200 50  0001 C CNN
F 3 "~" H 2350 3200 50  0001 C CNN
	1    2350 3200
	0    1    1    0   
$EndComp
$Comp
L Device:Q_NPN_BCE Q1
U 1 1 600F9519
P 6050 5350
F 0 "Q1" H 6241 5396 50  0000 L CNN
F 1 "NPN" H 6241 5305 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 6250 5450 50  0001 C CNN
F 3 "~" H 6050 5350 50  0001 C CNN
	1    6050 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_BCE Q2
U 1 1 600F9881
P 6050 6200
F 0 "Q2" H 6241 6246 50  0000 L CNN
F 1 "NPN" H 6241 6155 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 6250 6300 50  0001 C CNN
F 3 "~" H 6050 6200 50  0001 C CNN
	1    6050 6200
	1    0    0    -1  
$EndComp
Text GLabel 2600 2900 0    50   Input ~ 0
!RESET
Wire Wire Line
	2700 2900 2650 2900
Wire Wire Line
	2650 2900 2650 2850
Connection ~ 2650 2900
Wire Wire Line
	2650 2900 2600 2900
Wire Wire Line
	2700 3300 2650 3300
Wire Wire Line
	2650 3300 2650 3400
Wire Wire Line
	2650 3400 2350 3400
Wire Wire Line
	2350 3400 2350 3350
Wire Wire Line
	2700 3100 2650 3100
Wire Wire Line
	2650 3100 2650 3000
Wire Wire Line
	2650 3000 2350 3000
Wire Wire Line
	2350 3000 2350 3050
$Comp
L power:GND #PWR0103
U 1 1 60104834
P 1950 3450
F 0 "#PWR0103" H 1950 3200 50  0001 C CNN
F 1 "GND" H 1950 3300 50  0000 C CNN
F 2 "" H 1950 3450 50  0001 C CNN
F 3 "" H 1950 3450 50  0001 C CNN
	1    1950 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3000 2300 3000
Connection ~ 2350 3000
Wire Wire Line
	2350 3400 2300 3400
Connection ~ 2350 3400
Wire Wire Line
	2000 3400 1950 3400
Wire Wire Line
	1950 3400 1950 3000
Wire Wire Line
	1950 3000 2000 3000
Wire Wire Line
	1950 3450 1950 3400
Connection ~ 1950 3400
Wire Wire Line
	2650 2550 2650 2500
Wire Wire Line
	2650 2500 3200 2500
Wire Wire Line
	3200 2500 3200 2600
Wire Wire Line
	3200 2500 3300 2500
Wire Wire Line
	3300 2500 3300 2600
Connection ~ 3200 2500
Wire Wire Line
	3300 2500 3400 2500
Wire Wire Line
	3400 2500 3400 2600
Connection ~ 3300 2500
$Comp
L power:+5V #PWR0104
U 1 1 601097F9
P 3300 2450
F 0 "#PWR0104" H 3300 2300 50  0001 C CNN
F 1 "+5V" H 3300 2600 50  0000 C CNN
F 2 "" H 3300 2450 50  0001 C CNN
F 3 "" H 3300 2450 50  0001 C CNN
	1    3300 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2450 3300 2500
$Comp
L power:+5V #PWR0105
U 1 1 6010A6FB
P 2650 3650
F 0 "#PWR0105" H 2650 3500 50  0001 C CNN
F 1 "+5V" H 2550 3750 50  0000 C CNN
F 2 "" H 2650 3650 50  0001 C CNN
F 3 "" H 2650 3650 50  0001 C CNN
	1    2650 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3700 2650 3700
Wire Wire Line
	2650 3700 2650 3650
Text GLabel 2650 3900 0    50   Input ~ 0
D+
Text GLabel 2650 4000 0    50   Input ~ 0
D-
Wire Wire Line
	2650 4000 2700 4000
Wire Wire Line
	2700 3900 2650 3900
Wire Wire Line
	2700 4200 2650 4200
Wire Wire Line
	2650 4200 2650 4250
$Comp
L power:GND #PWR0106
U 1 1 6010E691
P 2650 4600
F 0 "#PWR0106" H 2650 4350 50  0001 C CNN
F 1 "GND" H 2650 4450 50  0000 C CNN
F 2 "" H 2650 4600 50  0001 C CNN
F 3 "" H 2650 4600 50  0001 C CNN
	1    2650 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 4600 2650 4550
$Comp
L power:GND #PWR0107
U 1 1 6010F983
P 3250 6300
F 0 "#PWR0107" H 3250 6050 50  0001 C CNN
F 1 "GND" H 3250 6150 50  0000 C CNN
F 2 "" H 3250 6300 50  0001 C CNN
F 3 "" H 3250 6300 50  0001 C CNN
	1    3250 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 6300 3250 6250
Wire Wire Line
	3250 6250 3200 6250
Wire Wire Line
	3200 6250 3200 6200
Wire Wire Line
	3250 6250 3300 6250
Wire Wire Line
	3300 6250 3300 6200
Connection ~ 3250 6250
Text GLabel 3950 3000 2    50   Input ~ 0
SCK
Text GLabel 3950 3100 2    50   Input ~ 0
MOSI
Text GLabel 3950 3200 2    50   Input ~ 0
MISO
Wire Wire Line
	3950 3000 3900 3000
Wire Wire Line
	3900 3100 3950 3100
Wire Wire Line
	3950 3200 3900 3200
$Comp
L power:GND #PWR0108
U 1 1 6011682F
P 7550 2600
F 0 "#PWR0108" H 7550 2350 50  0001 C CNN
F 1 "GND" H 7550 2450 50  0000 C CNN
F 2 "" H 7550 2600 50  0001 C CNN
F 3 "" H 7550 2600 50  0001 C CNN
	1    7550 2600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0109
U 1 1 60116B6E
P 7150 2250
F 0 "#PWR0109" H 7150 2100 50  0001 C CNN
F 1 "+5V" H 7150 2400 50  0000 C CNN
F 2 "" H 7150 2250 50  0001 C CNN
F 3 "" H 7150 2250 50  0001 C CNN
	1    7150 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2550 7150 2550
Wire Wire Line
	6850 2550 6850 2600
Wire Wire Line
	6950 2600 6950 2550
Connection ~ 6950 2550
Wire Wire Line
	6950 2550 6850 2550
Wire Wire Line
	7050 2550 7050 2600
Connection ~ 7050 2550
Wire Wire Line
	7050 2550 6950 2550
Wire Wire Line
	7150 2600 7150 2550
Connection ~ 7150 2550
Wire Wire Line
	7150 2550 7050 2550
Wire Wire Line
	7550 2600 7550 2550
Wire Wire Line
	7550 2550 7500 2550
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6011D7C3
P 7200 2300
F 0 "#FLG0101" H 7200 2375 50  0001 C CNN
F 1 "PWR_FLAG" V 7200 2400 50  0000 L CNN
F 2 "" H 7200 2300 50  0001 C CNN
F 3 "~" H 7200 2300 50  0001 C CNN
	1    7200 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	7150 2550 7150 2300
Wire Wire Line
	7150 2300 7200 2300
Wire Wire Line
	7150 2250 7150 2300
Connection ~ 7150 2300
Text GLabel 7900 3400 2    50   Input ~ 0
D-
Text GLabel 7900 3600 2    50   Input ~ 0
D+
Wire Wire Line
	7900 3600 7850 3600
Wire Wire Line
	7550 3600 7500 3600
Wire Wire Line
	7500 3600 7500 3500
Wire Wire Line
	7500 3500 7450 3500
Connection ~ 7500 3600
Wire Wire Line
	7500 3600 7450 3600
Wire Wire Line
	7450 3400 7500 3400
Wire Wire Line
	7850 3400 7900 3400
Wire Wire Line
	7500 3400 7500 3300
Wire Wire Line
	7500 3300 7450 3300
Connection ~ 7500 3400
Wire Wire Line
	7500 3400 7550 3400
$Comp
L power:GND #PWR0110
U 1 1 6012AEAE
P 7850 3150
F 0 "#PWR0110" H 7850 2900 50  0001 C CNN
F 1 "GND" H 7850 3000 50  0000 C CNN
F 2 "" H 7850 3150 50  0001 C CNN
F 3 "" H 7850 3150 50  0001 C CNN
	1    7850 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 3150 7850 3100
Wire Wire Line
	7850 3100 7800 3100
Wire Wire Line
	7850 3100 7850 3000
Wire Wire Line
	7850 3000 7800 3000
Connection ~ 7850 3100
Wire Wire Line
	7500 3000 7450 3000
Wire Wire Line
	7450 3100 7500 3100
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 6012F175
P 7200 4000
F 0 "#FLG0102" H 7200 4075 50  0001 C CNN
F 1 "PWR_FLAG" V 7200 4100 50  0000 L CNN
F 2 "" H 7200 4000 50  0001 C CNN
F 3 "~" H 7200 4000 50  0001 C CNN
	1    7200 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	7200 4000 7150 4000
Wire Wire Line
	6850 4000 6850 3950
Wire Wire Line
	6950 3950 6950 4000
Connection ~ 6950 4000
Wire Wire Line
	6950 4000 6850 4000
Wire Wire Line
	7050 4000 7050 3950
Connection ~ 7050 4000
Wire Wire Line
	7050 4000 6950 4000
Wire Wire Line
	7150 3950 7150 4000
Connection ~ 7150 4000
Wire Wire Line
	7150 4000 7050 4000
$Comp
L power:GND #PWR0111
U 1 1 60134209
P 7150 4050
F 0 "#PWR0111" H 7150 3800 50  0001 C CNN
F 1 "GND" H 7150 3900 50  0000 C CNN
F 2 "" H 7150 4050 50  0001 C CNN
F 3 "" H 7150 4050 50  0001 C CNN
	1    7150 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 4050 7150 4000
NoConn ~ 6550 3100
NoConn ~ 6550 3200
NoConn ~ 6550 3550
Text GLabel 9450 5000 2    50   Input ~ 0
SCK
Text GLabel 9450 4900 2    50   Input ~ 0
MOSI
Text GLabel 9450 4800 2    50   Input ~ 0
MISO
Text GLabel 9450 5100 2    50   Input ~ 0
!RESET
$Comp
L power:GND #PWR0112
U 1 1 6013AB86
P 8900 5450
F 0 "#PWR0112" H 8900 5200 50  0001 C CNN
F 1 "GND" H 8900 5300 50  0000 C CNN
F 2 "" H 8900 5450 50  0001 C CNN
F 3 "" H 8900 5450 50  0001 C CNN
	1    8900 5450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0113
U 1 1 6013AE5D
P 8900 4450
F 0 "#PWR0113" H 8900 4300 50  0001 C CNN
F 1 "+5V" H 8900 4600 50  0000 C CNN
F 2 "" H 8900 4450 50  0001 C CNN
F 3 "" H 8900 4450 50  0001 C CNN
	1    8900 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 5100 9400 5100
Wire Wire Line
	9400 5000 9450 5000
Wire Wire Line
	9450 4900 9400 4900
Wire Wire Line
	9400 4800 9450 4800
Wire Wire Line
	8900 4500 8900 4450
Wire Wire Line
	8900 5400 8900 5450
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 60149E5B
P 5000 5100
F 0 "J3" H 5108 5381 50  0000 C CNN
F 1 "4-Pin" H 5108 5290 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5000 5100 50  0001 C CNN
F 3 "~" H 5000 5100 50  0001 C CNN
	1    5000 5100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0114
U 1 1 6014AD1D
P 5250 4950
F 0 "#PWR0114" H 5250 4800 50  0001 C CNN
F 1 "+5V" H 5250 5100 50  0000 C CNN
F 2 "" H 5250 4950 50  0001 C CNN
F 3 "" H 5250 4950 50  0001 C CNN
	1    5250 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 6014AF95
P 5600 5150
F 0 "#PWR0115" H 5600 4900 50  0001 C CNN
F 1 "GND" H 5600 5000 50  0000 C CNN
F 2 "" H 5600 5150 50  0001 C CNN
F 3 "" H 5600 5150 50  0001 C CNN
	1    5600 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R06
U 1 1 6014B737
P 5400 5100
F 0 "R06" V 5400 5100 50  0000 C CNN
F 1 "390" V 5500 5100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5330 5100 50  0001 C CNN
F 3 "~" H 5400 5100 50  0001 C CNN
	1    5400 5100
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 601581BB
P 6150 6450
F 0 "#PWR0116" H 6150 6200 50  0001 C CNN
F 1 "GND" H 6150 6300 50  0000 C CNN
F 2 "" H 6150 6450 50  0001 C CNN
F 3 "" H 6150 6450 50  0001 C CNN
	1    6150 6450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 60158432
P 6150 5600
F 0 "#PWR0117" H 6150 5350 50  0001 C CNN
F 1 "GND" H 6150 5450 50  0000 C CNN
F 2 "" H 6150 5600 50  0001 C CNN
F 3 "" H 6150 5600 50  0001 C CNN
	1    6150 5600
	1    0    0    -1  
$EndComp
Text GLabel 6200 5100 2    50   Input ~ 0
A
Text GLabel 6200 5950 2    50   Input ~ 0
B
Wire Wire Line
	5200 5000 5250 5000
Wire Wire Line
	5250 5000 5250 4950
Wire Wire Line
	5250 5100 5200 5100
Wire Wire Line
	5550 5100 5600 5100
Wire Wire Line
	5600 5100 5600 5150
Wire Wire Line
	5200 5200 5500 5200
Wire Wire Line
	5500 5200 5500 5350
Wire Wire Line
	5200 5300 5450 5300
Wire Wire Line
	6200 5950 6150 5950
Wire Wire Line
	6150 5950 6150 6000
Wire Wire Line
	6150 5150 6150 5100
Wire Wire Line
	6150 5100 6200 5100
Wire Wire Line
	6150 5550 6150 5600
Wire Wire Line
	6150 6400 6150 6450
$Comp
L Device:LED D2
U 1 1 6018825D
P 5850 5950
F 0 "D2" H 5850 5850 50  0000 C CNN
F 1 "LED" H 5850 6050 50  0000 C CNN
F 2 "LED_SMD:LED_Cree-XQ_HandSoldering" H 5850 5950 50  0001 C CNN
F 3 "~" H 5850 5950 50  0001 C CNN
	1    5850 5950
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D1
U 1 1 601A3B0D
P 5850 5100
F 0 "D1" H 5850 5000 50  0000 C CNN
F 1 "LED" H 5850 5200 50  0000 C CNN
F 2 "LED_SMD:LED_Cree-XQ_HandSoldering" H 5850 5100 50  0001 C CNN
F 3 "~" H 5850 5100 50  0001 C CNN
	1    5850 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	5500 5350 5850 5350
Wire Wire Line
	5850 6200 5450 6200
Wire Wire Line
	6000 5950 6150 5950
Connection ~ 6150 5950
Wire Wire Line
	6000 5100 6150 5100
Connection ~ 6150 5100
$Comp
L Device:R R07
U 1 1 601AF0FC
P 5650 4900
F 0 "R07" V 5650 4900 50  0000 C CNN
F 1 "100" H 5750 5050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5580 4900 50  0001 C CNN
F 3 "~" H 5650 4900 50  0001 C CNN
	1    5650 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R08
U 1 1 601AF5EC
P 5650 5750
F 0 "R08" V 5650 5750 50  0000 C CNN
F 1 "100" H 5750 5900 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5580 5750 50  0001 C CNN
F 3 "~" H 5650 5750 50  0001 C CNN
	1    5650 5750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0118
U 1 1 601AF8E7
P 5650 5550
F 0 "#PWR0118" H 5650 5400 50  0001 C CNN
F 1 "+5V" H 5650 5700 50  0000 C CNN
F 2 "" H 5650 5550 50  0001 C CNN
F 3 "" H 5650 5550 50  0001 C CNN
	1    5650 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 5300 5450 6200
Wire Wire Line
	5650 5550 5650 5600
Wire Wire Line
	5700 5950 5650 5950
Wire Wire Line
	5650 5950 5650 5900
$Comp
L power:+5V #PWR0119
U 1 1 601C03E1
P 5650 4700
F 0 "#PWR0119" H 5650 4550 50  0001 C CNN
F 1 "+5V" H 5650 4850 50  0000 C CNN
F 2 "" H 5650 4700 50  0001 C CNN
F 3 "" H 5650 4700 50  0001 C CNN
	1    5650 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 4700 5650 4750
Wire Wire Line
	5650 5050 5650 5100
Wire Wire Line
	5650 5100 5700 5100
Text GLabel 3950 4100 2    50   Input ~ 0
A
Text GLabel 3950 4200 2    50   Input ~ 0
B
Wire Wire Line
	3950 4200 3900 4200
Wire Wire Line
	3900 4100 3950 4100
NoConn ~ 3900 2900
NoConn ~ 3900 3300
NoConn ~ 3900 3400
NoConn ~ 3900 3500
NoConn ~ 3900 3600
NoConn ~ 3900 3800
NoConn ~ 3900 3900
NoConn ~ 3900 4300
NoConn ~ 3900 4400
NoConn ~ 3900 4500
NoConn ~ 3900 4600
NoConn ~ 3900 4700
NoConn ~ 3900 4800
NoConn ~ 3900 5000
NoConn ~ 3900 5100
NoConn ~ 3900 5300
NoConn ~ 3900 5400
NoConn ~ 3900 5500
NoConn ~ 3900 5600
NoConn ~ 3900 5700
NoConn ~ 3900 5800
NoConn ~ 2700 3500
Text Notes 7400 7500 0    79   ~ 0
volcon
Text Notes 10600 7650 0    79   ~ 0
2
Text Notes 8150 7650 0    79   ~ 0
2021-02-07
Wire Notes Line
	4950 4500 4950 6650
Wire Notes Line
	4950 6650 6450 6650
Wire Notes Line
	6450 6650 6450 4500
Wire Notes Line
	6450 4500 4950 4500
Wire Notes Line
	6500 4250 8100 4250
Wire Notes Line
	1850 2250 1850 6500
Wire Notes Line
	1850 6500 4200 6500
Wire Notes Line
	4200 6500 4200 2250
Wire Notes Line
	4200 2250 1850 2250
Text Notes 1900 2350 0    50   ~ 0
ATmega32U4 AVR Microcontroller
Text Notes 4950 6650 0    50   ~ 0
Optical Sensors Interface
Text Notes 8650 4200 0    50   ~ 0
AVR In-System Programmer (ISP)
Text Notes 6500 2050 0    50   ~ 0
USB-C Receptacle\nConfigured to identify as USB 2.0 Device
Wire Notes Line
	6500 4250 6500 1900
Wire Notes Line
	6500 1900 8100 1900
Wire Notes Line
	8100 1900 8100 4250
Wire Notes Line
	8650 5650 8650 4100
Wire Notes Line
	8650 4100 9950 4100
Wire Notes Line
	9950 4100 9950 5650
Wire Notes Line
	9950 5650 8650 5650
Text Notes 7000 7100 0    50   ~ 0
Changes from revision 1:\n- KiCAD instead of Eagle.\n- ATmega32u4 instead of AT90usb162.\n- Removed serial connector.\n- Removed reset push-button.\n- SMD instead of through-hole components.\n- USB-C connector instead of USB-B.
$EndSCHEMATC
