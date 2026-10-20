
//Pin configuration and software settings
#include "config.h"

#include <TFT_eSPI.h>
#include <PNGdec.h>
#include <SPI.h>

#include "omnitrix_aliens.h"
#include "omnitrix_alien_background.h"
//Start animation with images
#if defined START_ANIMATION_WITH_IMAGES
#include "omnitrix_anim.h"
#endif

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

//Configure LCD pins in User_Setup.h or create your own setup in
//libraries/TFT_eSPI/User_Setups folder and include it in User_Setup_Select.h
/*
#define TFT_MOSI 11 // In some display driver board, it might be written as "SDA" and so on.
#define TFT_SCLK 12
#define TFT_CS   10  // Chip select control pin
#define TFT_DC   9  // Data Command control pin
#define TFT_RST  14  // Reset pin (could connect to Arduino RESET pin)
#define TFT_BL   40  // LED back-light
*/

#define MAX_IMAGE_WDITH 240  // Set rendering line buffer lengths for image

#define ALIEN_LAST_INDEX 11  //0...11 = 12 Total aliens

//Time Variables
#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define DEEP_SLEEP_TIMER 5        // 5 sec
uint32_t g_start;                   //timer for deep sleep

//Time definitions for demo and default mode
#if defined DEMO_ENABLED
#define TRANSFORMATION_TIME 10     //10 sec
#define OMNITRIX_RECHARGE_TIME 10  //10 sec
#else
#define TRANSFORMATION_TIME 60     //1 min
#define OMNITRIX_RECHARGE_TIME 60  //1 min
#endif

//Initialise timer variables as DEMO (in seconds)
// Up to 65535 seconds = 1092.25 min = 18.2 hours of recharging/transformation
RTC_DATA_ATTR uint16_t g_transform_time_val = TRANSFORMATION_TIME;    // Transformation Time Variable
RTC_DATA_ATTR uint16_t g_recharge_time_val = OMNITRIX_RECHARGE_TIME;  // Recharging Time Variable

//Time variables that are saved in deep sleep mode
RTC_DATA_ATTR uint32_t g_transformation_start_time;
RTC_DATA_ATTR uint32_t g_recharging_start_time;
RTC_DATA_ATTR uint16_t g_transformation_start_time_offset;
RTC_DATA_ATTR uint16_t g_recharging_start_time_offset;

/* LCD Colours
RGB to HEX: http://www.rinkydinkelectronics.com/calc_rgb565.php
HEX to RGB565: https://rgbcolorpicker.com/565
green RGB: 160, 225, 58 = 0xA0E13A = 0xA707 in RGB565
          : 143, 219, 53 = 0x8FDB34 = 0x8ec6
          : 168, 226, 88 = 0xA8E258 = 0xa70b
red RGB: 199, 0, 3 = 0xC70003 = 0xC000 in RGB565
        :229, 28, 34 = 0xE51C22 = 0xe0e4
gray RGB: 171, 171, 171 = 0xABABAB = 0xAD55 in RGB565
        : 99, 97, 98 = 0x636162 = 0x630c in RGB565
        : 101, 94, 112 = 0x655E70 = 0x62ee
        : 135, 133, 134 = 0x878586 = 0x8430
*/

#define OMNITRIX_GREEN 0xA707
#define OMNITRIX_RED 0xC000
#define OMNITRIX_GRAY 0xAD55

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

// Input states
#if defined POP_UP_BUTTONS_ENABLED
//Variables to keep track of the timing of recent interrupts are inside them for now
//This interrupt timer uses millis() instead of Epoch so it can be smaller
//since it will often reset because of sleep mode.
//Up to 18.2 hours of being awake and buttons functioning normaly, after sleep values reset
//volatile uint16_t interruptTime = 0;
//volatile uint16_t lastInterruptTime = 0;
volatile bool g_start_button_state = 0;        //State of start button
volatile bool g_select_button_state = 0;  //State of select button
#endif
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED || defined ROTARY_ENCODER_ENABLED
//Similar with pop up buttons, use of interrupts
volatile bool g_right_state = 0;  //State of right
volatile bool g_left_state = 0;   //State of left
#endif
// Types of inputs
typedef enum : uint8_t { // Up to 255 inputs
    INPUT_NONE,
    INPUT_START_BUTTON,
    INPUT_SELECT_BUTTON,
    INPUT_RIGHT,
    INPUT_LEFT
} Input;


//Display variables
PNG png;  // PNG decoder instance

TFT_eSPI tft = TFT_eSPI();

void show_symbols();
void show_alien();
int png_draw(PNGDRAW *pDraw);

#if defined POP_UP_BUTTONS_ENABLED
void IRAM_ATTR button_interrupt();
void IRAM_ATTR select_button_interrupt();
#endif
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED
void IRAM_ATTR right_button_interrupt();
void IRAM_ATTR left_button_interrupt();
#elif defined ROTARY_ENCODER_ENABLED
void IRAM_ATTR rot_encoder_interrupt();
#endif
