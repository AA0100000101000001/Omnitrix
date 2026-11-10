

#include "omnitrix_header.h"


void setup() {

  //Reduce Power consumption
  setCpuFrequencyMhz(DEFAULT_CPU_FREQ);  //Reduce CPU Freq
  //WiFi.mode(WIFI_OFF); //Turn off WIFI

  //initialize inputs and interrupts
  init_input();
  //Initialize leds
  init_leds();
  //Initizlize sound
  init_sound();
  //Initialize deep sleep mode
  init_time_sleep();

  //pinMode(TFT_BL, OUTPUT); //Screen

#if defined ENABLE_SERIAL
  Serial.begin(115200);
  Serial.println("START");
#endif

  tft.begin();
  //disconnect TFT_BL from deep sleep to save energy
  //gpio_reset_pin(GPIO_NUM_38);

  //If the omnitrix is booting for the first time then initialise g_alien_n, g_mode
  //When it wakes up from deep sleep the values will be saved
  if (g_first_boot) {
    delay(400); // delay fot tft.begin and serial
    g_alien_n = 0;
    g_mode = 1;
    rtc_set_time(0, 0, 0, 1, 1, 2023, 0);  // Set Time to 1st Jan 2023 00:00:00

    play_sound(1);  //Play boot sound

    //Display start screen
    tft.fillScreen(OMNITRIX_GREEN);
    show_symbols();

    g_first_boot = false;  //Never go to this section again
  }

  //reset timer
  reset_timer();

}

void loop() {

  //Get input from interrupts
  Input in = check_input();

  //Start mode
  if (g_mode == 1) {
    start_mode(in);
  }
  //Select alien mode
  else if (g_mode == 2) {
    select_alien_mode(in);
  }
  //Transformed mode
  else if (g_mode == 3) {
    transformed_mode(in);
  }
  //Recharging mode
  else if (g_mode == 4) {
    recharge_mode();
  }

  //Check timer for deep sleep
  check_timer();
}

//Initizlize sound
void init_sound() {
#if defined SOUND_ENABLED

  //DFT sound initialise
#if defined SOUND_DFPLAYER_PRO_ENABLED
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);
  //Check Connection
  if (!DF1201S.begin(Serial1)) {
#if defined ENABLE_SERIAL
    Serial.println("DFT Init failed, Muted");
#endif
    g_mute = true;  //If no sound device is detected mute audio
    delay(1000);
  } else {
    DF1201S.setVol(10);                     //Volume = 10
    DF1201S.setPrompt(true);                //shut down starting tone
    DF1201S.setLED(true);                   //Set DFplayer led off
    DF1201S.switchFunction(DF1201S.MUSIC);  //MUSIC function
    DF1201S.setPlayMode(DF1201S.SINGLE);    //Play one sound only
  }
  //play_sound(1); //Play boot sound
#endif

#endif
}


void play_sound(int16_t s) {
#if defined SOUND_ENABLED

  //If mute is false then play selected sound
  if (!g_mute) {

//DFT sound
#if defined SOUND_DFPLAYER_PRO_ENABLED
    DF1201S.playFileNum(s);
#endif
  }
#endif
}

//Initialize leds
void init_leds() {
#if defined LEDS_ENABLED

//Use of three pin RGB LEDS
#if defined RGB_LEDS_ENABLED
  pinMode(RGB_R_PIN, OUTPUT);
  pinMode(RGB_G_PIN, OUTPUT);
  pinMode(RGB_B_PIN, OUTPUT);
#endif

  //After the wake up, turn on leds
  if (g_mode == 4) {
    //Green led colour
    analogWrite(RGB_R_PIN, RED_LED_R);
    analogWrite(RGB_G_PIN, RED_LED_G);
    analogWrite(RGB_B_PIN, RED_LED_B);
  } else {
    //Red led colour
    analogWrite(RGB_R_PIN, GREEN_LED_R);
    analogWrite(RGB_G_PIN, GREEN_LED_G);
    analogWrite(RGB_B_PIN, GREEN_LED_B);
  }

#endif
}

