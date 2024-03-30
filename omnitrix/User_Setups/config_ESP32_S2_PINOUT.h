
//Uncomment for use of a development board 
//and no touch GC9A01 display
#define ESP32_S2_PINOUT

//Uncomment for buttons
#define POP_UP_BUTTONS_ENABLED

//Define input pins
#define CONFIG_START_BUTTON_PIN 	5
#define CONFIG_SELECT_BUTTON_PIN 	3

//Use one of these options for rotary encoder
//1. Uncomment for use of micro switches for encoder
#define MICRO_SWITCHES_ROTARY_ENCODER_ENABLED
//2. Uncomment for use of magnetic encoder
//#define MAGNETIC_ROTARY_ENCODER_ENABLED

//Define rotary encoder input pins
#define CONFIG_RIGHT_BUTTON_PIN		1
#define CONFIG_LEFT_BUTTON_PIN		4


//Uncomment for sound
//#define SOUND_ENABLED

//Use one of these options for sound
//1. Uncomment for use of Dfplayer Pro for sound
//#define SOUND_DFPLAYER_PRO_ENABLED

//Dfplayer Pro pins
#define CONFIG_RXD1 18
#define CONFIG_TXD1 17

//2. Uncomment for use of buzzer for sound
//#define SOUND_BUZZER_ENABLED

//Buzzer pins
#define CONFIG_BUZZER 18


//Uncomment for LEDs
//#define LEDS_ENABLED

//Uncomment for RGB LEDS
//#define RGB_LEDS_ENABLED

//1. Define RGB LED pins
#define CONFIG_RGB_LED_R 6
#define CONFIG_RGB_LED_G 7
#define CONFIG_RGB_LED_B 8

//2. Uncomment for Neopixel ring LEDs
//#define NEOPIXEL_RING_LEDS_ENABLED

#define CONFIG_DI 6

//3. Uncomment for IR controlled LEDs
//#define IR_CONTROLLED_LEDS_ENABLED

#define CONFIG_IR_TRANSMITTER 6