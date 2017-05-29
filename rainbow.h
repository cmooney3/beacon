#ifndef RAINBOW_H
#define RAINBOW_H

#include <FastLED.h>
#include "util.h"

namespace Rainbow {

constexpr int kMinHueStep = 2;
constexpr int kMaxHueStep = 20;

constexpr int kMinFrameHueStep = 3;
constexpr int kMaxFrameHueStep = 10;

constexpr int kMinFrames = 200;
constexpr int kMaxFrames = 1000;

constexpr int kFrameDelayMS = 2;

void RainbowAnimation(CRGB *leds, int num_leds) {
  LOG("Running Rainbow...");
  
  int start_hue = random(255);
  LOG("\tstart_hue = %d", start_hue);

  // This value sets how much the hue steps ahead for each pixel, effectively
  // controlling how wide the rainbow pattern is.
  int hue_step = random(kMinHueStep, kMaxHueStep);
  LOG("\thue_step = %d", hue_step);

  // This value sets how much the hue steps ahead on each frame, effectively
  // controlling how quickly the rainbow slides past.
  int frame_hue_step = random(kMinFrameHueStep, kMaxFrameHueStep);
  LOG("\tframe_hue_step = %d", frame_hue_step);

  int num_frames = random(kMinFrames, kMaxFrames);
  LOG("\tnum_frames = %d\t(~%dms)",
      num_frames, (num_frames * kFrameDelayMS));

  for (int i = 0; i < num_frames; i++) {
    fill_rainbow(leds, num_leds,
                 (start_hue + i * frame_hue_step) % 255, hue_step);
    FastLED.show();
    FastLED.delay(kFrameDelayMS);
  }
}

};

#endif // RAINBOW_H
