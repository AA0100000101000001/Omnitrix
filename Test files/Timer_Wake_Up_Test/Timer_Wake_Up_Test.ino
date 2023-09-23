
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define DEEP_SLEEP_TIMER 10000 // sec
uint32_t start; //timer for deep sleep

#define ALIEN_TRANSFORMATION_TIME_TEST 5000 //5 sec
#define OMNITRIX_RECHARGE_TIME_TEST 5000
#define ALIEN_TRANSFORMATION_TIME_DEFAULT 60000 //1 min
#define OMNITRIX_RECHARGE_TIME_DEFAULT 60000

int transform_time_val = ALIEN_TRANSFORMATION_TIME_TEST;
int recharge_time_val = OMNITRIX_RECHARGE_TIME_TEST;

//Time variables that are saved in deep sleep mode
RTC_DATA_ATTR uint32_t transform_timer;
RTC_DATA_ATTR uint32_t recharge_timer;
RTC_DATA_ATTR unsigned long millisOffset=0;

RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR int mode = 1;

int LED = 2;
const int buttonPin = 5; //Start button
const int SW = 3; //Encoder button

int buttonState = 0; //State of start button
int selectbuttonState = 0; //State of select button

// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(115200);

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //The omnitrix will wake up when the button is pressed
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_5,1);

  //Print the wakeup reason for ESP32
  get_wakeup_reason();

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(SW, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  
	buttonState = digitalRead(buttonPin);

  //If button is pressed then led is turned on
  if (mode == 1) {
    // check if the pushbutton is pressed. If it is, the buttonState is LOW:
    if (buttonState == HIGH) {
      // turn LED on:
      digitalWrite(LED, HIGH);
      mode = 2;
      delay(200);
      Serial.println("Button pressed, select alien");
    }

  //If button is pressed then led is turned off
  } else if (mode == 2) {
    
    mode2();
    
  
  } else if (mode == 3) {

    Serial.print("Tranformed into alien ");

  }

}

void mode2() {

  for(;mode == 2;) {

    //Read select button state
    selectbuttonState = digitalRead(SW);

    //If select button is pressed then go to next mode
    if (selectbuttonState == LOW) {
      mode = 3;
      Serial.println("Tranformed into alien");
    }

    //Read stasrt button state
    buttonState = digitalRead(buttonPin);

    // check if start button is pressed. If it is then go to the previous mode
    if (buttonState == HIGH) {
      // turn LED off:
      digitalWrite(LED, LOW);
      mode = 1;
      delay(200);
      Serial.println("Button pressed back to start");
    }


  }

}

void get_wakeup_reason() {

  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }

}
