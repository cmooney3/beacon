#ifndef FADE_H
#define FADE_H

#include <FastLED.h>
#include "util.h"

namespace Fade {

constexpr int kMinFrames = 250;
constexpr int kMaxFrames = 400;

constexpr int kMinWaveSize = 20;
constexpr int kMaxWaveSize = 65;

constexpr int kMinSpeed = 1;
constexpr int kMaxSpeed = 3;

constexpr int kFrameDelayMS = 2;

void FadeAnimation(CRGB *leds, int num_pole_leds, int num_ball_leds) {
  CRGB pole_c1, pole_c2;
  fillRandomContrastingColors(pole_c1, pole_c2);
  CRGB ball_c1, ball_c2;
  fillRandomContrastingColors(ball_c1, ball_c2);
  int dir = (random(0, 2) == 0) ? 1 : -1;
  int fade_size = random(kMinWaveSize, kMaxWaveSize);
  int speed = random(kMinSpeed, kMaxSpeed);
  int num_frames = random(kMinFrames, kMaxFrames);
  
  for (int offset = 0; abs(offset) < num_frames; offset += dir * speed) {
    for(int j = 0; j < num_pole_leds; j++) {
      int pole_perc = ((offset + j) % fade_size) * 255 / fade_size;
      CRGB mixed_c = blend(pole_c1, pole_c2, pole_perc);
      leds[j] = mixed_c;
    }

    int ball_perc = (offset % fade_size) * 255 / fade_size;
    CRGB ball_c = blend(ball_c1, ball_c2, ball_perc);
    setBallColor(leds + num_pole_leds, num_ball_leds, ball_c);

    FastLED.show();
    FastLED.delay(kFrameDelayMS);
  }
}

};

#endif //STRIPES_H
