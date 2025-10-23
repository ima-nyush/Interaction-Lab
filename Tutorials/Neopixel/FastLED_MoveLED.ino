#include <FastLED.h>

#define NUM_LEDS  60
#define LED_PIN   3

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
}

void loop() {

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,0,0);
    FastLED.show();
    delay(100);
    leds[i] = CRGB(0,0,0);
  }

  for(int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = CRGB(255,0,0);
    FastLED.show();
    delay(100);
    leds[i] = CRGB(0,0,0);
  }
}
