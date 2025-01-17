EESchema Schematic File Version 4
LIBS:Conexiones-cache
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
L Connector:Conn_01x08_Female J4
U 1 1 5DC8365F
P 5700 4050
F 0 "J4" H 5728 4026 50  0000 L CNN
F 1 "PT100" H 5728 3935 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 5700 4050 50  0001 C CNN
F 3 "~" H 5700 4050 50  0001 C CNN
	1    5700 4050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 5DC83F29
P 5700 1450
F 0 "J2" H 5672 1474 50  0000 R CNN
F 1 "Termocupla" H 5672 1383 50  0000 R CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-05A_1x05_P2.54mm_Vertical" H 5700 1450 50  0001 C CNN
F 3 "~" H 5700 1450 50  0001 C CNN
	1    5700 1450
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 5DC84EF3
P 5700 5350
F 0 "J6" H 5780 5342 50  0000 L CNN
F 1 "Rele" H 5780 5251 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 5700 5350 50  0001 C CNN
F 3 "~" H 5700 5350 50  0001 C CNN
	1    5700 5350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x40_Female J1
U 1 1 5DC858BB
P 3300 3150
F 0 "J1" H 3192 5235 50  0000 C CNN
F 1 "Raspberry Pi" H 3192 5144 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H 3300 3150 50  0001 C CNN
F 3 "~" H 3300 3150 50  0001 C CNN
	1    3300 3150
	-1   0    0    -1  
$EndComp
Text Label 5100 1550 0    50   ~ 0
t_cs
Text Label 5100 1650 0    50   ~ 0
t_miso
Text Label 5100 1450 0    50   ~ 0
t_clk
Text Label 5100 1350 0    50   ~ 0
3v3
Text Label 5100 2150 0    50   ~ 0
led_1
Text Label 5100 2250 0    50   ~ 0
led_2
Text Label 5100 2350 0    50   ~ 0
led_3
Text Label 5100 2450 0    50   ~ 0
led_4
Text Label 5100 3850 0    50   ~ 0
p_cs
Text Label 5100 4050 0    50   ~ 0
p_mosi
Text Label 5100 3750 0    50   ~ 0
p_miso
Text Label 5100 3950 0    50   ~ 0
p_clk
Text Label 5100 4450 0    50   ~ 0
5v
Text Label 5100 5350 0    50   ~ 0
r_out
Text Label 3800 2650 0    50   ~ 0
t_cs
Text Label 3800 3250 0    50   ~ 0
t_miso
Text Label 3800 3450 0    50   ~ 0
t_clk
Text Label 5100 1250 0    50   ~ 0
ground
Text Label 3800 1250 0    50   ~ 0
3v3
Text Label 3800 4050 0    50   ~ 0
led_1
Text Label 3800 4250 0    50   ~ 0
led_2
Text Label 3800 4450 0    50   ~ 0
led_3
Text Label 4200 5800 0    50   ~ 0
led_4
Text Label 3800 2450 0    50   ~ 0
p_cs
Text Label 3800 2750 0    50   ~ 0
p_mosi
Text Label 3800 2950 0    50   ~ 0
p_miso
Text Label 3800 2250 0    50   ~ 0
p_clk
Text Label 3800 1350 0    50   ~ 0
5v
Text Label 3800 5800 0    50   ~ 0
3v3
Text Label 3800 4350 0    50   ~ 0
b_out
Text Label 3800 1850 0    50   ~ 0
r_out
Text Label 3800 1550 0    50   ~ 0
5v
Wire Wire Line
	3500 1250 3800 1250
Wire Wire Line
	3800 1350 3500 1350
Wire Wire Line
	3500 1550 3800 1550
Wire Wire Line
	3800 1750 3500 1750
Wire Wire Line
	3500 1850 3800 1850
Wire Wire Line
	3500 2250 3800 2250
Wire Wire Line
	3800 2450 3500 2450
Wire Wire Line
	3500 2550 3800 2550
Wire Wire Line
	3800 2650 3500 2650
Wire Wire Line
	3500 2750 3800 2750
Wire Wire Line
	3500 2950 3800 2950
Wire Wire Line
	3800 3150 3500 3150
Wire Wire Line
	3500 3250 3800 3250
Wire Wire Line
	3800 3450 3500 3450
Wire Wire Line
	3800 4050 3500 4050
Wire Wire Line
	3500 4150 3800 4150
Wire Wire Line
	3800 4250 3500 4250
Wire Wire Line
	3500 4350 3800 4350
Wire Wire Line
	3800 4450 3500 4450
