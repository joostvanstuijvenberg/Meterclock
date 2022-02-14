/*
 * servoClass_lib.cpp
 *
 * Created: 28-3-2016 10:11:12
 *  Author: Gerard Harkema
 */ 

#include "Arduino.h"
#include "servoClass_lib.h"

servoClass servo;

// This ISR runs after Timer 2 reaches OCR2A and resets.
// In this ISR, we set OCR2A in order to schedule when the next
// interrupt will happen.
// Generally we will set OCR2A to 255 so that we have an
// interrupt every 128 us, but the first two interrupt intervals
// after the rising edge will be smaller so we can achieve
// the desired pulse width.
ISR(TIMER2_COMPA_vect)
{
	// The time that passed since the last interrupt is OCR2A + 1
	// because the timer value will equal OCR2A before going to 0.
	servo.time += OCR2A + 1;
	
	static uint16_t highTimeCopy = 3000;
	static uint8_t interruptCount = 0;
	
	if(servo.pinLevelHigh)
	{
		if(++interruptCount == 2)
		{
			OCR2A = 255;
		}
		
		// The servo pin is currently high.
		// Check to see if is time for a falling edge.
		// Note: We could == instead of >=.
		if(servo.time >= highTimeCopy)
		{
			// The pin has been high enough, so do a falling edge.
			// Set output port low


			servo.pinLevelHigh = false;
			servo.pin.digWrite(servo.pinLevelHigh);
			interruptCount = 0;
		}
	}
	else
	{
		// The servo pin is currently low.
		
		if(servo.time >= 40000)
		{
			// We've hit the end of the period (20 ms),
			// so do a rising edge.
			highTimeCopy = servo.highTime;
			// Set output port high

			servo.pinLevelHigh = true;
			servo.pin.digWrite(servo.pinLevelHigh);
			servo.time = 0;
			interruptCount = 0;
			OCR2A = ((highTimeCopy % 256) + 256)/2 - 1;
		}
	}
}

int16_t servoClass::init(uint8_t pin)
{

	this->pin.Mode(pin, OUTPUT);
	this->pin.digWrite(servo.pinLevelHigh);
	
	// Turn on CTC mode.  Timer 2 will count up to OCR2A, then
	// reset to 0 and cause an interrupt.
	TCCR2A = (1 << WGM21);
	// Set a 1:8 prescaler.  This gives us 0.5us resolution.
	TCCR2B = (1 << CS21);
	
	// Put the timer in a good default state.
	TCNT2 = 0;
	OCR2A = 255;
	
	TIMSK2 |= (1 << OCIE2A);  // Enable timer compare interrupt.
//	sei();   // Enable interrupts.
	return SERVO_NO_ERROR;
}


int16_t servoClass::setPosition(uint16_t highTimeMicroseconds)
{
	if(highTimeMicroseconds < minPulseTimeMicroseconds) return SERVO_ERROR;
	if(highTimeMicroseconds > maxPulseTimeMicroseconds) return SERVO_ERROR;
	
	TIMSK2 &= ~(1 << OCIE2A); // disable timer compare interrupt
	servo.highTime = highTimeMicroseconds * 2;
	TIMSK2 |= (1 << OCIE2A); // enable timer compare interrupt
	
	return SERVO_NO_ERROR;
}

int16_t servoClass::setPositionDegrees(uint16_t Degrees){
	
	uint16_t high_time_us;
	uint16_t time_span;
	double time_resolution;
	
	if(Degrees > MAX_DEGREES) return SERVO_ERROR;
	
	// Calculate highTimeMicroseconds for actual degrees
	time_span = maxPulseTimeMicroseconds - minPulseTimeMicroseconds;
	time_resolution = (time_span * 1.0) / 180.0;
	high_time_us = (uint16_t)(time_resolution * Degrees) + minPulseTimeMicroseconds;
	
	return this->setPosition(high_time_us);
}

int16_t servoClass::setMinPulseTime(uint16_t highTimeMicroseconds){

	if(highTimeMicroseconds > CYCLE_TIME) return SERVO_ERROR;

	minPulseTimeMicroseconds = highTimeMicroseconds;
	return SERVO_NO_ERROR;
}

int16_t servoClass::setMaxPulseTime(uint16_t highTimeMicroseconds){
	
	if(highTimeMicroseconds > CYCLE_TIME) return SERVO_ERROR;

	maxPulseTimeMicroseconds = highTimeMicroseconds;
	return SERVO_NO_ERROR;
}