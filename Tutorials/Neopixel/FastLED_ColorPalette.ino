#include <FastLED.h>

#define NUM_LEDS 60
#define LED_PIN 3

CRGB leds[NUM_LEDS];

int paletteIndex = 0;

CRGBPalette16 myPalette = CRGBPalette16(
  //
  CRGB(0, 0, 0),
  CRGB(50, 50, 100),
  CRGB(50, 50, 100),
  CRGB(0, 0, 0),
  //
  CRGB(0, 0, 0),
  CRGB(250, 250, 100),
  CRGB(250, 250, 100),
  CRGB(0, 0, 0),

  CRGB(0, 0, 0),
  CRGB(50, 50, 100),
  CRGB(50, 50, 100),
  CRGB(0, 0, 0),

  CRGB(0, 0, 10),
  CRGB(250, 250, 100),
  CRGB(50, 50, 100),
  CRGB(0, 0, 0));

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  // FastLED.setBrightness(50);
}

void loop() {

  //fill_palette (ledName, numberOfLeds, paletteStartingIndex, AmountToIncrementThePaletteIndexForEachLED, paletteDesign, Brightness, blendType)
  fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, myPalette, 100, LINEARBLEND);

  //change the start index of the palette to make animation
  EVERY_N_MILLISECONDS(10) {
    paletteIndex++;
  }

  FastLED.show();
}