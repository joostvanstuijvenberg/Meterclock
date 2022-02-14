/*
 * pinClass_lib.h
 *
 * Created: 24-3-2016 19:41:51
 *  Author: Gerard Harkema Harkema
 */ 


#ifndef PINCLASS_LIB_H_
#define PINCLASS_LIB_H_

#include <inttypes.h>

class pinClass{

private:
	uint8_t pin;
	uint8_t pin_mode;
	uint8_t value;

public:
	pinClass(void);
	pinClass(uint8_t pin, uint8_t mode);

	void mode(uint8_t pin, uint8_t mode);
	void write(uint8_t val);
	void toggle(void);
	int read(void);
};



#endif /* PINCLASS_LIB_H_ */