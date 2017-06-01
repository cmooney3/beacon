#ifndef FILL_H
#define FILL_H

#include <FastLED.h>
#include "util.h"

namespace Fill {

constexpr int kMinFills = 3;
constexpr int kMaxFills = 7;
constexpr int kMinSegmentSize = 2;
constexpr int kMaxSegmentSize = 10;
constexpr int kFrameDelayMS = 2;

void FillAnimation_Aux(CRGB *leds, int num_pole_leds, int num_ball_leds,
                       int segment_size, CRGB c1, CRGB c2) {
  int i;
  for (i = 0; i < num_pole_leds; i++) {
    leds[i] = c1;
  }

  for (i = 0; i < num_pole_leds; i++) {
    leds[i] = c2;
    if (i % segment_size == 0 || i == num_pole_leds - 1) {
      FastLED.show();
      FastLED.delay(kFrameDelayMS);
    }
  }

  for (i = num_pole_leds; i >= 0; i--) {
    leds[i] = c1;
    if (i % segment_size == 0 || i == num_pole_leds - 1) {
      FastLED.show();
      FastLED.delay(kFrameDelayMS);
    }
  }
}

void CenterFillAnimation_Aux(CRGB *leds, int num_pole_leds, int num_ball_leds,
                             int segment_size, CRGB c1, CRGB c2) {
  int i, j;
  int center = num_pole_leds / 2;

  for (i = 0; i < center; i += segment_size) {
    for (j = 0; j < num_pole_leds; j++) {
      leds[j] = (abs(center - j) <= i) ? c1 : c2;
    }
    FastLED.show();
    FastLED.delay(kFrameDelayMS);
  }

  fill_solid(leds, num_pole_leds, c1);
  FastLED.show();
  FastLED.delay(kFrameDelayMS);

  for (i = center - 1; i >= 0; i -= segment_size) {
    for (j = 0; j < num_pole_leds; j++) {
      leds[j] = (abs(center - j) <= i) ? c1 : c2;
    }
    FastLED.show();
    FastLED.delay(kFrameDelayMS);
  }

  fill_solid(leds, num_pole_leds, c2);
  FastLED.show();
  FastLED.delay(kFrameDelayMS);
}

void GenericFillAnimation(CRGB *leds, int num_pole_leds, int num_ball_leds,
                          bool center_fill) {
  CRGB c1, c2;
  fillRandomContrastingColors(c1, c2);

  // Selecting the number of segments to fill at once.  This effectively
  // changes the speed of the fill.  The framerate is too low to do one at
  // a time.
  int segment_size = random(kMinSegmentSize, kMaxSegmentSize);
  LOG("\tsegment_size = %d", segment_size);

  // Select a random number of animation loops to complete
  int num_fills = random(kMinFills, kMaxFills);
  LOG("\tnum_fills = %d", num_fills);  
  
  for (int i = 0; i < num_fills; i++) {
    if (center_fill) {
      // Note: We use a 1/2 segment size for Centerfill since it fills in
      // two directions at once, resulting in the animation completing 2x
      // faster that expected.  By halving it here we counteract that effect.
      CenterFillAnimation_Aux(leds, num_pole_leds, num_ball_leds,
                              segment_size / 2, c1, c2);
    } else {
      FillAnimation_Aux(leds, num_pole_leds, num_ball_leds,
                        segment_size, c1, c2);
    }
  }
}

void FillAnimation(CRGB *leds, int num_pole_leds, int num_ball_leds) {
  GenericFillAnimation(leds, num_pole_leds, num_ball_leds, false);
}

void CenterFillAnimation(CRGB *leds, int num_pole_leds, int num_ball_leds) {
  GenericFillAnimation(leds, num_pole_leds, num_ball_leds, true);
}

};

#endif // FILL_H
