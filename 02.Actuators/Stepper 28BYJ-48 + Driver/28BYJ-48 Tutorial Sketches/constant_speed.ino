// based on ConstantSpeed example by Mike McCauley (mikem@airspayce.com)
// Adapted for the 28BYJ-48 stepper motor + ULN2003 driver board
#include <AccelStepper.h>

// Driver board pins (IN1 -> D8, IN2 -> D9, IN3 -> D10, IN4 -> D11)
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;

// Define a stepper and the pins it will use
// AccelStepper::FULL4WIRE means a 4-wire stepper driven directly by 4 pins
// NOTE: the pin order is IN1, IN3, IN2, IN4
AccelStepper stepper(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4);

void setup() {
  // The run() function will accelerate up to
  // the speed set here
  stepper.setMaxSpeed(1000);
  // Set the desired constant speed for use with
  // runSpeed() in steps per second.
  // Negative value reverses direction
  stepper.setSpeed(200);
}

void loop() {
  stepper.runSpeed();
}
