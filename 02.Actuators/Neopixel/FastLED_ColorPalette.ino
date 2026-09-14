#include <FastLED.h>

#define NUM_LEDS 60
#define LED_PIN 3

CRGB leds[NUM_LEDS];
int paletteIndex = 0;

CRGBPalette16 myPalette = CRGBPalette16(
  CRGB(150, 30, 90),   // magenta
  CRGB(40, 60, 150),   // indigo blue
  CRGB(20, 100, 120),  // teal
  CRGB(160, 90, 30),   // brown

  CRGB(120, 40, 20),   // red
  CRGB(170, 120, 60),  // gold
  CRGB(50, 100, 60),   // green
  CRGB(100, 60, 130),  // plum

  CRGB(130, 50, 30),   // orange
  CRGB(60, 80, 150),   // steel blue
  CRGB(90, 120, 140),  // cyan-gray
  CRGB(160, 70, 50),   // copper

  CRGB(110, 50, 100),  // violet
  CRGB(70, 90, 130),   // blue
  CRGB(100, 80, 40),   // ochre
  CRGB(80, 40, 60)     // dark red
);

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
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
