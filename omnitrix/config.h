
//Pin configuration
//Edit configs/config_DEFAULT to create your own configuration or uncomment your preferred configuration
//#include "configs/config_CUSTOM.h" //Use your own configuration
//#include "configs/config_ESP32_S3_PINOUT.h" //Esp32-s3 Dev Board
#include "configs/config_ESP32_S3_PICO_PINOUT.h"  //Esp32-s3-Pico Dev Board

//HARDWARE SETTINGS

//WAKEUP SETTINGS: Use ext0 or ext1
//EXT0
//1. Uncomment for use of ext0
#define EXT0_ENABLED
//Choose wakeup pin and level:
#define EXT0_START_BUTTON
//#define EXT0_ROTARY_ENCODER

#if defined EXT0_START_BUTTON
#define EXT0_WAKEUP_PIN (gpio_num_t) CONFIG_START_BUTTON_PIN  //Wake up with start button
#define EXT0_WAKEUP_MODE 1                                    //Wake up with start button
#elif defined EXT0_ROTARY_ENCODER
#define EXT0_WAKEUP_PIN (gpio_num_t) CONFIG_RIGHT_BUTTON_PIN  //Wake up with rotary movement
#define EXT0_WAKEUP_MODE 0                                    //Wake up with rotary movement
#endif
//EXT1
//2. Uncomment for use of ext1
//#define EXT1_ENABLED
//Choose bitmap:
//#define EXT1_BITMASK (1ULL << CONFIG_START_BUTTON_PIN)  //0x0020 //gpio 5
//Choose mode:
//ESP_EXT1_WAKEUP_ALL_LOW: wake up when all GPIOs go low;
//ESP_EXT1_WAKEUP_ANY_HIGH: wake up if any of the GPIOs go high.
//#define EXT1_WAKEUP_MODE ESP_EXT1_WAKEUP_ANY_HIGH

//POP UP BUTTONS SETTINGS: Uncomment for buttons
#define POP_UP_BUTTONS_ENABLED

//ROTARY ENCODER SETTINGS: Use one of these options for rotary encoder
//1. Uncomment for use of micro switches for encoder
//#define MICRO_SWITCHES_ROTARY_ENCODER_ENABLED
//2. Uncomment for use of mechanical encoder
#define ROTARY_ENCODER_ENABLED
//3. Uncomment for use of magnetic encoder
//#define MAGNETIC_ROTARY_ENCODER_ENABLED

//SOUND SETTINGS: Uncomment for sound
//#define SOUND_ENABLED

//SOUND HARDWARE SELECTION: Use one of these options for sound
//1. Uncomment for use of Dfplayer Pro for sound
//#define SOUND_DFPLAYER_PRO_ENABLED
//2. Uncomment for use of buzzer for sound
//#define SOUND_BUZZER_ENABLED

//LED SETTINGS: Uncomment for LEDs
//#define LEDS_ENABLED

//LED SELECTION: Use one of these options
//1. Uncomment for RGB LEDS
//#define RGB_LEDS_ENABLED
//LED 2. Uncomment for Neopixel ring LEDs
//#define NEOPIXEL_RING_LEDS_ENABLED
//LED 3. Uncomment for IR controlled LEDs
//#define IR_CONTROLLED_LEDS_ENABLED

//SOFTWARE SETTINGS

//SERIAL OUTPUT
//Basic debugging info
#define ENABLE_SERIAL

//Choose one or more types of showing specialized Serial output
//1. Verbose general info
#define ENABLE_VERBOSE_INFO
//2. Verbose deep sleep info
//#define ENABLE_DEEP_SLEEP_INFO
//3. Info about FLASH/RAM
//#define ENABLE_MEMORY_INFO

//ANIMATION
//Choose only one type of animation
//1. Start animation with images
#define START_ANIMATION_WITH_IMAGES  //Has memory leaks
//2. Hard coded start animation
//#define START_ANIMATION_WITHOUT_IMAGES //Not finished

//SOUND
//Choose if sound will be muted in booting
//#define SOUND_MUTED_IN_BOOTING //Only if sound is enabled

//DEMO
//Choose if demo is enabled
#define DEMO_ENABLED
//Choose additional special type of demo //not implemented yet
//Demo automated display of the features
//#define DEMO_AUTOMATED_ENABLED
//Demo is user controlled (that could be implemented to go out of that state from the menu)
//(Automated could be implemented to go out of that state when a button is pressed)


//-------------------------------------------------------
//----------DON'T EDIT THIS------------------------------
//-------------------------------------------------------

