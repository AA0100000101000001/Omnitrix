/* This program displays on the LCD screen the omnitrix start animation followed by all the alien figures displayed one after the other in a loop. */

#include <PNGdec.h>

// Include image array
#include "omnitrix_aliens.h"
#include "omnitrix_alien_backround.h"
#include "omnitrix_anim_png_circle.h"

PNG png; // PNG decoder instance

#define MAX_IMAGE_WDITH 240 // Sets rendering line buffer lengths, adjust for your images

#define OMNITRIX_GREEN 0xA707
#define OMNITRIX_RED 0xC000
#define OMNITRIX_GRAY 0xAD55


#include "SPI.h"
#include <TFT_eSPI.h>              // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();         // Invoke custom library

int16_t xpos = 0;
int16_t ypos = 0;

//Number of aliens
int N = 11;
int Npos = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n Using the PNGdec library");

  // Initialise the TFT
  tft.begin();
  tft.fillScreen(OMNITRIX_GREEN);

  Serial.println("\r\nInitialisation done.");

}


void loop()
{

  showAnimation();
  delay(1000);

  for (Npos = 0;Npos <= N; Npos++) {
    
    eraseAlien();
    showAlien();
    delay(1000);

  }

  tft.fillScreen(OMNITRIX_GREEN);

  
}

void showAnimation() {

  int frame = 0;
  int fps = 40;

  for (; frame <= omnitrix_anim_N; frame++)  {
    
    delay(fps);
    
    //Serial.println(frame);
    int16_t rc = png.openFLASH((uint8_t *)omnitrix_anim[frame], sizeof(omnitrix_anim[frame]), pngDraw);

    //if (rc = PNG_SUCCESS) {
      tft.startWrite();
      rc = png.decode(NULL, 0);
      tft.endWrite();
    //}

  }

}


void showAlien() {

  uint16_t pngw = 0, pngh = 0; // To store width and height of image

  int16_t rc = png.openFLASH((uint8_t *)omnitrix_aliens[Npos], sizeof(omnitrix_aliens[Npos]), pngDraw);

  if (rc == PNG_SUCCESS) {
    Serial.println("Successfully png file");
    pngw = png.getWidth();
    pngh = png.getHeight();
    Serial.printf("Image metrics: (%d x %d), %d bpp, pixel type: %d\n", pngw, pngh, png.getBpp(), png.getPixelType());

    tft.startWrite();
    uint32_t dt = millis();
    rc = png.decode(NULL, 0);
    tft.endWrite();
    Serial.print(millis() - dt); Serial.println("ms");
    tft.endWrite();

    // png.close(); // Required for files, not needed for FLASH arrays
  }

}

void eraseAlien() {
  
  uint16_t pngw = 0, pngh = 0; // To store width and height of image

  int16_t rc2 = png.openFLASH((uint8_t *)omnitrix_alien_backround, sizeof(omnitrix_alien_backround), pngDraw);

  if (rc2 == PNG_SUCCESS) {
    Serial.println("Successfully png file");
    pngw = png.getWidth();
    pngh = png.getHeight();
    Serial.printf("Image metrics: (%d x %d), %d bpp, pixel type: %d\n", pngw, pngh, png.getBpp(), png.getPixelType());

    tft.startWrite();
    uint32_t dt = millis();
    rc2 = png.decode(NULL, 0);
    tft.endWrite();
    Serial.print(millis() - dt); Serial.println("ms");
    tft.endWrite();

    // png.close(); // Required for files, not needed for FLASH arrays
  }

}

