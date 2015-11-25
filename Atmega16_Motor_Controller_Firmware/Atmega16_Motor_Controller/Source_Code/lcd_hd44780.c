/*
        Author: Michal Wolowik
        Corporation: VOLOVIQUE
        Date: Warsaw 25 XI 2015

        Destination:
            Library to control LCD 2x16 display base on HD44780 controller

        File name:
            lcd_hd44780.h

        File destination:
            Main destiny of current code is collection of function which
            control and display messages on LCD

        Dependencies:
            To proper work of this library it is necessary to have 6
            of free microcontroller port which can be configure as
            output type push pull 
            Library is intended for Atmega AVR 8 microcontroller
                 
        Limitations:
            Library is designed for 4 wire connection only (DB7_DB4) 

        Compiler:
            avr gcc (AVR_8_bit_GNU_Toolchain_3.5.0_1662) 4.9.2

        GUI:
            Atmel Studio 7 (Version: 7.0.594)

        Documentation:
            HD44780U (LCD II) _ ADE_207_272(Z)'99.9 Rev. 0.0

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
            Application is intended for LCD 2x16 based on HD44780
*/





#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd_hd44780.h"




/* Special characters definitions array */
const unsigned char special_characters_array[SPC_QUANTITY] PROGMEM =
{
    0x00,0x00,0x0E,0x01,0x0F,0x11,0x0F,0x02, // Letter _ polish 'a'
    0x00,0x00,0x0E,0x11,0x1E,0x10,0x0E,0x03, // Letter _ polish 'e'
    0x02,0x04,0x16,0x19,0x11,0x11,0x11,0x00, // Letter _ polish 'n'
    0x00,0x02,0x0E,0x15,0x11,0x11,0x0E,0x00, // Letter _ polish 'o'
    0x04,0x04,0x06,0x04,0x0C,0x04,0x02,0x00, // Letter _ polish 'l'
    0x01,0x0E,0x15,0x08,0x06,0x11,0x0E,0x00, // Letter _ polish 'S'
    0x02,0x1F,0x09,0x02,0x04,0x08,0x1F,0x00, // Letter _ polish 'Zi'
    0x04,0x1F,0x01,0x02,0x04,0x08,0x1F,0x00  // Letter _ polish 'Zy'
};




void init_lcd(void)
{
    /* Set all necessary drive signal as outputs */
    RSOUT;
    ENABLEOUT;
    DB7OUT;
    DB6OUT;
    DB5OUT;
    DB4OUT;
        
    // Add necessary delay at least 500[ms]
    // for 5V power supply
    _delay_ms(500);

    write_operation(0x03, DIS_INST);

    // Add necessary delay at least 4.1[ms]
    _delay_ms(4);
    _delay_us(100);

    write_operation(0x03, DIS_INST);

    // Wait for more than 100[us]
    _delay_us(100);

    write_operation(0x03, DIS_INST);

    write_operation(0x02, DIS_INST);
    
    _delay_ms(1);

    // Interface 4-bits, 2 lines, field 5x7
    write_operation(0x02, DIS_INST);
    write_operation(0x08, DIS_INST);

    // Wait for more than 100[us]
    _delay_ms(1);

    // Disable Cursor, blinking
    write_operation(0x00, DIS_INST);
    write_operation(0x08, DIS_INST);

    // Wait for more than 100[us]
    _delay_ms(1);

    // Clear LCD
    write_operation(0x00, DIS_INST);
    write_operation(0x01, DIS_INST);

    // Wait for more than 100[us]
    _delay_ms(1);

    // Don't turn on the right
    write_operation(0x00, DIS_INST);
    write_operation(0x06, DIS_INST);

    // Wait for more than 100[us]
    _delay_ms(1);

    // Enable Display without blinking
    write_operation(0x00, DIS_INST);
    write_operation(0x0C, DIS_INST);

    // Wait for more than 100[us]
    _delay_ms(1);

    // Special char initialize
    spec_char_init();
    
    _delay_ms(1);
}




