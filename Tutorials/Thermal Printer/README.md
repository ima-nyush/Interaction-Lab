# Thermal Printer
Thermal printers use heat in order to print onto a specialized paper. This is commonly seen in the form of a receipt printer.

## Hardware

The printer we have on hand is a EM5822. It can use either TTL or RS232 to communicate instructions to it and takes ESC/POC commands for formatting.

*image here*

### Specifications
| | |
| - | - |
| Operating Voltage | 5-9V |
| Pinout | VCC CTS TX RX GND |
## Setup
While the printer can operate as low as 5V, it will have a fairly spotty print. For better results it should be operated at a higher voltage. This can be done by hooking up the power line to an external power source.

*image here of power source connection*

TTL requires a lower voltage (3.3V-5V) which makes it pair nicely with microcontrollers like the arduino uno in your kits. RS232 is generally more versatile, being less susceptible to noise, interference, and degradation, but requires a higher voltage of around 13V.

*image of TTL/arduino connection*

## Code
To ensure we don't print any unwanted serial communication, we use **SoftwareSerial** to control the printer instead of hardware serial. This allows us to use digital pins as RX/TX pins. As stated before, the printer takes [ESC/POC Commands](https://escpos.readthedocs.io/en/latest/font_cmds.html), allowing you to change text style and other print options.

Below is an simple example that prints "Hello World!" once in **bold**.

```C++
#include <SoftwareSerial.h>

SoftwareSerial ser(10, 11); //RX,TX pins

void setup() {
  ser.begin(9600); //begin software serial
  ser.print("\x1B\x21\x08"); //format text to be bold
  ser.println("Hello World!");
  ser.println();
}

void loop() {
}

```
