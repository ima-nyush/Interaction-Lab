#include <LedControl.h>

// Connect the module's IN side: DIN -> D12, CLK -> D11, CS -> D10.
// The last argument is the number of modules, not the device address.
LedControl matrix(12, 11, 10, 1);

const byte smile[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

const byte heart[8] = {
  B00000000,
  B01100110,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};

void showPattern(const byte pattern[]) {
  for (int row = 0; row < 8; row++) {
    matrix.setRow(0, row, pattern[row]);
  }
}

void setup() {
  matrix.shutdown(0, false);  // Wake up the first module (address 0).
  matrix.setIntensity(0, 2); // Brightness: 0 (dim) through 15 (bright).
  matrix.clearDisplay(0);

  // Step 1: one pixel for one second.
  matrix.setLed(0, 0, 0, true);
  delay(1000);
  matrix.clearDisplay(0);

  // Step 2: visit all 64 pixels once to check the display and orientation.
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      matrix.setLed(0, row, col, true);
      delay(60);
      matrix.setLed(0, row, col, false);
    }
  }
}

void loop() {
  // Step 3: switch between two frames, once per second.
  showPattern(smile);
  delay(1000);
  showPattern(heart);
  delay(1000);
}
