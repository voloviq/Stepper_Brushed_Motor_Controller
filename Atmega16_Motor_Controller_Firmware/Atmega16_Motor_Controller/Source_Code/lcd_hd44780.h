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




#ifndef _LCD_HD44780_H
#define _LCD_HD44780_H
 



/* Define how many special character will be written to CGRAM of display */
#define SPC_QUANTITY 64




/* Definition of command and data operation */
#define DIS_INST 0
#define DIS_DATA 1




/* Row definition */
#define ROW_ONE 0x80
#define ROW_TWO 0xC0




/* LCD 2x16 HD44780 signal ports definitions in 4 wire connection mode */

/* Set RS signal pin mask */
#define RSMASK     0x20
/* Set RS signal pin for output */
#define RSOUT      DDRA |= RSMASK
/* Set RS signal in high level state */
#define RSH        PORTA |= RSMASK
/* Set RS signal in high level state*/
#define RSL        PORTA &= ~RSMASK

/* Set ENABLE signal pin mask */
#define ENABLEMASK     0x20
/* Set ENABLE signal pin for output */
#define ENABLEOUT      DDRA |= ENABLEMASK
/* Set ENABLE signal in high level state */
#define ENABLEH        PORTA |= ENABLEMASK
/* Set ENABLE signal in high level state*/
#define ENABLEL        PORTA &= ~ENABLEMASK

/* Set DB7 signal pin mask */
#define DB7MASK     0x20
/* Set DB7 signal pin for output */
#define DB7OUT      DDRA |= DB7MASK
/* Set DB7 signal in high level state */
#define DB7H        PORTA |= DB7MASK
/* Set DB7 signal in high level state*/
#define DB7L        PORTA &= ~DB7MASK

/* Set DB6 signal pin mask */
#define DB6MASK     0x20
/* Set DB6 signal pin for output */
#define DB6OUT      DDRA |= DB6MASK
/* Set DB6 signal in high level state */
#define DB6H        PORTA |= DB6MASK
/* Set DB6 signal in high level state*/
#define DB6L        PORTA &= ~DB6MASK

/* Set DB5 signal pin mask */
#define DB5MASK     0x20
/* Set DB5 signal pin for output */
#define DB5OUT      DDRA |= DB5MASK
/* Set DB5 signal in high level state */
#define DB5H        PORTA |= DB5MASK
/* Set DB5 signal in high level state*/
#define DB5L        PORTA &= ~DB5MASK

/* Set DB4 signal pin mask */
#define DB4MASK     0x20
/* Set DB4 signal pin for output */
#define DB4OUT      DDRA |= DB4MASK
/* Set DB4 signal in high level state */
#define DB4H        PORTA |= DB4MASK
/* Set DB4 signal in high level state*/
#define DB4L        PORTA &= ~DB4MASK




/*
Function name       :   init_lcd
Description             :   Function initialize LCD after power up, 
                                   configure necessary ports, and display functionality
Inputs                     :   None
Output                    :   None
Function return       :   None
Testing result          :   PASS Tested on Atmega16
Test conditions       :   Tested on middle speed 8MHz with optimalization set to 02
Function valid         :   Function valid tested full functionality
Function rev.           :   V1_0
Approved by           :   M.Wolowik
Issue date               :   25.11.2015
Problem reports      :   None
*/
void init_lcd(void);




/*
Function name       :   set_position
Description             :   Function set current position in row
Input 1                    :   unsigned char x: range (0 up to 15)
Input 2                    :   unsigned char row: acceptable values  ROW_ONE, ROW_TWO
Output                    :   None
Function return       :   None
Testing result          :   PASS Tested on Atmega16
Test conditions       :   Tested on middle speed 8MHz with optimalization set to 02
Function valid         :   Function valid tested full functionality
Function rev.           :   V1_0
Approved by           :   M.Wolowik
Issue date               :   25.11.2015
Problem reports      :   None
*/
void set_position(unsigned char x, unsigned char row);







/*
Function name       :   spec_char_init
Description             :   Function initialize special characters in CGRAM
Input                       :   Global special_characters_array which define special characters
Output                    :   None
Function return       :   None
Testing result          :   PASS Tested on Atmega16
Test conditions       :   Tested on middle speed 8MHz with optimalization set to 02
Function valid         :   Function valid tested full functionality
Function rev.           :   V1_0
Approved by           :   M.Wolowik
Issue date               :   25.11.2015
Problem reports      :   None
*/
void spec_char_init(void);




