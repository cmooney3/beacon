#ifndef STATIC_H
#define STATIC_H

#include <FastLED.h>
#include "util.h"

namespace Static {

constexpr int kNumFrames = 75;
constexpr int kFrameDelayMS = 50;
constexpr int kMinSegmentLength = 1;
constexpr int kMaxSegmentLength = 10;

void StaticAnimation(CRGB *leds, int num_leds) {
  LOG("Running Static...");
  int segment_length = random(kMinSegmentLength, kMaxSegmentLength);
  LOG("\tnum_frames = %d", kNumFrames);
  LOG("\tframe_delay_ms = %d", kFrameDelayMS);
  LOG("\tsegment_length = %d", segment_length);

  for (uint16_t i = 0; i < kNumFrames; i++) {
    CRGB c = randomColor();
    for (uint16_t j = 0; j < num_leds; j++) {
      if (j % segment_length == 0) {
        c = randomColor();
      }
      leds[j] = c;
    }

    FastLED.show();
    FastLED.delay(kFrameDelayMS);
  }
}

};

#endif // STATIC_H
