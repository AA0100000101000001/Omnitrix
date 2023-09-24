/* This program tests the rotatry encoder in input pull up connection.*/

int anienNo = 0;
int rightState = 0;
int leftState = 0;
int encoderPos = 0;
int buttonState = 0;


int A = 1;
int B = 4;
int S = 3;

void setup() {
  
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(S, INPUT_PULLUP);

  Serial.begin(9600);

}

void loop() {


  rightState = digitalRead(A);

  if (rightState == LOW) {
    Serial.println("Right");
    delay(200);
  }
  
  leftState = digitalRead(B);

  if (leftState == LOW) {
    Serial.println("Left");
    delay(200);
  }
  
  buttonState = digitalRead(S);
  if (buttonState == LOW) {
    delay(200);
    Serial.println("Select Button pressed");
  }
  

}
