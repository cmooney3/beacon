#ifndef WAVE_H
#define WAVE_H

#include "PixelWrapper.h"
#include "util.h"

#define NUM_SWEEPS 5
#define MAX_WAVE_SIZE 5
#define MIN_WAVE_SIZE 2
#define FRAME_DELAY_MS 10

void WaveAnimation(PixelWrapper *px) {
  uint32_t color1 = randomColor(px);
  uint32_t color2 = randomColor(px);
  uint32_t color3;
  uint8_t r1, r2, r3;
  uint8_t g1, g2, g3;
  uint8_t b1, b2, b3;
  
  uint16_t n = px->numPixels();
  
  int8_t dir = randomDirection();
  float wave_size = MIN_WAVE_SIZE + rand() % (MAX_WAVE_SIZE - MIN_WAVE_SIZE);
  
  unpackColor(color1, &r1, &g1, &b1);
  unpackColor(color2, &r2, &g2, &b2);

  for (uint16_t offset = 32000; offset < 32000 + (n * NUM_SWEEPS) && offset > 32000 - (n * NUM_SWEEPS); offset += dir) {
    for(uint16_t j = 0; j < n; j++) {     
        
      float mix = sin((j + offset) / wave_size);      
      blendColors(r1, g1, b1, r2, g2, b2, &r3, &g3, &b3, mix);
      color3 = px->Color(r3, g3, b3);
        
      px->setPixelColor(j, color3);
    }
    px->show();
    delay(FRAME_DELAY_MS);
  }
}


#endif //STRIPES_H
