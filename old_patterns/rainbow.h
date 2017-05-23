#ifndef RAINBOW_H
#define RAINBOW_H

#include "PixelWrapper.h"
#include "util.h"

#define NUM_TIMES_AROUND 5
#define FRAME_DELAY_MS 2

#define FULL_NUM_TIMES_AROUND 2
#define FULL_FRAME_DELAY_MS 15

#define SATURATION 0.8
#define VALUE 0.56

void RainbowAnimation_Aux(PixelWrapper *px, int8_t dir) {
  uint8_t r, g, b;
  uint16_t n = px->numPixels();
  
  for (uint16_t offset = 32000; offset < 32000 + n && offset > 32000 - n; offset += dir) {
    
    for (uint8_t i = 0; i < n; i++) {
      hsvtorgb(((i + offset) % n) * NUM_HUES / n, SATURATION, VALUE, &r, &g, &b);
      
      px->setPixelColor(i, px->Color(r, g, b));
    } 
    
    px->show();
    delay(FRAME_DELAY_MS);
  }
}

void RainbowAnimation(PixelWrapper *px) {
  int8_t dir = randomDirection();
  for (uint8_t i = 0; i < NUM_TIMES_AROUND; i++) {
    RainbowAnimation_Aux(px, dir);
  }
}

void FullRainbowAnimation(PixelWrapper *px) {
  uint8_t r, g, b;
  uint16_t n = px->numPixels();
  uint32_t color;
  
  for (uint8_t i = 0; i < FULL_NUM_TIMES_AROUND; i++) {
    for (uint16_t hue = 0; hue < 360; hue++) {
      hsvtorgb(hue, SATURATION, VALUE, &r, &g, &b);
      color = px->Color(r, g, b);
      
      for (uint16_t j = 0; j < n; j++) {
        px->setPixelColor(j, color);
      } 
      px->show();
      delay(FULL_FRAME_DELAY_MS);
    }
  }
}

#endif // RAINBOW_H
