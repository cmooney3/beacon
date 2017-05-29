#ifndef BLOCKIFY_H
#define BLOCKIFY_H

#include <FastLED.h>
#include "util.h"

namespace Blockify {

constexpr int kMaxBlocks = 30;
constexpr int kMinBlocks = 4;
constexpr int kNumFlashes = 10;
constexpr int kFrameDelayMS = 200;

void BlockifyAnimation(CRGB *leds, int num_leds) {
  LOG("Running Blockify...");
  LOG("\tnum_leds = %d", num_leds);
  
  uint8_t num_blocks = kMinBlocks + rand() % (kMaxBlocks - kMinBlocks);
  LOG("\tnum_blocks = %d", num_blocks);
  
  int block_size = num_leds / num_blocks;
  LOG("\tblock_size = %d  (num_leds / num_blocks)", block_size);
  
  CRGB c1, c2;
  fillRandomContrastingColors(c1, c2);
  
  for (uint16_t i = 0; i < kNumFlashes; i++) {
    for (uint16_t j = 0; j < num_leds; j++) {
      leds[j] = (int)(j / block_size + i) % 2 ? c1 : c2;
    }
    
    FastLED.show();
    FastLED.delay(kFrameDelayMS);
  }
}

};

#endif // BLOCKIFY_H