Wire Wire Line
	3500 4550 3800 4550
Wire Wire Line
	5100 2150 5500 2150
Wire Wire Line
	5100 2250 5500 2250
Wire Wire Line
	5100 2350 5500 2350
Wire Wire Line
	5100 2450 5500 2450
Wire Wire Line
	5100 5350 5500 5350
Wire Wire Line
	5100 5450 5500 5450
Wire Wire Line
	3800 5800 4200 5800
NoConn ~ 5500 4150
NoConn ~ 5500 4250
Wire Wire Line
	5100 3750 5500 3750
Wire Wire Line
	5500 3850 5100 3850
Wire Wire Line
	5100 3950 5500 3950
Wire Wire Line
	5100 4050 5500 4050
Wire Wire Line
	5100 4350 5500 4350
Wire Wire Line
	5100 4450 5500 4450
Wire Wire Line
	5100 1250 5500 1250
Wire Wire Line
	5100 1350 5500 1350
Wire Wire Line
	5100 1450 5500 1450
Wire Wire Line
	5100 1550 5500 1550
Wire Wire Line
	5100 1650 5500 1650
NoConn ~ 3500 1450
NoConn ~ 3500 1650
NoConn ~ 3500 1950
NoConn ~ 3500 2150
NoConn ~ 3500 2350
NoConn ~ 3500 3050
NoConn ~ 3500 3350
NoConn ~ 3500 3550
NoConn ~ 3500 3750
NoConn ~ 3500 3850
NoConn ~ 3500 3950
NoConn ~ 3500 4650
NoConn ~ 3500 4750
NoConn ~ 3500 4850
NoConn ~ 3500 4950
NoConn ~ 3500 5150
$Comp
L Device:R R1
U 1 1 5DCB653E
P 4850 2300
F 0 "R1" H 4920 2346 50  0000 L CNN
F 1 "R" H 4920 2255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4780 2300 50  0001 C CNN
F 3 "~" H 4850 2300 50  0001 C CNN
	1    4850 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5DCB89CE
P 8100 1750
F 0 "#PWR01" H 8100 1500 50  0001 C CNN
F 1 "GND" H 8105 1577 50  0000 C CNN
F 2 "" H 8100 1750 50  0001 C CNN
F 3 "" H 8100 1750 50  0001 C CNN
	1    8100 1750
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5DCB8D26
P 8000 1550
F 0 "#FLG01" H 8000 1625 50  0001 C CNN
F 1 "PWR_FLAG" H 8000 1723 50  0000 C CNN
F 2 "" H 8000 1550 50  0001 C CNN
F 3 "~" H 8000 1550 50  0001 C CNN
	1    8000 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 1550 8000 1650
Wire Wire Line
	8000 1650 8100 1650
Wire Wire Line
	8200 1650 8200 1550
Wire Wire Line
	8100 1750 8100 1650
Connection ~ 8100 1650
Wire Wire Line
	8100 1650 8200 1650
Text Label 3800 2550 0    50   ~ 0
ground
Text Label 3800 3150 0    50   ~ 0
ground
Text Label 3800 4150 0    50   ~ 0
ground
Text Label 3800 4550 0    50   ~ 0
ground
Text Label 5100 2650 0    50   ~ 0
ground
Text Label 5100 4350 0    50   ~ 0
ground
Text Label 5100 5450 0    50   ~ 0
ground
Text Label 3800 1750 0    50   ~ 0
ground
Text Label 8200 1550 0    50   ~ 0
ground
NoConn ~ 3500 2050
NoConn ~ 3500 3650
NoConn ~ 3500 5050
NoConn ~ 3500 2850
$Comp
L Connector:Conn_01x06_Male J3
U 1 1 5DC88155
P 5700 2350
F 0 "J3" H 5672 2324 50  0000 R CNN
F 1 "Frente" H 5672 2233 50  0000 R CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-06A_1x06_P2.54mm_Vertical" H 5700 2350 50  0001 C CNN
F 3 "~" H 5700 2350 50  0001 C CNN
	1    5700 2350
	-1   0    0    -1  
$EndComp
Text Label 4600 2550 0    50   ~ 0
b_out
Wire Wire Line
	5100 2650 5500 2650
Wire Wire Line
	4600 2550 4850 2550
Wire Wire Line
	4850 2450 4850 2550
Connection ~ 4850 2550
Wire Wire Line
	4850 2550 5500 2550
Text Label 4850 2050 0    50   ~ 0
3v3
Wire Wire Line
	4850 2050 4850 2150
$EndSCHEMATC
