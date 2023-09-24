/* This Program turns on the inbuild LED of the ESP32 for 500 milli sec and then turns it off for another 500 milli sec. This procedure loops indefinitetly */


int LED = 2;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);                      // wait
  digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
  delay(500);                      // wait
}
