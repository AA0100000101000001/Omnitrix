
#ifndef O_MODE_TRANSITIONS
#define O_MODE_TRANSITIONS

#include <Arduino.h>
#include "config.h"
#include "omnitrix_types.h"
#include "omnitrix_display.h"
#include "omnitrix_time.h"


extern RTC_DATA_ATTR uint8_t g_mode;           // Up to 255 modes

//Function from omnitrix_time
extern void reset_timer();

//Start mode to Alien Selection mode begining
void mode1to2start();

//Start mode to Alien Selection mode end
void mode1to2finish();

//Alien Selection mode to Start mode
void mode2to1();

//Alien Selection mode to Transformation mode before delay/animation
void mode2to3start();

//Alien Selection mode to Transformation mode after delay/animation
void mode2to3finish();

//Transformation mode to Recharging mode
void mode3to4();

//Transformation mode to Start mode
void mode3to1();

//Recharging mode to Start mode
void mode4to1();


#endif