/* This program tests the ability of the omnitrix to go into deep sleep mode after a short period of time of inactivity and wake up when the transformation time is over 
in order to go to the recharging state.*/

#include <ESP32Time.h>
ESP32Time rtc;

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define DEEP_SLEEP_TIMER 5 // 5 sec
uint32_t start; //timer for deep sleep

#define ALIEN_TRANSFORMATION_TIME_TEST 20 //10 sec
#define OMNITRIX_RECHARGE_TIME_TEST 20 //10 sec
#define ALIEN_TRANSFORMATION_TIME_DEFAULT 60 //1 min
#define OMNITRIX_RECHARGE_TIME_DEFAULT 60 //1 min

//Convert timer variables int micro seconds
int transform_time_val = ALIEN_TRANSFORMATION_TIME_TEST * uS_TO_S_FACTOR;
int recharge_time_val = OMNITRIX_RECHARGE_TIME_TEST * uS_TO_S_FACTOR;

//Time variables that are saved in deep sleep mode
RTC_DATA_ATTR uint32_t transformation_start_time;
RTC_DATA_ATTR uint32_t recharging_start_time;
RTC_DATA_ATTR uint32_t transformation_start_time_offset;
RTC_DATA_ATTR uint32_t recharging_start_time_offset;

RTC_DATA_ATTR unsigned long millisOffset=0;

RTC_DATA_ATTR int bootCount = 0; //Number of times the system wakes up
RTC_DATA_ATTR int mode = 1; //Omnitrix state

int LED = 2;
const int buttonPin = 5; //Start button
const int SW = 3; //Encoder button

int buttonState = 0; //State of start button
int selectbuttonState = 0; //State of select button

// the setup function runs once when you press reset or power the board or wake up from deep sleep
void setup() {

  Serial.begin(115200);

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  delay(100);
  Serial.print("Mode: ");
  Serial.println(mode);

  if (bootCount == 1) {
    rtc.setTime(0, 0, 0, 1, 1, 2023);  // 1st Jan 2023 00:00:00
  }

  //The omnitrix will wake up when the button is pressed
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_5,1);

  //initialize inputs and outputs.
  pinMode(LED, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(SW, INPUT_PULLUP);

  //Check the wakeup reason for ESP32
  get_wakeup_reason();

  //reset timer 
  start = rtc.getLocalEpoch(); // Get epoch
}

// the loop function runs over and over again forever
void loop() {

  //Start mode
  if (mode == 1) {

    //Check if the pushbutton is pressed. 
	  buttonState = digitalRead(buttonPin);

    //If it is, then go to Alien Selection mode
    if (buttonState == HIGH) {
      // turn LED on:
      //digitalWrite(LED, HIGH);
      mode = 2;
      delay(200);
      Serial.println("Button pressed, select alien");

      //reset timer
      start = rtc.getLocalEpoch();
    }

    //Check timer for deep sleep
    check_timer();

  //Alien Selection mode
  } else if (mode == 2) {
    
    mode2();
    
  //Transormation mode
  } else if (mode == 3) {

    mode3();

  //Recharging mode
  } else if (mode == 4) {

    mode4();

  }

}

void mode2() {

  for(;mode == 2;) {

    //Read select button state
    selectbuttonState = digitalRead(SW);

    //If select button is pressed then go to next mode
    if (selectbuttonState == LOW) {
      
      mode2ToMode3();
      
      //reset timer
      start = rtc.getLocalEpoch();

    }

    //Read start button state
    buttonState = digitalRead(buttonPin);

    // check if start button is pressed. If it is then go to the previous mode
    if (buttonState == HIGH) {
      // turn LED off:
      //digitalWrite(LED, LOW);
      mode = 1;
      delay(200);
      Serial.println("Button pressed back to start");

      //reset timer
      start = rtc.getLocalEpoch();
    }

    //Check timer for deep sleep
    check_timer();

  }

}

