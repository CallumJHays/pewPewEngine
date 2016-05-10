// pewPewEngine/inputs.c
#include "cpu_speed.h"
#include "inputs.h"

void initInputs(void){
	// joystick ports
	DDRD &= ~(1 << 1); // UP - PD1
	DDRB &= ~(1 << 7); // DOWN - PB7
	DDRB &= ~(1 << 1); // LEFT - PB1
	DDRD &= ~(1 << 0); // RIGHT - PD0
	DDRB &= ~(1 << 0); // CENTER - PB0

	// button ports
	DDRF &= ~(1 << 5); // LEFT PF5
	DDRF &= ~(1 << 6); // RIGHT PF6

	// TODO thumbwheels
}

int getJoystickPosition(void){
	// if up
	if(PIND >> 1 & 1){
		return JOYSTICK_UP;
	}
	// if down
	else if(PINB >> 7 & 1){
		return JOYSTICK_DOWN;
	}
	// if left
	else if(PINB >> 1 & 1){
		return JOYSTICK_LEFT;
	}
	// if right
	else if(PIND >> 0 & 1){
		return JOYSTICK_RIGHT;
	}
	// must be in neutral
	return JOYSTICK_NEUTRAL;
}

int joystickPressed(void){
	return PINB >> 0 & 1;
}

int leftButtonPressed(void){
	return PINF >> 6 & 1;
}

int rightButtonPressed(void){
	return PINF >> 5 & 1;
}

// TODO: thumbwheels
