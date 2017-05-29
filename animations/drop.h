#ifndef DROP_H
#define DROP_H

#include <FastLED.h>
#include "util.h"

namespace Drop {

constexpr int kMinSegmentSize = 15;
constexpr int kMaxSegmentSize = 30;

constexpr int kMinSpeed = 15;
constexpr int kMaxSpeed = 30;

constexpr int kMinFills = 2;
constexpr int kMaxFills = 4;

constexpr int kFrameDelayMS = 60;

void DropAux(CRGB *leds, int num_leds,
             int fill_level, CRGB c1, CRGB c2, int speed, int segment_size) {
  int distance = num_leds - fill_level;
  for (int pos = 0; pos <= distance; pos += speed) {
    for (int j = 0; j < fill_level; j++) {
      leds[j] = c1;
    }

    for (int j = 0; j < distance; j++) {
      leds[fill_level + j] = c2;
    }

    for (int j = 0; j < segment_size && j < pos ; j++) {
      leds[num_leds - pos + j] = c1;
    }

    FastLED.show();
    FastLED.delay(kFrameDelayMS);
  }
}

void Drop(CRGB *leds, int num_leds, CRGB c1, CRGB c2,
          int segment_size, int speed) {
  int fill_level = 0;
  while (fill_level < num_leds) {
    DropAux(leds, num_leds, fill_level, c1, c2, speed, segment_size);
    fill_level += segment_size;
  }
}

void DropAnimation(CRGB *leds, int num_leds) {
  LOG("Running Drop...");
  CRGB c1, c2;
  fillRandomContrastingColors(c1, c2);

  int segment_size = random(kMinSegmentSize, kMaxSegmentSize);
  LOG("\tsegment_size = %d", segment_size);

  int speed = random(kMinSpeed, kMaxSpeed);
  LOG("\tspeed = %d", speed);

  int num_fills = random(kMinFills, kMaxFills);
  LOG("\tnum_fills = %d", num_fills);

  for (int i = 0; i < num_fills; i++) {
    Drop(leds, num_leds, c1, c2, segment_size, speed);
    Drop(leds, num_leds, c2, c1, segment_size, speed);
  }
}

};

#endif // DROP_H
