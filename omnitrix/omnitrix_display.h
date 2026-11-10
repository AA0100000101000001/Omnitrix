
#ifndef O_DISPLAY
#define O_DISPLAY

#include <Arduino.h>
#include "config.h"
#include <TFT_eSPI.h>
#include <PNGdec.h>
#include <SPI.h>

#include "omnitrix_aliens.h"
//Start animation with images
#if defined START_ANIMATION_WITH_IMAGES
#include "omnitrix_anim.h"
#include "omnitrix_alien_background.h"
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

//From main header
extern RTC_DATA_ATTR uint8_t g_alien_n;        // Up to 255 aliens

#define OMNITRIX_GREEN 0xA707
#define OMNITRIX_RED 0xC000
#define OMNITRIX_GRAY 0xAD55

#define MAX_IMAGE_WDITH 240  // Set rendering line buffer lengths for image

#define OMNITRIX_ANIM_FRAME_LAST_INDEX 10 //11 frames for animation
#define ALIEN_LAST_INDEX 11  //0...11 = 12 Total aliens



extern PNG png;  // PNG decoder instance
extern TFT_eSPI tft;


// Display position variables must be global for PNGdec
extern int16_t xpos;
extern int16_t ypos;

extern uint32_t g_anim_start;    //Timer that helps with animation
extern uint8_t g_current_frame; //Frame iterator (<= 255 total frames)

//For debugging animation
#if defined ENABLE_VERBOSE_ANIM_INFO
extern int end_animation_time;
extern double avrg_frame_time;
extern double avrg_frame_decod_time;
#endif


//Function that sets is_animating
void set_is_animating(bool s);

//Function that returns is_animating
bool get_is_animating();

//Method that shows animation
//Returns true if finished, false if not done
bool show_animation();

// Helper function for show_animation
void draw_start_animation_frame(uint8_t i);

//Function that displays start icon symbols
void show_symbols();

//Function that displays alien on screen
void show_alien();

//Method that displays green backround to erase alien
void erase_alien();

// This function displays png images
void show_image(const uint8_t *img, int img_size);

// This function will be called during decoding of the png file
int png_draw(PNGDRAW *pDraw);

#endif