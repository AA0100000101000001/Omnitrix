
#ifndef O_TYPES
#define O_TYPES

#include <stdint.h>

// Types of inputs
typedef enum : uint8_t { // Up to 255 inputs
    INPUT_NONE,
    INPUT_START_BUTTON,
    INPUT_SELECT_BUTTON,
    INPUT_RIGHT,
    INPUT_LEFT
} Input;

//Types of modes
typedef enum : uint8_t { // Up to 255 modes
    START_MODE,
    SELECT_ALIEN_MODE,
    TRANSFORMED_MODE,
    RECHARGING_MODE
} Mode;

extern RTC_DATA_ATTR uint8_t g_mode;           // Up to 255 modes

#endif