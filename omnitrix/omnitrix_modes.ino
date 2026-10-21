
//Mode 1
//First state, Omnitrix is in start mode
void start_mode(Input in) {

  //Animation for going to select alien mode is done
  if(is_animating) {

    // Animation time is done
    if (animating_finished) {

#if defined ENABLE_ANIM_INFO
      Serial.println("Start animation is done");
#endif

      is_animating = false;
      animating_finished = false;
      // Finish going to select alien mode
      mode1to2finish();
    }
  }

  // Start button is pressed
  if (in == INPUT_START_BUTTON) {
    //Go to select alien mode
    mode1to2start();
  }
}

//Mode 2
//Omnitrix is in select alien mode
void select_alien_mode(Input in) {

  // Delay/animation for before going to transformed mode
  if (is_animating) {

    // Green display delay is done
    if (millis() - g_anim_start >= 600) {

#if defined ENABLE_ANIM_INFO
      Serial.println("Delay for green display is done");
#endif

      is_animating = false;
      // Finish going to transformation mode
      mode2to3finish();
    }
  }

  // Right movement input
  if (in == INPUT_RIGHT) {
    //If the next alien number is bigger than the total number of aliens
    //then go back to first alien, else go to the next alien
    if ((g_alien_n + 1) > ALIEN_LAST_INDEX) {
      g_alien_n = 0;
    } else {
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
  }
  // Left movement input
  else if (in == INPUT_LEFT) {
    //If the next alien number is less than 0
    //then go back to the last alien, else go to the previous alien
    if ((g_alien_n - 1) < 0) {
      g_alien_n = ALIEN_LAST_INDEX;
    } else {
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
  }
  // Start button is pressed
  else if (in == INPUT_START_BUTTON) {
    //Go to start mode
    mode2to1();
  }
  // Select button is pressed
  else if (in == INPUT_SELECT_BUTTON) {
    //Go to transformation mode
    mode2to3start();
  }
}

//Mode 3
//Function for transformation
void transformed_mode(Input in) {

  // Select button is pressed
  if (in == INPUT_SELECT_BUTTON) {
    //Go to back to start
    mode3to1();
  }

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
