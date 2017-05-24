#ifndef RAINBOW_H
#define RAINBOW_H

#include <FastLED.h>
#include "util.h"

#define MIN_HUE_STEP 2
#define MAX_HUE_STEP 20

#define MIN_FRAME_HUE_STEP 3
#define MAX_FRAME_HUE_STEP 10

#define MIN_FRAMES 200
#define MAX_FRAMES 1000

#define FRAME_DELAY_MS 2

void RainbowAnimation(CRGB *leds, int num_leds, bool center_fill) {
  LOG("Running Rainbow...");
  
  int start_hue = random(255);
  LOG("\tstart_hue = %d", start_hue);

  // This value sets how much the hue steps ahead for each pixel, effectively controlling
  // how wide the rainbow pattern is.
  int hue_step = random(MIN_HUE_STEP, MAX_HUE_STEP);
  LOG("\thue_step = %d", hue_step);

  // This value sets how much the hue steps ahead on each frame, effectively controlling
  // how quickly the rainbow slides past.
  int frame_hue_step = random(MIN_FRAME_HUE_STEP, MAX_FRAME_HUE_STEP);
  LOG("\tframe_hue_step = %d", frame_hue_step);

  int num_frames = random(MIN_FRAMES, MAX_FRAMES);
  LOG("\tnum_frames = %d\t(~%dms)",
      num_frames, (num_frames * FRAME_DELAY_MS));

  for (int i = 0; i < num_frames; i++) {
    fill_rainbow(leds, num_leds, (start_hue + i * frame_hue_step) % 255, hue_step);
    FastLED.show();
    FastLED.delay(FRAME_DELAY_MS);
  }
}

#endif // RAINBOW_H
