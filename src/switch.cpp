// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

//
// Initializes pull-up resistor on PB3 and sets it into input mode
//
void initSwitchPB3(){
    // Set pin D11 (B3) to input mode
    DDRB &= ~(1 << DDB3);
    // Enable pull-up resistor on pin D11 (B3)
    PORTB |= (1 << PORTB3);

    // Enable interrupt on port B
    PCICR |= (1 << PCIE0);
    // Set pin D11 (B3) as interrupt source
    PCMSK0 |= (1 << PCINT3);
}
