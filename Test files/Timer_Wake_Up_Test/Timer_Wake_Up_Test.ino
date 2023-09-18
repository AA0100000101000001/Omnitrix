
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define DEEP_SLEEP_TIMER 10000 // sec
uint32_t start; //timer for deep sleep

RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR int mode = 1;

int LED = 2;
const int buttonPin = 5; //Start button

int buttonState = 0; //State of start button

// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(115200);

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //Print the wakeup reason for ESP32
  get_wakeup_reason();

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);
  pinMode(buttonPin, INPUT);
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
      Serial.println("Button pressed");
    }

  //If button is pressed then led is turned off
  } else if (mode == 2) {
    
    if (buttonState == HIGH) {
      // turn LED off:
      digitalWrite(LED, LOW);
      mode = 1;
      delay(200);
      Serial.println("Button pressed");
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
