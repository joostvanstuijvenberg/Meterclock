/*
 * pinClass_lib.cpp
 *
 * Created: 24-3-2016 19:41:27
 *  Author: Gerard Harkema Harkema
 */ 
#include <Arduino.h>
#include "pinClass_lib.h"


pinClass::pinClass(void){
	this->pin = ~0;
}

pinClass::pinClass(uint8_t pin, uint8_t mode){
	this->pin = pin;
	this->pin_mode = mode;
	pinMode(this->pin, this->pin_mode);
	this->value = digitalRead(this->pin);
		
}


void pinClass::mode(uint8_t pin, uint8_t mode){
	this->pin = pin;
	this->pin_mode = mode;
	pinMode(this->pin, this->pin_mode);
	this->value = digitalRead(this->pin);
}

void pinClass::write(uint8_t val){
	this->value = val;
	digitalWrite(this->pin, this->value);
	
}

int pinClass::read(void){
	this->value = digitalRead(this->pin);
	return this->value;
}

void pinClass::toggle(void){
	this->value = this->value ? LOW : HIGH;
	digitalWrite(this->pin, this->value);
}