

#include "omnitrix_header.h"

//------INTERRUPTS------------------------
//----------------------------------------

void IRAM_ATTR button_interrupt() {
  //Debouncing
  button_time = millis();
  if (button_time - last_button_time > 200)
  {
    buttonState = true;
    last_button_time = button_time;
  }
}

void IRAM_ATTR Rightbutton_interrupt() {
  //Debouncing
  button_time = millis();
  if (button_time - last_button_time > 200)
  {
    rightState = true;
    last_button_time = button_time;
  }
}

void IRAM_ATTR Leftbutton_interrupt() {
  //Debouncing
  button_time = millis();
  if (button_time - last_button_time > 200)
  {
    leftState = true;
    last_button_time = button_time;
  }
}

void IRAM_ATTR Selectbutton_interrupt() {
  //Debouncing
  button_time = millis();
  if (button_time - last_button_time > 200)
  {
    selectbuttonState = true;
    last_button_time = button_time;
  }
}

//------INTERRUPTS-END--------------------
//----------------------------------------

void setup() {

  Serial.begin(115200);
  delay(100);

  //initialize inputs and interrupts
  pinMode(buttonPin, INPUT);
  attachInterrupt(buttonPin, button_interrupt, RISING);
  pinMode(RightPin, INPUT);
  attachInterrupt(RightPin, Rightbutton_interrupt, RISING);
  pinMode(LeftPin, INPUT);
  attachInterrupt(LeftPin, Leftbutton_interrupt, RISING);
  pinMode(SelectPin, INPUT);
  attachInterrupt(SelectPin, Selectbutton_interrupt, RISING);

  //Init leds
  pinMode(rgb_r, OUTPUT);
  pinMode(rgb_g, OUTPUT);
  pinMode(rgb_b, OUTPUT);
  //pinMode(TFT_BL, OUTPUT); //Screen

  //Reduce Power consumption
  setCpuFrequencyMhz(80); //Reduce CPU Freq
  //WiFi.mode(WIFI_OFF); //Turn off WIFI

  //DFT sound initialise
  //Uncomment for sound
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);
  //Check Connection
  if (!DF1201S.begin(Serial1)){
    Serial.println("DFT Init failed, please check the wire connection! Muted");
    mute = true; //If no sound device is detected mute audio
    delay(1000);
  } 
  else {
    DF1201S.setVol(10); //Volume = 10
    DF1201S.setPrompt(true); //shut down starting tone
    DF1201S.setLED(true); //Set DFplayer led off
    DF1201S.switchFunction(DF1201S.MUSIC); //MUSIC function
    DF1201S.setPlayMode(DF1201S.SINGLE); //Play one sound only
  }
  //playSound(1); //Play boot sound
  

  Serial.println("START");

  tft.begin();
  delay(1000);
  //disconnect TFT_BL from deep sleep to save energy
  //gpio_reset_pin(GPIO_NUM_38);

  //If the omnitrix is booting for the first time then initialise alienNo, mode
  //When it wakes up from deep sleep the values will be saved
  if (bootCount == 0) {
    alienNo = 0;
    mode = 1;
    RTC_setTime(0, 0, 0, 1, 1, 2023, 0);  // Set Time to 1st Jan 2023 00:00:00:00
    playSound(1); //Play boot sound

    //Display start screen
    tft.fillScreen(OMNITRIX_GREEN);
    ShowSymbols();
  }
  bootCount++;
  Serial.print("Boot number: ");
  Serial.println(bootCount);

  //The omnitrix will wake up when the button is pressed
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_5,1);

  //Check the wakeup reason for ESP32
  get_wakeup_reason();
  //analogWrite(TFT_BL, 100);

  //After the wake up, turn on leds
  if (mode == 4) {
    //Green led colour
    analogWrite(rgb_r, RED_LED_R);
    analogWrite(rgb_g, RED_LED_G);
    analogWrite(rgb_b, RED_LED_B);
  } else {
    //Red led colour
    analogWrite(rgb_r, GREEN_LED_R);
    analogWrite(rgb_g, GREEN_LED_G);
    analogWrite(rgb_b, GREEN_LED_B);
  }
  
  //reset timer
  start = RTC_getLocalEpoch();

}

