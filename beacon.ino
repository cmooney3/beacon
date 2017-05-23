#include <FastLED.h>
#include <TimerOne.h>

#define DEBUG

#include "blockify.h"
#include "fill.h"

#define BRIGHTNESS_STEPS 5
#define MAX_BRIGHTNESS 255
#define BUTTON_PIN 5

#define UNUSED_ANALOG_INPUT 1
#define POWER_ON_DELAY_MS 1000

#define LED_PIN 7
#define NUM_LEDS (32 * 5)
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
  LOG("Serial configured.");
#endif

  // Read from an unused analog input to get a "random" seed for the rng
  LOG("Seeding random number generator...");
  int seed = analogRead(UNUSED_ANALOG_INPUT);
  LOG("Seed = %d", seed);
  randomSeed(seed);

  // Set up the brightness button as an input
  LOG("Configuring button's pin as an input w/ pullup resistor...");
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Set up timer to run the brightness button checks periodically
  LOG("Configuring Timer1 to poll the button state...");
  Timer1.initialize(100000);  // Period in Microseconds = 0.1 seconds
  Timer1.attachInterrupt(updateBrightness);
  

  // Initialize the LED strip
  LOG("Delaying briefly for LED power-on safety...");
  delay(POWER_ON_DELAY_MS);
  LOG("Initializing %d LEDs on pin %d...", NUM_LEDS, LED_PIN);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(brightnesses[brightness]);
}

void loop() {
  FillAnimation(leds, NUM_LEDS);
  BlockifyAnimation(leds, NUM_LEDS);
}
