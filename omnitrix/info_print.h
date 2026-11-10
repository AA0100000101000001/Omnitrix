
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
void print_info(String s);

//Function that outputs a variable if Serial is enabld
void print_info_var(String s, int v);

//VERBOSE INFO
//Function that shows message if verbose info is enabled
void print_verbose_info(String s);

//DEEP SLEEP INFO
//Function that outputs message if deep sleep info is enabled
void print_deep_sleep_info(String s);

//Function that outputs deep sleep time offset if deep sleep info is emabled
void print_deep_sleep_info_var(String m, uint16_t x);

//MEMORY INFO
//Function that shows free memory if memory info is enabled
void print_memory_info();

//Function that outputs a message if mempry info is emabled
void print_memory_info_mes(String m);

//Function that outputs a variable if mempry info is emabled
void print_memory_info_mes_var(String m, int x);

//ANIMATION INFO
//Function that outputs message if animation info is enabled
void print_anim_info(String s);

//Function that outputs variables with messages if animation info is emabled
void print_anim_info_vars(String m1, int x1, String m2, int x2);

//VERBOSE ANIMATION INFO
//Saves in the variable the current time if verbose animation info is enabled
void verbose_anim_info_save_anim_time(unsigned long *start_frame_time);

// Function print_verbose_anim_info_end_frame: prints info at the end of a frame
// Prints frame_duration_time, frame_duration_since_start, does avrg_frame_time calculation 
//If animation with images is used also shows frame_decod_duration_time
#if defined START_ANIMATION_WITH_IMAGES
void print_verbose_anim_info_end_frame(unsigned long *start_frame_time, unsigned long *start_frame_decod_time);
  
#elif defined START_ANIMATION_HARD_CODED
void print_verbose_anim_info_end_frame(unsigned long *start_frame_time);
#endif

// Function verbose_anim_end_info: prints info at the end of the animation
// Prints Average frame rate, Total start_animation time length and if animation with images if enabled Average frame decode time
void verbose_anim_end_info();


#endif