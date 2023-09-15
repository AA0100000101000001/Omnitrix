

//Method that shows animation
void showAnimation() {

  int frame = 0;
  int fps = 40;

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

  int XLup1, XLup2, YLup1, YLup2, XLdown1, XLdown2, YLdown1, YLdown2;
  int XRup1, XRup2, YRup1, YRup2, XRdown1, XRdown2, YRdown1, YRdown2;
  int black;

  upLine.drawLine(0, 0, 40, 60, OMNITRIX_GRAY);
  downLine.drawLine(40, 0, 0, 60, OMNITRIX_GRAY);

  //Yup are for the down symbols and Ydown are for the up symbols
  //draw down and upper left symbol
  XLup1 = -80;
  YLup1 = 119;
  XLup2 = -40;
  YLup2 = 179;
  XLdown1 = -40;
  YLdown1 = 0;
  XLdown2 = -80;
  YLdown2 = 59;
  //draw down and upper right symbol
  XRup1 = 240;
  YRup1 = 1;
  XRup2 = 280;
  YRup2 = 61;
  XRdown1 = 280;
  YRdown1 = 120;
  XRdown2 = 240;
  YRdown2 = 179;

  //When XLup1 <= -5 | XLup2 <= 35 black line center is at (0, 120), add 24 to x = 59 (add 6 so black lines touch at (120, 0), (120, 240))
  for (; /*XLup1 <= 19 | */XLup2 <= 59 ; XLup1++, XLdown1++, XLup2++, XLdown2++, XRup1--, XRdown1--, XRup2--, XRdown2--) {
    upLine.pushSprite(XLup1, YLup1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1, YLdown1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2, YRdown2, TFT_TRANSPARENT);
  }

//draw black lines
  upLine.drawLine(0, 0, 40, 60, TFT_BLACK);
  downLine.drawLine(40, 0, 0, 60, TFT_BLACK);
  for (black = 0; black <= BLACK_LINE_WIDTH; black++, XLup1++, XLdown1++, XLup2++, XLdown2++, XRup1--, XRdown1--, XRup2--, XRdown2--) {
    upLine.pushSprite(XLup1, YLup1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1, YLdown1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2, YRdown2, TFT_TRANSPARENT);
  }

}


//Function that displays start icon symbols
void ShowSymbols() {

  int XLup1, XLup2, YLup1, YLup2, XLdown1, XLdown2, YLdown1, YLdown2;
  int XRup1, XRup2, YRup1, YRup2, XRdown1, XRdown2, YRdown1, YRdown2;
  int black;


  upLine.drawLine(0, 0, 40, 60, OMNITRIX_GRAY);
  downLine.drawLine(40, 0, 0, 60, OMNITRIX_GRAY);

  //draw down and upper left symbol
  XLup1 = -80;
  YLup1 = 0;
  XLdown1 = -40;
  YLdown1 = 119;
  XLup2 = -40;  //x=80*y/120
  YLup2 = 60;   //y=x*120/80
  XLdown2 = -80;
  YLdown2 = 178;
  //draw down and upper right symbol
  XRup1 = 240;  //240-80
  YRup1 = 120;
  XRdown1 = 280;
  YRdown1 = 1;
  YRup2 = 180;
  XRup2 = 280;
  XRdown2 = 240;
  YRdown2 = 60;
  for (; XLup1 <= -5 | XLup2 <= 35 | XRup1 >= 315; XLup1++, XLdown1++, XLup2++, XLdown2++, XRup1--, XRdown1--, XRup2--, XRdown2--) {
    upLine.pushSprite(XLup1, YLup1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1, YLdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2, YRdown2, TFT_TRANSPARENT);
  }

  //draw black lines
  upLine.drawLine(0, 0, 40, 60, TFT_BLACK);
  downLine.drawLine(40, 0, 0, 60, TFT_BLACK);
  for (black = 0; black <= BLACK_LINE_WIDTH; black++, XLup1++, XLdown1++, XLup2++, XLdown2++, XRup1--, XRdown1--, XRup2--, XRdown2--) {
    upLine.pushSprite(XLup1, YLup1, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown1, YLdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XLup2, YLup2, TFT_TRANSPARENT);
    downLine.pushSprite(XLdown2, YLdown2, TFT_TRANSPARENT);
    upLine.pushSprite(XRup1, YRup1, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown1, YRdown1, TFT_TRANSPARENT);
    upLine.pushSprite(XRup2, YRup2, TFT_TRANSPARENT);
    downLine.pushSprite(XRdown2, YRdown2, TFT_TRANSPARENT);
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
    Serial.println("Successfully png file");

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