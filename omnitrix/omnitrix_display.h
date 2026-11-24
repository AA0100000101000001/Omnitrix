
#ifndef O_DISPLAY
#define O_DISPLAY

#include <Arduino.h>
#include "config.h"
#include "info_print.h"
#include "omnitrix_types.h"
#include <TFT_eSPI.h>
#include <PNGdec.h>
#include <SPI.h>

//From main header
extern RTC_DATA_ATTR uint8_t g_alien_n;        // Up to 255 aliens

#define OMNITRIX_GREEN OMNITRIX_GREEN_CONFIG
#define OMNITRIX_RED OMNITRIX_RED_CONFIG
#define OMNITRIX_GRAY OMNITRIX_GRAY_CONFIG

#define OMNITRIX_ANIM_FRAME_LAST_INDEX 10 //11 frames for animation
#define ALIEN_LAST_INDEX 11  //0...11 = 12 Total aliens


// Used by other modules
extern TFT_eSPI tft;
extern uint32_t g_anim_start;    //Timer that helps with animation
extern uint8_t g_current_frame; //Frame iterator (<= 255 total frames)

//For debugging animation
#if defined ENABLE_VERBOSE_ANIM_INFO
//extern int end_animation_time;
extern double avrg_frame_time;
extern double avrg_frame_decod_time;
#endif


//Function that sets is_animating
void set_is_animating(bool s);

//Function that returns is_animating
bool get_is_animating();

//Function that gets curent time
//Animation with images returns millis while hardcoded animation returns micros
unsigned long get_anim_time();

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