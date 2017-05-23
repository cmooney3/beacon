#ifndef FILL_H
#define FILL_H

#include <FastLED.h>
#include "util.h"

#define MIN_FILLS 3
#define MAX_FILLS 7
#define MIN_FILL_SEGMENTS 20
#define MAX_FILL_SEGMENTS 100
#define FRAME_DELAY_MS 1

void FillAnimation_Aux(CRGB *leds, int num_leds, int num_segments, CRGB c1, CRGB c2) {
  int segment_size = num_leds / num_segments;
  int i;
  
  for (i = 0; i < num_leds; i++) {
    leds[i] = c1;
  }

  for (i = 0; i < num_leds; i++) {
    leds[i] = c2;
    if (i % segment_size == 0 || i == num_leds - 1) {
      FastLED.show();
      FastLED.delay(FRAME_DELAY_MS);
    }
  }
  
  for (i = num_leds; i >= 0; i--) {
    leds[i] = c1;
    if (i % segment_size == 0 || i == num_leds - 1) {
      FastLED.show();
      FastLED.delay(FRAME_DELAY_MS);
    }
  }
}

void FillAnimation(CRGB *leds, int num_leds) {
  LOG("Running Fill...");
  LOG("\tnum_leds = %d", num_leds);
  
  CRGB c1, c2;
  fillRandomContrastingColors(c1, c2);

  // Selecting the number of segments to fill at once.  This effectively
  // changes the speed of the fill.  The framerate is too low to do one at
  // a time.
  int num_segments = random(MIN_FILL_SEGMENTS, MAX_FILL_SEGMENTS);
  LOG("\tnum_segments = %d", num_segments);

  int num_fills = random(MIN_FILLS, MAX_FILLS);
  LOG("\tnum_fills = %d", num_fills);  
  
  for (int i = 0; i < num_fills; i++) {
    LOG("\tFill #%d", i);
    FillAnimation_Aux(leds, num_leds, num_segments, c1, c2);
  }
}



/*

void FillFromCenterAnimation_Aux(PixelWrapper *px, uint32_t c1, uint32_t c2) {
  uint16_t n = px->numPixels();
  int i, j;
  int center = n / 2;
  
  for (i = 0; i < center; i++) {
    for (j = 0; j < n; j++) {
      if (abs(center - j) <= i) {
        px->setPixelColor(j, c1);
      } else {
        px->setPixelColor(j, c2); 
      }
    }
    px->show();
    delay(FRAME_DELAY_MS);
  }
  
  for (i = center - 1; i >= 0; i--) {
    for (j = 0; j < n; j++) {
      if (abs(center - j) <= i) {
        px->setPixelColor(j, c1);
      } else {
        px->setPixelColor(j, c2); 
      }
    }
    px->show();
    delay(FRAME_DELAY_MS);
  }
}

void FillFromCenterAnimation(PixelWrapper *px) {
  uint32_t color1 = randomColor(px);
  uint32_t color2 = randomColor(px);

  for (uint8_t i = 0; i < NUM_FILLS; i++) {
    FillFromCenterAnimation_Aux(px, color1, color2);
  }
}
*/

#endif //FILL_H
