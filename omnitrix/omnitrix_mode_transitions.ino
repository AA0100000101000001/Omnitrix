
//Start mode to Alien Selection mode
void mode1to2() {

  mode = 2;
	Serial.println("Button pressed, select alien");

}

//Alien Selection mode to Start mode
void mode2to1() {

  mode = 1;
  Serial.println("Button pressed, back to start");

}

//Alien Selection mode to Transformation mode
void mode2to3() {

  mode = 3;
  Serial.println("Tranformed into alien");

  //reset transformation time to current epoch
  transformation_start_time = rtc.getLocalEpoch();
  //Set offset to time passed since last time the timer was checked (in sec)
  transformation_start_time_offset = rtc.getLocalEpoch() - transformation_start_time;

  //Configure the wake up source to wake up every time the transfomation is done
  esp_sleep_enable_timer_wakeup(transform_time_val - transformation_start_time_offset * uS_TO_S_FACTOR);
  Serial.println("Transformation: Setup ESP32 to sleep for every " + String(ALIEN_TRANSFORMATION_TIME_TEST - transformation_start_time_offset) +
  " Seconds");

}

//Transformation mode to Recharging mode
void mode3to4() {

  Serial.println("Omnitrix is recharging");

  //reset recharging time
  recharging_start_time = rtc.getLocalEpoch();
  //Set offset to time passed since last time the timer was checked (in sec)
  recharging_start_time_offset = rtc.getLocalEpoch() - recharging_start_time;

  Serial.println(recharging_start_time_offset);
  Serial.println(recharge_time_val);

  mode = 4;

  //Configure the wake up source to wake up every time the recharge is done
  esp_sleep_enable_timer_wakeup(recharge_time_val - recharging_start_time_offset * uS_TO_S_FACTOR);
  Serial.println("Recharging1: Setup ESP32 to sleep for every " + String(OMNITRIX_RECHARGE_TIME_TEST - recharging_start_time_offset) +
  " Seconds");
}

//Transformation mode to Start mode
void mode3to1() {

  mode = 1;
  Serial.println("Button pressed, untransforming and going back to Start mode");

  //Disable waking up by timer
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
  Serial.println("Disabled Timer1");
}

//Rechargin mode to Start mode
void mode4to1() {

  Serial.println("Going back to start");
  
  mode = 1;

  //Disable waking up by timer
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
  Serial.println("Disabled Timer2");
}