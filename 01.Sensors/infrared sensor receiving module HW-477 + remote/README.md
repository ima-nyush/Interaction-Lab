# infrared sensor receiving module HW-477 + remote

The HW-477 infrared receiver module can receive infrared signals from common IR remote controls.

It is useful for projects where you want to control an Arduino wirelessly using a remote, such as turning LEDs on and off, controlling motors, changing colors, or triggering different interactions.

When you press a button on the remote, the remote sends an encoded infrared signal. The HW-477 module receives this signal, and the Arduino can decode it to determine which button was pressed.

## HW-477 Module Pinout and Wiring

The HW-477 infrared receiver module typically has three pins:
<img width="955" height="564" alt="image" src="https://github.com/user-attachments/assets/95c1ffaa-4c91-41ac-846d-2e22688e717e" />

VCC is the power supply pin usually connected to 5V on Arduino.\
GND is the ground pin.\
S / OUT is the signal output pin that sends the received infrared signal to the Arduino. (For this example, we will connect the signal pin to digital pin 2 on the Arduino.)
<img width="1510" height="1188" alt="image" src="https://github.com/user-attachments/assets/7f4db1a8-1b1b-48d8-a29d-9db1eb384322" />

## Installing the IRremote Library

Before using the infrared receiver, install the IRremote library.\
In the Arduino IDE, go to: Sketch > Include Library > Manage Libraries...\
Search for: IRremote\
Install the library named IRremote by Armin Joachimsmeyer.

## Arduino Example Code

### Finding the Command for Each Button

Before using the remote to control something, we first need to find out which command value is sent by each button.

The following code reads the infrared signal and prints the command value to the Serial Monitor.

```C++
#include <IRremote.hpp>

// Pin connected to the signal output of the IR receiver
const int IR_RECEIVE_PIN = 2;

void setup()
{
  // Start Serial communication
  Serial.begin(9600);

  // Start the infrared receiver
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop()
{
  // Check if an infrared signal has been received
  if (IrReceiver.decode())
  {
    // Get the command value from the remote
    int command = IrReceiver.decodedIRData.command;

    // Print the command value to the Serial Monitor
    Serial.print("Command: 0x");
    Serial.println(command, HEX);

    // Prepare the receiver for the next signal
    IrReceiver.resume();
  }
}
```

After uploading the code, open the Serial Monitor and set the baud rate to 9600.\
Press different buttons on the remote. You should see values similar to:

```C++
Command: 0x45
Command: 0x46
Command: 0x47
```

Each button should produce a different command value.\
Write down the values for the buttons you want to use.\
The command values **may be different** depending on your remote.

### Controlling an LED with the Remote

Once you know the command values, you can use them to control other components.

In this example:\
0xC turns the LED ON\
0x18 turns the LED OFF

```C++
#include <IRremote.hpp>

// Pin connected to the signal output of the IR receiver
const int IR_RECEIVE_PIN = 2;

// Use the Arduino's built-in LED
const int LED_PIN = 8;

void setup()
{
  // Start Serial communication
  Serial.begin(9600);

  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Start the infrared receiver
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop()
{
  // Check if an infrared signal has been received
  if (IrReceiver.decode())
  {
    // Get the command value from the remote
    int command = IrReceiver.decodedIRData.command;

    // Print the command value to the Serial Monitor
    Serial.print("Command: 0x");
    Serial.println(command, HEX);

    // Turn the LED on
    if (command == 0xC)
    {
      digitalWrite(LED_PIN, HIGH);
    }

    // Turn the LED off
    if (command == 0x18)
    {
      digitalWrite(LED_PIN, LOW);
    }

    // Prepare the receiver for the next signal
    IrReceiver.resume();
  }
}
```
https://github.com/user-attachments/assets/f929c963-a9b0-4d8c-9b92-2fe74ffbb275
