/**
 * @author  Lukas Herudek
 * @email   lukas.herudek@gmail.com
 * @version v1.0
 * @ide     Atmel Studio 6.2
 * @license GNU GPL v3
 * @brief   UART library for AVR
 * @verbatim
   ----------------------------------------------------------------------
    Copyright (C) Lukas Herudek, 2018
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.
	
	<http://www.gnu.org/licenses/>
@endverbatim
 */

#ifndef UART_H
#define UART_H

#define F_CPU				1000000UL
#define UART_BAUDRATE			19200UL

#define UART_TIMEOUT			10000UL //cca in us

#define UART_OK			0x01
#define UART_ERROR		0x00

void UART_init();
void UARTtx(char data);
unsigned char UARTrx(unsigned char *data);
void UARTstring(char* TX_string);
//Add for float numbers: -Wl,-u,vfprintf -lprintf_flt -lm --- Toolchain > Linker > Misc..
void UARTstringF(char *data, ...);
void UARTreceiver();

#endif /* UART_H */
