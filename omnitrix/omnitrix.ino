

#include "omnitrix_header.h"


void setup() {

#if defined ENABLE_SERIAL
  Serial.begin(115200);
#endif

//initialize inputs and interrupts
#if defined POP_UP_BUTTONS_ENABLED
  pinMode(START_BUTTON_PIN, INPUT);
  attachInterrupt(START_BUTTON_PIN, button_interrupt, RISING);
  pinMode(SELECT_BUTTON_PIN, INPUT);
  attachInterrupt(SELECT_BUTTON_PIN, select_button_interrupt, RISING);
#endif

//Initialize micro switch rotary encoder
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED
  pinMode(RIGHT_BUTTON_PIN, INPUT);
  pinMode(LEFT_BUTTON_PIN, INPUT);
  attachInterrupt(RIGHT_BUTTON_PIN, right_button_interrupt, RISING);
  attachInterrupt(LEFT_BUTTON_PIN, left_button_interrupt, RISING);
//Initialize rotary encoder
#elif defined ROTARY_ENCODER_ENABLED
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(RIGHT_BUTTON_PIN, rot_encoder_interrupt, CHANGE);  // Need to detect both rising or falling signal
  attachInterrupt(LEFT_BUTTON_PIN, rot_encoder_interrupt, CHANGE);
#endif

//Init leds
#if defined RGB_LEDS_ENABLED

//Use of three pin RGB LEDS
#if defined RGB_LEDS_ENABLED
  pinMode(RGB_R_PIN, OUTPUT);
  pinMode(RGB_G_PIN, OUTPUT);
  pinMode(RGB_B_PIN, OUTPUT);
#endif

#endif
  //pinMode(TFT_BL, OUTPUT); //Screen

  //Reduce Power consumption
  setCpuFrequencyMhz(80);  //Reduce CPU Freq
//WiFi.mode(WIFI_OFF); //Turn off WIFI

//Sound initialization
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

#if defined ENABLE_SERIAL
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

#if defined SOUND_ENABLED
    play_sound(1);  //Play boot sound
#endif

    //Display start screen
    tft.fillScreen(OMNITRIX_GREEN);
    show_symbols();

    g_first_boot = false;  //Never go to this section again
  }

//External wakeup setup
//EXT0
#ifdef EXT0_ENABLED
  //The omnitrix will wake up when a button is pressed
  esp_sleep_enable_ext0_wakeup(EXT0_WAKEUP_PIN, EXT0_WAKEUP_MODE);
//EXT1
#elif defined EXT1_ENABLED
  //The omnitrix will wake up when a combination of buttons is pressed
  esp_sleep_enable_ext1_wakeup(EXT1_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH);
#endif

  //Check the wakeup reason for ESP32 and operate accordingly for timers
  get_wakeup_reason();

//After the wake up, turn on leds
#if defined RGB_LEDS_ENABLED
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

  //reset timer
  reset_timer();
}


void loop() {

#if defined POP_UP_BUTTONS_ENABLED
  if (g_start_button_state) {
#if defined ENABLE_VERBOSE_INFO
    Serial.printf("Button pressed\n");
#endif
    g_start_button_state = false;

    //Check mode for start button
    start_button_mode();
  }
  if (g_select_button_state) {
#if defined ENABLE_VERBOSE_INFO
    Serial.printf("Select Button pressed\n");
#endif
    g_select_button_state = false;

    //Check mode for select button
    select_button_mode();
  }
#endif
//Rotary encoder
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED || defined ROTARY_ENCODER_ENABLED
  if (g_right_state) {
#if defined ENABLE_VERBOSE_INFO
    Serial.printf("Right Button pressed\n");
#endif
    g_right_state = false;

    //Check mode for right button
    right_button_mode();
  }
  if (g_left_state) {
#if defined ENABLE_VERBOSE_INFO
    Serial.printf("Left Button pressed\n");
#endif
    g_left_state = false;

    //Check mode for left button
    left_button_mode();
  }
#endif

  if (g_mode == 3) {
    transformed_mode();
  }
  if (g_mode == 4) {
    recharge_mode();
  }


  //Check timer for deep sleep
  check_timer();
}


#if defined SOUND_ENABLED
void play_sound(int16_t s) {

  //If mute is false then play selected sound
  if (!g_mute) {

//DFT sound
#if defined SOUND_DFPLAYER_PRO_ENABLED
    DF1201S.playFileNum(s);
#endif
  }
}
#endif

