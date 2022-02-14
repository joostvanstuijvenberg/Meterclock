/*
 * servoClass_lib.h
 *
 * Created: 28-3-2016 10:11:48
 *  Author: Gerard Harkema
 */ 


#ifndef SERVOCLASS_LIB_H_
#define SERVOCLASS_LIB_H_

#include "Arduino.h"
#include "pinClass_lib.h"


#define DEFAULT_MIN_PULSE_TIME_US		700			// Default Minimum pulse time in usec
#define DEFAULT_MAX_PULSE_TIME_US		2500		// Default Maximum pulse time in usec
#define DEFAULT_PULSE_TIME_US			((DEFAULT_MAX_PULSE_TIME_US + DEFAULT_MIN_PULSE_TIME_US) / 2) 		// Default pulse time in usec
#define CYCLE_TIME						20000		// Time the PWM cycles
#define MAX_DEGREES						180			// Maximum turn of the servo

#define SERVO_ERROR						-1
#define SERVO_NO_ERROR					0



class servoClass{

public:	
	int16_t init(uint8_t pin);
	int16_t setPosition(uint16_t highTimeMicroseconds);
	int16_t setPositionDegrees(uint16_t Degrees);
	int16_t setMinPulseTime(uint16_t highTimeMicroseconds);
	int16_t setMaxPulseTime(uint16_t highTimeMicroseconds);	

	// This is the time since the last rising edge in units of 0.5us.
	uint16_t time = 0;

	// This is the pulse width we want in units of 0.5us.
	uint16_t highTime = DEFAULT_PULSE_TIME_US * 2;

	// This is true if the servo pin is currently high.
	bool pinLevelHigh = false;

	uint16_t minPulseTimeMicroseconds = DEFAULT_MIN_PULSE_TIME_US;
	uint16_t maxPulseTimeMicroseconds = DEFAULT_MAX_PULSE_TIME_US;
	pinClass pin;
	
};


extern servoClass servo;


#endif /* SERVOCLASS_LIB_H_ */