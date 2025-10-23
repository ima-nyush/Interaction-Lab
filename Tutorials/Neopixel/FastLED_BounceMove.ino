#include <FastLED.h>

#define NUM_LEDS  60
#define LED_PIN   3

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

void loop() {

  uint16_t sinBeat = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);

  leds[sinBeat] = CRGB(0,0,255);
  
  fadeToBlackBy(leds, NUM_LEDS, 10);

  EVERY_N_MILLISECONDS(10){
  }

  FastLED.show();
}
