# Stepper motor tutorial (With stepper driver module A4988)

In this tutorial, we will use a **bipolar stepper motor** with an **A4988 stepper motor driver module**.

The A4988 driver makes controlling the motor relatively simple. Instead of controlling each motor coil directly, the Arduino only needs to send two main signals:

- **STEP** – moves the motor one step
- **DIR** – controls the direction of rotation

The motor should be powered using an **12V external power supply**, rather than directly from the Arduino.

<img width="1136" height="524" alt="image" src="https://github.com/user-attachments/assets/042dcd2e-75c4-4b89-bbdb-8a70c13e01f2" />


## A4988 Stepper Driver Module

The A4988 driver module connects the Arduino to the stepper motor.

The most important connections are:

- **STEP** – each pulse moves the motor one step
- **DIR** – determines the rotation direction
- **EN** – enables or disables the motor driver
- **5V** – logic power from the Arduino
- **GND** – ground
- **VIN** – external motor power supply
- **1A, 1B, 2A, 2B** – connections to the two motor coils

The stepper motor is connected directly to the motor output connector on the driver module.

## Wiring the Stepper Motor to an Arduino

In this example, connect the driver module to the Arduino as follows:

| A4988 Driver | Arduino Uno |
| --- | --- |
| DIR | D2 |
| STEP | D3 |
| EN | D4 |
| 5V | 5V |
| GND | GND |

The motor power supply connects separately to:

| Driver | External Power Supply |
| --- | --- |
| VIN | +12V |
| GND | GND |

The wiring is shown in the image below.

<img width="920" height="1272" alt="image" src="https://github.com/user-attachments/assets/fd730aeb-8d0a-4059-8f66-57c466d29969" />

> **Important:** Do not power the stepper motor directly from the Arduino 5V pin. Use an external power supply suitable for your motor.

> Avoid connecting or disconnecting the stepper motor while the driver is powered.

## Arduino Example Code

Install the **“AccelStepper”** library inside the Arduino IDE (via “Tools” > “Manage Libraries…”).

The example below is based on the **ConstantSpeed** example. This code will run the stepper motor at a constant speed.

```C++
#include <AccelStepper.h>

int DIR_PIN = 2;
int STEP_PIN = 3;
int EN_PIN = 4;

// Define a stepper motor using a driver
// AccelStepper::DRIVER means the driver uses
// STEP and DIR pins
AccelStepper stepper(
  AccelStepper::DRIVER,
  STEP_PIN,
  DIR_PIN
);

void setup()
{
  // Enable the stepper driver
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);

  // Set the maximum allowed speed
  stepper.setMaxSpeed(1000);

  // Set the constant running speed
  stepper.setSpeed(500);
}

void loop()
{
  // Keep the motor rotating at a constant speed
  stepper.runSpeed();
}

```
https://github.com/user-attachments/assets/04c3a805-a668-4761-b02a-6395c7d96e00

## Basic AccelStepper Functions

`setMaxSpeed(speed)` – Sets the maximum speed of the motor in steps per second.

`setSpeed(speed)` – Sets the constant running speed in steps per second; a negative value reverses the direction.

`setAcceleration(acceleration)` – Sets how quickly the motor speeds up or slows down.

`moveTo(position)` – Sets a target absolute position for the motor.

`move(distance)` – Moves the motor a certain number of steps relative to its current position.

`run()` – Moves the motor toward the target position while applying acceleration and deceleration.

`runSpeed()` – Runs the motor continuously at the speed set by `setSpeed()`.

`runToPosition()` – Runs the motor until it reaches the target position.

`stop()` – Tells the motor to decelerate and stop.

`currentPosition()` – Returns the motor's current position in steps.

`setCurrentPosition(position)` – Manually sets the motor's current position.

`distanceToGo()` – Returns the number of steps remaining before reaching the target position.
