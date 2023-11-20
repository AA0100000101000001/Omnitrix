

#include "omnitrix_header.h"

void setup() {

  Serial.begin(115200);
  delay(100);

  //Pins
  pinMode(buttonPin, INPUT);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(SW, INPUT);
  //leds
  pinMode(rgb_r, OUTPUT);
  pinMode(rgb_g, OUTPUT);
  pinMode(rgb_b, OUTPUT);
  //pinMode(TFT_BL, OUTPUT); //Screen

  //Reduce Power consumption
  setCpuFrequencyMhz(80); //Reduce CPU Freq
  WiFi.mode(WIFI_OFF); //Turn off WIFI

  //DFT sound initialise
  //Uncomment for sound
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);
  //Check Connection
  if (!DF1201S.begin(Serial1)){
    Serial.println("DFT Init failed, please check the wire connection! Muted");
    //mute = true; //If no sound device is detected mute audio
    delay(1000);
  } 
  //else {
    DF1201S.setVol(10); //Volume = 10
    DF1201S.setPrompt(true); //shut down starting tone
    DF1201S.setLED(true); //Set DFplayer led off
    DF1201S.switchFunction(DF1201S.MUSIC); //MUSIC function
    DF1201S.setPlayMode(DF1201S.SINGLE); //Play one sound only
  //}
  playSound(1); //Play boot sound
  

  Serial.println("START");

  tft.begin();
  delay(1000);
  //disconnect TFT_BL from deep sleep to save energy
  //gpio_reset_pin(GPIO_NUM_38);

  //readDisplayStatus();

  //If the omnitrix is booting for the first time then initialise alienNo, mode
  //When it wakes up from deep sleep the values will be saved
  if (bootCount == 0) {
    alienNo = 0;
    mode = 1;
    rtc.setTime(0, 0, 0, 1, 1, 2023);  // Set Time to 1st Jan 2023 00:00:00
    playSound(1); //Play boot sound

    //Display start screen
    tft.fillScreen(OMNITRIX_GREEN);
    ShowSymbols();
  }
  bootCount++;
  Serial.print("Boot number: ");
  Serial.println(bootCount);

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

  //The omnitrix will wake up when the button is pressed
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_5,1);

}

void loop() {
  
  //reset timer
  start = rtc.getLocalEpoch();
  
  //Omnitrix is in start mode
  if (mode == 1) {

    //Go to start mode
    startMode();

  //Omnitrix is ready to select alien
  } else if (mode == 2) {
    
    //Go to selection mode
    selectAlienMode();
  
  //Alien is selected
  } else if (mode == 3) {

    //Go to tranformed mode
    transformedMode();

  //Omnitrix is recharging
  } else if (mode == 4) {
    
    //Go to recharge mode
    rechargeMode();

  }

}

//Check time for deep sleep
void check_timer() {

  //if the time has passed then go to deep sleep
  if ((rtc.getLocalEpoch() - start) > DEEP_SLEEP_TIMER) {

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
        transformation_start_time_offset = rtc.getLocalEpoch() - transformation_start_time;

        //Configure the wake up source to wake up every time the transfomation is done
        esp_sleep_enable_timer_wakeup(transform_time_val - transformation_start_time_offset * uS_TO_S_FACTOR);
        Serial.println("Transformation: Setup ESP32 to sleep for every " + String(ALIEN_TRANSFORMATION_TIME_TEST - transformation_start_time_offset) +
        " Seconds");

      }
      //Recharging mode is not done, enable deep sleep timer for recharging offset
      else if (mode == 4) {

        //Set offset to time passed since last time the timer was checked (in sec)
        recharging_start_time_offset = rtc.getLocalEpoch() - recharging_start_time;

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

void readDisplayStatus() {

  /*uint8_t d1 = 0;
  uint8_t d2 = 0;
  uint8_t d3 = 0;
  uint8_t d4 = 0;
  */

  uint32_t data = 0;
  data = tft.readcommand32(0x04);
  Serial.print("data : ");
  Serial.println(data);
  
  /*tft.writecommand(0x09); //Read Display Status
  // Dummy read to throw away don't care value
  tft.readcommand8();
  

  Serial.print("d1 : ");
  Serial.println(d1);
  Serial.print("d2 : ");
  Serial.println(d2);
  Serial.print("d3 : ");
  Serial.println(d3);
  Serial.print("d4 : ");
  Serial.println(d4);
  */
}