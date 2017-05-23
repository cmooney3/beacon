#ifndef BLOCKIFY_H
#define BLOCKIFY_H

#include <FastLED.h>
#include "util.h"

#define MAX_BLOCKS 30
#define MIN_BLOCKS 4
#define NUM_FLASHES 10
#define FRAME_DELAY_MS 200

void BlockifyAnimation(CRGB *leds, int num_leds) {
  LOG("Running Blockify...");
  LOG("\tnum_leds = %d", num_leds);
  
  uint8_t num_blocks = MIN_BLOCKS + rand() % (MAX_BLOCKS - MIN_BLOCKS);
  LOG("\tnum_blocks = %d", num_blocks);
  
  int block_size = num_leds / num_blocks;
  LOG("\tblock_size = %d  (num_leds / num_blocks)", block_size);
  
  CRGB c1, c2;
  fillRandomContrastingColors(c1, c2);
  
  for (uint16_t i = 0; i < NUM_FLASHES; i++) {
    for (uint16_t j = 0; j < num_leds; j++) {
      leds[j] = (int)(j / block_size + i) % 2 ? c1 : c2;
    }
    
    FastLED.show();
    FastLED.delay(FRAME_DELAY_MS);
  }
}

#endif // BLOCKIFY_H
