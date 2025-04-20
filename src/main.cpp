// Author: Hans Sebastian	 
// Net ID: hanssebastian
// Date: February 21st 2025
// Assignment: Lab 2
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
//----------------------------------------------------------------------//
#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"
#include "switch.h"
#include "timer.h"

//
// Define a set of states that can be used in the state machine using an enum.
//
typedef enum {
	WAIT_PRESS,
	DEBOUNCE_PRESS,
	WAIT_RELEASE,
	DEBOUNCE_RELEASE
} state_t;

volatile state_t state = state_t::WAIT_PRESS;
volatile int dly = 100;

int main() {
	// Initialize necessary components.
	initLED();
	initSwitchPB3();
	initTimer0();
	// Enable interrupt service routines.
	sei();
	/*
	* Implement a state machine in the while loop which achieves the assignment
	* requirements.
	*/
	// Initialize port J for the timer compare A event.
	DDRJ |= (1 << DDJ0);
	PORTJ = 0;
	// Initialize the led mask variable to 0.
	uint8_t num = 0;
	while (1) {
		turnOnLEDWithChar(num);
		switch (state) {
			case state_t::DEBOUNCE_PRESS: {
				// Set state to WAIT_RELEASE.
				state = WAIT_RELEASE;
			} break;
			case state_t::DEBOUNCE_RELEASE: {
				// Change delay based on current delay.
				dly = (dly == 100) ? 200 : 100;
				// Reset back to first state.
				state = state_t::WAIT_PRESS;
			} break;
			default:
				break;
		}
		// Increment then wrap back after num reaches 0x10 (16).
		num = (num + 1) & 0xF; 
		// delay for 100 / 200 ms after.
		delayMs(dly);
	}
	return 0;
}

/* Implement an Pin Change Interrupt which handles the switch being
* pressed and released. When the switch is pressed and released, the LEDs
* change at twice the original rate. If the LEDs are already changing at twice
* the original rate, it goes back to the original rate.
*/
ISR(PCINT0_vect) {
	if (state == state_t::WAIT_PRESS) {
		// Set state to DEBOUNCE_PRESS.
		state = state_t::DEBOUNCE_PRESS;
	} else if (state == state_t::WAIT_RELEASE) {
		// Set state to DEBOUNCE_RELEASE.
		state = state_t::DEBOUNCE_RELEASE;
	}
}

ISR(TIMER0_COMPA_vect) {
	// Clear flag if set
	TIFR0 |= (1 << OCF0A);
	// Set first pin of port J to 1
	PORTJ |= (1 << PORTJ0);
}

// extern "C" void __vector_9(void) __attribute__ ((signal, used, externally_visible)); 
// void __vector_9(void) {
//	 if (state == state_t::WAIT_PRESS) {
//		 state = state_t::DEBOUNCE_PRESS;
//	 } else if (state == state_t::WAIT_RELEASE) {
//		 state = state_t::DEBOUNCE_RELEASE;
//	 }
// }