#ifndef MORSE_H
#define MORSE_H

#include "PixelWrapper.h"
#include "util.h"

#define DOT_LENGTH_MS 125
#define DASH_LENGTH_MS (DOT_LENGTH_MS * 3)
#define PAUSE_LENGTH_MS DOT_LENGTH_MS
#define CHARACTER_SEPARATOR_LENGTH_MS (DOT_LENGTH_MS * 2)
#define WORD_SEPARATOR_LENGTH_MS (DASH_LENGTH_MS * 2)

uint8_t morse_lens[] = {2, 4, 4, 4, 1, 4, 3, 4, 2, 4, 3, 4, 2, 2, 3, 4, 4, 3, 3, 1, 3, 5, 3, 4, 4, 4};
uint8_t morse_codes[] = {0x01, 0x08, 0x0A, 0x04, 0x00, 0x02, 0x06, 0x00, 0x00, 0x07,
                         0x05, 0x04, 0x03, 0x02, 0x07, 0x06, 0x0D, 0x02, 0x00, 0x01,
                         0x01, 0x01, 0x03, 0x09, 0x0B, 0x0C};
                         
void MorseAnimation(PixelWrapper *px) {
  uint8_t msg[] = "FIND ME";
  uint8_t len = 7;
  
  uint32_t color = px->Color(0, 120, 0);
  
  
  for (uint8_t i = 0; i < len; i++) {
    if (msg[i] == ' ') {
      delay(WORD_SEPARATOR_LENGTH_MS);
      continue; 
    }
    uint8_t char_index = msg[i] - 'A';
    
    for (int bit_number = morse_lens[char_index] - 1; bit_number >= 0; bit_number--) {
      allOn(px, color);

      uint8_t is_dash = (morse_codes[char_index] & (0x01 << bit_number));
      delay(is_dash ? DASH_LENGTH_MS : DOT_LENGTH_MS);
      
      allOff(px);
      delay(PAUSE_LENGTH_MS);
    }
    
    // At the end of a character, so pause
    delay(CHARACTER_SEPARATOR_LENGTH_MS - PAUSE_LENGTH_MS);
  }
}

#endif // MORSE_H
