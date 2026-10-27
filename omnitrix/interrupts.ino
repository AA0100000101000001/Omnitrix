
//------INTERRUPTS------------------------
//----------------------------------------
#if defined POP_UP_BUTTONS_ENABLED

void IRAM_ATTR button_interrupt() {
  static uint16_t lastInterruptTime = 0;
  uint16_t interruptTime = millis();
  //Debouncing
  if (interruptTime - lastInterruptTime > 200) {
    g_start_button_state = true;
    lastInterruptTime = interruptTime;
  }
}

void IRAM_ATTR select_button_interrupt() {
  static uint16_t lastInterruptTime = 0;
  uint16_t interruptTime = millis();
  //Debouncing
  if (interruptTime - lastInterruptTime > 200) {
    g_select_button_state = true;
    lastInterruptTime = interruptTime;
  }
}

#endif

//Micro Switches alternative to rotary encoder
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED

void IRAM_ATTR right_button_interrupt() {
  static uint16_t lastInterruptTime = 0;
  uint16_t interruptTime = millis();
  //Debouncing
  if (interruptTime - lastInterruptTime > 200) {
    g_right_state = true;
    lastInterruptTime = interruptTime;
  }
}

void IRAM_ATTR left_button_interrupt() {
  static uint16_t lastInterruptTime = 0;
  uint16_t interruptTime = millis();
  //Debouncing
  if (interruptTime - lastInterruptTime > 200) {
    g_left_state = true;
    lastInterruptTime = interruptTime;
  }
}
//Rotary Encoder
#elif defined ROTARY_ENCODER_ENABLED

void IRAM_ATTR rot_encoder_interrupt() {

  static uint8_t old_AB = 3;                                                                  // Lookup table index
  static int8_t encval = 0;                                                                   // Encoder value
  static const int8_t enc_states[] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0 };  // Lookup table
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  old_AB <<= 2;  // Remember previous state

  if (digitalRead(LEFT_BUTTON_PIN)) old_AB |= 0x02;   // Add current state of pin A
  if (digitalRead(RIGHT_BUTTON_PIN)) old_AB |= 0x01;  // Add current state of pin B

  encval += enc_states[(old_AB & 0x0f)];

  // Update counter if encoder has rotated a full indent, that is at least 4 steps
  if (encval > 3) {  // Four steps forward
    if (interruptTime - lastInterruptTime > 80) {
      g_right_state = true;  //Right
    }
    encval = 0;
    lastInterruptTime = millis();
  } else if (encval < -3) {  // Four steps backwards
    if (interruptTime - lastInterruptTime > 80) {
      g_left_state = true;  //Left
    }
    encval = 0;
    lastInterruptTime = millis();
  }
}

#endif
//------INTERRUPTS-END--------------------
//----------------------------------------

//Function that get input from interrupts. Returns:
//INPUT_START_BUTTON if start button is pressed
//INPUT_SELECT_BUTTON if select button is pressed
//INPUT_RIGHT if it gets right movement from encoder
//INPUT_LEFT if it gets left movement from encoder
//INPUT_NONE if none
static Input check_input() {

//Rotary encoder
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED || defined ROTARY_ENCODER_ENABLED
  if (g_right_state) {
#if defined ENABLE_VERBOSE_INFO
    Serial.printf("Right Button pressed\n");
#endif

//Play move encoder forward sound
#if defined SOUND_ENABLED
    play_sound(3); 
#endif
    g_right_state = false;

    //Check mode for right button
    //right_button_mode();
    reset_timer();
    return INPUT_RIGHT;
  }
  else if (g_left_state) {
#if defined ENABLE_VERBOSE_INFO
    Serial.printf("Left Button pressed\n");
#endif

//Play move encoder backwards
#if defined SOUND_ENABLED
    play_sound(4);  
#endif
    g_left_state = false;

    //Check mode for left button
    //left_button_mode();
    reset_timer();
    return INPUT_LEFT;
  }
#endif
#if defined POP_UP_BUTTONS_ENABLED
  else if (g_start_button_state) {
#if defined ENABLE_VERBOSE_INFO
    Serial.printf("Button pressed\n");
#endif
    g_start_button_state = false;

    //Check mode for start button
    //start_button_mode();
    reset_timer();
    return INPUT_START_BUTTON;
  }
  else if (g_select_button_state) {
#if defined ENABLE_VERBOSE_INFO
    Serial.printf("Select Button pressed\n");
#endif
    g_select_button_state = false;

    //Check mode for select button
    //select_button_mode();
    reset_timer();
    return INPUT_SELECT_BUTTON;
  }
#endif

  return INPUT_NONE;
}