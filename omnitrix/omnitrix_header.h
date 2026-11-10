
//Pin configuration and software settings
#include "config.h"

#include "omnitrix_time.h"
#include "interrupts.h"
//#include "omnitrix_modes.h"
//#include "omnitrix_mode_transitions.h"
#include "omnitrix_display.h"


// Types of inputs
// typedef enum : uint8_t { // Up to 255 inputs
//     INPUT_NONE,
//     INPUT_START_BUTTON,
//     INPUT_SELECT_BUTTON,
//     INPUT_RIGHT,
//     INPUT_LEFT
// } Input;


//Sound definition
#if defined SOUND_ENABLED

#if defined SOUND_MUTED_IN_BOOTING
bool g_mute = true;
#else
bool g_mute = false;
#endif

//DFT sound
#if defined SOUND_DFPLAYER_PRO_ENABLED
#include <DFRobot_DF1201S.h>
DFRobot_DF1201S DF1201S;
#endif

#endif



//LED colours
#if defined LEDS_ENABLED
#define GREEN_LED_R 168
#define GREEN_LED_G 226
#define GREEN_LED_B 88
#define RED_LED_R 229
#define RED_LED_G 28
#define RED_LED_B 34
#endif

//Variables that are saved in deep sleep mode
RTC_DATA_ATTR bool g_first_boot = true;  // For initialization
RTC_DATA_ATTR uint8_t g_alien_n;        // Up to 255 aliens

RTC_DATA_ATTR uint8_t g_mode;           // Up to 255 modes
