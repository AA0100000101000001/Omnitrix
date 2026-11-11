
#include "omnitrix_mode_transitions.h"

//Start mode to Alien Selection mode begining
void mode1to2start() {

  play_sound(2);  //Play select sound

  PRINT_INFO("Button pressed, select alien initiating...\n");
  
  reset_timer(); // For the delay of the animation
  g_anim_start = get_anim_time(); //get time of animation begin
  set_is_animating(true);

#if defined ALLOW_CPU_FREQ_CHANGES
  //Change cpu frequency to the faster allowed one for faster animation
  setCpuFrequencyMhz(MAX_CPU_FREQ); //Change cpu frequency to the faster allowed one 
#endif
  g_current_frame = 0; //Set start frame
  //Set debugging animation variables
#if defined ENABLE_VERBOSE_ANIM_INFO
  avrg_frame_time = 0;
  avrg_frame_decod_time = 0;
#endif

}

//Start mode to Alien Selection mode end
void mode1to2finish() {

  PRINT_INFO("Select alien\n");

#if defined ALLOW_CPU_FREQ_CHANGES
  //Change cpu frequency to the default one for battery
  setCpuFrequencyMhz(DEFAULT_CPU_FREQ); //Change cpu frequency to the faster allowed one 
#endif

  //Set select alien mode now after animation is done
  g_mode = 2;
  //Display alien
  show_alien();
}

//Alien Selection mode to Start mode
void mode2to1() {

  play_sound(4);  //Play move backwards

  g_mode = 1;
  PRINT_INFO("Button pressed, back to start\n");

  //display start
  tft.fillScreen(OMNITRIX_GREEN);
  show_symbols();
}

//Alien Selection mode to Transformation mode before delay/animation
void mode2to3start() {

  PRINT_INFO("Tranforming into alien...\n");

  play_sound(5);  //Play transformation sound

  //Display tranformation image
  tft.fillScreen(OMNITRIX_GREEN);
  
  reset_timer(); // For the delay of the green display
  g_anim_start = get_anim_time(); //get time of animation/delay begin
  set_is_animating(true);

  //delay(600); //green display delay

  
}

//Alien Selection mode to Transformation mode after delay/animation
void mode2to3finish() {

  PRINT_INFO("Tranformed into alien\n");

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
  PRINT_INFO("Transformation: Setup ESP32 to sleep for every %d sec\n", g_transform_time_val - g_transformation_start_time_offset);
}

//Transformation mode to Recharging mode
void mode3to4() {

  play_sound(7);  //Play detransformation sound

//Red led colour
#if defined RGB_LEDS_ENABLED
  analogWrite(RGB_R_PIN, RED_LED_R);
  analogWrite(RGB_G_PIN, RED_LED_G);
  analogWrite(RGB_B_PIN, RED_LED_B);
#endif

  //Display red screen
  tft.fillScreen(OMNITRIX_RED);
  show_symbols();

  PRINT_INFO("Omnitrix is recharging\n");

  //Start Rechargin timer
  //Set recharging start time to current epoch time
  g_recharging_start_time = get_time_now();

  g_mode = 4;

  //Set offset to time passed since last time the timer was checked (in sec)
  g_recharging_start_time_offset = get_time_now() - g_recharging_start_time;
  //Configure the wake up source to wake up every time the recharge is done
  esp_sleep_enable_timer_wakeup((g_recharge_time_val - g_recharging_start_time_offset) * uS_TO_S_FACTOR);
  PRINT_INFO("Recharging: Setup ESP32 to sleep for every %d sec\n", g_recharge_time_val - g_recharging_start_time_offset);
}

//Transformation mode to Start mode
void mode3to1() {

  play_sound(4);  //Play move backwards

  g_mode = 1;
  PRINT_INFO("Button pressed, untransforming and going back to Start mode\n");

  //display start
  tft.fillScreen(OMNITRIX_GREEN);
  show_symbols();

  //Disable waking up by timer
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
  PRINT_DEEP_SLEEP_INFO("mode3to1: Disabled Timer\n");
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

  PRINT_INFO("Going back to start\n");

  g_mode = 1;

  //Disable waking up by timer
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
  PRINT_DEEP_SLEEP_INFO("mode4to1: Disabled Timer\n");

  //reset timer
  reset_timer();
}