void mode2ToMode3() {

  mode = 3;
  delay(200);
  Serial.println("Tranformed into alien");

  Serial.println(rtc.getLocalEpoch()); //Get minutes passed since first boot
  //reset transformation time to current epoch
  transformation_start_time = rtc.getLocalEpoch();
  //Set offset to time passed since last time the timer was checked (in sec)
  transformation_start_time_offset = rtc.getLocalEpoch() - transformation_start_time;

  //Configure the wake up source to wake up every time the transfomation is done
  esp_sleep_enable_timer_wakeup(transform_time_val - transformation_start_time_offset * uS_TO_S_FACTOR);
  Serial.println("Transformation: Setup ESP32 to sleep for every " + String(ALIEN_TRANSFORMATION_TIME_TEST - transformation_start_time_offset) +
  " Seconds");

}

void mode3() {

  for(;mode == 3;) {

    //Check transformation time
    //Transformation time is done while omnitrix does not sleep
    if ((rtc.getLocalEpoch() - transformation_start_time) > ALIEN_TRANSFORMATION_TIME_TEST) {

      mode3ToMode4();

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
      mode = 1;
      Serial.println("Button pressed, untransforming and going back to Start mode");

      //Disable waking up by timer
      esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
      Serial.println("Disabled Timer1");

      //reset timer
      start = rtc.getLocalEpoch();
    }

  }

}

void mode4() {
  
  for(;mode == 4;) {

    //Check recharging time
    //Recharging time is done
    if ((rtc.getLocalEpoch() - recharging_start_time) > OMNITRIX_RECHARGE_TIME_TEST) {

      mode4ToMode1();

    //Recharging time is not finished
    } else {
      //Set offset to time passed since last time the timer was checked (in sec)
      recharging_start_time_offset = rtc.getLocalEpoch() - recharging_start_time;
    }
  

    //Check timer for deep sleep
    check_timer();

  }

}

void mode3ToMode4() {

  //reset recharging time
  recharging_start_time = rtc.getLocalEpoch();
  //Set offset to time passed since last time the timer was checked (in sec)
  recharging_start_time_offset = rtc.getLocalEpoch() - recharging_start_time;

  Serial.println(recharging_start_time_offset);
  Serial.println(recharge_time_val);

  mode = 4;

  //Configure the wake up source to wake up every time the recharge is done
  esp_sleep_enable_timer_wakeup(recharge_time_val - recharging_start_time_offset * uS_TO_S_FACTOR);
  Serial.println("Recharging1: Setup ESP32 to sleep for every " + String(OMNITRIX_RECHARGE_TIME_TEST - recharging_start_time_offset) +
  " Seconds");

}

void mode4ToMode1() {

  mode = 1;

  //Disable waking up by timer
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
  Serial.println("Disabled Timer2");

}

//Check time for deep sleep
void check_timer() {

  //if the time has passed then go to deep sleep
  if ((rtc.getLocalEpoch() - start) > DEEP_SLEEP_TIMER) {

    Serial.println("Going to sleep");
    
    esp_deep_sleep_start();
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

      Serial.println("Wakeup caused by external signal using RTC_IO"); 

      //Transformation mode is done, enable deep sleep timer for recharhing
      if (mode == 3) {

        //Set offset to time passed since last time the timer was checked (in sec)
        transformation_start_time_offset = rtc.getLocalEpoch() - transformation_start_time;

        //Configure the wake up source to wake up every time the transfomation is done
        esp_sleep_enable_timer_wakeup(transform_time_val - transformation_start_time_offset * uS_TO_S_FACTOR);
        Serial.println("Transformation: Setup ESP32 to sleep for every " + String(ALIEN_TRANSFORMATION_TIME_TEST - transformation_start_time_offset) +
        " Seconds");

      }
      //Recharging mode is done, disable timer
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

      Serial.println("Wakeup caused by timer"); 

      //Go to recharge mode after transformation time is finished
      if (mode == 3) {

        mode3ToMode4();

        Serial.println(rtc.getLocalEpoch()); //Get minutes passed since first boot

    
      //Go to start mode after recharge timer is finished
      } else if (mode == 4) {

        mode4ToMode1();

      }
        break;
      }
    //Wake up not caused by deep sleep
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }

}
