

#define OMNITRIX_ANIM_FRAME_LAST_INDEX 10 //11 frames for animation

// Display position variables must be global for PNGdec
int16_t xpos = 0;
int16_t ypos = 0;

static bool is_animating = false;
static bool animating_finished = false;
uint32_t g_anim_start;    //Timer that helps with animation


//Method that shows animation
void show_animation() {

//Use of images for start animation
#if defined START_ANIMATION_WITH_IMAGES

  int frame = 0;
  //int fps = 10;
#if defined ENABLE_ANIM_INFO
  int start_animation_time = millis();
  int end_animation_time;
  double avrg_frame_time = 0;
#endif

  for (; frame <= OMNITRIX_ANIM_FRAME_LAST_INDEX; frame++) {

    //delay(fps);
#if defined ENABLE_ANIM_INFO
    int start_frame_time = millis();
#endif

    draw_start_animation_frame(frame);

#if defined ENABLE_ANIM_INFO
    int frame_duration_time = millis() - start_frame_time;
    avrg_frame_time += frame_duration_time;
    Serial.printf("Time passed since frame: %d\n", frame_duration_time);
#endif
  }
#endif

#if defined ENABLE_ANIM_INFO
  end_animation_time = millis();
  Serial.printf("Average frame rate: %.2f\n", avrg_frame_time/(OMNITRIX_ANIM_FRAME_LAST_INDEX + 1));
  Serial.printf("Total start_animation time length : %d\n", end_animation_time - start_animation_time);
#endif
  animating_finished = true;
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

#if defined ENABLE_MEMORY_INFO
  Serial.printf("Free Internal Heap: %d\n", ESP.getFreeHeap());
  Serial.printf("Min Free Internal Heap: %d\n", ESP.getMinFreeHeap());
  Serial.printf("Total PSRAM Size: %d\n", ESP.getPsramSize());
  Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());
#endif

  int16_t rc = png.openFLASH((uint8_t *)img, img_size, png_draw);

#if defined ENABLE_MEMORY_INFO
  Serial.printf("Open flash rc: %d\n", rc);
#endif

  if (rc == PNG_SUCCESS) {
#if defined ENABLE_MEMORY_INFO
    Serial.println("Successfully png file");
#endif

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