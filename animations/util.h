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

#endif // UTIL_H
