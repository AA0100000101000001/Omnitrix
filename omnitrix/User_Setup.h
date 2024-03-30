
//Pin configuration
//Edit User_Setups/config_DEFAULT to create your own configuration or uncomment your preferred configuration
#include "User_Setups/config_ESP32_S2_PINOUT.h"
//#include "User_Setups/config_ESP32_S3_PINOUT.h"
//#include "User_Setups/config_ESP32_S3_TOUCH_LCD_1_28.h"


//Software Settings

//Choose only one type of animation
//1. Start animation with images
#define START_ANIMATION_WITH_IMAGES //Has memory leaks
//2. Hard coded start animation
//#define START_ANIMATION_WITHOUT_IMAGES //Not finished

//Choose if sound will be muted in booting
//#define SOUND_MUTED_IN_BOOTING //Only if sound is enabled

//Choose if demo is enebled
//#define DEMO_ENABLED
//Choose only one type of demo
//1. Demo automated display of the features that can go out of that state when a button is pressed
//#define DEMO_AYTOMATED_ENABLED
//2. Demo user controlled that can go out of that state from the menu
//#define DEMO_CONTROLLED_ENABLED


//-------------------------------------------------------
//----------DON'T EDIT THIS------------------------------
//-------------------------------------------------------


//Define button pins for the pop up mechanism
#if defined POP_UP_BUTTONS_ENABLED

	#define START_BUTTON_PIN 	CONFIG_START_BUTTON_PIN //Start button
	#define SELECT_BUTTON_PIN	CONFIG_SELECT_BUTTON_PIN //Select button

#endif

//Define input pins for the rotary encoder
//micro switches for encoder
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED && !defined MAGNETIC_ROTARY_ENCODER_ENABLED
	
	#define RIGHT_BUTTON_PIN	CONFIG_RIGHT_BUTTON_PIN //Right button
	#define LEFT_BUTTON_PIN		CONFIG_LEFT_BUTTON_PIN //Left button

//magnetic encoder
#elif !defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED && defined MAGNETIC_ROTARY_ENCODER_ENABLED
	
	#define RIGHT_BUTTON_PIN	CONFIG_RIGHT_BUTTON_PIN //Right button
	#define LEFT_BUTTON_PIN		CONFIG_LEFT_BUTTON_PIN //Left button
  
#else
  #error "You must use at least only one option for the rotary encoder"
#endif

//Check if sound is enabled
#if !defined SOUND_ENABLED && (defined SOUND_DFPLAYER_PRO_ENABLED || defined SOUND_BUZZER_ENABLED)
  #error "You must enable sound to use one of these sound options"
#endif
#if defined SOUND_ENABLED
	
	//Check which sound is enabled
  //Dfplayer pro sound
	#if defined SOUND_DFPLAYER_PRO_ENABLED && !defined SOUND_BUZZER_ENABLED
		
		#define RXD1 CONFIG_RXD1 //RX1
		#define TXD1 CONFIG_TXD1 //TX1
		
		//Buzzzer sound
  #elif !defined SOUND_DFPLAYER_PRO_ENABLED && defined SOUND_BUZZER_ENABLED
		#define BUZZER_PIN CONFIG_BUZZER //buzzer

	#else
	  #error "You must use at least only one option for the sound"
	#endif

#endif

//Define RGB LED pins
#if !defined LEDS_ENABLED && (defined RGB_LEDS_ENABLED || defined NEOPIXEL_RING_LEDS_ENABLED || defined(IR_CONTROLLED_LEDS_ENABLED))
  #error "You must enable LEDs to use one of these LED options"
#endif
#if defined LEDS_ENABLED

  //Check which what kind of LED is enabled
  //RGB LEDs are enabled
  #if (defined(RGB_LEDS_ENABLED) && !defined(NEOPIXEL_RING_LEDS_ENABLED) && !defined(IR_CONTROLLED_LEDS_ENABLED))

    #define RGB_LED_R CONFIG_RGB_LED_R //Red
    #define RGB_LED_G CONFIG_RGB_LED_G //Green
    #define RGB_LED_B CONFIG_RGB_LED_B //Blue

  //Neopixel ring LEDs are enabled
  #elif (!defined(RGB_LEDS_ENABLED) && defined(NEOPIXEL_RING_LEDS_ENABLED) && !defined(IR_CONTROLLED_LEDS_ENABLED))

    #define LED_DI CONFIG_DI //Data in

  //IR controlled LEDs are enebled
  #elif (!defined(RGB_LEDS_ENABLED) && !defined(NEOPIXEL_RING_LEDS_ENABLED) && defined(IR_CONTROLLED_LEDS_ENABLED))

    #define LED_IR_TRANS CONFIG_IR_TRANSMITTER

  //Error
  #else
    #error "You must use at least only one option for the LEDs"
  #endif
#endif

//Check if demo is enabled
#if !defined DEMO_ENABLED && (defined DEMO_AYTOMATED_ENABLED || defined DEMO_CONTROLLED_ENABLED)
  #error "You must enable Demo to use one of these demo options"
#endif
#if defined DEMO_ENABLED

  #if defined DEMO_AYTOMATED_ENABLED && !defined DEMO_CONTROLLED_ENABLED
  #elif !defined DEMO_AYTOMATED_ENABLED && defined DEMO_CONTROLLED_ENABLED
  #else
    #error "You must use at least only one option for the demo"
  #endif

#endif



//Check type of animation
#if defined START_ANIMATION_WITH_IMAGES && !defined START_ANIMATION_WITHOUT_IMAGES
#elif !defined START_ANIMATION_WITH_IMAGES && defined START_ANIMATION_WITHOUT_IMAGES
#else
  #error "You must use at least only one option for the start animation"
#endif

/* Failed LCD pin configuration
//Define Esp32-s2 development board pins
#if defined ESP32_S2_PINOUT
  #include "User_Setups/Setup303_ESP32S2_GC9A01.h"
#endif

//Define Esp32-s3 touch LCD pins
#if defined ESP32_S3_TOUCH_LCD_1_28
	//Using integrated Touch LCD with GC9A01/CST816S drivers
  #include "User_Setups/Setup302_ESP32S3_GC9A01_TOUCH.h"
#endif
*/

//-------------------------------------------------------
//----------DON'T EDIT THIS------------------------------
//-------------------------------------------------------