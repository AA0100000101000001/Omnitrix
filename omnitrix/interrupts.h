
#ifndef O_INTERRUPTS
#define O_INTERRUPTS

#include <Arduino.h>
#include "config.h"
#include "omnitrix_types.h"


// Input states
#if defined POP_UP_BUTTONS_ENABLED
//Variables to keep track of the timing of recent interrupts are inside them for now
//This interrupt timer uses millis() instead of Epoch so it can be smaller
//since it will often reset because of sleep mode.
//Up to 18.2 hours of being awake and buttons functioning normaly, after sleep values reset
//volatile uint16_t interruptTime = 0;
//volatile uint16_t lastInterruptTime = 0;
extern volatile bool g_start_button_state;        //State of start button
extern volatile bool g_select_button_state;  //State of select button
#endif

#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED || defined ROTARY_ENCODER_ENABLED
//Similar with pop up buttons, use of interrupts
extern volatile bool g_right_state;  //State of right
extern volatile bool g_left_state;   //State of left
#endif


//initialize inputs and interrupts
void init_input();

#if defined POP_UP_BUTTONS_ENABLED
void IRAM_ATTR button_interrupt();
void IRAM_ATTR select_button_interrupt();
#endif

//Micro Switches alternative to rotary encoder
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED
void IRAM_ATTR right_button_interrupt();
void IRAM_ATTR left_button_interrupt();
//Rotary Encoder
#elif defined ROTARY_ENCODER_ENABLED
void IRAM_ATTR rot_encoder_interrupt();
#endif

Input check_input();

//Function from omnitrix_time
extern void reset_timer();
//Function from sound
extern void play_sound(int16_t s);


#endif