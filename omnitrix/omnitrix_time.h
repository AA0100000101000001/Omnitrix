
#ifndef O_TIME
#define O_TIME

#include <Arduino.h>
#include "config.h"
#include "omnitrix_types.h"
#include <time.h>
#include <sys/time.h>


//Time Variables
#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define DEEP_SLEEP_TIMER DEEP_SLEEP_TIMER_CONFIG  // in sec
extern uint32_t g_start;          //timer for deep sleep

//Time definitions for demo and default mode
#if defined DEMO_ENABLED
#define TRANSFORMATION_TIME 10     //10 sec
#define OMNITRIX_RECHARGE_TIME 10  //10 sec
#else
#define TRANSFORMATION_TIME 60     //1 min
#define OMNITRIX_RECHARGE_TIME 60  //1 min
#endif

//Initialise timer variables as DEMO (in seconds)
// Up to 65535 seconds = 1092.25 min = 18.2 hours of recharging/transformation
extern RTC_DATA_ATTR uint16_t g_transform_time_val;    // Transformation Time Variable
extern RTC_DATA_ATTR uint16_t g_recharge_time_val;  // Recharging Time Variable

//Time variables that are saved in deep sleep mode
extern RTC_DATA_ATTR uint32_t g_transformation_start_time;
extern RTC_DATA_ATTR uint32_t g_recharging_start_time;
extern RTC_DATA_ATTR uint16_t g_transformation_start_time_offset;
extern RTC_DATA_ATTR uint16_t g_recharging_start_time_offset;


void init_time_sleep();  //Initialize deep sleep mode
void rtc_set_time(int sc, int mn, int hr, int dy, int mt, int yr, int ms);
uint64_t get_time_now();
void reset_timer();
void check_timer();
void get_wakeup_reason();

void mode3to4();
void mode4to1();

#endif