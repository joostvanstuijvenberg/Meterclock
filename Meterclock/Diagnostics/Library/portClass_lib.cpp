/*
 * portClass_lib.cpp
 *
 * Created: 23-5-2014 13:42:22
 *  Author: Gerard
 */ 


#include "wiring_private.h"
#include "pins_arduino.h"
//#include <Arduino.h>
//#include <inttypes.h>
//#include <avr/io.h>
#include "portClass_lib.h"

uint8_t PortBUsage = 0;
uint8_t PortCUsage = 0;
uint8_t PortDUsage = 0;

portClass::portClass(void){
}


void portClass::InitializePort(char Register, uint8_t OutputMask, uint8_t InitialOutputValue){


	switch (Register)
	{
		case 'b':
		case 'B':
			if(PortBUsage & PortMask){
//				Valid = false;
//				Error = true;
				return;
			}
			DDRB = OutputMask;
			PORT_Register = &PORTB;
			PIN_Register = &PINB;
			PortBUsage |= PortMask;
			break;
		case 'c':
		case 'C':
			if(PortBUsage & PortMask){
//				Valid = false;
//				Error = true;
				return;
			}
			DDRC = OutputMask;
			PORT_Register = &PORTC;
			PIN_Register = &PINC;
			PortCUsage |= PortMask;
			break;
		case 'd':
		case 'D':
			if(PortDUsage & PortMask){
//				Valid = false;
//				Error = true;
				return;
			}
			DDRD = OutputMask;
			PORT_Register = &PORTD;
			PIN_Register = &PIND;
			PortDUsage |= PortMask;
			break;
//		default:
//		Valid = false;
	}
	*PORT_Register = (InitialOutputValue & OutputMask);
}



void portClass::SetOutput(uint8_t OutputValue){
	*PORT_Register = OutputValue & PortMask;
}


uint8_t portClass::GetInput(void){
	return (*PIN_Register & PortMask);
}

