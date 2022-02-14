/*
 * LibPort.h
 *
 * Created: 23-7-2014 13:42:52
 *  Author: Gerard
 */ 


#ifndef PORTCLASS_LIB_H_
#define PORTCLASS_LIB_H_

#include <inttypes.h>

class portClass{

public:
	portClass(void);

	// Port functions
	void InitializePort(char Register, uint8_t OutputMask, uint8_t InitialOutputValue);
	void SetOutput(uint8_t OutputValue);
	uint8_t GetInput(void);



private:
//	bool Valid = false;
//	bool Error = false;
//	bool IsPin; // Indicate Pin Functions active else Port functions active
	
	unsigned char PortMask;

//	volatile uint8_t *DDR_Register;
	volatile uint8_t *PORT_Register;
	volatile uint8_t *PIN_Register;
	
	
private:

};


#endif /* PORTCLASS_LIB_H_ */