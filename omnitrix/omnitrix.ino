

#include "omnitrix_header.h"

void setup() {

  Serial.begin(9600);

  //Pins
  pinMode(buttonPin, INPUT);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  //leds
  pinMode(rgb_r, OUTPUT);
  pinMode(rgb_g, OUTPUT);
  pinMode(rgb_b, OUTPUT);
  //pinMode(TFT_BL, OUTPUT); //Screen

  //Reduce Power consumption
  setCpuFrequencyMhz(80); //Reduce CPU Freq
  WiFi.mode(WIFI_OFF); //Turn off WIFI

  //DFT sound initialise
  /*Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);
  while(!DF1201S.begin(Serial1)){
    Serial.println("Init failed, please check the wire connection!");
    mute = true; //If no sound device is detected mute audio
    delay(1000);
  }
  DF1201S.setVol(10); //Volume = 10
  DF1201S.setPrompt(false); //shut down starting tone
  DF1201S.setLED(false); //Set DFplayer led off
  DF1201S.switchFunction(DF1201S.MUSIC); //MUSIC function
  DF1201S.setPlayMode(DF1201S.SINGLE); //Play one sound only
  */

  //If the omnitrix is booting for the first time then initialise alienNo, mode
  //When it wakes up from deep sleep the values will be saved
  if (bootCount == 0) {
    alienNo = 0;
    mode = 1;
    playSound(1); //Play boot sound
  }
  bootCount++;
  Serial.print("Boot number: ");
  Serial.println(bootCount);

  //set tranform and recharge timer
  //rtc.setTime(30, 24, 15, 17, 1, 2021);  // 17th Jan 2021 15:24:30

  //The omnitrix will wake up when the button is pressed
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_5,1);

  //disconnect TFT_BL from deep sleep to save energy
  //gpio_reset_pin(GPIO_NUM_38);

  tft.begin();
  //analogWrite(TFT_BL, 100);
  //esp_lcd_panel_disp_on_off(,on)
  
  //Initialise up line sprite
  upLine.setColorDepth(8);
  upLine.createSprite(40, 60);

  upLine.fillSprite(TFT_TRANSPARENT);

  //Initialise down line sprite
  downLine.setColorDepth(8);
  downLine.createSprite(40, 60);

  downLine.fillSprite(TFT_TRANSPARENT);
  
  //After the wake up, display apropriate screen
  if (mode == 1) {

    //Display start screen
    tft.fillScreen(OMNITRIX_GREEN);
    ShowSymbols();
  } else if (mode == 2) {

    //Display backround selection screen
    tft.fillScreen(OMNITRIX_GREEN);
    ShowSelectSymbols();
  } else if (mode == 3) {

    Serial.print("Transformation time ");
    Serial.println(transform_timer);
    Serial.println(offsetMillis());

    //Display transformation screen
    tft.fillScreen(TFT_WHITE);
    ShowSymbols();
  } else if (mode == 4) {

    Serial.print("recharging time ");
    Serial.println(recharge_timer);
    Serial.println(offsetMillis());

    //Display red screen
    tft.fillScreen(OMNITRIX_RED);
    ShowSymbols();
  }

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


}

void loop() {

  
  //reset timer
  start = offsetMillis();
  
  //Omnitrix is in start mode
  if (mode == 1) {

    //Go to start mode
    startMode();

  //Omnitrix is ready to select alien
  } else if (mode == 2) {
    
    ShowAlien();
    
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

	//Serial.println("checking timer");
  
  //if the time has passed then go to deep sleep
  if ((offsetMillis() - start) > DEEP_SLEEP_TIMER) {

    Serial.println("Going to sleep");
    
    //turn off screen
    tft.fillScreen(TFT_BLACK);
    //analogWrite(TFT_BL, 0);
    
    esp_deep_sleep_start();
  }
}

//or use rtc.getMillis()
//Function for saving millis() time over deep sleep
unsigned long offsetMillis()
{
    return millis() + millisOffset;
}

void playSound(int16_t s) {

  //If mute is false then play selected sound
  if (!mute) {
    //DF1201S.playFileNum(s); 
  }
}