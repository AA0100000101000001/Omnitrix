/* This program uses a button in pull down resistor connection and the inbuild LED. When the button is pressed then the LED is turned on and when it is pressed again then the LED is turned off.*/

const int buttonPin = 5;  // the number of the pushbutton pin
const int ledPin = 2;    // the number of the LED pin

int buttonState = 0;  // variable for reading the pushbutton status
int mode = 1;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  //If button is pressed then led is turned on
  if (mode == 1) {
    // check if the pushbutton is pressed. If it is, the buttonState is LOW:
    if (buttonState == HIGH) {
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      mode = 2;
      delay(200);
      Serial.println("Button pressed");
    }

  //If button is pressed then led is turned off
  } else if (mode == 2) {
    
    if (buttonState == HIGH) {
      // turn LED off:
      digitalWrite(ledPin, LOW);
      mode = 1;
      delay(200);
      Serial.println("Button pressed");
    }
  }
}
