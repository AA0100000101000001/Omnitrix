

#include "omnitrix_header.h"

//------INTERRUPTS------------------------
//----------------------------------------
#if defined POP_UP_BUTTONS_ENABLED

void IRAM_ATTR button_interrupt() {
  //Debouncing
  interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200)
  {
    buttonState = true;
    lastInterruptTime = interruptTime;
  }
}

void IRAM_ATTR Selectbutton_interrupt() {
  //Debouncing
  interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200)
  {
    selectbuttonState = true;
    lastInterruptTime = interruptTime;
  }
}

#endif

#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED

void IRAM_ATTR Rightbutton_interrupt() {
  //Debouncing
  interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200)
  {
    rightState = true;
    lastInterruptTime = interruptTime;
  }
}

void IRAM_ATTR Leftbutton_interrupt() {
  //Debouncing
  interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200)
  {
    interruptTime = true;
    lastInterruptTime = interruptTime;
  }
}

#endif
//------INTERRUPTS-END--------------------
//----------------------------------------

void setup() {

  Serial.begin(115200);
  delay(100);

  //initialize inputs and interrupts
  #if defined POP_UP_BUTTONS_ENABLED
    pinMode(START_BUTTON_PIN, INPUT);
    attachInterrupt(START_BUTTON_PIN, button_interrupt, RISING);
    pinMode(SELECT_BUTTON_PIN, INPUT);
    attachInterrupt(SELECT_BUTTON_PIN, Selectbutton_interrupt, RISING);
  #endif
  #if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED
    pinMode(RIGHT_BUTTON_PIN, INPUT);
    attachInterrupt(RIGHT_BUTTON_PIN, Rightbutton_interrupt, RISING);
    pinMode(LEFT_BUTTON_PIN, INPUT);
    attachInterrupt(LEFT_BUTTON_PIN, Leftbutton_interrupt, RISING);
  #endif

  //Init leds
  #if defined RGB_LEDS_ENABLED

    //Use of three pin RGB LEDS
    #if defined RGB_LEDS_ENABLED
      pinMode(RGB_R_PIN, OUTPUT);
      pinMode(RGB_G_PIN, OUTPUT);
      pinMode(RGB_B_PIN, OUTPUT);
    #endif

  #endif
  //pinMode(TFT_BL, OUTPUT); //Screen

  //Reduce Power consumption
  setCpuFrequencyMhz(80); //Reduce CPU Freq
  //WiFi.mode(WIFI_OFF); //Turn off WIFI

  //Sound initialization
  #if defined SOUND_ENABLED
    //DFT sound initialise
    #if defined SOUND_DFPLAYER_PRO_ENABLED
      Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);
      //Check Connection
      if (!DF1201S.begin(Serial1)){
        Serial.println("DFT Init failed, Muted");
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
    #endif

  #endif
  

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
    RTC_setTime(0, 0, 0, 1, 1, 2023);  // Set Time to 1st Jan 2023 00:00:00

    #if defined SOUND_ENABLED
      playSound(1); //Play boot sound
    #endif

    //Display start screen
    tft.fillScreen(OMNITRIX_GREEN);
    ShowSymbols();
  }
  bootCount++;
  Serial.print("Boot number: ");
  Serial.println(bootCount);

  //The omnitrix will wake up when the button is pressed
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_5,1);

  //Check the wakeup reason for ESP32 and operate accordingly for timers
  get_wakeup_reason();

  //After the wake up, turn on leds
  #if defined RGB_LEDS_ENABLED
    if (mode == 4) {
      //Green led colour
      analogWrite(RGB_R_PIN, RED_LED_R);
      analogWrite(RGB_G_PIN, RED_LED_G);
      analogWrite(RGB_B_PIN, RED_LED_B);
    } else {
      //Red led colour
      analogWrite(RGB_R_PIN, GREEN_LED_R);
      analogWrite(RGB_G_PIN, GREEN_LED_G);
      analogWrite(RGB_B_PIN, GREEN_LED_B);
    }
  #endif
  
  //reset timer
  start = RTC_getLocalEpoch();

}

void loop() {
  
  #if defined POP_UP_BUTTONS_ENABLED
  if (buttonState) {
      //Serial.printf("Button pressed\n");
      buttonState = false;

      //Check mode for start button
      startButtonModes();
      
  }
  if (selectbuttonState) {
    //Serial.printf("Select Button pressed\n");
    selectbuttonState = false;

    //Check mode for select button
    selectbuttonModes();

  }
  #endif
  //Use of micro swithes for rotary encoder
  #if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED
  if (rightState) {
    Serial.printf("Right Button pressed\n");
    rightState = false;

    //Check mode for right button
    rightButtonModes();

  }
  if (leftState) {
    Serial.printf("Left Button pressed\n");
    leftState = false;

    //Check mode for left button
    leftButtonModes();

  }
  #endif

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
    //tft.writecommand(0x10);
    //delay(10);
    
    esp_deep_sleep_start();
  }
}

#if defined SOUND_ENABLED
void playSound(int16_t s) {

  //If mute is false then play selected sound
  if (!mute) {

    //DFT sound
    #if defined SOUND_DFPLAYER_PRO_ENABLED
    DF1201S.playFileNum(s); 
    #endif
  }
}
#endif

void get_wakeup_reason() {

  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  //Check wake up reason
  switch(wakeup_reason)
  {
    //Wake up by button so timer is not finished if enabled
    case ESP_SLEEP_WAKEUP_EXT0 : {

      //Serial.println("Wakeup caused by external signal using RTC_IO"); 

      //Transformation mode is not done, enable deep sleep timer for transformation offset
      if (mode == 3) {

        //Set offset to time passed since last time the timer was checked (in sec)
        transformation_start_time_offset = RTC_getLocalEpoch() - transformation_start_time;

        //Configure the wake up source to wake up every time the transfomation is done
        esp_sleep_enable_timer_wakeup((transform_time_val - transformation_start_time_offset) * uS_TO_S_FACTOR);
        Serial.println("Transformation: Setup ESP32 to sleep for every " + String(transform_time_val - transformation_start_time_offset) +
        " Seconds");

      }
      //Recharging mode is not done, enable deep sleep timer for recharging offset
      else if (mode == 4) {

        //Set offset to time passed since last time the timer was checked (in sec)
        recharging_start_time_offset = RTC_getLocalEpoch() - recharging_start_time;

        //Configure the wake up source to wake up every time the recharge is done
        esp_sleep_enable_timer_wakeup((recharge_time_val - recharging_start_time_offset) * uS_TO_S_FACTOR);
        Serial.println("Recharging1: Setup ESP32 to sleep for every " + String(recharge_time_val - recharging_start_time_offset) +
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