//Check external wakeup type
#if defined EXT0_ENABLED && !defined EXT1_ENABLED
#if defined EXT0_START_BUTTON && !defined EXT0_ROTARY_ENCODER
#elif !defined EXT0_START_BUTTON && defined EXT0_ROTARY_ENCODER
#else
#error "You must use only either EXT0_START_BUTTON or EXT0_ROTARY_ENCODER"
#endif
#elif !defined EXT0_ENABLED && defined EXT1_ENABLED
#else
#error "You must use only one option for the external wake up"
#endif

//Define button pins for the pop up mechanism
#if defined POP_UP_BUTTONS_ENABLED

#define START_BUTTON_PIN CONFIG_START_BUTTON_PIN    //Start button
#define SELECT_BUTTON_PIN CONFIG_SELECT_BUTTON_PIN  //Select button

#endif

//Define input pins for the rotary encoder
//micro switches for encoder
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED && !defined ROTARY_ENCODER_ENABLED && !defined MAGNETIC_ROTARY_ENCODER_ENABLED

#define RIGHT_BUTTON_PIN CONFIG_RIGHT_BUTTON_PIN  //Right button
#define LEFT_BUTTON_PIN CONFIG_LEFT_BUTTON_PIN    //Left button

//rotary encoder
#elif !defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED && defined ROTARY_ENCODER_ENABLED && !defined MAGNETIC_ROTARY_ENCODER_ENABLED

#define RIGHT_BUTTON_PIN CONFIG_RIGHT_BUTTON_PIN  //Right button
#define LEFT_BUTTON_PIN CONFIG_LEFT_BUTTON_PIN    //Left button

//magnetic encoder
#elif !defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED && !defined ROTARY_ENCODER_ENABLED && defined MAGNETIC_ROTARY_ENCODER_ENABLED

#define RIGHT_BUTTON_PIN CONFIG_RIGHT_BUTTON_PIN  //Right button
#define LEFT_BUTTON_PIN CONFIG_LEFT_BUTTON_PIN    //Left button

#else
#error "You must use only one option for the rotary encoder"
#endif

//Check if sound is enabled
#if !defined SOUND_ENABLED && (defined SOUND_DFPLAYER_PRO_ENABLED || defined SOUND_BUZZER_ENABLED)
#error "You must enable sound to use one of these sound options"
#endif
#if defined SOUND_ENABLED

//Check which sound is enabled
//Dfplayer pro sound
#if defined SOUND_DFPLAYER_PRO_ENABLED && !defined SOUND_BUZZER_ENABLED

#define RXD1 CONFIG_RXD1  //RX1
#define TXD1 CONFIG_TXD1  //TX1

//Buzzzer sound
#elif !defined SOUND_DFPLAYER_PRO_ENABLED && defined SOUND_BUZZER_ENABLED
#define BUZZER_PIN CONFIG_BUZZER  //buzzer

#else
#error "You must use only one option for the sound"
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

#define RGB_R_PIN CONFIG_RGB_LED_R  //Red
#define RGB_G_PIN CONFIG_RGB_LED_G  //Green
#define RGB_B_PIN CONFIG_RGB_LED_B  //Blue

//Neopixel ring LEDs are enabled
#elif (!defined(RGB_LEDS_ENABLED) && defined(NEOPIXEL_RING_LEDS_ENABLED) && !defined(IR_CONTROLLED_LEDS_ENABLED))

#define LED_DI CONFIG_DI  //Data in

//IR controlled LEDs are enebled
#elif (!defined(RGB_LEDS_ENABLED) && !defined(NEOPIXEL_RING_LEDS_ENABLED) && defined(IR_CONTROLLED_LEDS_ENABLED))

#define LED_IR_TRANS CONFIG_IR_TRANSMITTER

//Error
#else
#error "You must use only one option for the LEDs"
#endif
#endif


//Check if serial is enabled
#if !defined ENABLE_SERIAL && (defined ENABLE_VERBOSE_INFO || defined ENABLE_DEEP_SLEEP_INFO || defined ENABLE_MEMORY_INFO)
#error "You must enable Serial to use one of these Serial info options"
#endif

//Choose one or more types of showing Serial output
//1. Verbose general info
// #define ENABLE_VERBOSE_INFO
//2. Verbose deep sleep info
// #define ENABLE_DEEP_SLEEP_INFO
//3. Info about FLASH/RAM
// #define ENABLE_MEMORY_INFO

//Check type of animation
#if defined START_ANIMATION_WITH_IMAGES && !defined START_ANIMATION_WITHOUT_IMAGES
#elif !defined START_ANIMATION_WITH_IMAGES && defined START_ANIMATION_WITHOUT_IMAGES
#else
#error "You must use at least only one option for the start animation"
#endif

//Check if demo is enabled
#if !defined DEMO_ENABLED && defined DEMO_AUTOMATED_ENABLED
#error "You must enable Demo to use this demo option"
#endif


//-------------------------------------------------------
//----------DON'T EDIT THIS------------------------------
//-------------------------------------------------------