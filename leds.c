// pewPewEngine/leds.c
#include "cpu_speed.h"
#include "leds.h"

void initLEDs(void){
	DDRB |= (1 << LEFT_LED);
	DDRB |= (1 << RIGHT_LED);
}

void setLED(int LED, int on){
	// Can only turn on LEFT_LED and RIGHT_LED
	if(LED == LEFT_LED || LED == RIGHT_LED){
		if(on){
			PORTB |= (1 << LED);
		} else {
			PORTB &= ~(1 << LED);
		}
	}
}

void toggleLED(int LED){
	PORTB ^= (1 << LED);
}
