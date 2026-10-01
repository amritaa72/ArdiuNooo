#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#include "rajini_180x180_rgb565.h"

#define TFT_CS   10
#define TFT_DC   8
#define TFT_RST  9

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.init(135, 240);
  tft.setRotation(1);

  tft.fillScreen(ST77XX_BLACK);

  tft.drawRGBBitmap(0, 0, image_data, 240, 135);
}

void loop() {
}
