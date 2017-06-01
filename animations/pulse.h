#ifndef PULSE_H
#define PULSE_H

#include <FastLED.h>
#include "util.h"

namespace Pulse {

constexpr int kMinNumPulses = 3;
constexpr int kMaxNumPulses = 10;
constexpr int kMinNumGradientSteps = 8;
constexpr int kMaxNumGradientSteps = 16;
constexpr int kMinFrameDelayMS = 1;
constexpr int kMaxFrameDelayMS = 20;

void SinglePulse(CRGB *leds, int num_pole_leds, int num_ball_leds,
                 CRGB c1, CRGB c2, int frame_delay_ms, int num_gradient_steps) {
  int perc_step = 255 / num_gradient_steps;
  for (int i = 0; i <= num_gradient_steps * 2; i++) {
    int perc = (i < num_gradient_steps)?
                  i * perc_step:
                  (2 * num_gradient_steps - i) * perc_step;
    CRGB mixed = blend(c1, c2, perc);
    fill_solid(leds, num_pole_leds, mixed);

    FastLED.show();
    FastLED.delay(frame_delay_ms);
  }
}

void PulseAnimation(CRGB *leds, int num_pole_leds, int num_ball_leds) {
  CRGB c1, c2;
  fillRandomContrastingColors(c1, c2);
  int frame_delay_ms = random(kMinFrameDelayMS, kMaxFrameDelayMS);
  int num_pulses = random(kMinNumPulses, kMaxNumPulses);
  int num_gradient_steps = random(kMinNumGradientSteps, kMaxNumGradientSteps);

  for (uint8_t i = 0; i < num_pulses; i++) {
    SinglePulse(leds, num_pole_leds, num_ball_leds,
                c1, c2, frame_delay_ms, num_gradient_steps);
    FastLED.delay(frame_delay_ms * 5);
  } 
}

};

#endif // PULSE_H
