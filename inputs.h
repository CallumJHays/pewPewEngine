// pewPewEngine/inputs.h
// TODO: Change to a struct / interrupt model
#ifndef __PEW_PEW_INPUTS__
#define __PEW_PEW_INPUTS__

// use definition ints instead of return strings to save memory
#define JOYSTICK_UP 0
#define JOYSTICK_DOWN 1
#define JOYSTICK_LEFT 2
#define JOYSTICK_RIGHT 3
#define JOYSTICK_NEUTRAL 4

// initialise input registers CALL BEFORE USING BELOW FUNCTIONS
void initInputs(void);

// get an int representing the joystick's current position.
// above definitions define these positions
int getJoystickPosition(void);

// return 1 if joystick is center is pressed, otherwise 0
int joystickPressed(void);

// return 1 if left button is currently pressed, otherwise 0
int leftButtonPressed(void);

// return 1 if right button is currently pressed, otherwise 0
int rightButtonPressed(void);

#endif /* __PEW_PEW_INPUTS__ */