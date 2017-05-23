#ifndef TRACER_H
#define TRACER_H

#include "PixelWrapper.h"
#include "util.h"

#define NUM_PASSES 6
#define FALLOFF_RATE 10
#define FRAME_DELAY_MS 5
#define TRACER_WIDTH 7

void TracerAnimation_Aux(PixelWrapper *px, uint32_t fg, uint32_t bg) {
  uint16_t n = px->numPixels();
  int i, j;
  
  
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (abs(i - j) < TRACER_WIDTH) {
        px->setPixelColor(j, fg); 
      } else {
        px->setPixelColor(j, bg);
      }
    }
    px->show();
    delay(FRAME_DELAY_MS);
  }
  
  for (i = n - 1; i >= 0; i--) {
    for (j = 0; j < n; j++) {
      if (abs(i - j) < TRACER_WIDTH) {
        px->setPixelColor(j, fg); 
      } else {
        px->setPixelColor(j, bg);
      }
    }
    px->show();
    delay(FRAME_DELAY_MS);
  }
  
}

void TracerAnimation(PixelWrapper *px) {
  uint32_t fg = randomColor(px);
  uint32_t bg = randomColor(px);
  uint8_t i;

  for (i = 0; i < NUM_PASSES; i++) {
    TracerAnimation_Aux(px, fg, bg);
  }
}


#endif //FILL_H
