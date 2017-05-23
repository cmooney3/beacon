#ifndef PULSE_H
#define PULSE_H

#include "PixelWrapper.h"
#include "util.h"

#define NUM_PULSES 3
#define NUM_GRADIENT_STEPS 20

#define NUM_STROBES 30

void SinglePulse(PixelWrapper *px, uint32_t c1, uint32_t c2,
                 uint8_t interframe_delay_ms) {
  uint16_t n = px->numPixels();
  uint8_t i, j,
          r1, g1, b1,
          r2, g2, b2,
          r_mixed, g_mixed, b_mixed;
  uint32_t tmp_c;
  unpackColor(c1, &r1, &g1, &b1);
  unpackColor(c2, &r2, &g2, &b2);
  
  for (i = 0; i <= NUM_GRADIENT_STEPS * 2; i++) {
    uint8_t perc = (i >= NUM_GRADIENT_STEPS) ? NUM_GRADIENT_STEPS * 2 - i : i;
    float alpha = (float)perc / (float)NUM_GRADIENT_STEPS;
    
    
    blendColors(r1, g1, b1, r2, g2, b2,
                &r_mixed, &g_mixed, &b_mixed, alpha);
    tmp_c = px->Color(r_mixed, g_mixed, b_mixed);
    
    for (j = 0; j < n; j++)
      px->setPixelColor(j, tmp_c);
    px->show();
    delay(interframe_delay_ms);
  }
}

void PulseAnimation_Aux(PixelWrapper *px, uint32_t c1, uint32_t c2,
                        uint8_t interpulse_delay_ms, uint8_t interframe_delay_ms) {
   for (uint8_t i = 0; i < NUM_PULSES; i++) {
    SinglePulse(px, c1, c2, interframe_delay_ms);
    delay(interpulse_delay_ms);
    SinglePulse(px, c1, c2, interframe_delay_ms);
    delay(interpulse_delay_ms);
  }
}

void PulseAnimation(PixelWrapper *px) {
  PulseAnimation_Aux(px, randomColor(px), randomColor(px),
                     random(50, 150), random(3, 15));
}

void StrobeAnimation(PixelWrapper *px) {
 uint32_t c1 = randomColor(px), c2 = randomColor(px);
 
 for (uint8_t i = 0; i < NUM_STROBES; i++) {
   SinglePulse(px, c1, c2, 2);
   delay(1);  
 } 
}

#endif //PULSE_H