unsigned char replace_polish_character(unsigned char c)
{
    unsigned char ret = c;

    if( (c == 0xA5) || (c == 0xA4) ) // A
    {
        ret = 0x00;
    }
    else if( (c == 0x91) || (c == 0x90) ) // E
    {
        ret = 0x01;
    }
    else if( (c == 0xE4) || (c == 0xE3) ) // N
    {
        ret = 0x02;
    }
    else if(c == 0xA2) // O
    {
        ret = 0x03;
    }
    else if( (c == 0x88) || (c == 0x9D) ) // L
    {
        ret = 0x04;
    }
    else if( (c == 0x98) || (c == 0x9E) ) // S
    {
        ret = 0x05;
    }
    else if(c == 0xAB) // Zi
    {
        ret = 0x06;
    }
    else if( (c == 0xBE) || (c == 0xBD) ) // Zy
    {
        ret = 0x07;
    }
    return (ret);
}




void set_position(unsigned char x, unsigned char row)
{
    // Wait at least 1[ms]
    _delay_ms(1);
    
    // Save high nibble
    write_operation((((x+row)&0xF0)>>4), DIS_INST);
    // Save low nibble
    write_operation(((x+row)&0x0F), DIS_INST);
    
    // Wait at least 1[ms]
    _delay_ms(1);
}
 



void spec_char_init(void)
{
    unsigned char x;

    for(x=0; x<SPC_QUANTITY; x++)
    {
        // Save high nibble
        write_operation((((0x40+x)&0xF0)>>4), DIS_INST);
        // Save low nibble
        write_operation(((0x40+x)&0x0F), DIS_INST);
        
        // Wait at least 1[ms]
        _delay_ms(1);

        // Save char to CGRAM

        // Save high nibble
        write_operation(((special_characters_array[x]&0xF0)>>4), DIS_DATA);
        // Save low nibble
        write_operation(((special_characters_array[x])&0x0F), DIS_DATA);
        
        // Wait at least 1[ms]
        _delay_ms(1);
    }
}




void clrscr(void)
{
    // Wait at least 1[ms]
    _delay_ms(1);
    
    // Save high nibble
    write_operation(0x00, DIS_INST);
    // Save low nibble
    write_operation(0x01, DIS_INST);
    
    // Wait at least 1[ms]
    _delay_ms(1);
}




void write_operation(unsigned char bt, unsigned char rs)
{
    // Set RS signal
    if(rs == DIS_INST)
    	RSL;
    else
    	RSH;

    // Wait at least 50[us] after RS set
    _delay_us(50);

    // Save high nibble
    if(bt&0x08)
    	DB7H;
    else
    	DB7L;

    if(bt&0x04)
    	DB6H;
    else
    	DB6L;

    if(bt&0x02)
    	DB5H;
    else
    	DB5L;

    if(bt&0x01)
    	DB4H;
    else
    	DB4L;

    // Set low state on ENABLE signal
    ENABLEH;

    // Wait at least 1[us]
    _delay_us(1);

    // Set ENABLE to high before next operation
    ENABLEL;

    // Wait at least 1[us]
    _delay_us(1);
}




void blinking(unsigned char on_off)
{
    // Wait at least 1[ms]
    _delay_ms(1);
    
    // Enable or disable blinking

    // Save high nibble
    write_operation(0x00, DIS_INST);

    // Save low nibble
    if(on_off)
    write_operation(0x0D, DIS_INST);
    else
    write_operation(0x0C, DIS_INST);
    
    // Wait at least 1[ms]
    _delay_ms(1);
}




void lcd_write_string_flash(const char *str)
{
    char character;
    
    for (character = pgm_read_byte(str); character; ++str, character = pgm_read_byte(str))
    {
        // Save high nibble
        write_operation(((character&0xF0)>>4), DIS_DATA);
        // Save low nibble
        write_operation((character&0x0F), DIS_DATA);
    }
}




void lcd_write_string_ram(char *x, unsigned char length)
{
    while (--length > 0)
    {
        // Save high nibble
        write_operation(((*x&0xF0)>>4), DIS_DATA);
        // Save low nibble
        write_operation((*x&0x0F), DIS_DATA);
        x++;
    }
}