
#ifndef O_MODES
#define O_MODES

#include <Arduino.h>
#include "config.h"
#include "omnitrix_types.h"
#include "omnitrix_mode_transitions.h"

//Mode 1
//First state, Omnitrix is in start mode
void start_mode(Input in);

//Mode 2
//Omnitrix is in select alien mode
void select_alien_mode(Input in);

//Mode 3
//Function for transformation
void transformed_mode(Input in);

//Mode 4
//Recharge mode
void recharge_mode();

#endif