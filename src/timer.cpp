// Description: This file implements functions that utilize the timers
//----------------------------------------------------------------------//

#include "timer.h"

// Initialize timer0, you should not turn the timer on here.
// You will need to use CTC mode
void initTimer0() {
	TCCR0B = 0; // Turn off timer0
	TCCR0A |= (1 << WGM01); // Enable CTC
	OCR0A = 249;
	TIMSK0 |= (1 << OCIE0A); // Enable timer0 overflow interrupt
}

// This delays the program an amount specified by unsigned int `delay`.
// Use timer 0. Keep in mind that you need to choose your prescalar wisely
// such that your timer is precise to 1 millisecond and can be used for
// 100-200 milliseconds
//
void delayMs(unsigned int delay) {
	// Clear PORTJ0 bit before turning on timer
	PORTJ &= ~(1 << PORTJ0);
	TCCR0B |= (1 << CS01) | (1 << CS00); // Set prescaler to 64
	for (unsigned int count = 0; count < delay;) {
		// Wait until the timer overflows and PINJ0 is set to 1
		while (!(PINJ & (1 << PINJ0)));
		// Turn off PORTJ0 bit to reuse later
		PORTJ &= ~(1 << PORTJ0);
		// Increment `count` by 1 when the timer has been cleared
		count++;
	}
	// Clear PORTJ0 bit as a redundancy
	PORTJ &= ~(1 << PORTJ0);
	TCCR0B = 0; // Turn off timer0 
	TCNT0 = 0; // Clear timer counter just in case
	TIFR0 |= (1 << OCF0A); // Clear timer compare flag just in case
}
