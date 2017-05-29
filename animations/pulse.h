#ifndef STROBE_H
#define STROBE_H

#include <FastLED.h>
#include "util.h"

namespace Pulse {

constexpr int kMinNumPulses = 3;
constexpr int kMaxNumPulses = 10;
constexpr int kMinNumGradientSteps = 8;
constexpr int kMaxNumGradientSteps = 16;
constexpr int kMinFrameDelayMS = 1;
constexpr int kMaxFrameDelayMS = 20;

void SinglePulse(CRGB *leds, int num_leds, CRGB c1, CRGB c2,
                 int frame_delay_ms, int num_gradient_steps) {
  int perc_step = 255 / num_gradient_steps;
  for (int i = 0; i <= num_gradient_steps * 2; i++) {
    int perc = (i < num_gradient_steps)?
                  i * perc_step:
                  (2 * num_gradient_steps - i) * perc_step;
    CRGB mixed = blend(c1, c2, perc);
    fill_solid(leds, num_leds, mixed);

    FastLED.show();
    FastLED.delay(frame_delay_ms);
  }
}

//void PulseAnimation_Aux(PixelWrapper *px, uint32_t c1, uint32_t c2,
//                        uint8_t interpulse_delay_ms, uint8_t interframe_delay_ms) {
//   for (uint8_t i = 0; i < kNumPulses; i++) {
//    SinglePulse(px, c1, c2, interframe_delay_ms);
//    delay(interpulse_delay_ms);
//    SinglePulse(px, c1, c2, interframe_delay_ms);
//    delay(interpulse_delay_ms);
//  }
//}
//
//void PulseAnimation(PixelWrapper *px) {
//  PulseAnimation_Aux(px, randomColor(px), randomColor(px),
//                     random(50, 150), random(3, 15));
//}
//
void PulseAnimation(CRGB *leds, int num_leds) {
  LOG("Running Pulse...");
  CRGB c1, c2;
  fillRandomContrastingColors(c1, c2);
 
  int frame_delay_ms = random(kMinFrameDelayMS, kMaxFrameDelayMS);
  LOG("\tframe_delay_ms = %d", frame_delay_ms);
 
  int num_pulses = random(kMinNumPulses, kMaxNumPulses);
  LOG("\tnum_pulses = %d", num_pulses);
  
  int num_gradient_steps = random(kMinNumGradientSteps, kMaxNumGradientSteps);
  LOG("\tnum_gradient_steps = %d", num_gradient_steps);

  for (uint8_t i = 0; i < num_pulses; i++) {
    SinglePulse(leds, num_leds, c1, c2, frame_delay_ms, num_gradient_steps);
    FastLED.delay(frame_delay_ms * 5);
  } 
}

};

#endif // STROBE_H
