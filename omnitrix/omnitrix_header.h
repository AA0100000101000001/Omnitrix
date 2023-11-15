
#include <TFT_eSPI.h>
#include <PNGdec.h>
#include "SPI.h"
#include <DFRobot_DF1201S.h>
#include <WiFi.h>
#include <ESP32Time.h>
//#include <PCM.h>

#include "omnitrix_aliens.h"
#include "omnitrix_alien_backround.h"
#include "omnitrix_anim.h"

//LCD pins

#define TFT_MOSI 35 
#define TFT_SCLK 36
#define TFT_CS   34 
#define TFT_DC   26
#define TFT_RST  33
/*
#define TFT_BL   38
*/

#define RXD1 18 //RX1
#define TXD1 17 //TX1


#define MAX_IMAGE_WDITH 240 // Set rendering line buffer lengths for image

#define ALIEN_NUMBER 11 //0...11 = 12

//Time Variables
ESP32Time rtc;

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define DEEP_SLEEP_TIMER 30 //5 // 5 sec
uint32_t start; //timer for deep sleep

#define ALIEN_TRANSFORMATION_TIME_TEST 20 //10 sec
#define OMNITRIX_RECHARGE_TIME_TEST 20 //10 sec
#define ALIEN_TRANSFORMATION_TIME_DEFAULT 60 //1 min
#define OMNITRIX_RECHARGE_TIME_DEFAULT 60 //1 min

//Convert timer variables into micro seconds
int transform_time_val = ALIEN_TRANSFORMATION_TIME_TEST * uS_TO_S_FACTOR;
int recharge_time_val = OMNITRIX_RECHARGE_TIME_TEST * uS_TO_S_FACTOR;

//Time variables that are saved in deep sleep mode
RTC_DATA_ATTR uint32_t transformation_start_time;
RTC_DATA_ATTR uint32_t recharging_start_time;
RTC_DATA_ATTR uint32_t transformation_start_time_offset;
RTC_DATA_ATTR uint32_t recharging_start_time_offset;

/* Colours
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

//Pins
const int buttonPin = 5; //Start button
const int A = 1; //Encoder right
const int B = 4; //Encoder left
const int SW = 3; //Encoder button

const int rgb_r = 6;
const int rgb_g = 7;
const int rgb_b = 8;

//Variables that are saved in deep sleep mode
RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR int alienNo;
RTC_DATA_ATTR int mode;

int buttonState = 0; //State of start button
int rightState = 0; //State of right
int leftState = 0; //State of left
int selectbuttonState = 0; //State of select button


//Display variables
PNG png; // PNG decoder instance

TFT_eSPI tft = TFT_eSPI();

//DFT sound
DFRobot_DF1201S DF1201S;
bool mute = false;

void ShowSymbols();
void ShowAlien();
void pngDraw(PNGDRAW *pDraw);