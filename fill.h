#ifndef FILL_H
#define FILL_H

#include <FastLED.h>
#include "util.h"

#define MIN_FILLS 3
#define MAX_FILLS 7
#define MIN_SEGMENT_SIZE 2
#define MAX_SEGMENT_SIZE 10
#define FRAME_DELAY_MS 1

void FillAnimation_Aux(CRGB *leds, int num_leds, int segment_size, CRGB c1, CRGB c2) {
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

void CenterFillAnimation_Aux(CRGB *leds, int num_leds, int segment_size, CRGB c1, CRGB c2) {
  int i, j;
  int center = num_leds / 2;

  for (i = 0; i < center; i += segment_size) {
    for (j = 0; j < num_leds; j++) {
      leds[j] = (abs(center - j) <= i) ? c1 : c2;
    }
    FastLED.show();
    FastLED.delay(FRAME_DELAY_MS);
  }

  fill_solid(leds, num_leds, c1);
  FastLED.show();
  FastLED.delay(FRAME_DELAY_MS);

  for (i = center - 1; i >= 0; i -= segment_size) {
    for (j = 0; j < num_leds; j++) {
      leds[j] = (abs(center - j) <= i) ? c1 : c2;
    }
    FastLED.show();
    FastLED.delay(FRAME_DELAY_MS);
  }

  fill_solid(leds, num_leds, c2);
  FastLED.show();
  FastLED.delay(FRAME_DELAY_MS);
}

void FillAnimation(CRGB *leds, int num_leds, bool center_fill) {
  CRGB c1, c2;
  fillRandomContrastingColors(c1, c2);

  // Selecting the number of segments to fill at once.  This effectively
  // changes the speed of the fill.  The framerate is too low to do one at
  // a time.
  int segment_size = random(MIN_SEGMENT_SIZE, MAX_SEGMENT_SIZE);
  LOG("\tsegment_size = %d", segment_size);

  // Select a random number of animation loops to complete
  int num_fills = random(MIN_FILLS, MAX_FILLS);
  LOG("\tnum_fills = %d", num_fills);  
  
  for (int i = 0; i < num_fills; i++) {
    LOG("\tFill #%d", i);
    if (center_fill) {
      // Note: We use a 1/2 segment size for Centerfill since it fills in
      // two directions at once, resulting in the animation completing 2x
      // faster that expected.  By halving it here we counteract that effect.
      CenterFillAnimation_Aux(leds, num_leds, segment_size / 2, c1, c2);
    } else {
      FillAnimation_Aux(leds, num_leds, segment_size, c1, c2);
    }
  }
}

void FillAnimation(CRGB *leds, int num_leds) {
  LOG("Running Fill...");
  FillAnimation(leds, num_leds, false);
}

void CenterFillAnimation(CRGB *leds, int num_leds) {
  LOG("Running CenterFill...");
  FillAnimation(leds, num_leds, true);
}

#endif // FILL_H
