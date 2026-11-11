
#include "interrupts.h"


volatile bool g_start_button_state = 0;        //State of start button
volatile bool g_select_button_state = 0;  //State of select button
volatile bool g_right_state = 0;  //State of right
volatile bool g_left_state = 0;   //State of left


//initialize inputs and interrupts
void init_input() {

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
}

//------INTERRUPTS------------------------
//----------------------------------------

#define INTERRUPT_DEBOUNCE_TIME 200

//Debouncing wrapper function
static bool IRAM_ATTR debounce(uint32_t *last_interrupt_time, uint32_t debounce_ms) {
  
  uint32_t interrupt_time = millis();
  //Debouncing
  if (interrupt_time - *last_interrupt_time > debounce_ms) {
    *last_interrupt_time = interrupt_time;
    return true;
  }
  return false;
}


#if defined POP_UP_BUTTONS_ENABLED

void IRAM_ATTR button_interrupt() {
  static uint32_t last_interrupt_time = 0;
  //Debouncing
  if (debounce(&last_interrupt_time, INTERRUPT_DEBOUNCE_TIME)) {
    g_start_button_state = true;
  }
}

void IRAM_ATTR select_button_interrupt() {
  static uint32_t last_interrupt_time = 0;
  //Debouncing
  if (debounce(&last_interrupt_time, INTERRUPT_DEBOUNCE_TIME)) {
    g_select_button_state = true;
  }
}

#endif

//Micro Switches alternative to rotary encoder
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED

void IRAM_ATTR right_button_interrupt() {
  static uint32_t last_interrupt_time = 0;
  //Debouncing
  if (debounce(&last_interrupt_time, INTERRUPT_DEBOUNCE_TIME)) {
    g_right_state = true;
  }
}

void IRAM_ATTR left_button_interrupt() {
  static uint32_t last_interrupt_time = 0;
  //Debouncing
  if (debounce(&last_interrupt_time, INTERRUPT_DEBOUNCE_TIME)) {
    g_left_state = true;
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
Input check_input() {

//Rotary encoder
#if defined MICRO_SWITCHES_ROTARY_ENCODER_ENABLED || defined ROTARY_ENCODER_ENABLED
  if (g_right_state) {
    PRINT_VERBOSE_INFO("Right Button pressed\n");

    //Play move encoder forward sound
    play_sound(3); 

    g_right_state = false;

    //Check mode for right button
    //right_button_mode();
    reset_timer();
    return INPUT_RIGHT;
  }
  else if (g_left_state) {
    PRINT_VERBOSE_INFO("Left Button pressed\n");

    //Play move encoder backwards
    play_sound(4);  
    g_left_state = false;

    //Check mode for left button
    //left_button_mode();
    reset_timer();
    return INPUT_LEFT;
  }
#endif
#if defined POP_UP_BUTTONS_ENABLED
  else if (g_start_button_state) {
    PRINT_VERBOSE_INFO("Button pressed\n");
    g_start_button_state = false;

    //Check mode for start button
    //start_button_mode();
    reset_timer();
    return INPUT_START_BUTTON;
  }
  else if (g_select_button_state) {
    PRINT_VERBOSE_INFO("Select Button pressed\n");
    g_select_button_state = false;

    //Check mode for select button
    //select_button_mode();
    reset_timer();
    return INPUT_SELECT_BUTTON;
  }
#endif

  return INPUT_NONE;
}


