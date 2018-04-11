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

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include "UART.h"


ISR(USART_RX_vect) //RX Interrupt
{
	UARTreceiver();
}


void UART_init()
{
	DDRD |= (1<<PORTD1);//TX
	DDRD &= (~(1<<PORTD0));//RX
	PORTD |= (1<<PORTD1) | (1<<PORTD0);

	UBRR0  = (F_CPU/8/UART_BAUDRATE)-1;
	UCSR0A = (1<<U2X0);//double UART speed
	UCSR0B = (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);//enable RX and TX, enable RX interrupt
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);//8N1
}

/**************************************************************************/

void UARTtx(char data)
{
	unsigned long wait=0;
	while(!(UCSR0A&(1<<UDRE0)))//wait for empty transmit buffer
	{
		_delay_us(1);
		wait++;
		if(wait>=UART_TIMEOUT)	return;
	}
	UDR0 = data;//put data into buffer, sends the data
}

unsigned char UARTrx(unsigned char *data)
{
	unsigned long wait=0;

	while(!(UCSR0A&(1<<RXC0)))
	{
		_delay_us(1);
		wait++;
		if(wait>=UART_TIMEOUT)	return UART_ERROR;
	}
	*data = UDR0;//get and return received data from buffer
	return UART_OK;
}

void UARTstring(char* TX_string)
{
	while(*TX_string)	UARTtx(*TX_string++);
}

//Add for float numbers: -Wl,-u,vfprintf -lprintf_flt -lm --- Toolchain > Linker > Misc..
void UARTstringF(char *data, ...)
{
	char char_buffer[260] = {0};
	unsigned char i_counter=0;
	int pocet_znaku=sizeof(char_buffer)/sizeof(char_buffer[0]);
	va_list pArgs;
	va_start(pArgs, data);
	vsnprintf(char_buffer, pocet_znaku - 1, data, pArgs);
	va_end(pArgs);
	
	while(char_buffer[i_counter])
	{
		UARTtx(char_buffer[i_counter++]);
	}
	UARTtx('\n');
}


void UARTreceiver() 
{
	//unsigned char Data[1] = {0};
}


