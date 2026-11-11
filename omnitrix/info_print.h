
#ifndef O_PRINT
#define O_PRINT

#include <Arduino.h>
#include "config.h"

#ifndef OMNITRIX_ANIM_FRAME_LAST_INDEX
#define OMNITRIX_ANIM_FRAME_LAST_INDEX 10 //11 frames for animation
#endif

//Variables from omnitrix_display
extern uint32_t g_anim_start;
extern int end_animation_time;
extern double avrg_frame_time;
#if defined START_ANIMATION_WITH_IMAGES
extern double avrg_frame_decod_time;
#endif
//Function from omnitrix_display
extern unsigned long get_anim_time();


//SERIAL ENABLED
//Function that outputs message if Serial is enabld
#if defined ENABLE_SERIAL
  #define PRINT_INFO(...) Serial.printf(__VA_ARGS__)
#else
  #define PRINT_INFO(...) ((void)0)
#endif

//VERBOSE INFO
//Function that shows message if verbose info is enabled
#if defined ENABLE_VERBOSE_INFO
  #define PRINT_VERBOSE_INFO(...) Serial.printf("VERBOSE: " __VA_ARGS__)
#else
  #define PRINT_VERBOSE_INFO(...) ((void)0)
#endif

//DEEP SLEEP INFO
//Function that outputs message if deep sleep info is enabled
#if defined ENABLE_DEEP_SLEEP_INFO
  #define PRINT_DEEP_SLEEP_INFO(...) Serial.printf("DEEP_SLEEP_INFO: " __VA_ARGS__)
#else
  #define PRINT_DEEP_SLEEP_INFO(...) ((void)0)
#endif

//MEMORY INFO
#if defined ENABLE_MEMORY_INFO
//Function that outputs a message if memory info is emabled
  #define PRINT_MEMORY_INFO_MES(...) Serial.printf("MEMORY_INFO: " __VA_ARGS__)
  //Function that shows free memory if memory info is enabled
  #define PRINT_MEMORY_INFO Serial.printf("Free Internal Heap: %d\n", ESP.getFreeHeap()); Serial.printf("Min Free Internal Heap: %d\n", ESP.getMinFreeHeap()); Serial.printf("Total PSRAM Size: %d\n", ESP.getPsramSize()); Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram())
#else
  #define PRINT_MEMORY_INFO_MES(...) ((void)0)
  #define PRINT_MEMORY_INFO ((void)0)
#endif

//ANIMATION INFO
//Function that outputs message if animation info is enabled
#if defined ENABLE_ANIM_INFO
  #define PRINT_ANIM_INFO(...) Serial.printf("ANIM_INFO: " __VA_ARGS__)
#else
  #define PRINT_ANIM_INFO(...) ((void)0)
#endif

//VERBOSE ANIMATION INFO
//Saves in the variable the current time if verbose animation info is enabled
void verbose_anim_info_save_anim_time(unsigned long *start_frame_time);

// Function print_verbose_anim_info_end_frame: prints info at the end of a frame
// Prints frame_duration_time, frame_duration_since_start, does avrg_frame_time calculation 
//If animation with images is used also shows frame_decod_duration_time
#if defined START_ANIMATION_WITH_IMAGES
void print_verbose_anim_info_end_frame(unsigned long *start_frame_time, unsigned long *start_frame_decod_time);
  
#elif defined START_ANIMATION_WITHOUT_IMAGES
void print_verbose_anim_info_end_frame(unsigned long *start_frame_time);
#endif

// Function verbose_anim_end_info: prints info at the end of the animation
// Prints Average frame rate, Total start_animation time length and if animation with images if enabled Average frame decode time
void verbose_anim_end_info();


#endif