/*
Function name       :   clrscr
Description             :   Function realize clear screen functionality
Input                       :   None
Output                    :   None
Function return       :   None
Testing result          :   PASS Tested on Atmega16
Test conditions       :   Tested on middle speed 8MHz with optimalization set to 02
Function valid         :   Function valid tested full functionality
Function rev.           :   V1_0
Approved by           :   M.Wolowik
Issue date               :   25.11.2015
Problem reports      :   None
*/
void clrscr(void);




/*
Function name       :   write_operation
Description             :   Function realize write nibble byte operation
Input 1                    :   unsigned char bt: nibble of byte to write 
                                    (0xXV _ where V is valid nibble of byte, 
                                    X _ whatever high nibble of byte)
Input 2                    :   unsigned char rs: what kind of operation should
                                   be performed (  DIS_INST for instruction and
                                   DIS_DATA for data)
Output                    :   None
Function return       :   None
Testing result          :   PASS Tested on Atmega16
Test conditions       :   Tested on middle speed 8MHz with optimalization set to 02
Function valid         :   Function valid tested full functionality
Function rev.           :   V1_0
Approved by           :   M.Wolowik
Issue date               :   25.11.2015
Problem reports      :   None
*/
void write_operation(unsigned char bt, unsigned char rs);




/*
Function name       :   replace_polish_character
Description             :   Function just replace polish special character
                                   to value of this character defined in special_characters_array
Input 2                    :   unsigned char c: get polish special character like '³', '¹' etc.
Output                    :   None
Function return       :   unsigned char: return index to special_characters_array 
Testing result          :   PASS Tested on Atmega16
Test conditions       :   Tested on middle speed 8MHz with optimalization set to 02
Function valid         :   Function valid tested full functionality
Function rev.           :   V1_0
Approved by           :   M.Wolowik
Issue date               :   25.11.2015
Problem reports      :   None
*/
unsigned char replace_polish_character(unsigned char c);




/*
Function name        :   blinking
Description              :   Function just enable square character blinking
Input                        :   unsigned char on_off: 1 _ blinking on, 0 _ blinking off
Output                     :   None
Function return       :    None 
Testing result          :   PASS Tested on Atmega16
Test conditions       :   Tested on middle speed 8MHz with optimalization set to 02
Function valid         :   Function valid tested full functionality
Function rev.           :   V1_0
Approved by           :   M.Wolowik
Issue date               :   25.11.2015
Problem reports      :   None
*/
void blinking(unsigned char on_off);




/*
Function name       :   lcd_write_string_flash
Description             :   Function write string to be displayed from flash memory
Input                       :   const char *str: string should be specified as
                                   PSTR("Sample string\0") _ it is necessary to add \0 always
                                   Note: To specify string from flash in file where that sting be applied
                                   it is necessary to add  #include <avr/pgmspace.h> library
Output                    :   None
Function return       :   None 
Testing result          :   PASS Tested on Atmega16
Test conditions       :   Tested on middle speed 8MHz with optimalization set to 02
Function valid         :   Function valid tested full functionality
Function rev.           :   V1_0
Approved by           :   M.Wolowik
Issue date               :   25.11.2015
Problem reports      :   None
*/
void lcd_write_string_flash(const char *str);




/*
Function name       :   lcd_write_string_ram
Description             :   Function write string to be displayed from ram memory
Input 1                    :   const char *str _ string should be specified as
                                   "Sample string\0" _ it is necessary to add \0 always
Input 2                    :   unsigned char length: size of string max 15 characters
Output                    :   None
Function return       :   None 
Testing result          :   PASS Tested on Atmega16
Test conditions       :   Tested on middle speed 8MHz with optimalization set to 02
Function valid         :   Function valid tested full functionality
Function rev.           :   V1_0
Approved by           :   M.Wolowik
Issue date               :   25.11.2015
Problem reports      :   None
*/
void lcd_write_string_ram(char *x, unsigned char length);




#endif /* _LCD_HD44780_H */

