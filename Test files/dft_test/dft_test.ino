/* This program is testing the DFRobot_DF1201S library with a ESP32. It uses a button as input to play three sounds. When the button is pressed then the first sound is played, 
when it is pressed again then the second sound is played and when it is pressed for the third time then the third sound is played. If the button is pressed again then the sequence
will repeat from the first sound.*/

#include <DFRobot_DF1201S.h>
//#include <SoftwareSerial.h>

#define RXD1 18 //RX
#define TXD1 17 //TX
//SoftwareSerial DF1201SSerial(18, 17);  //RX  TX

const int buttonPin = 5;
int16_t sel = 9;

DFRobot_DF1201S DF1201S;
void setup(void){
  Serial.begin(115200);
  
  pinMode(buttonPin, INPUT);

  //DF1201SSerial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);
  //while(!DF1201S.begin(DF1201SSerial)){
  while(!DF1201S.begin(Serial1)){
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }
  
  DF1201S.setPrompt(false); //shut down starting tone
  /*Wait for the end of the prompt tone */
  delay(2000);
  /*Set playback mode to "repeat all"*/
  DF1201S.setPlayMode(DF1201S.SINGLE);
  /*Set volume to 10*/
  DF1201S.setVol(/*VOL = */10);
  Serial.print("VOL:");
  /*Get volume*/
  Serial.println(DF1201S.getVol());
  /*Enter music mode*/
  DF1201S.switchFunction(DF1201S.MUSIC);

}

void loop(){


  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    delay(200);

    if (sel == 9) {
    
      DF1201S.playFileNum(9);
      Serial.println(sel);
      sel = 10;

    } else if (sel == 10) {

      DF1201S.playFileNum(10);
      Serial.println(sel);
      sel = 11;
    } else if (sel == 11) {

      DF1201S.playFileNum(11);
      Serial.println(sel);
      sel = 9;
    }

  }

}
