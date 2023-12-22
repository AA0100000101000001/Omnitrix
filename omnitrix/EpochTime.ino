
//Based on ESP32Time Library by Felix Biego

#ifdef RTC_DATA_ATTR
RTC_DATA_ATTR static bool overflow;
#else
static bool overflow;
#endif

uint32_t startTime;
uint32_t timePassed;

void RTC_setTime(int sc, int mn, int hr, int dy, int mt, int yr, int ms) {
  // seconds, minute, hour, day, month, year $ microseconds(optional)
  // ie setTime(20, 34, 8, 1, 4, 2021) = 8:34:20 1/4/2021
  struct tm t = {0, 0, 0, 0, 0, 0, 0, 0, 0};      // Initalize to all 0's
  t.tm_year = yr - 1900;    // This is year-1900, so 121 = 2021
  t.tm_mon = mt - 1;
  t.tm_mday = dy;
  t.tm_hour = hr;
  t.tm_min = mn;
  t.tm_sec = sc;
  time_t timeSinceEpoch = mktime(&t);
  setTime(timeSinceEpoch, ms);
}

void setTime(unsigned long epoch, int ms) {
  struct timeval tv;
  if (epoch > 2082758399){
	  overflow = true;
	  tv.tv_sec = epoch - 2082758399;  // epoch time (seconds)
  } else {
	  overflow = false;
	  tv.tv_sec = epoch;  // epoch time (seconds)
  }
  tv.tv_usec = ms;    // microseconds
  settimeofday(&tv, NULL);
}

unsigned long RTC_getLocalEpoch() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	unsigned long epoch = tv.tv_sec;
	if (overflow){
		epoch += 63071999 + 2019686400;
	}
	return epoch;
}