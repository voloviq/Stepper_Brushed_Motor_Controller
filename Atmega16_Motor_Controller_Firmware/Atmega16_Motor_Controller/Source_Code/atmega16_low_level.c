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
            atmega16_low_level.c

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




#include <avr/io.h>
#include <util/delay.h>
#include "atmega16_low_level.h"




void init_PWM(void)
{
/*
    Description what is and how:
    
        TCCR0 Timer Counter Control Register (TIMER0)

        BITS DESCRIPTION

        NO:   NAME   DESCRIPTION

        BIT 7 : FOC0   Force Output Compare [Not used in this example]
        BIT 6 : WGM00  Wave form generation mode [SET to 1]
        BIT 5 : COM01  Compare Output Mode        [SET to 1]
        BIT 4 : COM00  Compare Output Mode        [SET to 0]

        BIT 3 : WGM01  Wave form generation mode [SET to 1]
        BIT 2 : CS02   Clock Select               [SET to 0]
        BIT 1 : CS01   Clock Select               [SET to 0]
        BIT 0 : CS00   Clock Select               [SET to 1]
*/

   TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(0<<CS02)|(1<<CS01)|(0<<CS00);

   /* Set OC0 PIN as output. It is PB3 on ATmega16 ATmega16 */

   DDRB |= (1<<PB3);
}





void set_PWM_output(unsigned char duty)
{
   OCR0=duty;
}
