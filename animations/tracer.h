#ifndef TRACER_H
#define TRACER_H

#include <FastLED.h>
#include "util.h"

namespace Tracer {

constexpr int kMinPasses = 4;
constexpr int kMaxPasses = 6;

constexpr int kMinTracerWidth = 10;
constexpr int kMaxTracerWidth = 18;

constexpr int kMinSpeed = 4;
constexpr int kMaxSpeed = 8;

constexpr int kBallSpins = 3;

constexpr int kFrameDelayMS = 8;

void SetTracerBallColor(CRGB *leds, int num_pole_leds, int num_ball_leds,
                        int position, CRGB ball_c1, CRGB ball_c2) {
  CRGB c1 = (position / (num_pole_leds / (3 * kBallSpins)) % 3 == 0) ? ball_c1 : ball_c2;
  CRGB c2 = (position / (num_pole_leds / (3 * kBallSpins)) % 3 == 1) ? ball_c1 : ball_c2;
  CRGB c3 = (position / (num_pole_leds / (3 * kBallSpins)) % 3 == 2) ? ball_c1 : ball_c2;
  setBallSidesColor(leds + num_pole_leds, num_ball_leds, c1, c2, c3);
}

void TracerAnimation_Aux(CRGB *leds, int num_pole_leds, int num_ball_leds,
                         CRGB pole_c1, CRGB pole_c2, CRGB ball_c1, CRGB ball_c2,
                         int tracer_width, int speed) {
  int i, j;
  
  for (i = 0; i < num_pole_leds; i += speed) {
    for (j = 0; j < num_pole_leds; j++) {
      leds[j] = (abs(i - j) < tracer_width) ? pole_c1 : pole_c2;
    }
    SetTracerBallColor(leds, num_pole_leds, num_ball_leds, i, ball_c1, ball_c2);
    FastLED.show();
    FastLED.delay(kFrameDelayMS);
  }
  
  int ball_counter = 0;
  for (i = num_pole_leds - 1; i >= 0; i -= speed) {
    for (j = 0; j < num_pole_leds; j++) {
      leds[j] = (abs(i - j) < tracer_width) ? pole_c1 : pole_c2;
    }
    SetTracerBallColor(leds, num_pole_leds, num_ball_leds, ball_counter,
                       ball_c1, ball_c2);
    ball_counter += speed;
    FastLED.show();
    FastLED.delay(kFrameDelayMS);
  }
}


void TracerAnimation(CRGB *leds, int num_pole_leds, int num_ball_leds) {
  CRGB pole_c1, pole_c2;
  fillRandomContrastingColors(pole_c1, pole_c2);
  CRGB ball_c1, ball_c2;
  fillRandomContrastingColors(ball_c1, ball_c2);
  int num_passes = random(kMinPasses, kMaxPasses);
  int tracer_width = random(kMinTracerWidth, kMaxTracerWidth);
  int speed = random(kMinSpeed, kMaxSpeed);

  for (int i = 0; i < num_passes; i++) {
    TracerAnimation_Aux(leds, num_pole_leds, num_ball_leds,
                        pole_c1, pole_c2, ball_c1, ball_c2,
                        tracer_width, speed);
  }
}

};

#endif // TRACER_H
