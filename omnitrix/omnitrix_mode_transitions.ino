
//Start mode to Alien Selection mode begining
void mode1to2start() {

#if defined SOUND_ENABLED
  play_sound(2);  //Play select sound
#endif

#if defined ENABLE_SERIAL
  Serial.println("Button pressed, select alien initiating...");
#endif

  
  reset_timer(); // For the delay of the animation
  g_anim_start = millis(); //get time of animation begin
  is_animating = true;
  //Display animation
  show_animation();

}

//Start mode to Alien Selection mode end
void mode1to2finish() {

#if defined ENABLE_SERIAL
  Serial.println("Select alien");
#endif

  //Set select alien mode now after animation is done
  g_mode = 2;
  //Display alien
  show_alien();
}

//Alien Selection mode to Start mode
void mode2to1() {

#if defined SOUND_ENABLED
  play_sound(4);  //Play move backwards
#endif

  g_mode = 1;
#if defined ENABLE_SERIAL
  Serial.println("Button pressed, back to start");
#endif

  //display start
  tft.fillScreen(OMNITRIX_GREEN);
  show_symbols();
}

//Alien Selection mode to Transformation mode before delay/animation
void mode2to3start() {

#if defined ENABLE_SERIAL
  Serial.println("Tranforming into alien...");
#endif

#if defined SOUND_ENABLED
  play_sound(5);  //Play transformation sound
#endif

  //Display tranformation image
  tft.fillScreen(OMNITRIX_GREEN);
  
  reset_timer(); // For the delay of the green display
  g_anim_start = millis(); //get time of animation/delay begin
  is_animating = true;

  //delay(600); //green display delay

  
}

//Alien Selection mode to Transformation mode after delay/animation
void mode2to3finish() {

#if defined ENABLE_SERIAL
  Serial.println("Tranformed into alien");
#endif

  //Set transformation mode now after animation/delay is done
  g_mode = 3; 

  //Display transformed state image
  tft.fillScreen(TFT_WHITE);
  show_symbols();

  //Start transformation timer
  //Set transformation start time to current epoch time
  g_transformation_start_time = get_time_now();

  //Set offset to time passed since last time the timer was checked (in sec)
  g_transformation_start_time_offset = get_time_now() - g_transformation_start_time;
  //Configure the wake up source to wake up every time the transformation is done
  esp_sleep_enable_timer_wakeup((g_transform_time_val - g_transformation_start_time_offset) * uS_TO_S_FACTOR);
#if defined ENABLE_SERIAL
  Serial.println("Transformation: Setup ESP32 to sleep for every " + String(g_transform_time_val - g_transformation_start_time_offset) + " Seconds");
#endif
}

//Transformation mode to Recharging mode
void mode3to4() {

#if defined SOUND_ENABLED
  play_sound(7);  //Play detransformation sound
#endif

//Red led colour
#if defined RGB_LEDS_ENABLED
  analogWrite(RGB_R_PIN, RED_LED_R);
  analogWrite(RGB_G_PIN, RED_LED_G);
  analogWrite(RGB_B_PIN, RED_LED_B);
#endif

  //Display red screen
  tft.fillScreen(OMNITRIX_RED);
  show_symbols();

#if defined ENABLE_SERIAL
  Serial.println("Omnitrix is recharging");
#endif

  //Start Rechargin timer
  //Set recharging start time to current epoch time
  g_recharging_start_time = get_time_now();

  g_mode = 4;

  //Set offset to time passed since last time the timer was checked (in sec)
  g_recharging_start_time_offset = get_time_now() - g_recharging_start_time;
  //Configure the wake up source to wake up every time the recharge is done
  esp_sleep_enable_timer_wakeup((g_recharge_time_val - g_recharging_start_time_offset) * uS_TO_S_FACTOR);
#if defined ENABLE_SERIAL
  Serial.println("Recharging: Setup ESP32 to sleep for every " + String(g_recharge_time_val - g_recharging_start_time_offset) + " Seconds");
#endif
}

//Transformation mode to Start mode
void mode3to1() {

#if defined SOUND_ENABLED
  play_sound(4);  //Play move backwards
#endif

  g_mode = 1;
#if defined ENABLE_SERIAL
  Serial.println("Button pressed, untransforming and going back to Start mode");
#endif

  //display start
  tft.fillScreen(OMNITRIX_GREEN);
  show_symbols();

  //Disable waking up by timer
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
#if defined ENABLE_DEEP_SLEEP_INFO
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
  show_symbols();

#if defined ENABLE_SERIAL
  Serial.println("Going back to start");
#endif

  g_mode = 1;

  //Disable waking up by timer
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
#if defined ENABLE_DEEP_SLEEP_INFO
  Serial.println("Disabled Timer2");
#endif

  //reset timer
  reset_timer();
}
