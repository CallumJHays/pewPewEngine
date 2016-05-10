// pewPewEngine/timer.c

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint16_t pewPewTimerDiff = 0;

void initTimerInterrupt(void){
    // Note: the following code makes very little sense to me. 
    // This was provided by my lecturer without reference to a 
    // data sheet and therefore I have little to no notion what
    // each bit bashing operation is doing.
	//Set to Normal Timer Mode using TCCR0B
    TCCR0B &= ~((1<<WGM02));
    
    //Set Prescaler using TCCR0B, using Clock Speed find timer speed = 1/(ClockSpeed/Prescaler)
    //Prescaler = 1024
    //Timer Speed = 128 nano seconds
    //Timer Overflow Speed = 32640 nano seconds (Timer Speed * 255) - (255 since 8-bit timer)
    TCCR0B |= (1<<CS02)|(1<<CS00);
    TCCR0B &= ~((1<<CS01));	
    
    //enable interrupt overflow
    TIMSK0 |= (1 << TOIE0);
	
    //Ensure to enable global interrupts as well.
    sei();

    pewPewTimerDiff = 0;
}

uint16_t getTimeDiff(void){
    // temp variable
	uint16_t toReturn = pewPewTimerDiff;
	pewPewTimerDiff = 0;
	return toReturn;
}

ISR(TIMER0_OVF_vect){
	// time passed = 32640 microseconds = 33 milliseconds
    // 65505ms = max value for pewPewTimer
    if(pewPewTimerDiff < 65505){
        // increment timer by 33ms
        pewPewTimerDiff += 33;
    }
}