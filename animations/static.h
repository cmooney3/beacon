#ifndef STATIC_H
#define STATIC_H

#include <FastLED.h>
#include "util.h"

namespace Static {

constexpr int kNumFrames = 75;
constexpr int kNumPulses = 5;
constexpr int kPulseStep = 255 / (kNumFrames / kNumPulses / 2);
constexpr int kFrameDelayMS = 50;
constexpr int kMinSegmentLength = 1;
constexpr int kMaxSegmentLength = 10;

void StaticAnimation(CRGB *leds, int num_pole_leds, int num_ball_leds) {
  int segment_length = random(kMinSegmentLength, kMaxSegmentLength);
  CRGB ball_c = randomColor();
  CRGB ball_fade_c = (random(2) % 2 == 0) ? CRGB::White : CRGB::Black;
  int perc = 0;
  int dir = 1;

  for (int i = 0; i < kNumFrames; i++) {
    CRGB c = randomColor();
    for (int j = 0; j < num_pole_leds; j++) {
      if (j % segment_length == 0) {
        c = randomColor();
      }
      leds[j] = c;
    }

    CRGB ball_color = blend(ball_c, ball_fade_c, perc);
    perc += dir * kPulseStep;
    if (perc < 0) {
      perc = 0;
      dir *= -1;
    } else if (perc > 255) {
      perc = 255;
      dir *= -1;
    }
    setBallColor(leds + num_pole_leds, num_ball_leds, ball_color);

    FastLED.show();
    FastLED.delay(kFrameDelayMS);
  }
}

};

#endif // STATIC_H
