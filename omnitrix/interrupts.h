
#ifndef O_INTERRUPTS
#define O_INTERRUPTS

#include <Arduino.h>
#include "config.h"
#include "info_print.h"
#include "omnitrix_types.h"


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