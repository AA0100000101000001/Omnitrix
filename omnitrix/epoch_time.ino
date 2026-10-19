
//Based on ESP32Time Library by Felix Biego

#ifdef RTC_DATA_ATTR
RTC_DATA_ATTR static bool overflow;
#else
static bool overflow;
#endif

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

void reset_timer() {
  g_start = get_time_now();
}