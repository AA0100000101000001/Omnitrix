
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
