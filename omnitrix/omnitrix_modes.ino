
//Switch statement for start button modes
void startButtonModes() {

  switch (mode) {
    //Omnitrix is in start mode
    case 1:
      //Go to select alien mode
		  mode1to2();

      //reset timer
      start = RTC_getLocalEpoch();
      break;

    //Omnitrix is in select alien mode
    case 2:
      //Go to start mode
      mode2to1();

      //reset timer
      start = RTC_getLocalEpoch();
      break;
  }

}

//Switch statement for right button modes
void rightButtonModes() {

  #if defined SOUND_ENABLED
  playSound(3); //Play move encoder forward 
  #endif

  switch (mode) {
    //Omnitrix is in select alien mode
    case 2:
      //If the next alien number is bigger than the total number of aliens
      //then go back to first alien, else go to the next alien
      if ((alienNo  + 1)> ALIEN_NUMBER ) {
        alienNo = 0;
      }
      else {
        alienNo += 1;
      }

      //Display green backround png to erase previous alien
      eraseAlien();
      //Display alien
      ShowAlien();

      Serial.print("Right, alien no:");
      Serial.println(alienNo);
      delay(200);
      break;
  }

  //reset timer
  start = RTC_getLocalEpoch();

}

//Switch statement for left button modes
void leftButtonModes() {

  #if defined SOUND_ENABLED
  playSound(4); //Play move encoder backwards 
  #endif

  switch (mode) {
    //Omnitrix is in select alien mode
    case 2:
      //If the next alien number is less than 0
      //then go back to the last alien, else go to the previous alien
      int alien_overflow = alienNo;
      if ((alien_overflow - 1) < 0 ) {
        alienNo = ALIEN_NUMBER;
      }
      else {
        alienNo -= 1;
      }
          
      //Erase previous alien
      eraseAlien();
      //Display alien
      ShowAlien();

      Serial.print("Left, alien no:");
      Serial.println(alienNo);
      delay(200);
      break;
  }

  //reset timer
  start = RTC_getLocalEpoch();

}

//Switch statement for select button modes
void selectbuttonModes() {

  switch (mode) {
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
  start = RTC_getLocalEpoch();

  Serial.print("mode ");
  Serial.println(mode);

}

//Mode 3
//Function for transformation
void transformedMode() {

  //Check transformation time
  //Transformation time is done while omnitrix is not sleeping
  if ((RTC_getLocalEpoch() - transformation_start_time) > transform_time_val) {

    //Go to next mode
    mode3to4();

  //Transformation time is not finished
  } else {
    //Set offset to time passed since last time the timer was checked (in sec)
    transformation_start_time_offset = RTC_getLocalEpoch() - transformation_start_time;
  }
}

//Mode 4
//Recharge mode
void rechargeMode() {

  //Check recharging time
  //Recharging time is done while omnitrix is not sleeping
  if ((RTC_getLocalEpoch() - recharging_start_time) > recharge_time_val) {
      
    //Go to first mode
    mode4to1();

  //Recharging time is not finished
  } else {
    //Set offset to time passed since last time the timer was checked (in sec)
    recharging_start_time_offset = RTC_getLocalEpoch() - recharging_start_time;
  }
  
}
