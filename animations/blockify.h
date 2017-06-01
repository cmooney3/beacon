#ifndef BLOCKIFY_H
#define BLOCKIFY_H

#include <FastLED.h>
#include "util.h"

namespace Blockify {

constexpr int kMaxBlocks = 30;
constexpr int kMinBlocks = 4;
constexpr int kNumFlashes = 10;
constexpr int kFrameDelayMS = 200;

void BlockifyAnimation(CRGB *leds, int num_pole_leds, int num_ball_leds) {
  uint8_t num_blocks = kMinBlocks + rand() % (kMaxBlocks - kMinBlocks);
  int block_size = num_pole_leds / num_blocks;
  
  CRGB pole_c1, pole_c2;
  fillRandomContrastingColors(pole_c1, pole_c2);
  CRGB ball_c1, ball_c2;
  fillRandomContrastingColors(ball_c1, ball_c2);
  
  for (uint16_t i = 0; i < kNumFlashes; i++) {
    for (uint16_t j = 0; j < num_pole_leds; j++) {
      leds[j] = (int)(j / block_size + i) % 2 ? pole_c1 : pole_c2;
    }
    for (uint16_t j = 0; j < num_ball_leds; j++) {
      leds[num_pole_leds + 1 + j] = (i % 2) ? ball_c1 : ball_c2;
    }

    FastLED.show();
    FastLED.delay(kFrameDelayMS);
  }
}

};

#endif // BLOCKIFY_H
