
/*	Edit this file to make new configuration files for other boards */

//Uncomment for CST816S touch driver and GC9A01 lcd display
//#define ESP32_S3_TOUCH_LCD_1_28
//Uncomment for no touch GC9A01 display
//#define ESP32_S2_PINOUT //or
//#define ESP32_S3_PINOUT

//Define input pins for pop up buttons if enabled
#define CONFIG_START_BUTTON_PIN 	0 //write pin
#define CONFIG_SELECT_BUTTON_PIN 	0 //write pin

//ROTARY. Define rotary encoder input pins if enabled
#define CONFIG_RIGHT_BUTTON_PIN		0 //write pin
#define CONFIG_LEFT_BUTTON_PIN		0 //write pin

//SOUND 1. Dfplayer Pro pins if sound and dflpayer are enabled
#define CONFIG_RXD1 0 //write pin
#define CONFIG_TXD1 0 //write pin

//SOUND 2. Buzzer pins if sound and buzzer are enabled
#define CONFIG_BUZZER 0 //write pin


//LED 1. Define RGB LED pins if enabled
#define CONFIG_RGB_LED_R 0 //write pin
#define CONFIG_RGB_LED_G 0 //write pin
#define CONFIG_RGB_LED_B 0 //write pin

//LED 2. Define Neopixel ring LEDs if enabled
#define CONFIG_DI 0 //write pin

//LED 3. Define IR controlled LEDs if enabled
#define CONFIG_IR_TRANSMITTER 0 //write pin

