

//Based on ESP32Time Library by Felix Biego
#ifdef RTC_DATA_ATTR
RTC_DATA_ATTR static bool overflow;
#else
static bool overflow;
#endif
//Based on ESP32Time Library by Felix Biego
void rtc_set_time(int sc, int mn, int hr, int dy, int mt, int yr, int ms) {
  // seconds, minute, hour, day, month, year $ microseconds(optional)
  // ie setTime(20, 34, 8, 1, 4, 2021) = 8:34:20 1/4/2021
  struct tm t = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };  // Initalize to all 0's
  t.tm_year = yr - 1900;                        // This is year-1900, so 121 = 2021
  t.tm_mon = mt - 1;
  t.tm_mday = dy;
  t.tm_hour = hr;
  t.tm_min = mn;
  t.tm_sec = sc;
  time_t time_since_epoch = mktime(&t);

  struct timeval tv;
  unsigned long epoch = (unsigned long)time_since_epoch;
  if (epoch > 2082758399) {
    overflow = true;
    tv.tv_sec = epoch - 2082758399;  // epoch time (seconds)
  } else {
    overflow = false;
    tv.tv_sec = epoch;  // epoch time (seconds)
  }
  tv.tv_usec = ms;  // microseconds
  settimeofday(&tv, NULL);
}

uint64_t get_time_now() {
  time_t now;
  time(&now);
  uint64_t timenow = (uint64_t)now;
  if (overflow) {
    timenow += 63071999 + 2019686400;
  }
  return timenow;
}

// Reset time for deep sleep
void reset_timer() {
  g_start = get_time_now();
}

//Check time for deep sleep
void check_timer() {

  //if the time has passed then go to deep sleep
  if ((get_time_now() - g_start) > DEEP_SLEEP_TIMER) {

#if defined ENABLE_SERIAL
    Serial.println("Going to sleep");
#endif

    esp_deep_sleep_start();
  }
}

void get_wakeup_reason() {

  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  //Check wake up reason
  switch (wakeup_reason) {
    //Wake up by button so timer is not finished if enabled
    case ESP_SLEEP_WAKEUP_EXT0:
      {

#if defined ENABLE_DEEP_SLEEP_INFO
        Serial.println("Wakeup caused by external signal using RTC_IO");
#endif

        //Transformation mode is not done, enable deep sleep timer for transformation offset
        if (g_mode == 3) {

          //Set offset to time passed since last time the timer was checked (in sec)
          g_transformation_start_time_offset = get_time_now() - g_transformation_start_time;

          //Configure the wake up source to wake up every time the transformation is done
          esp_sleep_enable_timer_wakeup((g_transform_time_val - g_transformation_start_time_offset) * uS_TO_S_FACTOR);
#if defined ENABLE_SERIAL
          Serial.println("Transformation: Setup ESP32 to sleep for every " + String(g_transform_time_val - g_transformation_start_time_offset) + " Seconds");
#endif

        }
        //Recharging mode is not done, enable deep sleep timer for recharging offset
        else if (g_mode == 4) {

          //Set offset to time passed since last time the timer was checked (in sec)
          g_recharging_start_time_offset = get_time_now() - g_recharging_start_time;

          //Configure the wake up source to wake up every time the recharge is done
          esp_sleep_enable_timer_wakeup((g_recharge_time_val - g_recharging_start_time_offset) * uS_TO_S_FACTOR);
#if defined ENABLE_SERIAL
          Serial.println("Recharging1: Setup ESP32 to sleep for every " + String(g_recharge_time_val - g_recharging_start_time_offset) + " Seconds");
#endif
        }

        break;
      }
    //Wake up by timer
    case ESP_SLEEP_WAKEUP_TIMER:
      {

#if defined ENABLE_DEEP_SLEEP_INFO
        Serial.println("Wakeup caused by timer");
#endif

        //Transformation mode is done, enable deep sleep timer for recharging
        if (g_mode == 3) {

          mode3to4();


          //Recharging mode is done, disable timer and go to start mode
        } else if (g_mode == 4) {

          mode4to1();
        }
        break;
      }
    //Wake up not caused by deep sleep
    default:
      {
#if defined ENABLE_DEEP_SLEEP_INFO
        Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
#endif
        break;
      }
  }
}