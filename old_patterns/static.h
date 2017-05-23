#ifndef STATIC_H
#define STATIC_H

#include "PixelWrapper.h"
#include "util.h"

#define NUM_FRAMES 100
#define FRAME_DELAY_MS 50


void StaticAnimation(PixelWrapper *px) {
  uint16_t n = px->numPixels();
  
  for (uint16_t i = 0; i < NUM_FRAMES; i++) {
    for (uint16_t j = 0; j < n; j++) {
      px->setPixelColor(j, randomColor(px));
    }
    px->show();
    delay(FRAME_DELAY_MS);
  }
}


#endif //STATIC_H
