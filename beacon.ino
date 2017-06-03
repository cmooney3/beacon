#include <FastLED.h>
#include <TimerOne.h>

#define DEBUG

#include "animations/blockify.h"
#include "animations/drop.h"
#include "animations/fill.h"
#include "animations/pulse.h"
#include "animations/rainbow.h"
#include "animations/static.h"
#include "animations/stripes.h"
#include "animations/tracer.h"

#define BRIGHTNESS_STEPS 5
#define MAX_BRIGHTNESS 255
#define BUTTON_PIN 5

#define UNUSED_ANALOG_INPUT 1
#define POWER_ON_DELAY_MS 1000

#define LED_PIN 7
#define NUM_POLE_LEDS (30 * 5)
#define NUM_BALL_LEDS (8 * 3)
#define NUM_LEDS (NUM_POLE_LEDS + NUM_BALL_LEDS)
#define CHIPSET     WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

// These global values keep track of the "brightness" setting controlled by the
// onboard button.
int brightnesses[] = {7, 20, 35, 60, 80, 120, 255};
int num_brightnesses = sizeof(brightnesses) / sizeof(brightnesses[0]);
int brightness = num_brightnesses / 2;
int last_button_position = false;

// This function will be called periodically to update the button state and
// brightness levels.
void updateBrightness() {
  bool button_down = (bool)digitalRead(BUTTON_PIN);
  if (!button_down && last_button_position) {
    brightness = (brightness + 1) % num_brightnesses;
    FastLED.setBrightness(brightnesses[brightness]);
  }
  last_button_position = button_down;
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif

  // Read from an unused analog input to get a "random" seed for the rng
  randomSeed(analogRead(UNUSED_ANALOG_INPUT));

  // Set up the brightness button as an input
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Set up timer to run the brightness button checks periodically
  Timer1.initialize(100000);  // Period in Microseconds = 0.1 seconds
  Timer1.attachInterrupt(updateBrightness);
  
  // Initialize the LED strip
  delay(POWER_ON_DELAY_MS);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(brightnesses[brightness]);
}

typedef void (*Animation)(CRGB*, int, int);
Animation animations[] = {
  &Drop::DropAnimation,
  &Blockify::BlockifyAnimation,
  &Rainbow::RainbowAnimation,
  &Fill::FillAnimation,
  &Static::StaticAnimation,
  &Fill::CenterFillAnimation,
  &Pulse::PulseAnimation,
  &Tracer::TracerAnimation,
  //&Stripes::StripesAnimation,
};
int num_animations = sizeof(animations) / sizeof(animations[0]);

void loop() {
  for (int i = 0; i < num_animations; i++) {
    (*animations[i])(leds, NUM_POLE_LEDS, NUM_BALL_LEDS);
  }
}
