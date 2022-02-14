#include <Arduino.h>
#include "pinClass_lib.h"

int main(void)
{
	
	pinClass L_pin = pinClass(LED_BUILTIN, OUTPUT);
	init();
	Serial.begin(9600);
	Serial.println("Hello World.");

	while(true) {
		L_pin.toggle();
		delay(500);		
	}
	
	return 0;
}