void loop() {
  
  if (buttonState) {
      //Serial.printf("Button pressed\n");
      buttonState = false;

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
    if (rightState) {
      Serial.printf("Right Button pressed\n");
      rightState = false;

      playSound(3); //Play move encoder forward 

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
    if (leftState) {
      Serial.printf("Left Button pressed\n");
      leftState = false;

      playSound(4); //Play move encoder backwards 

      switch (mode) {
        //Omnitrix is in select alien mode
        case 2:
          //If the next alien number is less than 0
          //then go back to the last alien, else go to the previous alien
          if ((alienNo - 1) < 0 ) {
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
    if (selectbuttonState) {
      //Serial.printf("Select Button pressed\n");
      selectbuttonState = false;

      switch (mode) {
        //Omnitrix is in select alien mode
        case 2:
          //Go to transformation mode
          mode2to3();

          //reset timer
          start = RTC_getLocalEpoch();
          break;

        //Omnitrix is in transformation mode
         case 3:
          //Go to Start mode
          mode3to1();

          //reset timer
          start = RTC_getLocalEpoch();
          break;
      }
      Serial.print("mode ");
      Serial.println(mode);

    }
    if (mode == 3){
      transformedMode();
    }
    if (mode == 4){
      rechargeMode();
    }

    //Check timer for deep sleep
    check_timer();

}

//Check time for deep sleep
void check_timer() {

  //if the time has passed then go to deep sleep
  if ((RTC_getLocalEpoch() - start) > DEEP_SLEEP_TIMER) {

    Serial.println("Going to sleep");
    //Enter Display Sleep mode
    tft.writecommand(0x10);
    delay(10);
    
    esp_deep_sleep_start();
  }
}

void playSound(int16_t s) {

  //If mute is false then play selected sound
  if (!mute) {
    //Uncomment for sound
    DF1201S.playFileNum(s); 
  }
}

void get_wakeup_reason() {

  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  //Check wake up reason
  switch(wakeup_reason)
  {
    //Wake up by button
    case ESP_SLEEP_WAKEUP_EXT0 : {

      //Serial.println("Wakeup caused by external signal using RTC_IO"); 

      //Transformation mode is not done, enable deep sleep timer for transformation offset
      if (mode == 3) {

        //Set offset to time passed since last time the timer was checked (in sec)
        transformation_start_time_offset = RTC_getLocalEpoch() - transformation_start_time;

        //Configure the wake up source to wake up every time the transfomation is done
        esp_sleep_enable_timer_wakeup(transform_time_val - transformation_start_time_offset * uS_TO_S_FACTOR);
        Serial.println("Transformation: Setup ESP32 to sleep for every " + String(ALIEN_TRANSFORMATION_TIME_TEST - transformation_start_time_offset) +
        " Seconds");

      }
      //Recharging mode is not done, enable deep sleep timer for recharging offset
      else if (mode == 4) {

        //Set offset to time passed since last time the timer was checked (in sec)
        recharging_start_time_offset = RTC_getLocalEpoch() - recharging_start_time;

        //Configure the wake up source to wake up every time the recharge is done
        esp_sleep_enable_timer_wakeup(recharge_time_val - recharging_start_time_offset * uS_TO_S_FACTOR);
        Serial.println("Recharging1: Setup ESP32 to sleep for every " + String(OMNITRIX_RECHARGE_TIME_TEST - recharging_start_time_offset) +
        " Seconds");

      }

      break;
    }
    //Wake up by timer
    case ESP_SLEEP_WAKEUP_TIMER : {

      //Serial.println("Wakeup caused by timer"); 

      //Transformation mode is done, enable deep sleep timer for recharhing
      if (mode == 3) {
        
        delay(200);
        mode3to4();

    
      //Recharging mode is done, disable timer and go to start mode
      } else if (mode == 4) {

        delay(200);
        mode4to1();

      }
        break;
      }
    //Wake up not caused by deep sleep
    default : { } //Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }

}
