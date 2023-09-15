

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

		  mode = 2;
		  Serial.println("Button pressed, select alien");
		  delay(400);
      //reset timer
      start = offsetMillis();
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
      start = offsetMillis();
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
      start = offsetMillis();
    }

    //Read select button state
    selectbuttonState = digitalRead(SW);

    //If select button is pressed then go to next mode
    if (selectbuttonState == LOW) {
      mode = 3;

      playSound(5); //Play transformation sound

      //Display tranformation image
      tft.fillScreen(OMNITRIX_GREEN);
      delay(600);

      tft.fillScreen(TFT_WHITE);
      ShowSymbols();
      Serial.println(alienNo);

      delay(200);

      Serial.print("Tranformed into alien ");
      Serial.println(alienNo);

      //Start timer for transormation
      transform_timer = offsetMillis();
      Serial.print("Transformation time ");
      Serial.println(transform_timer);
      
      //reset timer
      //start = offsetMillis();

    }

    
    //Read start button state
    buttonState = digitalRead(buttonPin);

    // check if start button is pressed. If it is then go to the previous mode
    if (buttonState == HIGH) {
      
      playSound(4); //Play move backwards 

      mode = 1;
      delay(300);

      //display start
      tft.fillScreen(OMNITRIX_GREEN);
      ShowSymbols();

      Serial.println("Button pressed, back to start");
      
      //reset timer
      start = offsetMillis();
    }

    //Check timer for deep sleep
    check_timer();

  }

}

//Mode 3
//Function for transformation
void transformedMode() {

  for (;mode == 3;) {

    //Serial.println(millis());


    //if encoder button is pressed then go to previous mode

    //check if transformation time is over
    if ((offsetMillis() - transform_timer) > transform_time_val) {
      
      playSound(7); //Play detransformation sound
      delay(2500);

      //Go to next mode
      mode = 4;

      //Red led colour
      analogWrite(rgb_r, GREEN_LED_R);
      analogWrite(rgb_g, GREEN_LED_G);
      analogWrite(rgb_b, GREEN_LED_B);
      
      //Display red screen
      tft.fillScreen(OMNITRIX_RED);
      ShowSymbols();

      Serial.println("Omnitrix is recharging");
      
      //Reset transform timer
      transform_timer = 0;

      //Start timer for recharging
      recharge_timer = offsetMillis();
      Serial.print("recharging time ");
      Serial.println(recharge_timer);
    }

    //Check timer for deep sleep
    check_timer();
    

  }
}

//Mode 4
//Recharge mode
void rechargeMode() {

  for (;mode == 4;) {

    //Serial.println(millis());
    
    //check if recharge time is over
    if ((offsetMillis() - recharge_timer) > recharge_time_val) {

      //Go to first mode
      mode = 1;
      Serial.println("Going back to start");

      //Green led colour
      analogWrite(rgb_r, RED_LED_R);
      analogWrite(rgb_g, RED_LED_G);
      analogWrite(rgb_b, RED_LED_B);

      //Display green screen
      tft.fillScreen(OMNITRIX_GREEN);
      ShowSymbols();

      //Reset recharge timer
      recharge_timer = 0;
    }

    //Check timer for deep sleep
    check_timer();
    
  }
}
