
//Uncomment for use of a development board 
//and no touch GC9A01 display
#define ESP32_S2_PINOUT


//Define input pins for pop up buttons if enabled
#define CONFIG_START_BUTTON_PIN 	5
#define CONFIG_SELECT_BUTTON_PIN 	3

//ROTARY. Define rotary encoder input pins if enabled
#define CONFIG_RIGHT_BUTTON_PIN		1
#define CONFIG_LEFT_BUTTON_PIN		4

//SOUND 1. Dfplayer Pro pins if sound and dflpayer are enabled
#define CONFIG_RXD1 18
#define CONFIG_TXD1 17

//SOUND 2. Buzzer pins if sound and buzzer are enabled
#define CONFIG_BUZZER 18


//LED 1. Define RGB LED pins if enabled
#define CONFIG_RGB_LED_R 6
#define CONFIG_RGB_LED_G 7
#define CONFIG_RGB_LED_B 8

//LED 2. Define Neopixel ring LEDs if enabled
#define CONFIG_DI 6

//LED 3. Define IR controlled LEDs if enabled
#define CONFIG_IR_TRANSMITTER 6