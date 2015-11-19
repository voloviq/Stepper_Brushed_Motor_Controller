/*
	Author: Michal Wolowik
	Corporation: VOLOVIQUE
	Date: Warsaw 06 XI 2015

	Destination:
		Software for motor controller board. Main intention of current
		firmware is drive with speed and step regulation for DC brushed,
		and stepper motor unipolar and bipolar. Additionally software check
		over current, temperature and measure real speed of engines.

	File name:
		atmega16_low_level.h

	File destination:
		Main destiny of current code is collection of function which
		configure all Atmega peripherals.

	Dependencies:
		Timer 1 PWM 1kHz frequency
		ADC to measure over current, temperature
		USB to communicate with PC to setup regulation parameter and
		firmware update
		MCU Clock set to 12MHz (12 is necessary for manual USB driving)
		Software heartbeat located on portx (TODO) Led

	Compiler:
		avr gcc (AVR_8_bit_GNU_Toolchain_3.5.0_1662) 4.9.2

	GUI:
		Atmel Studio 7 (Version: 7.0.594)

	Documentation:
		Atmega16/16L Rev. 2466T AVR 07/10

	Responsible:
		This library is free software; you can redistribute it and/or
		modify it under the terms of the GNU Lesser General Public
		License as published by the Free Software Foundation; either
		version 2.1 of the License, or (at your option) any later version.

		This library is distributed in the hope that it will be useful,
		but WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
		Lesser General Public License for more details.

	Notes:
		Application is intended for Volovique Motors Controller revision 1.0.
*/


#ifndef ATMEGA16_LOW_LEVEL_H_
#define ATMEGA16_LOW_LEVEL_H_





void init_PWM(void);





void set_PWM_output(unsigned char duty);




#endif
 /* ATMEGA16_LOW_LEVEL_H_ */