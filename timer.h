// pewPewEngine/timer.h

// keeps track of the number of milliseconds passed since getTimeDiff() last called.
// if reaches max value; 65505ms, stays at 65505ms.
uint16_t pewPewTimerDiff;

// used to initialize and configure the interrupt MUST BE CALLED.
void initTimerInterrupt(void);

// use this function to get the time difference in milliseconds compared
// to the last time this function was called.
uint16_t getTimeDiff(void);