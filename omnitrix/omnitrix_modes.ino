
//Switch statement for start button modes
void start_button_mode() {

  switch (g_mode) {
    //Omnitrix is in start mode
    case 1:
      //Go to select alien mode
		  mode1to2();

      //reset timer
      reset_timer();
      break;

    //Omnitrix is in select alien mode
    case 2:
      //Go to start mode
      mode2to1();

      //reset timer
      reset_timer();
      break;
  }

}

//Switch statement for right button modes
void right_button_mode() {

  #if defined SOUND_ENABLED
  play_sound(3); //Play move encoder forward 
  #endif

  switch (g_mode) {
    //Omnitrix is in select alien mode
    case 2:
      //If the next alien number is bigger than the total number of aliens
      //then go back to first alien, else go to the next alien
      if ((g_alien_n  + 1)> ALIEN_LAST_INDEX ) {
        g_alien_n = 0;
      }
      else {
        g_alien_n += 1;
      }

      //Display green backround png to erase previous alien
      erase_alien();
      //Display alien
      show_alien();

      #if defined ENABLE_SERIAL
        Serial.print("Right, alien no:");
        Serial.println(g_alien_n);
      #endif
      break;
  }

  //reset timer
  reset_timer();

}

//Switch statement for left button modes
void left_button_mode() {

  #if defined SOUND_ENABLED
  play_sound(4); //Play move encoder backwards 
  #endif

  switch (g_mode) {
    //Omnitrix is in select alien mode
    case 2:
      //If the next alien number is less than 0
      //then go back to the last alien, else go to the previous alien
      if ((g_alien_n - 1) < 0 ) {
        g_alien_n = ALIEN_LAST_INDEX;
      }
      else {
        g_alien_n -= 1;
      }
          
      //Erase previous alien
      erase_alien();
      //Display alien
      show_alien();
      
      #if defined ENABLE_SERIAL
        Serial.print("Left, alien no:");
        Serial.println(g_alien_n);
      #endif
      break;
  }

  //reset timer
  reset_timer();

}

//Switch statement for select button modes
void select_button_mode() {

  switch (g_mode) {
    //Omnitrix is in select alien mode
    case 2:
      //Go to transformation mode
      mode2to3();

      break;

    //Omnitrix is in transformation mode
    case 3:
      //Go to Start mode
      mode3to1();

      break;
  }

  //reset timer
  reset_timer();

  #if defined ENABLE_SERIAL
    Serial.print("mode ");
    Serial.println(g_mode);
  #endif

}

//Mode 3
//Function for transformation
void transformed_mode() {

  //Check transformation time
  //Transformation time is done while omnitrix is not sleeping
  if ((get_time_now() - g_transformation_start_time) > g_transform_time_val) {

    //Go to next mode
    mode3to4();

  //Transformation time is not finished
  } else {
    #if defined ENABLE_DEEP_SLEEP_INFO
      //Set offset to time passed since last time the timer was checked (in sec)
      g_transformation_start_time_offset = get_time_now() - g_transformation_start_time;
      Serial.print("transformation_start_time_offset: ");
      Serial.println(g_transformation_start_time_offset);
    #endif
  }
}

//Mode 4
//Recharge mode
void recharge_mode() {

  //Check recharging time
  //Recharging time is done while omnitrix is not sleeping
  if ((get_time_now() - g_recharging_start_time) > g_recharge_time_val) {
      
    //Go to first mode
    mode4to1();

  //Recharging time is not finished
  } else {
    #if defined ENABLE_DEEP_SLEEP_INFO
      //Set offset to time passed since last time the timer was checked (in sec)
      g_recharging_start_time_offset = get_time_now() - g_recharging_start_time;
      Serial.print("recharging_start_time_offset: ");
      Serial.println(g_recharging_start_time_offset);
    #endif
  }
  
}
