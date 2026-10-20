# LDC screen (I2C)
An I2C LCD screen is a simple and convenient way to display text, numbers, sensor readings, and other information in Arduino projects.
Compared with a standard LCD screen, an I2C LCD requires only four wires to connect to an Arduino. This makes it especially useful when you want to save Arduino pins for other sensors, buttons, or actuators.
A common version is the 16×2 LCD, which can display 16 characters per row across 2 rows.

## I2C LCD Module Pinout

The I2C LCD module has four pins, and the wiring is shown in the image below.

<img width="794" height="300" alt="image" src="https://github.com/user-attachments/assets/ffa13674-9e27-4fc3-a6de-2fbf5d83a947" />

GND is the ground pin.
VCC is the power supply pin. (It is usually connected to 5V)
SDA is the I2C data pin.
SCL is the I2C clock pin.

On an Arduino Uno, the I2C pins are: SDA → A4, SCL → A5

## Installing the LCD Library

Before using the LCD, you need to install the LiquidCrystal I2C library.

In the Arduino IDE, go to: Sketch > Include Library > Manage Libraries...

Search for: LiquidCrystal I2C

and install the library.

## Arduino Example Code – Displaying Text

The example below initializes the LCD and displays two lines of text.

```C++
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD address: 0x27
// LCD size: 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // Initialize the LCD
  lcd.init();

  // Turn on the LCD backlight
  lcd.backlight();

  // Move the cursor to column 0, row 0
  lcd.setCursor(0, 0);
  lcd.print("Hello!");

  // Move the cursor to column 0, row 1
  lcd.setCursor(0, 1);
  lcd.print("IMA Arduino");
}

void loop()
{
}
```

<img width="794" height="595" alt="LiquidCrystal_I2C_img" src="https://github.com/user-attachments/assets/780c4956-97c3-4563-b580-2bb720944628" />


