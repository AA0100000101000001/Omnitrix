

#define OMNITRIX_ANIM_FRAME_LAST_INDEX 10 //11 frames for animation

// Display position variables must be global for PNGdec
int16_t xpos = 0;
int16_t ypos = 0;

//Method that shows animation
void show_animation() {

//Start animation with images
#if defined START_ANIMATION_WITH_IMAGES

  int frame = 0;
  int fps = 10;

  for (; frame <= OMNITRIX_ANIM_FRAME_LAST_INDEX; frame++) {

    delay(fps);

    int16_t rc = png.openFLASH((uint8_t *)omnitrix_anim[frame], sizeof(omnitrix_anim[frame]), png_draw);

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
#endif
}



//Method that shows the symbols for select mode
void show_select_symbols() {

//Select Symbols with image
#if defined START_ANIMATION_WITH_IMAGES

  int16_t rc = png.openFLASH((uint8_t *)omnitrix_anim[10], sizeof(omnitrix_anim[10]), png_draw);

  if (rc == PNG_SUCCESS) {
#if defined ENABLE_MEMORY_INFO
    Serial.println("Successfully png file");
#endif

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
#endif
}


//Function that displays start icon symbols
void show_symbols() {

#if defined ENABLE_MEMORY_INFO
  Serial.println("show symbols");
#endif

//Start Symbols with image
#if defined START_ANIMATION_WITH_IMAGES

  int16_t rc = png.openFLASH((uint8_t *)omnitrix_anim[0], sizeof(omnitrix_anim[0]), png_draw);

  if (rc == PNG_SUCCESS) {
#if defined ENABLE_MEMORY_INFO
    Serial.println("Successfully png file");
#endif

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
#endif
}

//Function that displays alien on screen
void show_alien() {

  int16_t rc = png.openFLASH((uint8_t *)omnitrix_aliens[g_alien_n], sizeof(omnitrix_aliens[g_alien_n]), png_draw);

  if (rc == PNG_SUCCESS) {
#if defined ENABLE_MEMORY_INFO
    Serial.println("Successfully png file");
#endif

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
}

//Method that displays green backround to erase alien
void erase_alien() {

  int16_t rc = png.openFLASH((uint8_t *)omnitrix_alien_background, sizeof(omnitrix_alien_background), png_draw);

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