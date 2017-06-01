#ifndef STRIPES_H
#define STRIPES_H

#include <FastLED.h>
#include "util.h"

namespace Stripes {

constexpr int kMinNumStripes = 12;
constexpr int kMaxNumStripes = 30;

constexpr int kMinSweeps = 2;
constexpr int kMaxSweeps = 3;

constexpr int kMinSpeed = 2;
constexpr int kMaxSpeed = 4;

constexpr int kFrameDelayMS = 50;

void StripesAnimation(CRGB *leds, int num_pole_leds, int num_ball_leds) {
  CRGB c1, c2;
  fillRandomContrastingColors(c1, c2);
  int num_stripes = random(kMinNumStripes, kMaxNumStripes);
  int stripe_size = num_pole_leds / num_stripes;
  int num_sweeps = random(kMinSweeps, kMaxSweeps);
  int dir = random(0, 2) ? 1 : -1;
  int speed = random(kMinSpeed, kMaxSpeed);

  for (int sweep = 0; sweep < num_sweeps; sweep++) {
    for (int offset = 128;
         offset < 128 + num_pole_leds && offset > 128 - num_pole_leds;
         offset += dir * speed) {
      for(int j = 0; j < num_pole_leds; j++) {
        leds[j] = (((j + offset) / stripe_size) % 2 == 0) ? c1 : c2;
      }
      FastLED.show();
      FastLED.delay(kFrameDelayMS);
    }
  }
}

};

#endif //STRIPES_H
