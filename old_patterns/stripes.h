#ifndef STRIPES_H
#define STRIPES_H

#include "PixelWrapper.h"
#include "util.h"

#define NUM_SWEEPS 5
#define NUM_STRIPES 4
#define FRAME_DELAY_MS 10

void StripeSweepAnimation(PixelWrapper *px) {
  uint32_t color1 = randomColor(px);
  uint32_t color2 = randomColor(px);
  uint16_t n = px->numPixels();
  uint16_t stripe_size = n / NUM_STRIPES;
  int8_t dir = randomDirection();

  for (uint8_t i = 0; i < NUM_SWEEPS; i++) {
    for (uint16_t offset = 128; offset < 128 + n && offset > 128 - n; offset += dir) {
      for(uint16_t j = 0; j < n; j++) {       
        if (((j + offset) / stripe_size) % 2 == 0) {
          px->setPixelColor(j, color1);
        } else {
          px->setPixelColor(j, color2);
        }
      }
      px->show();
      delay(FRAME_DELAY_MS);
    }
  }
}


#endif //STRIPES_H
