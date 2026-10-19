
//Start mode to Alien Selection mode
void mode1to2() {

  #if defined SOUND_ENABLED
  playSound(2); //Play select sound
  #endif

  mode = 2;
  #if defined ENABLE_SERIAL
	  Serial.println("Button pressed, select alien");
  #endif

  //Display animation
  showAnimation();
      
	delay(600);

  //Display alien
  ShowAlien();

}

//Alien Selection mode to Start mode
void mode2to1() {
      
  #if defined SOUND_ENABLED
  playSound(4); //Play move backwards 
  #endif

  mode = 1;
  #if defined ENABLE_SERIAL
    Serial.println("Button pressed, back to start");
  #endif

  delay(300);

  //display start
  tft.fillScreen(OMNITRIX_GREEN);
  ShowSymbols();

}

//Alien Selection mode to Transformation mode
void mode2to3() {

  mode = 3;
  #if defined ENABLE_SERIAL
    Serial.println("Tranformed into alien");
  #endif

  #if defined SOUND_ENABLED
  playSound(5); //Play transformation sound
  #endif

  //Display tranformation image
  tft.fillScreen(OMNITRIX_GREEN);
  delay(600);

  //Display transformed state image
  tft.fillScreen(TFT_WHITE);
  ShowSymbols();

  delay(200);

  //Start transformation timer
  //Set transformation start time to current epoch time
  transformation_start_time = getTimeNow();
  //Set offset to time passed since last time the timer was checked (in sec)
  transformation_start_time_offset = getTimeNow() - transformation_start_time;

  //Configure the wake up source to wake up every time the transformation is done
  esp_sleep_enable_timer_wakeup((transform_time_val - transformation_start_time_offset) * uS_TO_S_FACTOR);
  #if defined ENABLE_SERIAL
    Serial.println("Transformation: Setup ESP32 to sleep for every " + String(transform_time_val - transformation_start_time_offset) +
  " Seconds");
  #endif

}

//Transformation mode to Recharging mode
void mode3to4() {
  
  #if defined SOUND_ENABLED
  playSound(7); //Play detransformation sound
  #endif
  delay(2500);

  //Red led colour
  #if defined RGB_LEDS_ENABLED
    analogWrite(RGB_R_PIN, RED_LED_R);
    analogWrite(RGB_G_PIN, RED_LED_G);
    analogWrite(RGB_B_PIN, RED_LED_B);
  #endif
  
  //Display red screen
  tft.fillScreen(OMNITRIX_RED);
  ShowSymbols();

  #if defined ENABLE_SERIAL
    Serial.println("Omnitrix is recharging");
  #endif

  //Start Rechargin timer
  //Set recharging start time to current epoch time
  recharging_start_time = getTimeNow();
  //Set offset to time passed since last time the timer was checked (in sec)
  recharging_start_time_offset = getTimeNow() - recharging_start_time;

  #if defined ENABLE_DEEP_SLEEP_INFO
    Serial.println(recharging_start_time_offset);
    Serial.println(recharge_time_val);
  #endif

  mode = 4;

  //Configure the wake up source to wake up every time the recharge is done
  esp_sleep_enable_timer_wakeup((recharge_time_val - recharging_start_time_offset) * uS_TO_S_FACTOR);
  #if defined ENABLE_SERIAL
    Serial.println("Recharging: Setup ESP32 to sleep for every " + String(recharge_time_val - recharging_start_time_offset) +
  " Seconds");
  #endif
  
}

//Transformation mode to Start mode
void mode3to1() {

  #if defined SOUND_ENABLED
  playSound(4); //Play move backwards 
  #endif

  mode = 1;
  #if defined ENABLE_SERIAL
    Serial.println("Button pressed, untransforming and going back to Start mode");
  #endif

  //display start
  tft.fillScreen(OMNITRIX_GREEN);
  ShowSymbols();

  //Disable waking up by timer
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
  #if defined ENABLE_SERIAL
    Serial.println("Disabled Timer1");
  #endif
}

//Recharging mode to Start mode
void mode4to1() {

  //Green led colour
  #if defined RGB_LEDS_ENABLED
  analogWrite(RGB_R_PIN, GREEN_LED_R);
  analogWrite(RGB_G_PIN, GREEN_LED_G);
  analogWrite(RGB_B_PIN, GREEN_LED_B);
  #endif
  
  //Display green screen
  tft.fillScreen(OMNITRIX_GREEN);
  ShowSymbols();

  #if defined ENABLE_SERIAL
    Serial.println("Going back to start");
  #endif
  
  mode = 1;

  //Disable waking up by timer
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
  #if defined ENABLE_SERIAL
    Serial.println("Disabled Timer2");
  #endif
  
  //reset timer
  resetTimer();
}
