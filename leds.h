// pewPewEngine/leds.h
#ifndef __PEW_PEW_LEDS__
#define __PEW_PEW_LEDS__

// define to make coding easier
#define LEFT_LED 2
#define RIGHT_LED 3

// initialise LED registers. CALL BEFORE USING FUNCTIONS BELOW
void initLEDs(void);

// set LED at pin <int LED> to 1 or 0 <int on>
void setLED(int LED, int on);

// toggle the LED at pin <int LED>
void toggleLED(int LED);

#endif /* __PEW_PEW_LEDS__ */