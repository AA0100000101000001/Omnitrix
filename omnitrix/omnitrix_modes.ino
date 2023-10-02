

//Mode 1
//Function to display start
void startMode() {
	
	for(;mode == 1;) {
		//Read start button state
		buttonState = digitalRead(buttonPin);

		// check if start button is pressed. If it is then go to the next mode
		if (buttonState == HIGH) {

      playSound(2); //Play select sound

      //Display animation
      showAnimation();
      delay(200);
      //tft.fillScreen(OMNITRIX_GREEN);
      //ShowSelectSymbols();
      
	    delay(400);

      //Go to next mode
		  mode1to2();

      //reset timer
      start = rtc.getLocalEpoch();
		}

    //Check timer for deep sleep
    check_timer();
	}

}

//Mode 2
//Function for alien selection
void selectAlienMode() {

  for(;mode == 2;) {

    //Read right and left state
    rightState = digitalRead(A);
    leftState = digitalRead(B);

    //Encoder is turned right
    if (rightState == LOW) {

      playSound(3); //Play move encoder forward 

      //If the next alien number is bigger than the total number of aliens
      //then go back to first alien, else go to the next alien
      if ((alienNo  + 1)> ALIEN_NUMBER ) {
        alienNo = 0;
      }
      else {
        alienNo += 1;
      }

      //Display alien
      //tft.fillScreen(OMNITRIX_GREEN);
      //ShowSelectSymbols();
      //Display green backround png to erase previous alien
      eraseAlien();
      ShowAlien();

      Serial.print("Right, alien no:");
      Serial.println(alienNo);
      delay(200);

      //reset timer
      start = rtc.getLocalEpoch();
    }
    //Encoder is turned left
    else if (leftState == LOW) {
      
      playSound(4); //Play move encoder backwards 

      //If the next alien number is less than 0
      //then go back to the last alien, else go to the previous alien
      if ((alienNo - 1) < 0 ) {
        alienNo = ALIEN_NUMBER;
      }
      else {
        alienNo -= 1;
      }

      //Display alien
      //tft.fillScreen(OMNITRIX_GREEN);
      //ShowSelectSymbols();
      //Erase previous alien
      eraseAlien();
      ShowAlien();

      Serial.print("Left, alien no:");
      Serial.println(alienNo);
      delay(200);
      
      //reset timer
      start = rtc.getLocalEpoch();
    }

    //Read select button state
    selectbuttonState = digitalRead(SW);

    //If select button is pressed then go to next mode
    if (selectbuttonState == LOW) {

      playSound(5); //Play transformation sound

      //Display tranformation image
      tft.fillScreen(OMNITRIX_GREEN);
      delay(600);

      tft.fillScreen(TFT_WHITE);
      ShowSymbols();
      Serial.println(alienNo);

      delay(200);

      //Go to next mode
      mode2to3();
      
      //reset timer
      start = rtc.getLocalEpoch();

    }

    
    //Read start button state
    buttonState = digitalRead(buttonPin);

    // check if start button is pressed. If it is then go to the previous mode
    if (buttonState == HIGH) {
      
      playSound(4); //Play move backwards 

      delay(300);

      //display start
      tft.fillScreen(OMNITRIX_GREEN);
      ShowSymbols();

      //Go to previous mode
      mode2to1();
      
      //reset timer
      start = rtc.getLocalEpoch();
    }

    //Check timer for deep sleep
    check_timer();

  }

}

//Mode 3
//Function for transformation
void transformedMode() {

  for (;mode == 3;) {

    //Check transformation time
    //Transformation time is done while omnitrix does not sleep
    if ((rtc.getLocalEpoch() - transformation_start_time) > ALIEN_TRANSFORMATION_TIME_TEST) {
      
      playSound(7); //Play detransformation sound
      delay(2500);

      //Red led colour
      analogWrite(rgb_r, GREEN_LED_R);
      analogWrite(rgb_g, GREEN_LED_G);
      analogWrite(rgb_b, GREEN_LED_B);
      
      //Display red screen
      tft.fillScreen(OMNITRIX_RED);
      ShowSymbols();

      //Go to next mode
      mode3to4();
    //Transformation time is not finished
    } else {
      //Set offset to time passed since last time the timer was checked (in sec)
      transformation_start_time_offset = rtc.getLocalEpoch() - transformation_start_time;
    }

    //Check timer for deep sleep
    check_timer();

    //Read select button state
    selectbuttonState = digitalRead(SW);

    //if encoder button is pressed then go to Start mode
    if (selectbuttonState == LOW) {

      delay(200);

      //Go to Start mode
      mode3to1();

      //reset timer
      start = rtc.getLocalEpoch();
    }

  }
}

//Mode 4
//Recharge mode
void rechargeMode() {

  for (;mode == 4;) {

    //Check recharging time
    //Recharging time is done
    if ((rtc.getLocalEpoch() - recharging_start_time) > OMNITRIX_RECHARGE_TIME_TEST) {

      //Green led colour
      analogWrite(rgb_r, RED_LED_R);
      analogWrite(rgb_g, RED_LED_G);
      analogWrite(rgb_b, RED_LED_B);

      //Display green screen
      tft.fillScreen(OMNITRIX_GREEN);
      ShowSymbols();
      
      //Go to first mode
      mode4to1();
    //Recharging time is not finished
    } else {
      //Set offset to time passed since last time the timer was checked (in sec)
      recharging_start_time_offset = rtc.getLocalEpoch() - recharging_start_time;
    }

    //Check timer for deep sleep
    check_timer();
    
  }
}
