// Description: This file implements turnOnLED and initLED to control
// the LEDs.
//----------------------------------------------------------------------//


#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

// Initialize PA0, PA1, PA2, and PA3 to outputs
void initLED(){
	// Set all the necessary port bits (PORTA0 - PORTA3) to 1
    DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3);
}

// This must be one line of code.
// In this function you will be giving a number `num` which will be represented
// in binary by four LEDs. You must effectively assign the lowest four bits of
// `num` to the appropriate bits of `PORTA`.
void turnOnLEDWithChar(unsigned char num) {
    // Zero first 4 bits of PORTA register using &
    // Lastly set the same bits using the new value of num 
    // (4 most significant bits of `num` is cleared in `main`)
    PORTA = (PORTA & 0xF0) | num;
}
