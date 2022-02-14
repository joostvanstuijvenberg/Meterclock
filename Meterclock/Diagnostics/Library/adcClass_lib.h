/*
 * adcClass_lib.h
 *
 * Created: 24-3-2016 20:20:55
 *  Author: Gerard Harkema
 */ 


#ifndef ADCCLASS_LIB_H_
#define ADCCLASS_LIB_H_

#include <inttypes.h>

class adcClass{

public:

	adcClass();
	
	void startConversion(uint8_t pin);
	bool conversionBusy(void);
	uint16_t getValue();
	void analogReference(uint8_t mode);
		
protected:
	uint8_t analog_reference;	
};

extern adcClass adc;

#endif /* ADCCLASS_LIB_H_ */