

//Configure LCD pins in User_Setup.h or create your own setup in
//libraries/TFT_eSPI/User_Setups folder and include it in User_Setup_Select.h
/*
#define TFT_MOSI 11 // In some display driver board, it might be written as "SDA" and so on.
#define TFT_SCLK 12
#define TFT_CS   10  // Chip select control pin
#define TFT_DC   9  // Data Command control pin
#define TFT_RST  14  // Reset pin (could connect to Arduino RESET pin)
#define TFT_BL   40  // LED back-light
#define TFT_BACKLIGHT_ON HIGH
*/

//Uncomment for no touch GC9A01 display
#define ESP32_S3_PINOUT

//Define input pins for pop up buttons if enabled
#define CONFIG_START_BUTTON_PIN 	2
#define CONFIG_SELECT_BUTTON_PIN 	4

//ROTARY. Define rotary encoder input pins if enabled
#define CONFIG_RIGHT_BUTTON_PIN		6
#define CONFIG_LEFT_BUTTON_PIN		5

//SOUND 1. Dfplayer Pro pins if sound and dflpayer are enabled
#define CONFIG_RXD1 
#define CONFIG_TXD1 

//SOUND 2. Buzzer pins if sound and buzzer are enabled
#define CONFIG_BUZZER 1


//LED 2. Define addressable LEDs if enabled
#define CONFIG_DI 21

//LED 1. Define RGB LED pins if enabled
#define CONFIG_RGB_LED_R 
#define CONFIG_RGB_LED_G 
#define CONFIG_RGB_LED_B 
