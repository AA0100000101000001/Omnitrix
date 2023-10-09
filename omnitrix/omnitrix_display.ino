
// Display position variables must be global for PNGdec
int16_t xpos = 0;
int16_t ypos = 0;

//Method that shows animation
void showAnimation() {

  int frame = 0;
  int fps = 10;

  for (; frame <= omnitrix_anim_N; frame++)  {
    
    delay(fps);
    
    int16_t rc = png.openFLASH((uint8_t *)omnitrix_anim[frame], sizeof(omnitrix_anim[frame]), pngDraw);

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();

  }
}



//Method that shows the symbols for select mode
void  ShowSelectSymbols() {

  int16_t rc = png.openFLASH((uint8_t *)omnitrix_anim[10], sizeof(omnitrix_anim[10]), pngDraw);

  if (rc == PNG_SUCCESS) {
    //Serial.println("Successfully png file");

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }

}


//Function that displays start icon symbols
void ShowSymbols() {

  //Serial.println("show symbols");

  int16_t rc = png.openFLASH((uint8_t *)omnitrix_anim[0], sizeof(omnitrix_anim[0]), pngDraw);

  if (rc == PNG_SUCCESS) {
    //Serial.println("Successfully png file");

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
 
}

//Function that displays alien on screen
void ShowAlien() {

  int16_t rc = png.openFLASH((uint8_t *)omnitrix_aliens[alienNo], sizeof(omnitrix_aliens[alienNo]), pngDraw);

  if (rc == PNG_SUCCESS) {
    //Serial.println("Successfully png file");

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
}

//Method that displays green backround to erase alien
void eraseAlien() {
  
  int16_t rc = png.openFLASH((uint8_t *)omnitrix_alien_backround, sizeof(omnitrix_alien_backround), pngDraw);

  if (rc == PNG_SUCCESS) {
    //Serial.println("Successfully png file");

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
}

// This function will be called during decoding of the png file
void pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WDITH];         // Line buffer for rendering
  uint8_t maskBuffer[1 + MAX_IMAGE_WDITH / 8];  // Mask buffer

  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);

  if (png.getAlphaMask(pDraw, maskBuffer, 255)) {
    tft.pushMaskedImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer, maskBuffer);
  }
}