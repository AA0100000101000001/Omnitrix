
#include "omnitrix_display.h"


//Display variables
PNG png;  // PNG decoder instance
TFT_eSPI tft = TFT_eSPI();

#define OMNITRIX_ANIM_FRAME_LAST_INDEX 10 //11 frames for animation

// Display position variables must be global for PNGdec
int16_t xpos = 0;
int16_t ypos = 0;

static bool is_animating = false;
//bool is_animating = false;
uint32_t g_anim_start;    //Timer that helps with animation
uint8_t g_current_frame; //Frame iterator (<= 255 total frames)

//For debugging animation
#if defined ENABLE_VERBOSE_ANIM_INFO
//int end_animation_time;
double avrg_frame_time;
double avrg_frame_decod_time;
#endif


//Function that sets is_animating
void set_is_animating(bool s) {
  is_animating = s;
}

//Function that returns is_animating
bool get_is_animating() {
  return is_animating;
}

//Function that gets curent time
//Animation with images returns millis while hardcoded animation returns micros
unsigned long get_anim_time() {
#if defined START_ANIMATION_WITH_IMAGES
  return millis();
#elif defined START_ANIMATION_HARD_CODED
  return micros();
#endif
}

//Method that shows animation
//Returns true if finished, false if not done
bool show_animation() {

//Use of images for start animation
#if defined START_ANIMATION_WITH_IMAGES
  
  //Animation frames not done
  if (g_current_frame <= OMNITRIX_ANIM_FRAME_LAST_INDEX) {

    uint32_t next_frame = g_anim_start + ((g_current_frame+1) * FRAME_RATE);

    print_anim_info_vars("millis: ", get_anim_time(), ", next frame at: ", next_frame);

      //These will be used only if animation info is enabled
      unsigned long start_frame_time, start_frame_decod_time; 
      //Save timestamp for the start of the frame
      verbose_anim_info_save_anim_time(&start_frame_time);

    //Check time for next frame
    // g_anim_start + ((g_current_frame+1) * FRAME_RATE) is the next timestamp where the next frame appears
    if (get_anim_time() >= next_frame) {
      //Save timestamp for the start of the decoding
      verbose_anim_info_save_anim_time(&start_frame_decod_time);

      //Draw current frame
      draw_start_animation_frame(g_current_frame);

      print_verbose_anim_info_end_frame(&start_frame_time, &start_frame_decod_time);

      g_current_frame++; //go to next frame

    }

  }
  // Animation frames finished
  else {

    //Finished animation info
    verbose_anim_end_info();
    return true; //Animation done
  }
  
  return false; //Animation not done
#endif

}

// Helper function for show_animation
void draw_start_animation_frame(uint8_t i) {

//Use of images for start animation
#if defined START_ANIMATION_WITH_IMAGES
  
  show_image(omnitrix_anim[i], sizeof(omnitrix_anim[i]));
#endif
}

//Method that shows the symbols for select mode
void show_select_symbols() {

  //Select Symbols with image
  show_image(omnitrix_anim[10], sizeof(omnitrix_anim[10]));

}

//Function that displays start icon symbols
void show_symbols() {

  //Start Symbols with image
  show_image(omnitrix_anim[0], sizeof(omnitrix_anim[0]));
}

//Function that displays alien on screen
void show_alien() {

  show_image(omnitrix_aliens[g_alien_n], sizeof(omnitrix_aliens[g_alien_n]));

}

//Method that displays green backround to erase alien
void erase_alien() {

  show_image(omnitrix_alien_background, sizeof(omnitrix_alien_background));

}

// This function displays png images
void show_image(const uint8_t *img, int img_size) {

  print_memory_info();

  int16_t rc = png.openFLASH((uint8_t *)img, img_size, png_draw);

  print_memory_info_mes_var("Open flash rc: ", rc);

  if (rc == PNG_SUCCESS) {
    print_memory_info_mes("Successfully png file");

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }

}

// This function will be called during decoding of the png file
int png_draw(PNGDRAW *pDraw) {
  uint16_t line_buffer[MAX_IMAGE_WDITH];         // Line buffer for rendering
  uint8_t mask_buffer[1 + MAX_IMAGE_WDITH / 8];  // Mask buffer

  png.getLineAsRGB565(pDraw, line_buffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);

  if (png.getAlphaMask(pDraw, mask_buffer, 255)) {
    tft.pushMaskedImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, line_buffer, mask_buffer);
  }

  return 1;
}