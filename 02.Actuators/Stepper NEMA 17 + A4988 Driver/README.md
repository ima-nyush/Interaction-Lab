# Stepper motor tutorial (With stepper driver module A4988)

In this tutorial, we will use a **NEMA 17 stepper motor** with an **A4988 driver module**.

The motor should be powered using an **12V external power supply**.

<img width="1136" height="524" alt="image" src="https://github.com/user-attachments/assets/042dcd2e-75c4-4b89-bbdb-8a70c13e01f2" />


## A4988 Stepper Driver Module

The A4988 driver module connects the Arduino to the stepper motor.

These are the key pins that control the behavior of the stepper motor:
- **STEP** – each pulse moves the motor one step
- **DIR** – determines the rotation direction
- **EN** – enables or disables the motor driver

## Wiring the Stepper Motor to an Arduino

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

> Avoid connecting or disconnecting the stepper motor while the driver is powered.

## Library & Arduino Example Codes

Install the **“AccelStepper”** library by Mike McCauley inside the Arduino IDE (via “Tools” > “Manage Libraries…”).

[**Arduino Example Codes**](https://github.com/ima-nyush/Interaction-Lab/tree/03ae6ac81cc2111a9086ece07198315e5930f280/02.Actuators/Stepper%20NEMA%2017%20%2B%20A4988%20Driver/Tutorial%20Sketches)

IxLab examples codes for stepper motors based on by Mike McCauley's AccelStepper library



- Constant speed example: Shows how to run AccelStepper in the simplest, fixed speed mode with no accelerations.
- Run to position example: Shows how to use runToNewPosition which sets a new target position and then waits until the stepper has achieved it.
- Bounce example: Make a single stepper bounce from one limit to another.
- Knob stepper example: Make a single stepper follow the analog value read from a pot or whatever. The stepper will move at a constant speed to each newly set posiiton, depending on the value of the pot.
- Multi stepper example: Shows how to use multiple simultaneous steppers.
- Random example: Make a single stepper perform random changes in speed, position and acceleration.
  
Additional documenttion: https://www.airspayce.com/mikem/arduino/AccelStepper/index.html


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
