# Unipolar Stepper Motor – 28BYJ-48 + Driver Board



A stepper motor is a motor that moves in small, precise increments called **steps**.

Unlike a regular DC motor, which spins continuously when powered, a stepper motor can be controlled to rotate a specific number of steps in either direction. This makes it useful for projects that require controlled movement, such as rotating displays, small robots, camera mechanisms, and interactive installations.

In this tutorial, we will use a common **28BYJ-48 unipolar stepper motor** together with a **stepper motor driver board**.

The driver board is necessary because the Arduino cannot safely provide enough current to drive the stepper motor coils directly.

## 28BYJ-48 Stepper Motor and Driver Board

The 28BYJ-48 is a **5-wire unipolar stepper motor**.
<img width="922" height="702" alt="image" src="https://github.com/user-attachments/assets/e1e8eb6c-aafc-473a-9d92-3739f96aabcd" />


Instead of connecting the motor directly to the Arduino, the motor plugs into the connector on the driver board.

The driver board usually has four control inputs:

- **IN1**
- **IN2**
- **IN3**
- **IN4**

These inputs control the motor coils.

The board also has:

- **VCC** for power
- **GND** for ground

Some driver boards also include indicator LEDs that show which motor coils are currently being activated.

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

## Arduino Example Code

Arduino includes a built-in library called `Stepper`, so you do not need to install an additional library.

In this example, the motor rotates approximately one full revolution in one direction, waits for one second, and then rotates back in the opposite direction.

```C++
#include <Stepper.h>

// Approximate number of steps for one output-shaft revolution
const int STEPS_PER_REVOLUTION = 2048;

// Create the stepper motor object
//
// The pin order used here is:
// IN1, IN3, IN2, IN4
Stepper myStepper(
  STEPS_PER_REVOLUTION,
  8,
  10,
  9,
  11
);

void setup()
{
  // Set the motor speed in RPM
  myStepper.setSpeed(10);

  // Start Serial communication
  Serial.begin(9600);
}

void loop()
{
  // Rotate approximately one revolution clockwise
  Serial.println("Clockwise");
  myStepper.step(STEPS_PER_REVOLUTION);

  delay(1000);

  // Rotate approximately one revolution counterclockwise
  Serial.println("Counterclockwise");
  myStepper.step(-STEPS_PER_REVOLUTION);

  delay(1000);
}
