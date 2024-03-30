

//Choose pin configuration
//#include "User_Setup/config_CUSTOM.h" //Use your own configuration
#include "User_Setup/config_ESP32_S2_PINOUT.h"  //Esp32-s2 Dev Board
//#include "User_Setup/config_ESP32_S3_PINOUT.h" //Esp32-s3 Dev Board

#include <TFT_eSPI.h>
#include <PNGdec.h>
#include "SPI.h"
//#include <PCM.h>

#if defined SOUND_ENABLED
#include <DFRobot_DF1201S.h>
#endif

#include "omnitrix_aliens.h"
#include "omnitrix_alien_backround.h"
#include "omnitrix_anim.h"

//Input pins
#if defined BUTTONS_ENABLED
  #define START_BUTTON_PIN CONFIG_START_BUTTON_PIN //Start button
  #define RIGHT_BUTTON_PIN CONFIG_RIGHT_BUTTON_PIN //Right button
  #define LEFT_BUTTON_PIN CONFIG_LEFT_BUTTON_PIN //Left button
  #define SELECT_BUTTON_PIN CONFIG_SELECT_BUTTON_PIN //Select button
#endif

//LED pins
#if defined RGB_LEDS_ENABLED
  #define RGB_R_PIN CONFIG_RGB_LED_R //Red
  #define RGB_G_PIN CONFIG_RGB_LED_G //Green
  #define RGB_B_PIN CONFIG_RGB_LED_B //Blue
#endif

//Sound pins
#if defined SOUND_ENABLED
  #define RXD1 CONFIG_RXD1 //RX1
  #define TXD1 CONFIG_RXD1 //TX1
#endif

//Configure LCD pins in User_Setup.h or create your own setup in 
//libraries/TFT_eSPI/User_Setups folder and include it in User_Setup_Select.h
/*
#define TFT_MOSI 35 // In some display driver board, it might be written as "SDA" and so on.
#define TFT_SCLK 36
#define TFT_CS   34  // Chip select control pin
#define TFT_DC   26  // Data Command control pin
#define TFT_RST  33  // Reset pin (could connect to Arduino RESET pin)

//#define TFT_BL   38  // LED back-light
*/

#define MAX_IMAGE_WDITH 240 // Set rendering line buffer lengths for image

#define ALIEN_NUMBER 11 //0...11 = 12

//Time Variables
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define DEEP_SLEEP_TIMER 5 // 5 sec
uint32_t start; //timer for deep sleep

//Time definitions for demo and default mode
#define TRANSFORMATION_TIME_DEMO 20 //20 sec
#define OMNITRIX_RECHARGE_TIME_DEMO 20 //20 sec
#define TRANSFORMATION_TIME_DEFAULT 60 //1 min
#define OMNITRIX_RECHARGE_TIME_DEFAULT 60 //1 min

//Initialise timer variables as DEMO (in seconds)
// Up to 65535 seconds = 1092.25 min = 18.2 hours of recharging/transformation
RTC_DATA_ATTR uint16_t transform_time_val = TRANSFORMATION_TIME_DEMO; // Transformation Time Variable
RTC_DATA_ATTR uint16_t recharge_time_val = OMNITRIX_RECHARGE_TIME_DEMO; // Recharging Time Variable

//Time variables that are saved in deep sleep mode
RTC_DATA_ATTR uint32_t transformation_start_time;
RTC_DATA_ATTR uint32_t recharging_start_time;
RTC_DATA_ATTR uint16_t transformation_start_time_offset;
RTC_DATA_ATTR uint16_t recharging_start_time_offset;

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

#define GREEN_LED_R 168
#define GREEN_LED_G 226
#define GREEN_LED_B 88
#define RED_LED_R 229
#define RED_LED_G 28
#define RED_LED_B 34

//Variables that are saved in deep sleep mode
RTC_DATA_ATTR uint16_t bootCount = 0;  // Up to 65535 reboots before overflow
RTC_DATA_ATTR uint8_t alienNo; // Up to 255 aliens
RTC_DATA_ATTR uint8_t mode; // Up to 255 modes

#if defined BUTTONS_ENABLED
//Variables to keep track of the timing of recent interrupts
//This button timer uses millis() instead of Epoch so it can be smaller 
//since it will often reset because of sleep mode.
//Up to 18.2 hours of being awake and buttons functioning normaly
volatile uint16_t button_time = 0;  
volatile uint16_t last_button_time = 0; 

//Input states
volatile bool buttonState = 0; //State of start button
volatile bool rightState = 0; //State of right
volatile bool leftState = 0; //State of left
volatile bool selectbuttonState = 0; //State of select button
#endif


//Display variables
PNG png; // PNG decoder instance

TFT_eSPI tft = TFT_eSPI();

//DFT sound
#if defined SOUND_ENABLED
  DFRobot_DF1201S DF1201S;
  bool mute = false;
#endif

void ShowSymbols();
void ShowAlien();
void pngDraw(PNGDRAW *pDraw);
