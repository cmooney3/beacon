#ifndef UTIL_H
#define UTIL_H

#ifdef DEBUG
  char buf[128];
  #define LOG(...) {sprintf(buf, __VA_ARGS__); Serial.println(buf);}
#else
  #define LOG(...) {}
#endif

#define SATURATION 255
#define VALUE 255

CRGB randomColor() {
  return CHSV(random(255), SATURATION, VALUE);
}

void fillRandomContrastingColors(CRGB &c1, CRGB &c2) {
  int h1 = random(255);
  int offset = random(180) - 90;
  int h2 = (h1 + 128 + offset) % 255;
  
  LOG("\tRandomContrastingColors generated\th1: %d\th2: %d", h1, h2);
  c1 = CHSV(h1, SATURATION, VALUE);
  c2 = CHSV(h2, SATURATION, VALUE);
}

#define LEDS_PER_STICK 8
void setBallTopBottomColors(CRGB *leds, int num_leds, CRGB top, CRGB bottom) {
  for (int j = 0; j < LEDS_PER_STICK; j++) {
    leds[j] = (j < LEDS_PER_STICK / 2) ? bottom : top; 
  }
  for (int j = LEDS_PER_STICK; j < LEDS_PER_STICK * 2; j++) {
    leds[j] = (j < LEDS_PER_STICK * 3 / 2) ? top : bottom; 
  }
  for (int j = LEDS_PER_STICK * 2; j < LEDS_PER_STICK * 3; j++) {
    leds[j] = (j < LEDS_PER_STICK * 5 / 2) ? bottom : top; 
  }
}

void setBallColor(CRGB *leds, int num_leds, CRGB c) {
  for (int j = 0; j < num_leds; j++) {
    leds[j] = c;
  }
}

void setBallSidesColor(CRGB *leds, int num_leds, CRGB c1, CRGB c2, CRGB c3) {
  for (int j = 0; j < LEDS_PER_STICK; j++) {
    leds[j] = c1;
  }
  for (int j = LEDS_PER_STICK; j < LEDS_PER_STICK * 2; j++) {
    leds[j] = c2;
  }
  for (int j = LEDS_PER_STICK * 2; j < LEDS_PER_STICK * 3; j++) {
    leds[j] = c3;
  }
}

#endif // UTIL_H
