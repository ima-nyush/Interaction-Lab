# Unipolar Stepper Motor – 28BYJ-48 + Driver 

In this tutorial, we will use a common **28BYJ-48 unipolar stepper motor** paired with its corresponding **motor driver**.

## 28BYJ-48 Stepper Motor and Driver Board

The 28BYJ-48 is a **5-wire unipolar stepper motor**.
<img width="922" height="702" alt="image" src="https://github.com/user-attachments/assets/e1e8eb6c-aafc-473a-9d92-3739f96aabcd" />


## Wiring the Stepper Motor to an Arduino

Connect the 28BYJ-48 motor to the driver board using its motor connector.

Then connect the driver board to the Arduino as follows:

| Driver Board | Arduino Uno |
| --- | --- |
| IN1 | D8 |
| IN2 | D9 |
| IN3 | D10 |
| IN4 | D11 |
| VCC | 5V |
| GND | GND |

The wiring is shown in the image below.

<img width="1212" height="1422" alt="image" src="https://github.com/user-attachments/assets/a97fa9a7-f16b-4858-9605-b2f2fadf2e88" />

For a simple demonstration, the motor can be powered from the Arduino's 5V pin.

For projects where the motor is under load or running frequently, it is better to use a separate **5V power supply** for the motor.

If you use an external power supply, make sure its **GND is connected to the Arduino GND**.


## Library & Arduino Example Codes

Install the **“AccelStepper”** library by Mike McCauley inside the Arduino IDE (via “Tools” > “Manage Libraries…”).

[**28BYJ-48 Stepper Example Codes**](https://github.com/ima-nyush/Interaction-Lab/tree/25ed0ac0f5635a3fc33109607a194aa7c0b5f8c2/02.Actuators/Stepper%2028BYJ-48%20%2B%20Driver/28BYJ-48%20Tutorial%20Sketches)

IxLab examples codes for stepper motors based on by Mike McCauley's AccelStepper library

- Constant speed example: Shows how to run AccelStepper in the simplest, fixed speed mode with no accelerations.
- Run to position example: Shows how to use runToNewPosition which sets a new target position and then waits until the stepper has achieved it.
- Bounce example: Make a single stepper bounce from one limit to another.
- Knob stepper example: Make a single stepper follow the analog value read from a pot or whatever. The stepper will move at a constant speed to each newly set posiiton, depending on the value of the pot.
- Multi stepper example: Shows how to use multiple simultaneous steppers.
- Random example: Make a single stepper perform random changes in speed, position and acceleration.
  
Additional documenttion: https://www.airspayce.com/mikem/arduino/AccelStepper/index.html
